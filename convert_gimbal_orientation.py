#!/usr/bin/env python
# -*- coding: utf-8 -*-
#
# Copyright SpearUAV 2021
# All rights reserved.
#
#  ____
# / ___| _ __   ___  __ _ _ __ _   _  __ ___   __
# \___ \| '_ \ / _ \/ _` | '__| | | |/ _` \ \ / /
#  ___) | |_) |  __/ (_| | |  | |_| | (_| |\ V /
# |____/| .__/ \___|\__,_|_|   \__,_|\__,_| \_/
#
########################################################

import numpy as np
from scipy.spatial.transform import Rotation as R


def convert_gimbal_orientation_to_world(body_roll, body_pitch, body_yaw, gimbal_roll, gimbal_pitch, gimbal_yaw,
                                        is_degrees=True):
    Rw_b = R.from_euler('zxy', np.array([body_roll, body_pitch, body_yaw]), degrees=is_degrees)
    Rb_g = R.from_euler('zxy', np.array([gimbal_roll, gimbal_pitch, gimbal_yaw]), degrees=is_degrees)
    Rw_g = Rw_b * Rb_g

    return Rw_g.as_euler('zxy')


if __name__ == '__main__':
    drone_body_roll, drone_body_pitch, drone_body_yaw = np.pi/2, 0, 0
    drone_gimbal_roll, drone_gimbal_pitch, drone_gimbal_yaw = 0, -np.pi/6, 0

    vector = convert_gimbal_orientation_to_world(drone_body_roll, drone_body_pitch, drone_body_yaw,
                                                 drone_gimbal_roll, drone_gimbal_pitch, drone_gimbal_yaw,
                                                 is_degrees=False)
    print(np.around(np.degrees(vector), 2))
