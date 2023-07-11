import serial
import serial.tools.list_ports as ports
from sys import platform
from time import sleep

class SerialPort:

    def __init__(self, ser=serial.Serial()):
        self.ser = ser

    def __getListPorts__(self):
        if platform == "darwin":
            return [str(port).split(" ")[0] for port in ports.comports() if "usb" in str(port)]

        return [str(port).split(" ")[0] for port in ports.comports()]

    def readData(self):

        return self.ser.read(self.ser.in_waiting).decode().strip()

Sptest = SerialPort()
name = Sptest.__getListPorts__()[0]
baud = 9600
Sptest.ser = serial.Serial(port=name, baudrate=baud)

while True:
    print(Sptest.readData())
    sleep(0.067)
