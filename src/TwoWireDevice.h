
#ifndef __TWOWIREDEVICE_H
#define __TWOWIREDEVICE_H

#include <stdint.h>
#include <Wire.h>
#include <Arduino.h>

class TwoWireDevice
{
    public:
        TwoWireDevice(const uint8_t addr);
        TwoWireDevice(TwoWire*, const uint8_t addr);

        bool begin();

    protected:

        void read(const uint8_t reg, uint8_t *buf, const uint8_t num);
        void write(const uint8_t reg, const uint8_t *buf, const uint8_t num);

        void      write8(const uint8_t reg, const uint8_t value);
        void      write16(const uint8_t reg, const uint16_t value);
        uint8_t   read8(const uint8_t reg);
        uint16_t  read16(const uint8_t reg);
        uint32_t  read24(const uint8_t reg);

        uint8_t _i2caddr;
        TwoWire* _wire = &Wire;
};

#endif //__TWOWIREDEVICE_H
