# Onion Omega2 UC1701 Library

### Description
This library enables the Omega2(+) to control a UC1701 based display via SPI. It contains many graphics-drawing and display-drawing functions. Due to the current state of the OnionIoT provided bit-banged SPI driver ([which has multiple issues](https://github.com/OnionIoT/spi-gpio-driver/issues)), drawing is extremely slow (1-2 FPS). Thus, this library is rather suited for displaying simple user interfaces, simple graphics or static pictures. 
