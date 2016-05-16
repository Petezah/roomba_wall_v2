# roomba_wall_v2

An AVR program for ATTiny85 to transmit a virtual wall signal for an iRobot Roomba

## Folder layout

* /firmware
  * Source for the ATTiny85 firmware
* /hardware
  * Files describing the board layout, etc

## Building

### Prerequisites for "happy path":

* Raspberry Pi configured with BCM SPI enabled
* AVR-GCC installed
  *  Easiest way to get this is 'sudo apt-get install arduino'
* Jumpers to wire SPI bus of Raspberry Pi to the ISP pins of the ATTiny85 (details coming later)

### Steps

* cd firmware
* make fuse
* make install

NB: 'make fuse' will set the AVR up for an external oscillator.  It is better to do this step after the board is fully assembled.

## Layout

My prototype board layout is as follows:

![Breadboard layout for roomba_wall_v2 using ATTiny85]("https://github.com/Petezah/roomba_wall_v2/blob/develop/hardware/roomba_wall_v2_bb.png" "Breadboard layout for roomba_wall_v2")
