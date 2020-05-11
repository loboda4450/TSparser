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
    << " CC=" << (uint16_t)(getContinuityCounter().to_ulong()) << endl;
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
//=============================================================================================================================================================================

