MCU=attiny85
AVRDUDEMCU=t85
SYSCLOCK=8000000
CC=/usr/bin/avr-gcc
CFLAGS=-g -Os -Wall -mcall-prologues -mmcu=$(MCU) -DF_CPU=$(SYSCLOCK) -I./
OBJ2HEX=/usr/bin/avr-objcopy
AVRDUDE=/usr/bin/avrdude
SOURCES=main.cpp roomba_send.cpp simple_ir.cpp
TARGET=roomba_wall_v2

all :
	$(CC) $(CFLAGS) $(SOURCES) -o $(TARGET)
	$(OBJ2HEX) -R .eeprom -O ihex $(TARGET) $(TARGET).hex
	rm -f $(TARGET)

install : all
	sudo gpio -g mode 22 out
	sudo gpio -g write 22 0
	sudo $(AVRDUDE) -p $(AVRDUDEMCU) -P /dev/spidev0.0 -c linuxspi -b 10000 -U flash:w:$(TARGET).hex
	sudo gpio -g write 22 1

noreset : all
	sudo $(AVRDUDE) -p $(AVRDUDEMCU) -P /dev/spidev0.0 -c linuxspi -b 10000 -U flash:w:$(TARGET).hex

fuse :
	sudo gpio -g mode 22 out
	sudo gpio -g write 22 0
	sudo $(AVRDUDE) -p $(AVRDUDEMCU) -P /dev/spidev0.0 -c linuxspi -b 10000 -U lfuse:w:0xfd:m -U hfuse:w:0xdf:m -U efuse:w:0xff:m
	sudo gpio -g write 22 1

clean :
	rm -f *.hex *.obj *.o
