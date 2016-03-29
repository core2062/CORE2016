#include "WPILib.h"
#include "ZXGestureSensor.h"

ZXGestureSensor::ZXGestureSensor(I2C::Port port):
gestureSensor(port, I2C_ADR)
{
	byte buffer[1];
	if(gestureSensor.Read(ZX_MODEL, 1, buffer) || gestureSensor.Write(ZX_DRCFG, 0x00) || gestureSensor.Write(ZX_DRE, 0x00))
		std::cout << "ERROR: ZX Gesture Sensor not initialized correctly!" << std::endl;
	else if(buffer[0] != ZX_MODEL_VER)
		std::cout << "ERROR: Found wrong ZX Gesture Sensor Version: " << buffer[0] << std::endl;
}
int ZXGestureSensor::getZValue(void) {
	byte buffer[1];
	if(!gestureSensor.Read(ZX_ZPOS, 1, buffer))
		return -1;
	else
		return (int)buffer[0];
}
int ZXGestureSensor::getXValue(void) {
	byte buffer[1];
	if(!gestureSensor.Read(ZX_XPOS, 1, buffer))
		return -1;
	else
		return (int)buffer[0];
}
bool ZXGestureSensor::valueReady(void) {
	byte buffer[1];
	gestureSensor.Read(ZX_STATUS, 1, buffer);
	buffer[0] &= 0b00000001;
    if (buffer[0]) {
        return true;
    }
    return false;
}
ZXGestureSensor::GestureType ZXGestureSensor::getGesture(void)
{
	byte gesture[1];
    if (!gestureSensor.Read(ZX_GESTURE, 1, gesture)) {
        return NO_GESTURE;
    }
    switch (gesture[0]) {
        case RIGHT_SWIPE:
            return RIGHT_SWIPE;
        case LEFT_SWIPE:
            return LEFT_SWIPE;
        case UP_SWIPE:
            return UP_SWIPE;
        default:
            return NO_GESTURE;
    }
}
