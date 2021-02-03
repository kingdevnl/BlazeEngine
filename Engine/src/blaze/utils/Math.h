#ifndef BLAZE_MATH_H
#define BLAZE_MATH_H

#define PI 3.141592653589793

inline float Min(float val, float min) {
    if (val < min) {
        val = min;
    }
    return val;
}

inline float Max(float val, float max) {
    if (val > max) {
        val = max;
    }
    return val;
}
inline float Clamp(float val, float minimum, float maximum) {
    val = Min(val, minimum);
    val = Max(val, maximum);
    return val;
}


inline float ToRadians(double degrees) {
    return (degrees * PI) / 180;
}

#endif //BLAZE_MATH_H
