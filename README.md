# Tramway Display
## Description
Downloads and displays the departure times of the next 3 trams.
## Hardware Setup
```
ILI9341    Raspberry Pi
━━━━━━━━┓ ┏━━━━━━━━━━━━
    LED ┃━┃ 12 (GPIO 18)
    SCK ┃━┃ 23 (GPIO 11)
   MISO ┃━┃ 21 (GPIO 9)
   MOSI ┃━┃ 19 (GPIO 10)
     CS ┃━┃ 24 (GPIO 8)
    RST ┃━┃ 22 (GPIO 25)
     DC ┃━┃ 18 (GPIO 24)
    VIN ┃━┃ 17 (3V3)
    GND ┃━┃ 20 (GND)
━━━━━━━━┛ ┗━━━━━━━━━━━━
```
## Software Configuration
### Build
Download the sources to your Raspberry Pi:
```bash
git clone --recursive https://github.com/c0dem4ster/bim31monitor_rpi0.git
```
Enter the source directory:
```bash
cd bim31monitor_rpi0
```
Build the binaries:
```bash
make
```
### Configure
Open up the Raspbian configuration dialog:
```bash
sudo raspi-config
```
Then enable `Interfacing Options > SPI` and disable `Advanced Options > Overscan`.

To enable the display device drivers, create the file `/etc/modprobe.d/fbtft.conf` with the following content:
```
options fbtft_device name=fb_ili9341 gpios=reset:25,dc:24,led:18 speed=16000000 bgr=1 rotate=90 custom=1
```

and the file `/etc/modules-load.d/fbtft.conf`, containing:
```
spi-bcm2835
fbtft_device
```

To run the program at boot-time, add the following line to `/etc/rc.local` before the `exit` statement:
```bash
nohup python3 <path of cloned repo>/bim31monitor_rpi0/loader.py &
con2fbmap 1 0
```

### Finish
Finally, reboot the Pi:
```bash
sudo reboot
```
