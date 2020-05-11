#pragma once
#include "tsCommon.h"
#include <string>
#include <bitset>

using namespace std;

/*
MPEG-TS packet:
`        3                   2                   1                   0  `
`      1 0 9 8 7 6 5 4 3 2 1 0 9 8 7 6 5 4 3 2 1 0 9 8 7 6 5 4 3 2 1 0  `
`     +-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+ `
`   0 |                             Header                            | `
`     +-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+ `
`   4 |                  Adaptation field + Payload                   | `
`     |                                                               | `
` 184 |                                                               | `
`     +-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+ `


MPEG-TS packet header:
`        3                   2                   1                   0  `
`      1 0 9 8 7 6 5 4 3 2 1 0 9 8 7 6 5 4 3 2 1 0 9 8 7 6 5 4 3 2 1 0  `
`     +-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+ `
`   0 |       SB      |E|S|T|           PID           |TSC|AFC|   CC  | `
`     +-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+ `

Sync byte                    (SB ) :  8 bits
Transport error indicator    (E  ) :  1 bit
Payload unit start indicator (S  ) :  1 bit
Transport priority           (T  ) :  1 bit
Packet Identifier            (PID) : 13 bits
Transport scrambling control (TSC) :  2 bits
Adaptation field control     (AFC) :  2 bits
Continuity counter           (CC ) :  4 bits
*/


//=============================================================================================================================================================================

class xTS
{
public:
  static constexpr uint32_t TS_PacketLength = 188;
  static constexpr uint32_t TS_HeaderLength = 4;

  static constexpr uint32_t PES_HeaderLength = 6;

  static constexpr uint32_t BaseClockFrequency_Hz         =    90000; //Hz
  static constexpr uint32_t ExtendedClockFrequency_Hz     = 27000000; //Hz
  static constexpr uint32_t BaseClockFrequency_kHz        =       90; //kHz
  static constexpr uint32_t ExtendedClockFrequency_kHz    =    27000; //kHz
  static constexpr uint32_t BaseToExtendedClockMultiplier =      300;
};

//=============================================================================================================================================================================

class xTS_PacketHeader {
public:
    enum class ePID : uint16_t {
        PAT = 0x0000,
        CAT = 0x0001,
        TSDT = 0x0002,
        IPMT = 0x0003,
        NIT = 0x0010, //DVB specific PID
        SDT = 0x0011, //DVB specific PID
        NuLL = 0x1FFF,
    };

protected:
    bitset<8> syncByte;
    bitset<1> transportErrorIndicator;
    bitset<1> payloadUnitStartIndicator;
    bitset<1> transportPriority;
    bitset<13> packetIdentifier;
    bitset<2> transportScramblingControl;
    bitset<2> adaptationFieldControl;
    bitset<4> continuityCounter;

public:
    void setSyncByte(const bitset<8> &syncByte);

    void setTransportErrorIndicator(const bitset<1> &transportErrorIndicator);

    void setPayloadUnitStartIndicator(const bitset<1> &payloadUnitStartIndicator);

    void setTransportPriority(const bitset<1> &transportPriority);

    void setPacketIdentifier(const bitset<13> &packetIdentifier);

    void setTransportScramblingControl(const bitset<2> &value);

    void setAdaptationFieldControl(const bitset<2> &adaptationFieldControl);

    void setContinuityCounter(const bitset<4> &continuityCounter);

    const bitset<8> &getSyncByte() const;

    const bitset<1> &getTransportErrorIndicator() const;

    const bitset<1> &getPayloadUnitStartIndicator() const;

    const bitset<1> &getTransportPriority() const;

    const bitset<13> &getPacketIdentifier() const;

    const bitset<2> &getTransportScramblingControl() const;

    const bitset<2> &getAdaptationFieldControl() const;

    const bitset<4> &getContinuityCounter() const;

    void Reset();

    int32_t Parse(bitset<8> *Input);

    void Print() const;

public:
      bool     hasAdaptationField() const;
      bool     hasPayload        () const;
};



class xTS_AdaptationField {
protected:
    bitset<8> AdaptationFieldLength;
    bitset<1> DiscontinuityIndicator;
    bitset<1> RandomAccessIndicator;
    bitset<1> ElementaryStreamPriorityIndicator;
    bitset<1> ProgramClockReferenceFlag;
    bitset<1> OriginalProgramClockReferenceFlag;
    bitset<1> SplicingPointFlag;
    bitset<1> TransportPrivateDataFlag;
    bitset<1> AdaptationFieldExtensionFlag;

public:
    void setAdaptationFieldLength(const bitset<8> &adaptationFieldLength);


    void setDiscontinuityIndicator(const bitset<1> &discontinuityIndicator);


    void setRandomAccessIndicator(const bitset<1> &randomAccessIndicator);


    void setElementaryStreamPriorityIndicator(const bitset<1> &elementaryStreamPriorityIndicator);


    void setProgramClockReferenceFlag(const bitset<1> &programClockReferenceFlag);


    void setOriginalProgramClockReferenceFlag(const bitset<1> &originalProgramClockReferenceFlag);


    void setSplicingPointFlag(const bitset<1> &splicingPointFlag);


    void setTransportPrivateDataFlag(const bitset<1> &transportPrivateDataFlag);


    void setAdaptationFieldExtensionFlag(const bitset<1> &adaptationFieldExtensionFlag);

    const bitset<8> &getAdaptationFieldLength() const;

    const bitset<1> &getDiscontinuityIndicator() const;

    const bitset<1> &getRandomAccessIndicator() const;

    const bitset<1> &getElementaryStreamPriorityIndicator() const;

    const bitset<1> &getProgramClockReferenceFlag() const;

    const bitset<1> &getOriginalProgramClockReferenceFlag() const;

    const bitset<1> &getSplicingPointFlag() const;

    const bitset<1> &getTransportPrivateDataFlag() const;

    const bitset<1> &getAdaptationFieldExtensionFlag() const;

    void Reset();

    void Print() const;

    uint32_t getNumBytes() const {}

    int32_t Parse(bitset<8> *Input, bitset<2> AdaptationFieldControl);
};

//=============================================================================================================================================================================
