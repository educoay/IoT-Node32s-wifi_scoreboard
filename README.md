# IoT-Node32s-wifi_scoreboard

A simple wireless scoreboard project concept using NodeMCU-32S.

## About the Project

* Scores are manipulated thru the browser by opening the NodeMCU's assigned IP address.

* This project uses the 74HC595 (shift register) to drive six (3 each team) 7-segments (42 pins)

* This project can be upscaled by using larger sets of 7-segments or LED Strips with MOSFET transistors and a much beefier power supply.

* WebGUI is not mobile-friendly (not responsive).

## Parts list

```
1 NodeMCU-32S

6 74HC595 Shift Register
6 seven segments (common cathode)

1 breadboard power supply (5v)
1 7v 2.5A power supply
3 prototyping breadboard
bunch of wires
```

## Schematic Diagram
https://www.digikey.com/schemeit/project/wifi-scoreboard-DMD2HC8401NG/

## Built with
Arduino IDE: https://www.arduino.cc/en/Main/Software

ShiftRegister74HC595 by Timo Denk

WiFiClient built-in library

ESP32WebServer from IOTSHARING.COM

WiFi by Pranav Cherukupalli

## Author

* **Jansen Ducusin** - *Initial work* - [Senducusin](https://github.com/senducusin)

## License

This project is licensed under the MIT License - see the [LICENSE.md](LICENSE.md) file for details
