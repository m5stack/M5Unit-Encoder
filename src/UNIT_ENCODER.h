#ifndef __UNIT_ENCODER_H
#define __UNIT_ENCODER_H

#include "Arduino.h"
#include "Wire.h"

#define ENCODER_ADDR 0x40
#define ENCODER_REG  0x10
#define BUTTON_REG   0x20
#define RGB_LED_REG  0x30

class UNIT_ENCODER {
   private:
    uint8_t _addr;
    TwoWire* _wire;
    uint8_t _scl;
    uint8_t _sda;
    uint8_t _speed;
    void writeBytes(uint8_t addr, uint8_t reg, uint8_t* buffer, uint8_t length);
    void readBytes(uint8_t addr, uint8_t reg, uint8_t* buffer, uint8_t length);

   public:
    void begin(TwoWire* wire = &Wire, uint8_t addr = ENCODER_ADDR,
               uint8_t sda = 21, uint8_t scl = 22, uint32_t speed = 200000L);
    signed short int getEncoderValue();
    bool getButtonStatus();
    void setLEDColor(uint8_t index, uint32_t color);
};

#endif
