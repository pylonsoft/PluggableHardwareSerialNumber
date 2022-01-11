/*
  Copyright (c) 2021, PylonSoft

   Permission to use, copy, modify, and/or distribute this software for
   any purpose with or without fee is hereby granted, provided that the
   above copyright notice and this permission notice appear in all copies.

   THE SOFTWARE IS PROVIDED "AS IS" AND THE AUTHOR DISCLAIMS ALL
   WARRANTIES WITH REGARD TO THIS SOFTWARE INCLUDING ALL IMPLIED
   WARRANTIES OF MERCHANTABILITY AND FITNESS. IN NO EVENT SHALL THE AUTHOR
   BE LIABLE FOR ANY SPECIAL, DIRECT, INDIRECT, OR CONSEQUENTIAL DAMAGES
   OR ANY DAMAGES WHATSOEVER RESULTING FROM LOSS OF USE, DATA OR PROFITS,
   WHETHER IN AN ACTION OF CONTRACT, NEGLIGENCE OR OTHER TORTIOUS ACTION,
   ARISING OUT OF OR IN CONNECTION WITH THE USE OR PERFORMANCE OF THIS
   SOFTWARE.
 */

#include "PluggableHardwareSerialNumber.h"
#include "avr/boot.h"

#define INTERNAL_SERIAL_START_ADDRESS  0x0E
#define INTERNAL_SERIAL_LENGTH 20

#if defined(USBCON)

PluggableHardwareSerialNumber_& PluggableHardwareSerialNumber()
{
	static PluggableHardwareSerialNumber_ obj;
	return obj;
}

int PluggableHardwareSerialNumber_::begin()
{
	return 0;
}

int PluggableHardwareSerialNumber_::getInterface(uint8_t* interfaceCount)
{
	return 0;
}

int PluggableHardwareSerialNumber_::getDescriptor(USBSetup& setup)
{
	return 0;
}

uint8_t PluggableHardwareSerialNumber_::getShortName(char *name)
{
	uint8_t SigReadAddress = INTERNAL_SERIAL_START_ADDRESS;
	for (uint8_t SerialCharNum = 0; SerialCharNum < INTERNAL_SERIAL_LENGTH; SerialCharNum++) {
		uint8_t SerialByte = boot_signature_byte_get(SigReadAddress);

		if (SerialCharNum & 0x01) {
			SerialByte >>= 4;
			SigReadAddress++;
		}

		SerialByte &= 0x0F;

		name[SerialCharNum] = (SerialByte >= 10) ? (('A' - 10) + SerialByte) : ('0' + SerialByte);
	}

	return INTERNAL_SERIAL_LENGTH;
}

bool PluggableHardwareSerialNumber_::setup(USBSetup& setup)
{
	return false;
}

PluggableHardwareSerialNumber_::PluggableHardwareSerialNumber_(void) : PluggableUSBModule(1, 1, epType)
{
	epType[0] = EP_TYPE_CONTROL;
	PluggableUSB().plug(this);
}


#endif /* if defined(USBCON) */
