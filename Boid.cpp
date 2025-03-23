//
// Created by Paul on 23.03.2025.
//

#include "Boid.h"

#include "Vector2.h"

#define SEPARATION_RADIUS_SQUARED 1.0f
#define ALIGNMENT_RADIUS_SQUARED 1.0f
#define COHESION_RADIUS_SQUARED 1.0f

namespace BoidSimulation2D {
    Boid::Boid(const Vector2& position, const Vector2& velocity, const Vector2& acceleration, const float maxSpeed,
               const float maxForce) {
        this->position = position;
        this->velocity = velocity;
        this->acceleration = acceleration;
        this->maxSpeed = maxSpeed;
        this->maxForce = maxForce;
    }

    void Boid::update(std::vector<Boid>& allBoids) {
        const Vector2 vecSep = separation(allBoids);
        const Vector2 vecAlign = alignment(allBoids);
        const Vector2 vecCoh = cohesion(allBoids);

        acceleration = vecSep + vecAlign + vecCoh;

        velocity += acceleration;
        velocity = limit(velocity, maxSpeed);

        position += velocity;
    }

    Vector2 Boid::separation(std::vector<Boid>& allBoids) const {
        Vector2 steer = Vector2::Zero;
        int count = 0;

        for (Boid& other : allBoids) {
            if (const float distSquared = Vector2::distanceSquared(position, other.position);
                distSquared > 0 && distSquared < SEPARATION_RADIUS_SQUARED) {

                const Vector2 diff = position - other.position.normalized();
                steer += diff;
                count++;
            }
        }

        if (count > 0) {
            steer *= 1.0f / static_cast<float>(count);
        }

        return  limit(steer, maxForce);
    }

    Vector2 Boid::alignment(std::vector<Boid>& allBoids) const {
        Vector2 avgVelocity = Vector2::Zero;
        int count = 0;

        for (Boid& other : allBoids) {
            if (const float distSquared = Vector2::distanceSquared(position, other.position);
                distSquared > 0 && distSquared < ALIGNMENT_RADIUS_SQUARED) {

                avgVelocity += other.velocity;
                count++;
            }
        }

        if (count > 0) {
            avgVelocity *= 1.0f / static_cast<float>(count);
        }

        return limit(avgVelocity - velocity, maxForce);
    }

    Vector2 Boid::cohesion(std::vector<Boid>& allBoids) const {
        Vector2 centerMass = Vector2::Zero;
        int count = 0;

        for (Boid& other : allBoids) {
            if (const float distSquared = Vector2::distanceSquared(position, other.position);
                distSquared > 0 && distSquared < COHESION_RADIUS_SQUARED) {

                centerMass += other.position;
                count++;
            }
        }

        if (count > 0) {
            centerMass *= 1.0f / static_cast<float>(count);
            return limit(centerMass - position, maxForce);
        }

        return  Vector2::Zero;
    }

    Vector2 Boid::limit(const Vector2 vector, const float max) {
        if (vector.magnitude() > max) {
            return vector.normalized() * max;
        }

        return vector;
    }
} // BoidSimulation2D
