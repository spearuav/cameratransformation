#!/usr/bin/env python
# -*- coding: utf-8 -*-
#
# Copyright SpearUAV 2021
# All rights reserved.
#
# __author__ = "Eden Ben Asulin"
#  ____
# / ___| _ __   ___  __ _ _ __ _   _  __ ___   __
# \___ \| '_ \ / _ \/ _` | '__| | | |/ _` \ \ / /
#  ___) | |_) |  __/ (_| | |  | |_| | (_| |\ V /
# |____/| .__/ \___|\__,_|_|   \__,_|\__,_| \_/
#
########################################################

import numpy as np
from scipy.spatial.transform import Rotation as R


def convert_gimbal_orientation_to_world(body_yaw, body_pitch, body_roll, gimbal_yaw, gimbal_pitch, gimbal_roll,
                                        is_degrees=True):
    Rw_b = R.from_rotvec(np.array([body_yaw, body_pitch, body_roll]), degrees=is_degrees)
    Rb_g = R.from_rotvec(np.array([gimbal_yaw, -gimbal_pitch, gimbal_roll]), degrees=is_degrees)
    Rw_g = Rw_b * Rb_g

    return Rw_g.as_euler('zxy')


if __name__ == '__main__':
    drone_body_yaw, drone_body_pitch, drone_body_roll = np.pi/2, 0, 0
    drone_gimbal_yaw, drone_gimbal_pitch, drone_gimbal_roll = 0, -np.pi/6, 0

    vector = convert_gimbal_orientation_to_world(drone_body_roll, drone_body_pitch, drone_body_yaw,
                                                 drone_gimbal_roll, drone_gimbal_pitch, drone_gimbal_yaw,
                                                 is_degrees=False)
    print(np.around(np.degrees(vector), 2))
