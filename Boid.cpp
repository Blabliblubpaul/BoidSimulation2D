//
// Created by Paul on 23.03.2025.
//

#include "Boid.h"

#include <iostream>

#include "immintrin.h"
#include "Vector2.h"

#define WINDOW_WIDTH 640
#define WINDOW_HEIGHT 480

#define VISUAL_RANGE 75

#define SPEED 10

namespace BoidSimulation2D {
    constexpr float minDistance = 20;
    constexpr float separationFactor = 0.05f;

    constexpr float alignmentFactor = 0.05f;

    constexpr float centeringFactor = 0.005f;

    Boid::Boid(const Vector2& position, const Vector2& velocity, const Vector2& acceleration, const float maxSpeed, const float maxForce) {
        this->position = position;
        this->velocity = velocity;
        this->acceleration = acceleration;
        this->maxSpeed = maxSpeed;
        this->maxForce = maxForce;
    }

    void Boid::update(std::vector<Boid>& allBoids, const int boidAmount) {
        Vector2 move = Vector2::Zero;
        Vector2 avgVelocity = Vector2::Zero;
        Vector2 center = Vector2::Zero;

        int numNeighbors = 0;
        for (Boid& other : allBoids) {
            if (&other == this) {
                continue;
            }

            // Separation
            if (Vector2::distance(position, other.position) < minDistance) {
                move += position - other.position;
            }

            if (Vector2::distance(position, other.position) < VISUAL_RANGE) {
                // Alignment
                avgVelocity += other.velocity;

                // Cohesion
                center += other.position;

                numNeighbors++;
            }
        }

        // Separation
        move *= separationFactor;

        // Alignment
        if (numNeighbors > 0) {
            // Alignment
            avgVelocity /= static_cast<float>(numNeighbors);

            avgVelocity = (avgVelocity - velocity) * alignmentFactor;

            // Cohesion
            center /= static_cast<float>(numNeighbors);

            center = (center - position) * centeringFactor;
        }
        else {
            // Alignment
            avgVelocity = Vector2::Zero;

            // Cohesion
            center = Vector2::Zero;
        }

        acceleration = move + avgVelocity + center;


        velocity = limit(velocity + acceleration, 15);
        velocity += keepInBounds();

        position += velocity * (SPEED * 0.0167f);
    }

    Vector2 Boid::keepInBounds() const {
        constexpr float margin = 200;
        constexpr float turnFactor = 1;

        Vector2 velocity = Vector2::Zero;

        if (position.x < margin) {
            velocity.x += turnFactor;
        }
        else if (position.x > WINDOW_WIDTH - margin) {
            velocity.x -= turnFactor;
        }

        if (position.y < margin) {
            velocity.y += turnFactor;
        }
        else if (position.y > WINDOW_HEIGHT - margin) {
            velocity.y -= turnFactor;
        }

        return velocity;
    }

    Vector2 Boid::limit(const Vector2 vector, const float max) {
        if (vector.magnitude() > max) {
            return vector.normalized() * max;
        }

        return vector;
    }
} // BoidSimulation2D
