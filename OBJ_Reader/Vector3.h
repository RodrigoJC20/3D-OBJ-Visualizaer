#pragma once
#include <cmath>

class Vector3 {
public:
    float x, y, z;

    Vector3() : x(0.0f), y(0.0f), z(0.0f) {}

    Vector3(float x, float y, float z) : x(x), y(y), z(z) {}

    Vector3 normalize() const {
        float length = std::sqrt(x * x + y * y + z * z);
        return Vector3(x / length, y / length, z / length);
    }

    Vector3 cross(const Vector3& other) const {
        return Vector3(y * other.z - z * other.y, z * other.x - x * other.z, x * other.y - y * other.x);
    }

    float dot(const Vector3& other) const {
		return x * other.x + y * other.y + z * other.z;
	}

    Vector3 operator+(const Vector3& other) const {
        return Vector3(x + other.x, y + other.y, z + other.z);
    }

    Vector3 operator-(const Vector3& other) const {
        return Vector3(x - other.x, y - other.y, z - other.z);
    }

    Vector3 operator*(float scalar) const {
        return Vector3(x * scalar, y * scalar, z * scalar);
    }
};