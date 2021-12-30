#include "UNIT_ENCODER.h"

void UNIT_ENCODER::writeBytes(uint8_t addr, uint8_t reg, uint8_t *buffer,
                              uint8_t length) {
    _wire->beginTransmission(addr);
    _wire->write(reg);
    for (int i = 0; i < length; i++) {
        _wire->write(*(buffer + i));
    }
    _wire->endTransmission();
}

void UNIT_ENCODER::readBytes(uint8_t addr, uint8_t reg, uint8_t *buffer,
                             uint8_t length) {
    uint8_t index = 0;
    _wire->beginTransmission(addr);
    _wire->write(reg);
    _wire->endTransmission();
    _wire->requestFrom(addr, length);
    for (int i = 0; i < length; i++) {
        buffer[index++] = _wire->read();
    }
}

void UNIT_ENCODER::begin(TwoWire *wire, uint8_t addr, uint8_t sda, uint8_t scl,
                         uint32_t speed) {
    _wire  = wire;
    _addr  = addr;
    _sda   = sda;
    _scl   = scl;
    _speed = speed;
    _wire->begin(_sda, _scl, _speed);
}

signed short int UNIT_ENCODER::getEncoderValue() {
    uint8_t data[2];
    readBytes(_addr, ENCODER_REG, data, 2);
    signed short int value = (signed short int)((data[0]) | (data[1]) << 8);
    return value;
}

bool UNIT_ENCODER::getButtonStatus() {
    uint8_t data;
    readBytes(_addr, BUTTON_REG, &data, 1);
    return data;
}

void UNIT_ENCODER::setLEDColor(uint8_t index, uint32_t color) {
    uint8_t data[4];
    data[3] = color & 0xff;
    data[2] = (color >> 8) & 0xff;
    data[1] = (color >> 16) & 0xff;
    data[0] = index;
    writeBytes(_addr, RGB_LED_REG, data, 4);
}
