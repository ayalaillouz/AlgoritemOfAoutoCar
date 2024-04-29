import numpy as np
import sys

class KalmanFilter:
    def __init__(self, dt, process_noise, measurement_noise):
        self.dt = dt
        self.F = np.array([[1, 0, dt, 0],
                           [0, 1, 0, dt],
                           [0, 0, 1, 0],
                           [0, 0, 0, 1]])
        self.H = np.array([[1, 0, 0, 0],
                           [0, 1, 0, 0]])
        self.Q = np.eye(4) * process_noise
        self.R = np.eye(2) * measurement_noise
        self.P = np.eye(4)

    def predict(self):
        self.x = np.dot(self.F, self.x)
        self.P = np.dot(self.F, np.dot(self.P, self.F.T)) + self.Q

    def update(self, z):
        y = z - np.dot(self.H, self.x)
        S = np.dot(self.H, np.dot(self.P, self.H.T)) + self.R
        K = np.dot(self.P, np.dot(self.H.T, np.linalg.inv(S)))
        self.x = self.x + np.dot(K, y)
        I = np.eye(4)
        self.P = np.dot(I - np.dot(K, self.H), self.P)

# Example of using the Kalman filter
input1 = float(sys.argv[1])
input2 = float(sys.argv[2])
input3 = float(sys.argv[3])
input4 = float(sys.argv[4])
input5 = float(sys.argv[5])
initial_state = np.array([0, 0, 0, 0])  # Initial state: x, y, vx, vy
process_noise = 0.1
measurement_noise = 0.1
dt = input1
kf = KalmanFilter(dt, process_noise, measurement_noise)
kf.x = initial_state

# Measurements of x, y position
measurements = np.array([[input2,input3],[input4,input5]])

# Run the Kalman filter
filtered_positions = []
for measurement in measurements:
    kf.predict()
    kf.update(measurement)
    filtered_positions.append(kf.x[:2])
for p in filtered_positions:
    print(" ".join(str(os) for os in p))
