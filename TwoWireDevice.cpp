#include "TwoWireDevice.h"

#include "Arduino.h"
#include <stdio.h>
//#include <math.h>

TwoWireDevice::TwoWireDevice(TwoWire *wire, const uint8_t addr) : _i2caddr(addr), _wire(wire)
{
}

TwoWireDevice::TwoWireDevice(const uint8_t addr) : _i2caddr(addr), _wire(&Wire)
{
}

bool TwoWireDevice::begin()
{
    _wire->begin();
    return true;
}

/**************************************************************************/
/*!
    @brief  write one byte of data to the specified register
    @param  reg the register to write to
    @param  value the value to write
*/
/**************************************************************************/
void TwoWireDevice::write8(const uint8_t reg, const uint8_t value)
{
	write(reg, &value, 1);
}

// void BME280_I2C::write8(uint8_t reg, uint8_t value)
// {
//     _wire -> beginTransmission((uint8_t)_i2caddr);
//     _wire -> write((uint8_t)reg);
//     _wire -> write((uint8_t)value);
//     _wire -> endTransmission();
// }

/**************************************************************************/
/*!
    @brief  read one byte of data from the specified register
    @param  reg the register to read
    @returns one byte of register data
*/
/**************************************************************************/
uint8_t TwoWireDevice::read8(const uint8_t reg)
{
	uint8_t ret;
	read(reg, &ret, 1);

	return ret;
}
// uint8_t BME280_I2C::read8(uint8_t reg) {
//     _wire -> beginTransmission((uint8_t)_i2caddr);
//     _wire -> write((uint8_t)reg);
//     _wire -> endTransmission();
//     _wire -> requestFrom((uint8_t)_i2caddr, (uint8_t)1);
//
//     return _wire -> read();
// }

uint16_t TwoWireDevice::read16(const uint8_t reg)
{
    _wire -> beginTransmission(_i2caddr);
    _wire -> write(reg);
    _wire -> endTransmission();
    _wire -> requestFrom(_i2caddr, 2);
    return ((_wire -> read() << 8) | _wire -> read());
}

uint32_t TwoWireDevice::read24(const uint8_t reg)
{
    uint32_t value;

    _wire -> beginTransmission(_i2caddr);
    _wire -> write(reg);
    _wire -> endTransmission();
    _wire -> requestFrom(_i2caddr, 3);

    value = _wire->read();
    value <<= 8;
    value |= _wire->read();
    value <<= 8;
    //if(_wire)
    value |= _wire->read();

    return value;
}

void TwoWireDevice::read(const uint8_t reg, uint8_t *buf, const uint8_t num)
{
	uint8_t pos = 0;

	//on arduino we need to read in 32 byte chunks
	while(pos < num)
    {
		uint8_t read_now = min(32, (num - pos));
		_wire->beginTransmission(_i2caddr);
		_wire->write(reg + pos);
		_wire->endTransmission();
		_wire->requestFrom(_i2caddr, read_now);

		for(int i=0; i<read_now; i++)
        {
			buf[pos] = _wire->read();
			pos++;
		}
	}
}

void TwoWireDevice::write(const uint8_t reg, const uint8_t *buf, const uint8_t num)
{
	_wire->beginTransmission(_i2caddr);
	_wire->write(reg);
	_wire->write(buf, num);
	_wire->endTransmission();
}
