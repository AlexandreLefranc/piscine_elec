# https://fabacademy.org/archives/2015/doc/makefile.html
# https://stackoverflow.com/questions/68876459/gnu-makefile-for-c-embedded
# https://unix.stackexchange.com/questions/144029/command-to-determine-ports-of-a-device-like-dev-ttyusb0

MCU			= atmega328p
F_CPU		= 16000000
PORT		= /dev/ttyUSB0
BAUDRATE	= 115200

CC		= avr-gcc
CFLAGS	=-mmcu=$(MCU) -Wall -Os -DF_CPU=$(F_CPU)


.PHONY: all
all: hex flash

.PHONY: hex
hex:
	$(CC) $(CFLAGS) -o main.bin main.c
	avr-objcopy -O ihex main.bin main.hex

.PHONY: flash
flash:
	avrdude -c arduino -p $(MCU) -P $(PORT) -b $(BAUDRATE) -U flash:w:main.hex

.PHONY: clean
clean:
	rm -rf main.bin
	rm -rf main.hex