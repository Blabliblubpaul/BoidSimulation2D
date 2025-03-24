//
// Created by Paul on 23.03.2025.
//

#ifndef VECTOR2_H
#define VECTOR2_H

#include <cmath>

namespace BoidSimulation2D {
    struct Vector2 {
        static const Vector2 Zero;
        static const Vector2 One;
        static const Vector2 UnitX;
        static const Vector2 UnitY;

        float x;
        float y;

        Vector2() : x(0), y(0) {}

        constexpr  explicit Vector2(const float value) {
            x = y = value;
        }

        constexpr Vector2(const float x, const float y) {
            this->x = x;
            this->y = y;
        }

        [[nodiscard]]
        float magnitudeSquared() const {
            return x * x + y * y;
        }

        [[nodiscard]]
        float magnitude() const {
            return sqrtf(magnitudeSquared());
        }

        [[nodiscard]]
        Vector2 normalized() const {
            const float magnitude = this->magnitude();

            if (magnitude == 0) {
                return Zero;
            }

            return {x / magnitude, y / magnitude};
        }

        [[nodiscard]]
        float dot(const Vector2& other) const {
            return this->x * other.x + this->y * other.y;
        }

        [[nodiscard]]
        Vector2 operator+(const Vector2& other) const {
            return {x + other.x, y + other.y};
        }
        void operator+=(const Vector2& other) {
            x += other.x;
            y += other.y;
        }

        [[nodiscard]]
        Vector2 operator-(const Vector2& other) const {
            return {x - other.x, y - other.y};
        }
        void operator-=(const Vector2& other) {
            x -= other.x;
            y -= other.y;
        }

        [[nodiscard]]
        Vector2 operator*(const float scalar) const {
            return {x * scalar, y * scalar};
        }
        void operator*=(const float scalar) {
            x *= scalar;
            y *= scalar;
        }

        [[nodiscard]]
        Vector2 operator/(const float scalar) const {
            return {x / scalar, y / scalar};
        }
        void operator/=(const float scalar) {
            x /= scalar;
            y /= scalar;
        }

        [[nodiscard]]
        static float distance(const Vector2& a, const Vector2& b) {
            return (b - a).magnitude();
        }

        [[nodiscard]]
        static float distanceSquared(const Vector2& a, const Vector2& b) {
            return (b - a).magnitudeSquared();
        }
    };
} // BoidSimulation2D

#endif // VECTOR2_H
