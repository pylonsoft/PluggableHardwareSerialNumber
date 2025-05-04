# PluggableHardwareSerialNumber

Allow to use the hardware serial number of an AVR USB MCU for CDC projects.

If you connect multiple AVR-USB boards to a computer using the CDC serial
emulation you might have the problem to choose the correct serial device
in your application. The default Arduino code uses one serial number for
all compilations which doesn't help. Most if not all AVR USB boards
provide a unique serial number by the hardware.

## Usage

Use it in your code this way:

```

#include "PluggableHardwareSerialNumber.h"

void setup() {
	int c = PluggableHardwareSerialNumber().begin();
	Serial.begin(115200);
}

void loop() {
}

```

## Linux

If you connect a board with such code to a Linux computer you will see
the serial number with tools like `lsusb` (iSerial line).

You can then use the udev tool chain to have a fixed symbolic link to
your device. Create a file in the udev rules directory (p.e.
`/etc/udev/rules.d/95-myserial.rules`) containing something like this:

```
SUBSYSTEMS=="usb", ATTRS{idProduct}=="8036", ATTRS{idVendor}=="2341", ATTRS{serial}=="1234567890123456789F", SYMLINK+="ttyMyCustomDevice", OWNER="nobody", GROUP="nobody", MODE="0777"
```

Of course you have to adapt the values of the vendor ID, product ID and
serial number. Change the other fields too as applicable to your needs.
