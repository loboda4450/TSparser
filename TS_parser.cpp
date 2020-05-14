#include <iostream>
#include "tsCommon.h"
#include "tsTransportStream.h"

using namespace std;


int main( int argc, char *argv[ ], char *envp[ ]) {
    FILE * file =  fopen(R"(/home/loobson/Politechnika/TSparser/example_new.ts)", "rb");
    if(file == nullptr) { printf("wrong file name\n"); return EXIT_FAILURE;}

    char * buffer;
    buffer = (char*) malloc (sizeof(char)*188);

    xTS_PacketHeader TS_PacketHeader;
    xTS_AdaptationField TS_AdaptationField;

    int32_t TS_PacketId = 0;
    bitset<8> ts_buffor[188];
    while (!feof(file)) {
        fread(buffer, 188, 1, file);
        for(int i = 0; i < 188; i++){
            ts_buffor[i] = bitset<8> (buffer[i]);
        }

        TS_PacketHeader.Reset();
        TS_PacketHeader.Parse(ts_buffor);
        TS_AdaptationField.Parse(ts_buffor, TS_PacketHeader.getAdaptationFieldControl());
        printf("%010d TS:", TS_PacketId);
        TS_PacketHeader.Print();

        TS_AdaptationField.Reset();
        if(TS_PacketHeader.hasAdaptationField()) {
            TS_AdaptationField.Parse(ts_buffor, TS_PacketHeader.getAdaptationFieldControl());
            TS_AdaptationField.Print();
        }

        TS_PacketId++;
        if(TS_PacketId > 189){
            break;
        }
    }

    free (buffer);
    fclose(file);
    return 0;
}