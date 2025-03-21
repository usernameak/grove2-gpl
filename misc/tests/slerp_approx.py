from pyquaternion import Quaternion
import matplotlib.pyplot as plt
import numpy as np

q1 = Quaternion(axis=[1, 0, 0], angle=0)
q2 = Quaternion(axis=[1, 1, 1], angle=3.14159265)

t = np.arange(0, 1, 0.01)

ATTENUATION = 0.8228677
K           = 0.5855064

def lerp(a, b, val):
    return a * (1.0 - val) + b * val

def slerpCorrection(t, cosAlpha):
    factor = 1.0 - ATTENUATION * cosAlpha
    factor *= factor
    k = K * factor

    b = 2.0 * k
    c = -3.0 * k
    d = 1.0 + k

    return t * (t * (b * t + c) + d)

def slerpFast(q1, q2, t):
    cosAlpha = q1.x * q2.x + q1.y * q2.y + q1.z * q2.z + q1.w * q2.w
    if t < 0.5:
        tp = slerpCorrection(t, cosAlpha)
    else:
        tp = 1.0 - slerpCorrection(1.0 - t, cosAlpha)

    q = Quaternion(
        lerp(q1.w, q2.w, tp),
        lerp(q1.x, q2.x, tp),
        lerp(q1.y, q2.y, tp),
        lerp(q1.z, q2.z, tp),
    )

    return q.unit

def nlerp(q1, q2, t):
    q = Quaternion(
        lerp(q1.w, q2.w, t),
        lerp(q1.x, q2.x, t),
        lerp(q1.y, q2.y, t),
        lerp(q1.z, q2.z, t),
    )

    return q.unit
  
x = np.vectorize(lambda tn: Quaternion.slerp(q1, q2, tn).x)(t)
y = np.vectorize(lambda tn: Quaternion.slerp(q1, q2, tn).y)(t)
z = np.vectorize(lambda tn: Quaternion.slerp(q1, q2, tn).z)(t)
w = np.vectorize(lambda tn: Quaternion.slerp(q1, q2, tn).w)(t)
  
x1 = np.vectorize(lambda tn: slerpFast(q1, q2, tn).x)(t)
y1 = np.vectorize(lambda tn: slerpFast(q1, q2, tn).y)(t)
z1 = np.vectorize(lambda tn: slerpFast(q1, q2, tn).z)(t)
w1 = np.vectorize(lambda tn: slerpFast(q1, q2, tn).w)(t)
  
x2 = np.vectorize(lambda tn: nlerp(q1, q2, tn).x)(t)
y2 = np.vectorize(lambda tn: nlerp(q1, q2, tn).y)(t)
z2 = np.vectorize(lambda tn: nlerp(q1, q2, tn).z)(t)
w2 = np.vectorize(lambda tn: nlerp(q1, q2, tn).w)(t)
  
figure, axis = plt.subplots(2, 4)
  
axis[0, 0].plot(t, x)
axis[0, 0].plot(t, x1)
axis[0, 0].plot(t, x2)
axis[0, 0].set_title("X")

axis[0, 1].plot(t, x1 - x)
axis[0, 1].plot(t, x2 - x)
axis[0, 1].set_title("X error")
  
axis[0, 2].plot(t, y)
axis[0, 2].plot(t, y1)
axis[0, 2].plot(t, y2)
axis[0, 2].set_title("Y")

axis[0, 3].plot(t, y1 - y)
axis[0, 3].plot(t, y2 - y)
axis[0, 3].set_title("Y error")
  
axis[1, 0].plot(t, z)
axis[1, 0].plot(t, z1)
axis[1, 0].plot(t, z2)
axis[1, 0].set_title("Z")

axis[1, 1].plot(t, z1 - z)
axis[1, 1].plot(t, z2 - z)
axis[1, 1].set_title("Z error")
  
axis[1, 2].plot(t, w)
axis[1, 2].plot(t, w1)
axis[1, 2].plot(t, w2)
axis[1, 2].set_title("W")

axis[1, 3].plot(t, w1 - w)
axis[1, 3].plot(t, w2 - w)
axis[1, 3].set_title("W error")
  
plt.show()
