#include <iostream>
#include <fstream>
#include "tsCommon.h"
#include "tsTransportStream.h"

using namespace std;

ofstream ofs_audio("parsed_audio.mp2", ofstream::binary);


void save(string data, uint32_t data_len){
    for(size_t i = data.size() - data_len; i < data_len; i+=8){
        string sub = data.substr(i, 8);
        bitset<8> bit(sub);
        char c = static_cast<char>(bit.to_ulong());
        ofs_audio << c;
    }
}


int main( int argc, char *argv[ ], char *envp[ ]) {
    FILE *file = fopen("example_new.ts", "rb");
    if (file == nullptr) {
        printf("wrong file name\n");
        return EXIT_FAILURE;
    }

    char * buffer;
    buffer = (char *) malloc(sizeof(char) * xTS::TS_PacketLength);

    xTS_PacketHeader TS_PacketHeader;
    xTS_AdaptationField TS_AdaptationField;
    xPES_Assembler PES_Assembler;

    PES_Assembler.Init(136);

    int32_t TS_PacketId = 0;

    bitset<8> ts_buffor[188];

    while (!feof(file)) {
        fread(buffer, xTS::TS_PacketLength, 1, file);
        for (int i = 0; i < xTS::TS_PacketLength; i++) {
            ts_buffor[i] = bitset<8>(buffer[i]);
        }

        TS_PacketHeader.Reset();
        TS_PacketHeader.Parse(ts_buffor);


        if (TS_PacketHeader.getSyncByte().to_string() == "01000111" and TS_PacketHeader.getPacketIdentifier().to_ulong() == 136) {
            printf("%010d TS:", TS_PacketId);
            TS_PacketHeader.Print();
            TS_AdaptationField.Reset();

            if (TS_PacketHeader.hasAdaptationField()) {
                TS_AdaptationField.Parse(ts_buffor, TS_PacketHeader.getAdaptationFieldControl());
                TS_AdaptationField.Print();
            }
        }

        xPES_Assembler::eResult Result = PES_Assembler.AbsorbPacket(ts_buffor, &TS_PacketHeader, &TS_AdaptationField);
        switch (Result) {
            case xPES_Assembler::eResult::StreamPackedLost  :
                printf(" PES: PcktLost\n");
                break;
            case xPES_Assembler::eResult::AssemblingStarted :
                printf(" PES: Started assembling\n");
                break;
            case xPES_Assembler::eResult::AssemblingContinue:
                printf(" PES: Continue\n");
                break;
            case xPES_Assembler::eResult::AssemblingFinished:
                printf(" PES: Finished");
                save(PES_Assembler.getPacket(), PES_Assembler.getNumPacketBytes());
                PES_Assembler.PrintPESH();
                printf("\n");
                break;
            default:
                break;
        }

        TS_PacketId++;
//        if(TS_PacketId == 200) break;
    }

    free(buffer);
    fclose(file);
    return 0;
}