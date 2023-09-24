
# Flight board 1.5

Work in progress of new design

## Description of the flight computer 1.5:
This board is an updated version of the first flight controler with little extra. So basicly I copy the old desing that it was an arduino shield and made it a standalone board. All the sensor is part of the board too, so no more module.All this help to make a board much smaller and more reliable. In extra I add a latching circuit too arme the board. You need to hold the button 3sec to power up the circuit and same thing to power it off. All switching is made with an mosfet so no mecanical switching excluding the power button. So the vibration can't make or break a connection and this is why the push button have an latching circuit, too avoid a false triger. Moreover I add a circuit too datalog the data on an SD card,I made a test circuit to test the 2 pyro. The circuit pass a little current (40mA) in the fuse and we mesure the voltage after so we can test for a short or open fuse. We can use this same circuit after to valid an ignition. I also add a logic circuit too avoid to put main power in the pyro when we trigger the test. It need 2 mosfet to be activate to ignite the fuse. A buzzer and a led status is also added. The board is powerd by a usb or lipo 1S(3.7v) that it can be charge by usb on the board. The RDF900 is powered by usb if its available but we will not be able to use full power only on usb so this is for testing only, on normal condition we will use an lipo 3S(11.1v). The pyro is powered by an lipo 4S(14.8v).

## Update log:

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
