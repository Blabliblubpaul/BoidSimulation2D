//
// Created by Paul on 23.03.2025.
//

#include "BoidSimple.h"

#include <iostream>

#include "Vector2.h"

#define WINDOW_WIDTH 640
#define WINDOW_HEIGHT 480

#define VISUAL_RANGE 75

#define SEPARATION_DISTANCE 50.0f
#define ALIGNMENT_RADIUS_SQUARED 1.0f
#define COHESION_RADIUS_SQUARED 1.0f

#define SPEED 10

namespace BoidSimulation2D {
    BoidSimple::BoidSimple(const Vector2& position, const Vector2& velocity, const Vector2& acceleration, const float maxSpeed,
               const float maxForce) {
        this->position = position;
        this->velocity = velocity;
        this->acceleration = acceleration;
        this->maxSpeed = maxSpeed;
        this->maxForce = maxForce;
    }

    void BoidSimple::update(std::vector<BoidSimple>& allBoidSimples) {
        const Vector2 vecSep = separation(allBoidSimples);
        const Vector2 vecAlign = alignment(allBoidSimples);
        const Vector2 vecCoh = cohesion(allBoidSimples);
        const Vector2 vecBounds = keepInBounds();

        acceleration = vecSep + vecAlign + vecCoh;

        velocity = limit(velocity + acceleration, 15);
        velocity += vecBounds;

        position += velocity * (SPEED * 0.0167f);
    }

    Vector2 BoidSimple::separation(std::vector<BoidSimple>& allBoidSimples) const {
        constexpr float minDistance = 20;
        constexpr float separationFactor = 0.05f;

        Vector2 move = Vector2::Zero;

        for (BoidSimple& other : allBoidSimples) {
            if (&other != this) {
                if (Vector2::distance(position, other.position) < minDistance) {
                    move += position - other.position;
                }
            }
        }

        return move * separationFactor;
    }

    Vector2 BoidSimple::alignment(std::vector<BoidSimple>& allBoidSimples) const {
        constexpr float alignmentFactor = 0.05f;

        Vector2 avgVelocity = Vector2::Zero;
        int numNeighbors = 0;

        for (BoidSimple& other : allBoidSimples) {
            if (&other == this) {
                continue;
            }

            if (Vector2::distance(position, other.position) < VISUAL_RANGE) {
                avgVelocity += other.velocity;
                numNeighbors++;
            }
        }

        if (numNeighbors > 0) {
            avgVelocity /= static_cast<float>(numNeighbors);

            return (avgVelocity - velocity) * alignmentFactor;
        }

        return Vector2::Zero;
    }

    Vector2 BoidSimple::cohesion(std::vector<BoidSimple>& allBoidSimples) const {
        constexpr float centeringFactor = 0.005f;

        Vector2 center = Vector2::Zero;
        int numNeighbors = 0;

        for (BoidSimple& other : allBoidSimples) {
            if (&other == this) {
                continue;
            }

            if (Vector2::distance(position, other.position) < VISUAL_RANGE) {
                center += other.position;

                numNeighbors++;
            }
        }

        if (numNeighbors > 0) {
            center /= static_cast<float>(numNeighbors);

            return (center - position) * centeringFactor;
        }

        return Vector2::Zero;
    }

    Vector2 BoidSimple::keepInBounds() const {
        constexpr float margin = 200;
        constexpr float turnFactor = 1;

        Vector2 velocity = Vector2::Zero;

        if (position.x < margin) {
            velocity.x += turnFactor;
        }

        if (position.x > WINDOW_WIDTH - margin) {
            velocity.x -= turnFactor;
        }

        if (position.y < margin) {
            velocity.y += turnFactor;
        }

        if (position.y > WINDOW_HEIGHT - margin) {
            velocity.y -= turnFactor;
        }

        return velocity;
    }

    Vector2 BoidSimple::limit(const Vector2 vector, const float max) {
        if (vector.magnitude() > max) {
            return vector.normalized() * max;
        }

        return vector;
    }
} // BoidSimpleSimulation2D
