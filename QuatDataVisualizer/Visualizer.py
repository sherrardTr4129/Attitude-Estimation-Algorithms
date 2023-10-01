from SerialManagerClass import SerialManager
import json
import time

class DataVisualizer:
    def __init__(self) -> None:
        """
        class constructor
        """
        self.serial_port = "/dev/ttyACM0"
        self.baud_rate = 115200
        self.ser_man = SerialManager(self.serial_port, self.baud_rate)

    def runViz(self):
        """
        visualization event loop manager. Gets new data
        from the Nicla Sense Me board via serial, and generates
        useful visualizations.
        """
        if(not self.ser_man.open()):
            print("could not open serial port {}!".format(self.serial_port))
            return
        
        while(True):
            # read a line from the serial port
            new_line_str = str(self.ser_man.read(), encoding='utf-8')

            # try to convert it to JSON
            try:
                new_line_json = json.loads(new_line_str)
            except json.JSONDecodeError:
                continue

            #TODO: do something with this data
            print(new_line_json)

if __name__ == "__main__":
    data_vis = DataVisualizer()
    data_vis.runViz()