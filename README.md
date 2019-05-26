# Tramway Display
## Description
Downloads and displays the departure times of the next 3 trams.
## Setup
### Build
Download the sources to your Raspberry Pi:
```
git clone https://github.com/c0dem4ster/bim31monitor_rpi0.git
```
Enter the source directory:
```
cd bim31monitor_rpi0
```
Build the binaries:
```
gcc -lm main.c lib/gfx/gfx.c
```
### Configure
Open up the Raspbian configuration dialog:
```
sudo raspi-config
```
Then enable `Interfacing Options > SPI` and disable `Advanced Options > Overscan`.  
To enable the display device drivers, create the file `/etc/modprobe.d/fbtft.conf` with the following content:
```
options fbtft_device name=fb_ili9341 gpios=reset:25,dc:24,led:18 speed=16000000 bgr=1 rotate=90 custom=1
```
To run the program at boot-time, add the following line to `/etc/rc.local` before the `exit` statement:
```
python3 <absolute source path>/loader.py
```
### Finish
Finally, reboot the Pi:
```
sudo reboot
```

## Integration
To use it with your own projects, you will need to add the following lines to your design file(s):
```vhdl
-- allows us to use BCD_TYPE
library work;
use work.typedef.all;
```
In the architecture head add:
```vhdl
component bin2bcd
  -- set bandwidth of conversion here
  generic(bin_width: integer := 32;
          dec_width: integer := 5);
  port(RESET_n: in std_logic;
        CLK    : in std_logic;
        BIN    : in std_logic_vector;
        BCD    : out BCD_TYPE;
        FIN    : out	std_logic);
end component;
```
And don't forget the port map in the architecture body!