#ifndef SAMPLER_H
#define SAMPLER_H
#include <random>
#include <cstdint>
#include "Vector2.h"
#include "Vector3.h"


std::random_device rnd_dev;
std::mt19937 mt(rnd_dev());
std::uniform_real_distribution<float> rand_dist(0, 1);
inline float rnd() {
    return rand_dist(mt);
}
inline float rnd2() {
    return 2.0f * rnd() - 1.0f;
}


std::uniform_int_distribution<> randint_dist(0, 10000);
inline int rndint() {
    return randint_dist(mt);
}


uint64_t msws_x = rnd_dev(), msws_w = 0, msws_s = 0xb5ad4eceda1ce2a9;
inline static uint32_t msws() {
    msws_x *= msws_x;
    msws_x += (msws_w += msws_s);
    return msws_x = (msws_x >> 32) | (msws_x << 32);
}
inline static float msws_rnd() {
    return (double)(msws()) / UINT32_MAX;
}
inline static float msws_rnd2() {
    return 2.0f * msws_rnd() - 1.0f;
}

inline Vector2 randVec2() {
    return Vector2(rnd2(), rnd2());
}


inline Vector2 randVec2(float xmin, float xmax, float ymin, float ymax) {
    return Vector2(xmin + rnd() * (xmax - xmin), ymin + rnd() * (ymax - ymin));
}


inline Vector3 randVec3() {
    return Vector3(rnd2(), rnd2(), rnd2());
}


inline Vector3 randVec3(float xmin, float xmax, float ymin, float ymax, float zmin, float zmax) {
    return Vector3(xmin + rnd() * (xmax - xmin), ymin + rnd() * (ymax - ymin), zmin + rnd() * (zmax - zmin));
}


inline Vector3 random_in_unitSphere() {
    Vector3 v;
    do {
        v = randVec3();
    } while (v.LengthSq() > 1.0f);
    return v;
}
inline Vector3 random_in_unitHemisphere(const Vector3& right, const Vector3& forward, const Vector3& up) {
    float x, y, z;
    Vector3 v;
    do {
        x = rnd2();
        y = rnd();
        z = rnd2();
        v = x * right + y * up + z * forward;
    } while (v.LengthSq() > 1.0f);
    return v;
};

inline Vector3 random_in_unitDisk(const Vector3& right, const Vector3& up) {
    Vector3 v;
    do {
        v = rnd2() * right + rnd2() * up;
    } while (v.LengthSq() > 1.0);
    return v;
}

inline Vector3 random_in_unitAstroid(const Vector3& right, const Vector3& up) {
    Vector3 v;
    float x;
    float y;
    do {
        x = rnd2();
        y = rnd2();
        v = x * right + y * up;
    } while (std::pow(x, 2.0f / 3.0f) + std::pow(y, 2.0f / 3.0f) > 1.0f);
    return v;
}

#endif