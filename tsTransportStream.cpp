#include <iostream>
#include "tsTransportStream.h"
#define PENIS 0
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
    cout << " SB=" <<(uint32_t)(getSyncByte().to_ulong())
    << " E=" << getTransportErrorIndicator()
    << " S=" << getPayloadUnitStartIndicator()
    << " P=" << getTransportPriority()
    << " PID=" << (uint16_t)(getPacketIdentifier().to_ulong())
    << " TSC=" << (uint16_t)(getTransportScramblingControl().to_ulong())
    << " AF=" << (uint16_t)(getAdaptationFieldControl().to_ulong())
    << " CC=" << (uint16_t)(getContinuityCounter().to_ulong());
    if(!hasAdaptationField()) printf("\n");
}

int32_t xTS_PacketHeader::Parse(bitset<8> * Input) {
    if(Input[0].to_string() != "01000111"){
        return PENIS;
    }

    string Header = Input[0].to_string() + Input[1].to_string() + Input[2].to_string() + Input[3].to_string();
    setSyncByte(bitset<8> (Header.substr(0, 8)));
    setTransportErrorIndicator(bitset<1>(Header[8]));
    setPayloadUnitStartIndicator(bitset<1>(Header[9]));
    setTransportPriority(bitset<1>(Header[10]));
    setPacketIdentifier(bitset<13>(Header.substr(11, 13)));
    setTransportScramblingControl((bitset<2>(Header.substr(24, 2))));
    setAdaptationFieldControl((bitset<2>(Header.substr(26, 2))));
    setContinuityCounter((bitset<4>(Header.substr(28, 4))));

    if(hasAdaptationField()){
        xTS_AdaptationField TS_AdaptationField;
        TS_AdaptationField.Reset();
        TS_AdaptationField.Parse(Input, getAdaptationFieldControl());
        TS_AdaptationField.Print();
    }

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
    auto tmp = getAdaptationFieldControl().to_string();
    return tmp == "10" or tmp == "11";
}

bool xTS_PacketHeader::hasPayload() const {
    return getAdaptationFieldControl().to_ulong() == 3;
}

//=============================================================================================================================================================================
// xTS_AdaptationField
//=============================================================================================================================================================================

const bitset<8> &xTS_AdaptationField::getAdaptationFieldLength() const {
    return AdaptationFieldLength;
}

void xTS_AdaptationField::setAdaptationFieldLength(const bitset<8> &adaptationFieldLength) {
    AdaptationFieldLength = adaptationFieldLength;
}

const bitset<1> &xTS_AdaptationField::getDiscontinuityIndicator() const {
    return DiscontinuityIndicator;
}

void xTS_AdaptationField::setDiscontinuityIndicator(const bitset<1> &discontinuityIndicator) {
    DiscontinuityIndicator = discontinuityIndicator;
}

const bitset<1> &xTS_AdaptationField::getRandomAccessIndicator() const {
    return RandomAccessIndicator;
}

void xTS_AdaptationField::setRandomAccessIndicator(const bitset<1> &randomAccessIndicator) {
    RandomAccessIndicator = randomAccessIndicator;
}

const bitset<1> &xTS_AdaptationField::getElementaryStreamPriorityIndicator() const {
    return ElementaryStreamPriorityIndicator;
}

void xTS_AdaptationField::setElementaryStreamPriorityIndicator(const bitset<1> &elementaryStreamPriorityIndicator) {
    ElementaryStreamPriorityIndicator = elementaryStreamPriorityIndicator;
}

const bitset<1> &xTS_AdaptationField::getProgramClockReferenceFlag() const {
    return ProgramClockReferenceFlag;
}

void xTS_AdaptationField::setProgramClockReferenceFlag(const bitset<1> &programClockReferenceFlag) {
    ProgramClockReferenceFlag = programClockReferenceFlag;
}

const bitset<1> &xTS_AdaptationField::getOriginalProgramClockReferenceFlag() const {
    return OriginalProgramClockReferenceFlag;
}

void xTS_AdaptationField::setOriginalProgramClockReferenceFlag(const bitset<1> &originalProgramClockReferenceFlag) {
    OriginalProgramClockReferenceFlag = originalProgramClockReferenceFlag;
}

const bitset<1> &xTS_AdaptationField::getSplicingPointFlag() const {
    return SplicingPointFlag;
}

void xTS_AdaptationField::setSplicingPointFlag(const bitset<1> &splicingPointFlag) {
    SplicingPointFlag = splicingPointFlag;
}

const bitset<1> &xTS_AdaptationField::getTransportPrivateDataFlag() const {
    return TransportPrivateDataFlag;
}

void xTS_AdaptationField::setTransportPrivateDataFlag(const bitset<1> &transportPrivateDataFlag) {
    TransportPrivateDataFlag = transportPrivateDataFlag;
}

const bitset<1> &xTS_AdaptationField::getAdaptationFieldExtensionFlag() const {
    return AdaptationFieldExtensionFlag;
}

void xTS_AdaptationField::setAdaptationFieldExtensionFlag(const bitset<1> &adaptationFieldExtensionFlag) {
    AdaptationFieldExtensionFlag = adaptationFieldExtensionFlag;
}

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
}

void xTS_AdaptationField::Print() const {
    cout << " AF: L=" << (uint16_t) getAdaptationFieldLength().to_ulong()
    << " DC=" << getDiscontinuityIndicator()
    << " RA=" << getRandomAccessIndicator()
    << " SP=" << getElementaryStreamPriorityIndicator()
    << " PR=" << getProgramClockReferenceFlag()
    << " OR=" << getOriginalProgramClockReferenceFlag()
    << " SP=" << getSplicingPointFlag()
    << " TP=" << getTransportPrivateDataFlag()
    << " EX=" << getAdaptationFieldExtensionFlag()
    << endl;
}

int32_t xTS_AdaptationField::Parse(bitset<8> *Input, bitset<2> AdaptationFieldControl) {
    string af = Input[5].to_string();
    setAdaptationFieldLength(bitset<8> (Input[4].to_string()));
    setDiscontinuityIndicator(bitset<1> (af[0]));
    setRandomAccessIndicator(bitset<1>(af[1]));
    setElementaryStreamPriorityIndicator(bitset<1>(af[2]));
    setProgramClockReferenceFlag(bitset<1>(af[3]));
    setOriginalProgramClockReferenceFlag(bitset<1> (af[4]));
    setSplicingPointFlag(bitset<1>(af[5]));
    setTransportPrivateDataFlag(bitset<1>(af[6]));
    setAdaptationFieldExtensionFlag(bitset<1>(af[7]));

    return 0;
}
