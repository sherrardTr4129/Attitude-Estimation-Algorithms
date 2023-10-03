from SerialManagerClass import SerialManager
from scipy.spatial.transform import Rotation
import matplotlib.animation as animation
import matplotlib.pyplot as plt
import json
import time
import copy

class DataVisualizer:
    def __init__(self) -> None:
        """
        class constructor
        """
        # serial communication members
        self.serial_port = "/dev/ttyACM0"
        self.baud_rate = 115200
        self.ser_man = SerialManager(self.serial_port, self.baud_rate)      

        # matplot lib class members
        self.fig = plt.figure()
        self.gt_plot = self.fig.add_subplot(121, projection='3d')
        self.est_plot = self.fig.add_subplot(122, projection='3d')

        # points to rotate for visualization purposes
        self.point_dict = dict()
        self.point_dict["top_right"] = [0.5, 0.5, 0]
        self.point_dict["top_left"] = [-0.5, 0.5, 0]
        self.point_dict["bottom_right"] = [0.5, -0.5, 0]
        self.point_dict["bottom_left"] = [-0.5, -0.5, 0]
        self.point_dict["local_x"] = [1, 0, 0]
        self.point_dict["local_y"] = [0, 1, 0]
        self.point_dict["local_z"] = [0, 0, 1]

    def performRotation(self, rotation):
        """
        a helper function that performs a given rotation
        on a copy of the non-oriented visualization box points.

        :param rotation: the Rotation class instance to apply to 
        our visualization box points

        :return: a copy of our visualization box points, rotated by
        the provided rotation.
        """
        point_dict_copy = copy.deepcopy(self.point_dict)

        point_dict_copy["top_right"] = rotation.apply(point_dict_copy["top_right"])
        point_dict_copy["top_left"] = rotation.apply(point_dict_copy["top_left"])
        point_dict_copy["bottom_right"] = rotation.apply(point_dict_copy["bottom_right"])
        point_dict_copy["bottom_left"] = rotation.apply(point_dict_copy["bottom_left"])
        point_dict_copy["local_x"] = rotation.apply(point_dict_copy["local_x"])
        point_dict_copy["local_y"] = rotation.apply(point_dict_copy["local_y"])
        point_dict_copy["local_z"] = rotation.apply(point_dict_copy["local_z"])

        return point_dict_copy

    def animationCallback(self, i):
        """
        animation callback for generating live
        orientation visual representations.

        :param i: animation frame index (not used here)
        """
        
        # read a line from the serial port
        new_line_str = str(self.ser_man.read(), encoding='utf-8')

        # try to convert it to JSON
        try:
            new_line_json = json.loads(new_line_str)
        except json.JSONDecodeError:
            return

        # extract quaternion data and ingest into Rotation object
        try:
            gt_quat = new_line_json["ground_truth_quat"]
            est_quat = new_line_json["estimated_quat"]
            gt_rot = Rotation.from_quat([gt_quat["x"], gt_quat["y"], gt_quat["z"], gt_quat["w"]])
            est_rot = Rotation.from_quat([est_quat["x"], est_quat["y"], est_quat["z"], est_quat["w"]])
        except KeyError:
            return
        
        # clear plots
        self.gt_plot.clear()
        self.est_plot.clear()

        # rotate visualization component
        gt_box = self.performRotation(gt_rot)
        est_box = self.performRotation(est_rot)

        # extract visual marker points
        gt_tr = gt_box["top_right"]
        gt_br = gt_box["bottom_right"]
        gt_tl = gt_box["top_left"]
        gt_bl = gt_box["bottom_left"]
        gt_x = gt_box["local_x"]
        gt_y = gt_box["local_y"]
        gt_z = gt_box["local_z"]

        est_tr = est_box["top_right"]
        est_br = est_box["bottom_right"]
        est_tl = est_box["top_left"]
        est_bl = est_box["bottom_left"]
        est_x = est_box["local_x"]
        est_y = est_box["local_y"]
        est_z = est_box["local_z"]

        # plot modified visual marker points
        self.gt_plot.plot([gt_tr[0], gt_tl[0]], [gt_tr[1], gt_tl[1]], [gt_tr[2], gt_tl[2]], color='black') # top right to top left
        self.gt_plot.plot([gt_tl[0], gt_bl[0]], [gt_tl[1], gt_bl[1]], [gt_tl[2], gt_bl[2]], color='black') # top left to bottom left
        self.gt_plot.plot([gt_bl[0], gt_br[0]], [gt_bl[1], gt_br[1]], [gt_bl[2], gt_br[2]], color='black') # bottom left to bottom right
        self.gt_plot.plot([gt_br[0], gt_tr[0]], [gt_br[1], gt_tr[1]], [gt_br[2], gt_tr[2]], color='black') # bottom right to top right
        self.gt_plot.plot([0, gt_x[0]], [0, gt_x[1]], [0, gt_x[2]]) # local frame x axis
        self.gt_plot.plot([0, gt_y[0]], [0, gt_y[1]], [0, gt_y[2]]) # local frame y axis
        self.gt_plot.plot([0, gt_z[0]], [0, gt_z[1]], [0, gt_z[2]]) # local frame z axis
        self.gt_plot.text(gt_x[0], gt_x[1], gt_x[2], "X_loc") # local X frame label
        self.gt_plot.text(gt_y[0], gt_y[1], gt_y[2], "Y_loc") # local Y frame label
        self.gt_plot.text(gt_z[0], gt_z[1], gt_z[2], "Z_loc") # local Z frame label

        self.est_plot.plot([est_tr[0], est_tl[0]], [est_tr[1], est_tl[1]], [est_tr[2], est_tl[2]], color='black') # top right to top left
        self.est_plot.plot([est_tl[0], est_bl[0]], [est_tl[1], est_bl[1]], [est_tl[2], est_bl[2]], color='black') # top left to bottom left
        self.est_plot.plot([est_bl[0], est_br[0]], [est_bl[1], est_br[1]], [est_bl[2], est_br[2]], color='black') # bottom left to bottom right
        self.est_plot.plot([est_br[0], est_tr[0]], [est_br[1], est_tr[1]], [est_br[2], est_tr[2]], color='black') # bottom right to top right
        self.est_plot.plot([0, est_x[0]], [0, est_x[1]], [0, est_x[2]]) # local frame x axis
        self.est_plot.plot([0, est_y[0]], [0, est_y[1]], [0, est_y[2]]) # local frame y axis
        self.est_plot.plot([0, est_z[0]], [0, est_z[1]], [0, est_z[2]]) # local frame z axis
        self.est_plot.text(est_x[0], est_x[1], est_x[2], "X_loc") # local X frame label
        self.est_plot.text(est_y[0], est_y[1], est_y[2], "Y_loc") # local Y frame label
        self.est_plot.text(est_z[0], est_z[1], est_z[2], "Z_loc") # local Z frame label

        # set axis limits
        self.gt_plot.set_xlim(-1, 1)
        self.gt_plot.set_ylim(-1, 1)
        self.gt_plot.set_zlim(-1, 1)
        self.est_plot.set_xlim(-1, 1)
        self.est_plot.set_ylim(-1, 1)
        self.est_plot.set_zlim(-1, 1)

        # turn off tick labels
        self.gt_plot.set_zticklabels([])
        self.gt_plot.set_yticklabels([])
        self.gt_plot.set_xticklabels([])
        self.est_plot.set_zticklabels([])
        self.est_plot.set_yticklabels([])
        self.est_plot.set_xticklabels([])

        # set axis labels
        self.gt_plot.set_xlabel('X global frame')
        self.gt_plot.set_ylabel('Y global frame')
        self.gt_plot.set_zlabel('Z global frame')
        self.est_plot.set_xlabel('X global frame')
        self.est_plot.set_ylabel('Y global frame')
        self.est_plot.set_zlabel('Z global frame')

        # set plot titles
        self.gt_plot.set_title("Ground Truth Orientation")
        self.est_plot.set_title("Estimated Orientation")
    
    def runViz(self):
        """
        visualization event loop intialization function.
        """

        # try to open serial port
        if(not self.ser_man.open()):
            raise Exception("could not open serial port {}!".format(self.serial_port))
        
        # register animation callback function
        self.anim = animation.FuncAnimation(self.fig, self.animationCallback, interval=1)
        plt.show()
        return self.anim

if __name__ == "__main__":
    data_vis = DataVisualizer()
    data_vis.runViz()