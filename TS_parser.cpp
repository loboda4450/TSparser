#include <iostream>
#include "tsCommon.h"
#include "tsTransportStream.h"

using namespace std;


int main( int argc, char *argv[ ], char *envp[ ]) {
    FILE * file =  fopen(R"(/home/loobson/Politechnika/TSparser/example_new.ts)", "rb");
    char * buffer;
    buffer = (char*) malloc (sizeof(char)*188);

    xTS_PacketHeader TS_PacketHeader;

    int32_t TS_PacketId = 0;
    bitset<8> ts_buffor[188];
    while (!feof(file)) {
        fread(buffer, 188, 1, file);
        for(int i = 0; i < 188; i++){
            ts_buffor[i] = bitset<8> (buffer[i]);
        }

//        for(auto & i : af_buffor){
//            for(int j = 0; j < 8; j++){
//                cout << i[j];
//            }
//        }
//        cout << endl;

        TS_PacketHeader.Reset();
        TS_PacketHeader.Parse(ts_buffor);

        printf("%010d TS:", TS_PacketId);
        TS_PacketHeader.Print();

        TS_PacketId++;
        if(TS_PacketId > 40){
            break;
        }
    }
    free (buffer);
    fclose(file);
    return 0;
}
