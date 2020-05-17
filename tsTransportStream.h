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
protected:
    bitset<8>  syncByte;
    bitset<1>  transportErrorIndicator;
    bitset<1>  payloadUnitStartIndicator;
    bitset<1>  transportPriority;
    bitset<13> packetIdentifier;
    bitset<2>  transportScramblingControl;
    bitset<2>  adaptationFieldControl;
    bitset<4>  continuityCounter;

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
    bool hasAdaptationField() const;
    bool hasPayload() const;
};


class xTS_AdaptationField {
protected:
    bitset<8>  AdaptationFieldLength;
    bitset<1>  DiscontinuityIndicator;
    bitset<1>  RandomAccessIndicator;
    bitset<1>  ElementaryStreamPriorityIndicator;
    bitset<1>  ProgramClockReferenceFlag;
    bitset<1>  OriginalProgramClockReferenceFlag;
    bitset<1>  SplicingPointFlag;
    bitset<1>  TransportPrivateDataFlag;
    bitset<1>  AdaptationFieldExtensionFlag;
    bitset<33> ProgramClockReferenceBase;
    bitset<6>  PCRReserved;
    bitset<9>  ProgramClockReferenceExtension;
    bitset<33> OriginalProgramClockReferenceBase;
    bitset<6>  OPCRReserved;
    bitset<9>  OriginalProgramClockReferenceExtension;
    bitset<8>  SpliceCountdown;
    bitset<8>  TransportPrivateDataLength;
    bitset<8>  AdaptationFieldExtensionLength;
    bitset<1>  ltwFlag;
    bitset<1>  PiecewiseRateFlag;
    bitset<1>  SeamlessSpliceFlag;
    bitset<5>  EXReserved;
    bitset<1>  ltwValidFlag;
    bitset<15> ltwOffset;
    bitset<2>  PiecewiseReserved;
    bitset<22> PiecewiseRate;
    bitset<4>  SpliceType;
    bitset<3>  DtsNext32;
    bitset<1>  FMarker;
    bitset<15> DtsNext29;
    bitset<1>  SMarker;
    bitset<15> DtsNext14;
    bitset<1>  TMarker;
    u_int16_t  AFEXReservedLength;
    u_int16_t  StuffingLength;

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
    void setProgramClockReferenceBase(const bitset<33> &programClockReferenceBase);
    void setPcrReserved(const bitset<6> &pcrReserved);
    void setProgramClockReferenceExtension(const bitset<9> &programClockReferenceExtension);
    void setOriginalProgramClockReferenceBase(const bitset<33> &originalProgramClockReferenceBase);
    void setOpcrReserved(const bitset<6> &opcrReserved);
    void setOriginalProgramClockReferenceExtension(const bitset<9> &originalProgramClockReferenceExtension);
    void setSpliceCountdown(const bitset<8> &spliceCountdown);
    void setTransportPrivateDataLength(const bitset<8> &transportPrivateDataLength);
    void setAdaptationFieldExtensionLength(const bitset<8> &adaptationFieldExtensionLength);
    void setLtwFlag(const bitset<1> &ltwFlag);
    void setPiecewiseRateFlag(const bitset<1> &piecewiseRateFlag);
    void setSeamlessSpliceFlag(const bitset<1> &seamlessSpliceFlag);
    void setExReserved(const bitset<5> &exReserved);
    void setLtwValidFlag(const bitset<1> &ltwValidFlag);
    void setLtwOffset(const bitset<15> &ltwOffset);
    void setPiecewiseReserved(const bitset<2> &piecewiseReserved);
    void setPiecewiseRate(const bitset<22> &piecewiseRate);
    void setSpliceType(const bitset<4> &spliceType);
    void setDtsNext32(const bitset<3> &dtsNext32);
    void setFMarker(const bitset<1> &fMarker);
    void setDtsNext29(const bitset<15> &dtsNext29);
    void setSMarker(const bitset<1> &sMarker);
    void setDtsNext14(const bitset<15> &dtsNext14);
    void setTMarker(const bitset<1> &tMarker);
    void setAfexReservedLength(uint16_t afexReservedLength);
    void setStuffingLength(u_int16_t stuffingLength);

    const bitset<8> &getAdaptationFieldLength() const;
    const bitset<1> &getDiscontinuityIndicator() const;
    const bitset<1> &getRandomAccessIndicator() const;
    const bitset<1> &getElementaryStreamPriorityIndicator() const;
    const bitset<1> &getProgramClockReferenceFlag() const;
    const bitset<1> &getOriginalProgramClockReferenceFlag() const;
    const bitset<1> &getSplicingPointFlag() const;
    const bitset<1> &getTransportPrivateDataFlag() const;
    const bitset<1> &getAdaptationFieldExtensionFlag() const;
    const bitset<33> &getProgramClockReferenceBase() const;
    const bitset<6> &getPcrReserved() const;
    const bitset<9> &getProgramClockReferenceExtension() const;
    const bitset<33> &getOriginalProgramClockReferenceBase() const;
    const bitset<6> &getOpcrReserved() const;
    const bitset<9> &getOriginalProgramClockReferenceExtension() const;
    const bitset<8> &getSpliceCountdown() const;
    const bitset<8> &getTransportPrivateDataLength() const;
    const bitset<8> &getAdaptationFieldExtensionLength() const;
    const bitset<1> &getLtwFlag() const;
    const bitset<1> &getPiecewiseRateFlag() const;
    const bitset<1> &getSeamlessSpliceFlag() const;
    const bitset<5> &getExReserved() const;
    const bitset<1> &getLtwValidFlag() const;
    const bitset<15> &getLtwOffset() const;
    const bitset<2> &getPiecewiseReserved() const;
    const bitset<22> &getPiecewiseRate() const;
    const bitset<4> &getSpliceType() const;
    const bitset<3> &getDtsNext32() const;
    const bitset<1> &getFMarker() const;
    const bitset<15> &getDtsNext29() const;
    const bitset<1> &getSMarker() const;
    const bitset<15> &getDtsNext14() const;
    const bitset<1> &getTMarker() const;
    u_int16_t getAfexReservedLength() const;
    u_int16_t getStuffingLength() const;

    void Reset();
    void Print() const;
    uint32_t getNumBytes(size_t index) const;
    int32_t Parse(bitset<8> *Input, bitset<2> AdaptationFieldControl);
};

//=============================================================================================================================================================================
