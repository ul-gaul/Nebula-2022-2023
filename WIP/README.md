
# Flight board 1.5

## Description of the flight computer 1.5:
This board is an updated version of the first flight controler with little extra. So basicly I copy the old desing that it was an arduino shield and made it a standalone board. All the sensor is part of the board too, so no more module.All this help to make a board much smaller and more reliable. In extra I add a latching circuit too arme the board. You need to hold the button 3sec to power up the circuit and same thing to power it off. All switching is made with an mosfet so no mecanical switching excluding the power button. So the vibration can't make or break a connection and this is why the push button have an latching circuit, too avoid a false triger. Moreover I add a circuit too datalog the data on an SD card,I made a test circuit to test the 2 pyro. The circuit pass a little current (40mA) in the fuse and we mesure the voltage after so we can test for a short or open fuse. We can use this same circuit after to valid an ignition. I also add a logic circuit too avoid to put main power in the pyro when we trigger the test. It need 2 mosfet to be activate to ignite the fuse. A buzzer and a led status is also added. The board is powerd by a usb or lipo 1S(3.7v) that it can be charge by usb on the board. The RFD900 is powered by usb if its available but we will not be able to use full power only on usb so this is for testing only, on normal condition we will use an lipo 3S(11.1v). The pyro is powered by an lipo 4S(14.8v).

## Update log
### 23/09/23
I add the possibility to use the RFD900 with the USB.

### 23/09/22
I can say that the schematic is now done but it will need to be verified to but sure that everything is ok and avoid poor mistake.
1.Redesing of the logic circuit protection to be more secure
2.Add a different batteries for the RFD900 so if the RFD900 drain it the pyro still have its own power.
3.In link with the second point, now the pyro is on 4s lipo (14.8v)

### 23/09/17
The schematic is almost done. Need to retink of some part of the logic part to protect the pyro cause it look like it can cause an oscilation (this part is not even up to date)
1.Add a buzzer.
2.Add poly fuse.
3.Add the logic circuit to protect the pyro. (see note on top)
4.Add latching circuit. (Hold 3s to power on/off)
5.Add many status leds. (one led can be placed externaly by a screw terminal)

This week I will try to list all the feature of this board, finalyze the schematic, add the data sheets of some ICs.
## Features
* Standalone board
* Powered by usb or lipo 1S
* Lipo charger in board
* Self test on igniter
* 2 ignitions circuits
* Gyro/Baro in board
* SD card for dataloging
* Latching circuit for powered the circuit
## Documentation
This is a list of documentation for the Ic

* [STM32F103C8](https://www.st.com/resource/en/datasheet/stm32f103c8.pdf) Main  microcontroller
* [ICM-20602](https://invensense.tdk.com/wp-content/uploads/2016/10/DS-000176-ICM-20602-v1.0.pdf) High Performance 6-Axis MEMS
* [BMP280](https://www.bosch-sensortec.com/media/boschsensortec/downloads/datasheets/bst-bmp280-ds001.pdf) Digital pressure sensor
* [L76L-M33](https://github.com/ul-gaul/Nebula-2022-2023/blob/cef41a131481a57f440abe9ede77973086518a58/WIP/Documentation/Quectel_L76_Series_Hardware_Design_V3.1.pdf) GNSS Module (GPS)
* [GT-0930RP2](https://github.com/ul-gaul/Nebula-2022-2023/blob/aa67e142a6133a87d8f8f1008be1e9982ea42536/WIP/Documentation/GT-0930RP2-14-Feb-2019.pdf) Buzzer
* [HM-10](https://github.com/ul-gaul/Nebula-2022-2023/blob/aa67e142a6133a87d8f8f1008be1e9982ea42536/WIP/Documentation/11.%20HM10%20BLE_FTDI.pdf)  BLE Module
* [TPS61201DRCR](https://www.ti.com/lit/ds/symlink/tps61201.pdf?ts=1695532721814&ref_url=https%253A%252F%252Fwww.ti.com%252Fproduct%252FTPS61201%252Fpart-details%252FTPS61201DRCR)  Low Input Voltage Synchronous Boost Converter
* [LM1085](https://www.ti.com/lit/ds/symlink/lm1085.pdf?ts=1695467476779&ref_url=https%253A%252F%252Fwww.ti.com%252Fproduct%252FLM1085%252Fpart-details%252FLM1085ISX-3.3%252FNOPB) 3-A Low Dropout Positive Regulators
* [max1898eub42+T](https://www.analog.com/media/en/technical-documentation/data-sheets/max1898.pdf) Linear Charger for Single-Cell Li+ Battery
* [LTC2954ITS8-1](https://www.analog.com/media/en/technical-documentation/data-sheets/2954fb.pdf) Pushbutton On/Off Controller with µP Interrup
* [CD74HC4051-EP](https://www.ti.com/lit/ds/symlink/cd74hc4051-ep.pdf?ts=1695467019480&ref_url=https%253A%252F%252Fwww.google.com%252F) Analog Multiplexer and Demultiplexer
* [SN74LVC2G02](https://www.ti.com/lit/ds/symlink/sn74lvc2g02.pdf?ts=1695487659279) Dual 2-Input Positive-NOR Gate
* [74HC86](https://www.ti.com/lit/ds/symlink/sn74hc86.pdf?ts=1695463772948&ref_url=https%253A%252F%252Fwww.google.de%252F) Quadruple 2-Input XOR Gates
* [SN74LVC2G08](https://www.ti.com/lit/ds/symlink/sn74lvc2g08.pdf?ts=1695451693627) Dual 2-Input Positive-AND Gate



## Authors
List of authors
- [@Luka Dupuis](https://github.com/bestrider14)

