#include <iostream>
#include "tsTransportStream.h"
#define Hehe 1

using namespace std;

//=============================================================================================================================================================================
// xTS_PacketHeader
//=============================================================================================================================================================================
void xTS_PacketHeader::Reset() {
    setSyncByte(0x00000000);
    setTransportErrorIndicator(0x0);
    setPayloadUnitStartIndicator(0x0);
    setTransportPriority(0x0);
    setPacketIdentifier(0x0000000000000);
    setTransportScramblingControl(0x00);
    setAdaptationFieldControl(0x00);
    setContinuityCounter(0x0000);
}

void xTS_PacketHeader::Print() const {
    printf("SB=%d E=%d S=%d P=%d PID=%d TSC=%d AF=%d CC=%d",
           (uint32_t) (getSyncByte().to_ulong()),
           (uint8_t) getTransportErrorIndicator().to_ulong(),
           (uint8_t) getPayloadUnitStartIndicator().to_ulong(),
           (uint8_t) getTransportPriority().to_ulong(),
           (uint16_t) (getPacketIdentifier().to_ulong()),
           (uint16_t) (getTransportScramblingControl().to_ulong()),
           (uint16_t) (getAdaptationFieldControl().to_ulong()),
           (uint16_t) (getContinuityCounter().to_ulong()));
//    if (!hasAdaptationField()) printf("\n");
}

int32_t xTS_PacketHeader::Parse(bitset<8> * Input) {
    string Header = Input[0].to_string() + Input[1].to_string() + Input[2].to_string() + Input[3].to_string();
    setSyncByte(bitset<8> (Header.substr(0, 8)));
    setTransportErrorIndicator(bitset<1>(Header[8]));
    setPayloadUnitStartIndicator(bitset<1>(Header[9]));
    setTransportPriority(bitset<1>(Header[10]));
    setPacketIdentifier(bitset<13>(Header.substr(11, 13)));
    setTransportScramblingControl((bitset<2>(Header.substr(24, 2))));
    setAdaptationFieldControl((bitset<2>(Header.substr(26, 2))));
    setContinuityCounter((bitset<4>(Header.substr(28, 4))));

    return Hehe;
}

const bitset<8> &xTS_PacketHeader::getSyncByte() const {
    return syncByte;
}

const bitset<1> &xTS_PacketHeader::getTransportErrorIndicator() const {
    return transportErrorIndicator;
}

const bitset<1> &xTS_PacketHeader::getPayloadUnitStartIndicator() const {
    return payloadUnitStartIndicator;
}

const bitset<1> &xTS_PacketHeader::getTransportPriority() const {
    return transportPriority;
}

const bitset<13> &xTS_PacketHeader::getPacketIdentifier() const {
    return packetIdentifier;
}

const bitset<2> &xTS_PacketHeader::getTransportScramblingControl() const {
    return transportScramblingControl;
}

const bitset<2> &xTS_PacketHeader::getAdaptationFieldControl() const {
    return adaptationFieldControl;
}

const bitset<4> &xTS_PacketHeader::getContinuityCounter() const {
    return continuityCounter;
}

void xTS_PacketHeader::setSyncByte(const bitset<8> &value) {
    xTS_PacketHeader::syncByte = value;
}

void xTS_PacketHeader::setTransportErrorIndicator(const bitset<1> &value) {
    xTS_PacketHeader::transportErrorIndicator = value;
}

void xTS_PacketHeader::setPayloadUnitStartIndicator(const bitset<1> &value) {
    xTS_PacketHeader::payloadUnitStartIndicator = value;
}

void xTS_PacketHeader::setTransportPriority(const bitset<1> &value) {
    xTS_PacketHeader::transportPriority = value;
}

void xTS_PacketHeader::setPacketIdentifier(const bitset<13> &value) {
    xTS_PacketHeader::packetIdentifier = value;
}

void xTS_PacketHeader::setTransportScramblingControl(const bitset<2> &value) {
    xTS_PacketHeader::transportScramblingControl = value;
}

void xTS_PacketHeader::setAdaptationFieldControl(const bitset<2> &value) {
    xTS_PacketHeader::adaptationFieldControl = value;
}

void xTS_PacketHeader::setContinuityCounter(const bitset<4> &value) {
    xTS_PacketHeader::continuityCounter = value;
}

bool xTS_PacketHeader::hasAdaptationField() const {
    auto afc = getAdaptationFieldControl().to_string();
    return afc == "10" or afc == "11";
}

bool xTS_PacketHeader::hasPayload() const {
    return getAdaptationFieldControl().to_string() == "11";
}

//=============================================================================================================================================================================
// xTS_AdaptationField
//=============================================================================================================================================================================

void xTS_AdaptationField::Reset() {
    setAdaptationFieldLength(0x00000000);
    setDiscontinuityIndicator(0x0);
    setRandomAccessIndicator(0x0);
    setElementaryStreamPriorityIndicator(0x0);
    setProgramClockReferenceFlag(0x0);
    setOriginalProgramClockReferenceFlag(0x0);
    setSplicingPointFlag(0x0);
    setTransportPrivateDataFlag(0x0);
    setAdaptationFieldExtensionFlag(0x0);
    setProgramClockReferenceBase(0x000000000000000000000000000000000);
    setPcrReserved(0x000000);
    setProgramClockReferenceExtension(0x000000000);
    setOriginalProgramClockReferenceBase(0x000000000000000000000000000000000);
    setOpcrReserved(0x000000);
    setOriginalProgramClockReferenceExtension(0x000000000);
    setSpliceCountdown(0x00000000);
    setTransportPrivateDataLength(0x00000000);
    setAdaptationFieldExtensionLength(0x00000000);
    setLtwFlag(0x0);
    setPiecewiseRateFlag(0x0);
    setSeamlessSpliceFlag(0x0);
    setExReserved(0x00000);
    setLtwValidFlag(0x0);
    setLtwOffset(0x000000000000000);
    setPiecewiseReserved(0x00);
    setPiecewiseRate(0x0000000000000000000000);
    setSpliceType(0x0000);
    setDtsNext32(0x000);
    setFMarker(0x0);
    setDtsNext29(0x000000000000000);
    setSMarker(0x0);
    setDtsNext14(0x000000000000000);
    setTMarker(0x0);
    setAfexReservedLength(0);
    setStuffingLength(0);
}

void xTS_AdaptationField::Print() const {
    printf(" AF: L=%d DC=%d RA=%d SP=%d PR=%d OR=%d SP=%d TP=%d EX=%d",
           (uint16_t) getAdaptationFieldLength().to_ulong(),
           (uint8_t) getDiscontinuityIndicator().to_ulong(),
           (uint8_t) getRandomAccessIndicator().to_ulong(),
           (uint8_t) getElementaryStreamPriorityIndicator().to_ulong(),
           (uint8_t) getProgramClockReferenceFlag().to_ulong(),
           (uint8_t) getOriginalProgramClockReferenceFlag().to_ulong(),
           (uint8_t) getSplicingPointFlag().to_ulong(),
           (uint8_t) getTransportPrivateDataFlag().to_ulong(),
           (uint8_t) getAdaptationFieldExtensionFlag().to_ulong());

    if (getProgramClockReferenceFlag() == 1) {
        printf(" PCR=%lu",
               getProgramClockReferenceBase().to_ulong() * xTS::BaseToExtendedClockMultiplier + getProgramClockReferenceExtension().to_ulong());
    }
    if (getOriginalProgramClockReferenceFlag() == 1) {
        printf(" OPCR=%lu", getOriginalProgramClockReferenceBase().to_ulong() * xTS::BaseToExtendedClockMultiplier +
                            getOriginalProgramClockReferenceExtension().to_ulong());
    }

    printf(" Stuffing=%d", getStuffingLength());
}

int32_t xTS_AdaptationField::Parse(bitset<8> *Input, bitset<2> AdaptationFieldControl) {
    size_t index = 0;
    string af;

    for(int i = xTS::TS_HeaderLength + 1; i < 188;i++){
        af += Input[i].to_string();
    }

    setAdaptationFieldLength(bitset<8> (Input[4].to_string()));
    setDiscontinuityIndicator(bitset<1> (af[index++]));
    setRandomAccessIndicator(bitset<1>(af[index++]));
    setElementaryStreamPriorityIndicator(bitset<1>(af[index++]));
    setProgramClockReferenceFlag(bitset<1>(af[index++]));
    setOriginalProgramClockReferenceFlag(bitset<1> (af[index++]));
    setSplicingPointFlag(bitset<1>(af[index++]));
    setTransportPrivateDataFlag(bitset<1>(af[index++]));
    setAdaptationFieldExtensionFlag(bitset<1>(af[index++]));

    if(getProgramClockReferenceFlag() == 1) {
        setProgramClockReferenceBase(bitset<33>(af.substr(index, 33)));
        index += 33;
        setPcrReserved(bitset<6>(af.substr(index, 6)));
        index += 6;
        setProgramClockReferenceExtension(bitset<9>(af.substr(index, 9)));
        index += 9;
    }

    if(getOriginalProgramClockReferenceFlag() == 1) {
        setOriginalProgramClockReferenceBase(bitset<33> (af.substr(index, 33)));
        index += 33;
        setOpcrReserved(bitset<6> (af.substr(index, 6)));
        index += 6;
        setOriginalProgramClockReferenceExtension(bitset<9> (af.substr(index, 9)));
        index += 9;
    }

    if(getSplicingPointFlag() == 1) {
//        setSpliceCountdown(bitset<8> (af.substr(index, 8)));
        index += 8;
    }
    if(getTransportPrivateDataFlag() == 1) {
//        setTransportPrivateDataLength(bitset<8> (af.substr(index, 8)));
        index += 8;
    }
    if(getAdaptationFieldExtensionFlag() == 1) {
//        setAdaptationFieldExtensionLength(bitset<8> (af.substr(index, 8)));
//        index += 8;
//        setLtwFlag(bitset<1> (af[index]));
//        setPiecewiseRateFlag(bitset<1> (af[index++]));
//        setSeamlessSpliceFlag(bitset<1> (af[index++]));
//        setExReserved(bitset<5> (af.substr(index, 5)));
        index += 16;

        if(getLtwFlag() == 1) {
//            setLtwValidFlag(bitset<1> (af[index++]));
//            setLtwOffset(bitset<15> (af.substr(index, 15)));
            index += 16;
        }

        if(getPiecewiseRateFlag() == 1) {
//            setPiecewiseReserved(bitset<2> (af.substr(index, 2)));
//            index += 2;
//            setPiecewiseRate(bitset<22> (af.substr(index, 22)));
            index += 24;
        }

        if(getSeamlessSpliceFlag() == 1) {
//            setSpliceType(bitset<4> (af.substr(index, 4)));
//            index += 4;
//            setDtsNext32(bitset<3> (af.substr(index, 3)));
//            index += 3;
//            setFMarker(bitset<1> (af[index++]));
//            setDtsNext29(bitset<15> (af.substr(index, 15)));
//            index += 15;
//            setSMarker(bitset<1> (af[index++]));
//            setDtsNext14(bitset<15> (af.substr(index, 15)));
//            index += 15;
//            setTMarker(bitset<1> (af[index++]));
            index += 32;
        }

        setAfexReservedLength(188 - index/8);
    }

    setStuffingLength(getNumBytes(index));

    return 0;
}

const bitset<8> &xTS_AdaptationField::getAdaptationFieldLength() const {
    return AdaptationFieldLength;
}

const bitset<1> &xTS_AdaptationField::getDiscontinuityIndicator() const {
    return DiscontinuityIndicator;
}

const bitset<1> &xTS_AdaptationField::getRandomAccessIndicator() const {
    return RandomAccessIndicator;
}

const bitset<1> &xTS_AdaptationField::getElementaryStreamPriorityIndicator() const {
    return ElementaryStreamPriorityIndicator;
}

const bitset<1> &xTS_AdaptationField::getProgramClockReferenceFlag() const {
    return ProgramClockReferenceFlag;
}

const bitset<1> &xTS_AdaptationField::getOriginalProgramClockReferenceFlag() const {
    return OriginalProgramClockReferenceFlag;
}

const bitset<1> &xTS_AdaptationField::getSplicingPointFlag() const {
    return SplicingPointFlag;
}

const bitset<1> &xTS_AdaptationField::getTransportPrivateDataFlag() const {
    return TransportPrivateDataFlag;
}

const bitset<1> &xTS_AdaptationField::getAdaptationFieldExtensionFlag() const {
    return AdaptationFieldExtensionFlag;
}

const bitset<33> &xTS_AdaptationField::getProgramClockReferenceBase() const {
    return ProgramClockReferenceBase;
}

const bitset<6> &xTS_AdaptationField::getPcrReserved() const {
    return PCRReserved;
}

const bitset<9> &xTS_AdaptationField::getProgramClockReferenceExtension() const {
    return ProgramClockReferenceExtension;
}

const bitset<33> &xTS_AdaptationField::getOriginalProgramClockReferenceBase() const {
    return OriginalProgramClockReferenceBase;
}

const bitset<6> &xTS_AdaptationField::getOpcrReserved() const {
    return OPCRReserved;
}

const bitset<9> &xTS_AdaptationField::getOriginalProgramClockReferenceExtension() const {
    return OriginalProgramClockReferenceExtension;
}

const bitset<8> &xTS_AdaptationField::getSpliceCountdown() const {
    return SpliceCountdown;
}

const bitset<8> &xTS_AdaptationField::getTransportPrivateDataLength() const {
    return TransportPrivateDataLength;
}

const bitset<8> &xTS_AdaptationField::getAdaptationFieldExtensionLength() const {
    return AdaptationFieldExtensionLength;
}

const bitset<1> &xTS_AdaptationField::getLtwFlag() const {
    return ltwFlag;
}

const bitset<1> &xTS_AdaptationField::getPiecewiseRateFlag() const {
    return PiecewiseRateFlag;
}

const bitset<1> &xTS_AdaptationField::getSeamlessSpliceFlag() const {
    return SeamlessSpliceFlag;
}

const bitset<5> &xTS_AdaptationField::getExReserved() const {
    return EXReserved;
}

const bitset<1> &xTS_AdaptationField::getLtwValidFlag() const {
    return ltwValidFlag;
}

const bitset<15> &xTS_AdaptationField::getLtwOffset() const {
    return ltwOffset;
}

const bitset<2> &xTS_AdaptationField::getPiecewiseReserved() const {
    return PiecewiseReserved;
}

const bitset<22> &xTS_AdaptationField::getPiecewiseRate() const {
    return PiecewiseRate;
}

const bitset<4> &xTS_AdaptationField::getSpliceType() const {
    return SpliceType;
}

const bitset<3> &xTS_AdaptationField::getDtsNext32() const {
    return DtsNext32;
}

const bitset<1> &xTS_AdaptationField::getFMarker() const {
    return FMarker;
}

const bitset<15> &xTS_AdaptationField::getDtsNext29() const {
    return DtsNext29;
}

const bitset<1> &xTS_AdaptationField::getSMarker() const {
    return SMarker;
}

const bitset<15> &xTS_AdaptationField::getDtsNext14() const {
    return DtsNext14;
}

const bitset<1> &xTS_AdaptationField::getTMarker() const {
    return TMarker;
}

u_int16_t xTS_AdaptationField::getAfexReservedLength() const {
    return AFEXReservedLength;
}

u_int16_t xTS_AdaptationField::getStuffingLength() const {
    return StuffingLength;
}

uint32_t xTS_AdaptationField::getNumBytes(size_t index) const {
    return getAdaptationFieldLength().to_ulong() - index/8;
}

void xTS_AdaptationField::setAdaptationFieldLength(const bitset<8> &adaptationFieldLength) {
    AdaptationFieldLength = adaptationFieldLength;
}

void xTS_AdaptationField::setDiscontinuityIndicator(const bitset<1> &discontinuityIndicator) {
    DiscontinuityIndicator = discontinuityIndicator;
}

void xTS_AdaptationField::setRandomAccessIndicator(const bitset<1> &randomAccessIndicator) {
    RandomAccessIndicator = randomAccessIndicator;
}

void xTS_AdaptationField::setElementaryStreamPriorityIndicator(const bitset<1> &elementaryStreamPriorityIndicator) {
    ElementaryStreamPriorityIndicator = elementaryStreamPriorityIndicator;
}

void xTS_AdaptationField::setProgramClockReferenceFlag(const bitset<1> &programClockReferenceFlag) {
    ProgramClockReferenceFlag = programClockReferenceFlag;
}

void xTS_AdaptationField::setOriginalProgramClockReferenceFlag(const bitset<1> &originalProgramClockReferenceFlag) {
    OriginalProgramClockReferenceFlag = originalProgramClockReferenceFlag;
}

void xTS_AdaptationField::setSplicingPointFlag(const bitset<1> &splicingPointFlag) {
    SplicingPointFlag = splicingPointFlag;
}

void xTS_AdaptationField::setTransportPrivateDataFlag(const bitset<1> &transportPrivateDataFlag) {
    TransportPrivateDataFlag = transportPrivateDataFlag;
}

void xTS_AdaptationField::setAdaptationFieldExtensionFlag(const bitset<1> &adaptationFieldExtensionFlag) {
    AdaptationFieldExtensionFlag = adaptationFieldExtensionFlag;
}

void xTS_AdaptationField::setProgramClockReferenceBase(const bitset<33> &programClockReferenceBase) {
    ProgramClockReferenceBase = programClockReferenceBase;
}

void xTS_AdaptationField::setPcrReserved(const bitset<6> &pcrReserved) {
    PCRReserved = pcrReserved;
}

void xTS_AdaptationField::setProgramClockReferenceExtension(const bitset<9> &programClockReferenceExtension) {
    ProgramClockReferenceExtension = programClockReferenceExtension;
}

void xTS_AdaptationField::setOriginalProgramClockReferenceBase(const bitset<33> &originalProgramClockReferenceBase) {
    OriginalProgramClockReferenceBase = originalProgramClockReferenceBase;
}

void xTS_AdaptationField::setOpcrReserved(const bitset<6> &opcrReserved) {
    OPCRReserved = opcrReserved;
}

void xTS_AdaptationField::setOriginalProgramClockReferenceExtension(
        const bitset<9> &originalProgramClockReferenceExtension) {
    OriginalProgramClockReferenceExtension = originalProgramClockReferenceExtension;
}

void xTS_AdaptationField::setSpliceCountdown(const bitset<8> &spliceCountdown) {
    SpliceCountdown = spliceCountdown;
}

void xTS_AdaptationField::setTransportPrivateDataLength(const bitset<8> &transportPrivateDataLength) {
    TransportPrivateDataLength = transportPrivateDataLength;
}

void xTS_AdaptationField::setAdaptationFieldExtensionLength(const bitset<8> &adaptationFieldExtensionLength) {
    AdaptationFieldExtensionLength = adaptationFieldExtensionLength;
}

void xTS_AdaptationField::setLtwFlag(const bitset<1> &ltwFlag) {
    xTS_AdaptationField::ltwFlag = ltwFlag;
}

void xTS_AdaptationField::setPiecewiseRateFlag(const bitset<1> &piecewiseRateFlag) {
    PiecewiseRateFlag = piecewiseRateFlag;
}

void xTS_AdaptationField::setSeamlessSpliceFlag(const bitset<1> &seamlessSpliceFlag) {
    SeamlessSpliceFlag = seamlessSpliceFlag;
}

void xTS_AdaptationField::setExReserved(const bitset<5> &exReserved) {
    EXReserved = exReserved;
}

void xTS_AdaptationField::setLtwValidFlag(const bitset<1> &ltwValidFlag) {
    xTS_AdaptationField::ltwValidFlag = ltwValidFlag;
}

void xTS_AdaptationField::setLtwOffset(const bitset<15> &ltwOffset) {
    xTS_AdaptationField::ltwOffset = ltwOffset;
}

void xTS_AdaptationField::setPiecewiseReserved(const bitset<2> &piecewiseReserved) {
    PiecewiseReserved = piecewiseReserved;
}

void xTS_AdaptationField::setPiecewiseRate(const bitset<22> &piecewiseRate) {
    PiecewiseRate = piecewiseRate;
}

void xTS_AdaptationField::setSpliceType(const bitset<4> &spliceType) {
    SpliceType = spliceType;
}

void xTS_AdaptationField::setDtsNext32(const bitset<3> &dtsNext32) {
    DtsNext32 = dtsNext32;
}

void xTS_AdaptationField::setFMarker(const bitset<1> &fMarker) {
    FMarker = fMarker;
}

void xTS_AdaptationField::setDtsNext29(const bitset<15> &dtsNext29) {
    DtsNext29 = dtsNext29;
}

void xTS_AdaptationField::setSMarker(const bitset<1> &sMarker) {
    SMarker = sMarker;
}

void xTS_AdaptationField::setDtsNext14(const bitset<15> &dtsNext14) {
    DtsNext14 = dtsNext14;
}

void xTS_AdaptationField::setTMarker(const bitset<1> &tMarker) {
    TMarker = tMarker;
}

void xTS_AdaptationField::setAfexReservedLength(u_int16_t afexReservedLength) {
    AFEXReservedLength = afexReservedLength;
}

void xTS_AdaptationField::setStuffingLength(u_int16_t stuffingLength) {
    StuffingLength = stuffingLength;
}

//=============================================================================================================================================================================
// xPES_PacketHeader
//=============================================================================================================================================================================

void xPES_PacketHeader::Reset() {
    setMPacketStartCodePrefix(bitset<24>(0x000000000000000000000000));
    setMStreamId(bitset<8>(0x00000000));
    setMPacketLength(bitset<16>(0x0000000000000000));
    setPesScramblingControl(bitset<2>(0x00));
    setPesPriority(bitset<1>(0x0));
    setDataAlignmentIndicator(bitset<1>(0x0));
    setCopyright(bitset<1>(0x0));
    setOriginalOrCopy(bitset<1>(0x0));
    setPtsdtsFlags(bitset<2>(0x00));
    setEscrFlag(bitset<1>(0x0));
    setEsRateFlag(bitset<1>(0x0));
    setDsmTrickModeFlag(bitset<1>(0x0));
    setAdditionalCopyInfoFlag(bitset<1>(0x0));
    setPescrcFlag(bitset<1>(0x0));
    setPesExtensionFlag(bitset<1>(0x0));
    setPesHeaderDataLength(bitset<8>(0x00000000));
    setFpts(bitset<3>(0x000));
    setSpts(bitset<15>(0x000000000000000));
    setTpts(bitset<15>(0x000000000000000));
    setFdts(bitset<3>(0x000));
    setSdts(bitset<15>(0x000000000000000));
    setTdts(bitset<15>(0x000000000000000));
}

int32_t xPES_PacketHeader::Parse(const string Input) {
    size_t index = 0;
    setMPacketStartCodePrefix(bitset<24>(Input.substr(index, 24)));
    index += 24;
    setMStreamId(bitset<8>(Input.substr(index, 8)));
    index += 8;
    setMPacketLength(bitset<16>(Input.substr(index, 16)));
    index += 16;
    uint32_t u_m_StreamId = m_StreamId.to_ulong();
    if (u_m_StreamId != eStreamId::eStreamId_program_stream_map
        and u_m_StreamId != eStreamId::eStreamId_padding_stream
        and u_m_StreamId != eStreamId::eStreamId_private_stream_2
        and u_m_StreamId != eStreamId::eStreamId_ECM
        and u_m_StreamId != eStreamId::eStreamId_EMM
        and u_m_StreamId != eStreamId::eStreamId_program_stream_directory
        and u_m_StreamId != eStreamId::eStreamId_DSMCC_stream
        and u_m_StreamId != eStreamId::eStreamId_ITUT_H222_1_type_E
        and Input.length() > 48) {
        index +=2;
        setPesScramblingControl(bitset<2>(Input.substr(index, 2)));
        index += 2;
        setPesPriority(bitset<1>(Input[index++]));
        setDataAlignmentIndicator(bitset<1>(Input[index++]));
        setCopyright(bitset<1>(Input[index++]));
        setOriginalOrCopy(bitset<1>(Input[index++]));
        setPtsdtsFlags(bitset<2>(Input.substr(index, 2)));
        index += 2;
        setEscrFlag(bitset<1>(Input[index++]));
        setEsRateFlag(bitset<1>(Input[index++]));
        setDsmTrickModeFlag(bitset<1>(Input[index++]));
        setAdditionalCopyInfoFlag(bitset<1>(Input[index++]));
        setPescrcFlag(bitset<1>(Input[index++]));
        setPesExtensionFlag(bitset<1>(Input[index++]));
        setPesHeaderDataLength(bitset<8>(Input.substr(index, 8)));
        index += 8;
        if (getPtsdtsFlags().to_string() == "10") {
            index += 4;
            setFpts(bitset<3>(Input.substr(index, 3)));
            index += 4;
            setSpts(bitset<15>(Input.substr(index, 15)));
            index += 16;
            setTpts(bitset<15>(Input.substr(index, 15)));
            index += 16;
        } else if (getPtsdtsFlags().to_string() == "11") {
            index += 4;
            setFpts(bitset<3>(Input.substr(index, 3)));
            index += 4;
            setSpts(bitset<15>(Input.substr(index, 15)));
            index += 16;
            setTpts(bitset<15>(Input.substr(index, 15)));
            index += 20;
            setFdts(bitset<3>(Input.substr(index, 3)));
            index += 4;
            setSdts(bitset<15>(Input.substr(index, 15)));
            index += 16;
            setTdts(bitset<15>(Input.substr(index, 15)));
        }
    }
    return 0;
}

void xPES_PacketHeader::Print() const {
    printf(" PSCP=%d SID=%d PL=%d HL=%lu DL=%lu",
            getPacketStartCodePrefix(),
            getStreamId(),
            getPacketLength(),
            getPesHeaderDataLength().to_ulong() + xTS::TS_HeaderLength + 3,
            getPacketLength() - getPesHeaderDataLength().to_ulong() - 3);
    if(getPtsdtsFlags().to_string() == "10"){
        printf(" PTS=%lu", (bitset<33> (getFpts().to_string() + getSpts().to_string() + getTpts().to_string())).to_ulong());
        if(getPtsdtsFlags().to_string() == "11"){
            printf(" DTS=%lu", (bitset<33> (getFdts().to_string() + getSdts().to_string() + getTdts().to_string())).to_ulong());
        }
    }
}

void xPES_PacketHeader::setMPacketStartCodePrefix(const bitset<24> &mPacketStartCodePrefix) {
    m_PacketStartCodePrefix = mPacketStartCodePrefix;
}

void xPES_PacketHeader::setMStreamId(const bitset<8> &mStreamId) {
    m_StreamId = mStreamId;
}

void xPES_PacketHeader::setMPacketLength(const bitset<16> &mPacketLength) {
    m_PacketLength = mPacketLength;
}

const bitset<2> &xPES_PacketHeader::getPesScramblingControl() const {
    return PESScramblingControl;
}

const bitset<1> &xPES_PacketHeader::getPesPriority() const {
    return PESPriority;
}

const bitset<1> &xPES_PacketHeader::getDataAlignmentIndicator() const {
    return DataAlignmentIndicator;
}

const bitset<1> &xPES_PacketHeader::getCopyright() const {
    return Copyright;
}

const bitset<1> &xPES_PacketHeader::getOriginalOrCopy() const {
    return OriginalOrCopy;
}

const bitset<2> &xPES_PacketHeader::getPtsdtsFlags() const {
    return PTSDTSFlags;
}

const bitset<1> &xPES_PacketHeader::getEscrFlag() const {
    return ESCRFlag;
}

const bitset<1> &xPES_PacketHeader::getEsRateFlag() const {
    return ESRateFlag;
}

const bitset<1> &xPES_PacketHeader::getDsmTrickModeFlag() const {
    return DSMTrickModeFlag;
}

const bitset<1> &xPES_PacketHeader::getAdditionalCopyInfoFlag() const {
    return AdditionalCopyInfoFlag;
}

const bitset<1> &xPES_PacketHeader::getPescrcFlag() const {
    return PESCRCFlag;
}

const bitset<1> &xPES_PacketHeader::getPesExtensionFlag() const {
    return PESExtensionFlag;
}

const bitset<8> &xPES_PacketHeader::getPesHeaderDataLength() const {
    return PESHeaderDataLength;
}

const bitset<3> &xPES_PacketHeader::getFpts() const {
    return fPTS;
}

const bitset<15> &xPES_PacketHeader::getSpts() const {
    return sPTS;
}

const bitset<15> &xPES_PacketHeader::getTpts() const {
    return tPTS;
}

const bitset<3> &xPES_PacketHeader::getFdts() const {
    return fDTS;
}

const bitset<15> &xPES_PacketHeader::getSdts() const {
    return sDTS;
}

const bitset<15> &xPES_PacketHeader::getTdts() const {
    return tDTS;
}

void xPES_PacketHeader::setPesScramblingControl(const bitset<2> &pesScramblingControl) {
    PESScramblingControl = pesScramblingControl;
}

void xPES_PacketHeader::setPesPriority(const bitset<1> &pesPriority) {
    PESPriority = pesPriority;
}

void xPES_PacketHeader::setDataAlignmentIndicator(const bitset<1> &dataAlignmentIndicator) {
    DataAlignmentIndicator = dataAlignmentIndicator;
}

void xPES_PacketHeader::setCopyright(const bitset<1> &copyright) {
    Copyright = copyright;
}

void xPES_PacketHeader::setOriginalOrCopy(const bitset<1> &originalOrCopy) {
    OriginalOrCopy = originalOrCopy;
}

void xPES_PacketHeader::setPtsdtsFlags(const bitset<2> &ptsdtsFlags) {
    PTSDTSFlags = ptsdtsFlags;
}

void xPES_PacketHeader::setEscrFlag(const bitset<1> &escrFlag) {
    ESCRFlag = escrFlag;
}

void xPES_PacketHeader::setEsRateFlag(const bitset<1> &esRateFlag) {
    ESRateFlag = esRateFlag;
}

void xPES_PacketHeader::setDsmTrickModeFlag(const bitset<1> &dsmTrickModeFlag) {
    DSMTrickModeFlag = dsmTrickModeFlag;
}

void xPES_PacketHeader::setAdditionalCopyInfoFlag(const bitset<1> &additionalCopyInfoFlag) {
    AdditionalCopyInfoFlag = additionalCopyInfoFlag;
}

void xPES_PacketHeader::setPescrcFlag(const bitset<1> &pescrcFlag) {
    PESCRCFlag = pescrcFlag;
}

void xPES_PacketHeader::setPesExtensionFlag(const bitset<1> &pesExtensionFlag) {
    PESExtensionFlag = pesExtensionFlag;
}

void xPES_PacketHeader::setPesHeaderDataLength(const bitset<8> &pesHeaderDataLength) {
    PESHeaderDataLength = pesHeaderDataLength;
}

void xPES_PacketHeader::setFpts(const bitset<3> &fPts) {
    fPTS = fPts;
}

void xPES_PacketHeader::setSpts(const bitset<15> &sPts) {
    sPTS = sPts;
}

void xPES_PacketHeader::setTpts(const bitset<15> &tPts) {
    tPTS = tPts;
}

void xPES_PacketHeader::setFdts(const bitset<3> &fDts) {
    fDTS = fDts;
}

void xPES_PacketHeader::setSdts(const bitset<15> &sDts) {
    sDTS = sDts;
}

void xPES_PacketHeader::setTdts(const bitset<15> &tDts) {
    tDTS = tDts;
}



//=============================================================================================================================================================================
// xPES_Assembler
//=============================================================================================================================================================================

xPES_Assembler::xPES_Assembler() {

}

xPES_Assembler::~xPES_Assembler() {

}

void xPES_Assembler::Init(int32_t PID) {
    setMPid(PID);
}

void xPES_Assembler::setMPid(int32_t mPid) {
    m_PID = mPid;
}


xPES_Assembler::eResult xPES_Assembler::AbsorbPacket(const bitset<8> *TransportStreamPacket, const xTS_PacketHeader *PacketHeader,
                                                     const xTS_AdaptationField *AdaptationField) {

    if (PacketHeader->getPacketIdentifier().to_ulong() == m_PID) {
        uint8_t cc = PacketHeader->getContinuityCounter().to_ulong();
        if (PacketHeader->getPayloadUnitStartIndicator().to_ulong() == 1) {
            xBufferReset();
            m_PESH.Reset();
            m_Started = true;
            m_LastContinuityCounter = cc;
            m_EndContinuityCounter = (cc + 15) % 16;
            if (PacketHeader->hasPayload()) {
                xBufferAppend(TransportStreamPacket,
                              xTS::TS_HeaderLength + AdaptationField->getAdaptationFieldLength().to_ulong() + 1);
            }

            return xPES_Assembler::eResult::AssemblingStarted;

        } else if (cc == m_EndContinuityCounter) {
            if (PacketHeader->hasPayload()) {
                xBufferAppend(TransportStreamPacket,
                              xTS::TS_HeaderLength + AdaptationField->getAdaptationFieldLength().to_ulong() + 1);
            }
            m_PESH.Reset();
            m_PESH.Parse(m_Buffer);
            m_DataOffset = m_PESH.getPacketLength() + xTS::PES_HeaderLength;
            return xPES_Assembler::eResult::AssemblingFinished;
        } else if (0 <= cc and cc <= 15 and cc == (m_LastContinuityCounter + 1) % 16 and m_Started) {
            m_LastContinuityCounter++;
            if (PacketHeader->hasPayload()) {
                xBufferAppend(TransportStreamPacket,
                              xTS::TS_HeaderLength + AdaptationField->getAdaptationFieldLength().to_ulong() + 1);
            }

            return xPES_Assembler::eResult::AssemblingContinue;
        } else {
            xBufferReset();
            return xPES_Assembler::eResult::StreamPackedLost;
        }
    } else return xPES_Assembler::eResult::UnexpectedPID;
}

void xPES_Assembler::xBufferReset() {
    m_Started = false;
    m_LastContinuityCounter = 0;
    m_EndContinuityCounter = 15;
    m_Buffer = "";
}

void xPES_Assembler::xBufferAppend(const bitset<8> *Input, int32_t Size) {
    for(int i = Size; i < xTS::TS_PacketLength; i++){
        m_Buffer += Input[i].to_string();
    }
}