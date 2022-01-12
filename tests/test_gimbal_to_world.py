import unittest
import csv

import numpy as np

from convert_gimbal_orientation import convert_gimbal_orientation_to_world

TEST_FILE = 'camera_to_world_test_vectors.csv'


class GimbalToWorldTest(unittest.TestCase):
    def test_gimbal_to_world(self):
        with open(TEST_FILE, mode='r', encoding='utf-8-sig') as test_file:
            reader = csv.DictReader(test_file)
            for row in reader:
                print(row)
                vector = convert_gimbal_orientation_to_world(float(row['body_yaw_deg']),
                                                             float(row['body_pitch_deg']),
                                                             float(row['body_roll_deg']),
                                                             float(row['gimbal_yaw_body']),
                                                             float(row['gimbal_pitch_body']),
                                                             float(row['gimbal_roll_body']))
                print(np.around(np.degrees(vector), 2))

        self.assertEqual(True, True)  # add assertion here


if __name__ == '__main__':
    unittest.main()
