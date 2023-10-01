#!/usr/bin/python

import serial

class SerialManager:
    """
    A class to manage a given serial connetion
    """
    def __init__(self, port, baud):
        """
        class ctor
        :param port: the serial port to manage
        :param baud: the baud rate of the serial connection
        """
        self.port = port
        self.baud = baud
        self.serObj = None

    def open(self) -> bool:
        """
        open the provided serial port at the provided baud.
        :return res: the success/failure of the open operation
        """
        # construct serial object
        serObj = serial.Serial()

        # set individual object fields
        serObj.port = self.port
        serObj.baudrate = self.baud
        serObj.byteSize = serial.EIGHTBITS
        serObj.parity = serial.PARITY_NONE
        serObj.stopbits = serial.STOPBITS_ONE

        # attempt to open port
        try:
            serObj.open()
        except Exception as err:
            print("error opening serial port: %s" % err)

        # check if serial is open
        res = serObj.isOpen()

        if(res):
            self.serObj = serObj
            return res
        else:
            self.serObj = None
            return res

    def read(self) -> bytes:
        """
        reads a line from the serial interface.
        :return lineFromSer: the line read from the serial interface.
        """
        # try to read from the serial object
        lineFromSer = self.serObj.readline()

        return lineFromSer

    def close(self) -> None:
        """
        close the serial port.
        """
        # close the serial port
        self.serObj.close()
