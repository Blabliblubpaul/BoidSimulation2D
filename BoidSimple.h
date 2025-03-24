//
// Created by Paul on 23.03.2025.
//

#ifndef BOIDSIMPLE_H
#define BOIDSIMPLE_H
#include <vector>

#include "Vector2.h"

namespace BoidSimulation2D {
    class BoidSimple {
    public:
        Vector2 position;
        Vector2 velocity;
        Vector2 acceleration;
        float maxSpeed;
        float maxForce;

        BoidSimple() : position(Vector2::Zero), velocity(Vector2::Zero), acceleration(Vector2::Zero),
                 maxSpeed(0), maxForce(0) {}

        BoidSimple(const Vector2& position, const Vector2& velocity, const Vector2& acceleration, float maxSpeed,
             float maxForce);

        void update(std::vector<BoidSimple>& allBoidSimples);

    private:
        [[nodiscard]]
        Vector2 separation(std::vector<BoidSimple>& allBoidSimples) const;

        [[nodiscard]]
        Vector2 alignment(std::vector<BoidSimple>& allBoidSimples) const;

        [[nodiscard]]
        Vector2 cohesion(std::vector<BoidSimple>& allBoidSimples) const;

        [[nodiscard]]
        Vector2 keepInBounds() const;

        inline static Vector2 limit(Vector2 vector, float max);
    };
} // BoidSimpleSimulation2D

#endif //BOIDSIMPLE_H
