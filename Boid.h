//
// Created by Paul on 23.03.2025.
//

#ifndef BOID_H
#define BOID_H
#include <vector>

#include "Vector2.h"

namespace BoidSimulation2D {
    class Boid {
    public:
        Vector2 position;
        Vector2 velocity;
        Vector2 acceleration;
        float maxSpeed;
        float maxForce;

        Boid() : position(Vector2::Zero), velocity(Vector2::Zero), acceleration(Vector2::Zero),
                 maxSpeed(0), maxForce(0) {}

        Boid(const Vector2& position, const Vector2& velocity, const Vector2& acceleration, float maxSpeed,
             float maxForce);

        void update(std::vector<Boid>& allBoids);

    private:
        Vector2 separation(std::vector<Boid>& allBoids) const;

        Vector2 alignment(std::vector<Boid>& allBoids) const;

        Vector2 cohesion(std::vector<Boid>& allBoids) const;

        inline static Vector2 limit(Vector2 vector, float max);
    };
} // BoidSimulation2D

#endif //BOID_H
