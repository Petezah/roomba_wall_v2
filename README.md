# roomba_wall_v2

An AVR device, based on ATTiny85, to transmit a virtual wall signal for an iRobot Roomba

<img src="https://github.com/Petezah/roomba_wall_v2/blob/master/roomba_wall_v2.jpg"/>

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
* Jumpers to wire SPI bus of Raspberry Pi to the ISP pins on the finished board

### Steps

#### hardware

* Order a board based on the files in https://github.com/Petezah/roomba_wall_v2/tree/master/hardware/roomba_wall_v2
  * Alternately, order one directly from OSH Park here: https://oshpark.com/shared_projects/zFWYzgg5
* Purchase parts from [Mouser electronics](http://mouser.com) using the current BOM
  * Use the ones with "mouser" in their filenames
  * NB: The DC jack in the current BOM is incorrect
* Assemble the board--parts are all marked on the silkscreen

#### firmware

* Hook up the ISP pins on the assembled board to your Raspberry PI as follows:
  * ISP Pin 1 --> Raspberry Pi Pin 21 (MISO)
  * ISP Pin 2 --> Raspberry Pi Pin 17 (3.3V)
  * ISP Pin 3 --> Raspberry Pi Pin 23 (SCK)
  * ISP Pin 4 --> Raspberry Pi Pin 19 (MOSI)
  * ISP Pin 5 --> Raspberry Pi Pin 15 (GPIO22)
  * ISP Pin 6 --> Raspberry Pi Pin 25 (GND)
* Execute the following on the Raspberry Pi command line
  * cd firmware
  * make fuse
  * make install
