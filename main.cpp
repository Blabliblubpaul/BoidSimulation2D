#define SDL_MAIN_USE_CALLBACKS 1
#include <vector>
#include <SDL3/SDL.h>
#include <SDL3/SDL_main.h>

#include "Boid.h"

using namespace BoidSimulation2D;

#define SDL_HINT_RENDER_VSYNC "SDL_RENDER_VSYNC"

#define WINDOW_WIDTH 640
#define WINDOW_HEIGHT 480

#define HALF_WINDOW_WIDTH 320
#define HALF_WINDOW_HEIGHT 240

#define BOID_START_AMOUNT 22

static SDL_Window* window = nullptr;
static SDL_Renderer* renderer = nullptr;

static std::vector<Boid> boids;

int boidAmount = 0;

bool dead = false;

SDL_AppResult SDL_AppInit(void** appstate, int argc, char* argv[]) {
    if (!SDL_CreateWindowAndRenderer("Boid Simulation 2D", WINDOW_WIDTH, WINDOW_HEIGHT, NULL, &window, &renderer)) {
        SDL_Log("Couldn't create window and/or renderer: %s", SDL_GetError());
        return SDL_APP_FAILURE;
    }

    for (int i = 0; i < BOID_START_AMOUNT; i++) {
        for (int j = 0; j < BOID_START_AMOUNT; j++) {
            boidAmount++;

            boids.emplace_back(Vector2(HALF_WINDOW_WIDTH + i, HALF_WINDOW_HEIGHT + j),
       Vector2(5, 0), Vector2::Zero, 10, 10);
        }
    }

    SDL_SetRenderVSync(renderer, 1);

    return SDL_APP_CONTINUE;
}

SDL_AppResult SDL_AppEvent(void* appstate, SDL_Event* event) {
    if (event->type == SDL_EVENT_KEY_DOWN) {
        if (!dead && event->key.scancode == SDL_SCANCODE_SPACE) {
            dead = true;
        }
        else {
            return SDL_APP_SUCCESS;
        }
    }
    else if (event->type == SDL_EVENT_QUIT) {
        return SDL_APP_SUCCESS;
    }

    return SDL_APP_CONTINUE;
}

SDL_AppResult SDL_AppIterate(void* appstate) {
    if (!dead) {
        for (Boid& boid : boids) {
            boid.update(boids, boidAmount);
        }
    }

    SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255);
    SDL_RenderClear(renderer);

    SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);

    SDL_RenderDebugText(renderer, 5, 5, "Squash <SPACE>");

    if (dead) {
        SDL_SetRenderDrawColor(renderer, 255, 0, 0, 255);
    }

    SDL_FPoint* points = static_cast<SDL_FPoint*>(malloc(boidAmount * sizeof(SDL_FPoint)));
    int counter = 0;

    for (Boid& boid : boids) {
        *(points + counter) = SDL_FPoint {
            .x = boid.position.x,
            .y = boid.position.y
        };
        counter++;
    }

    SDL_RenderPoints(renderer, points, boidAmount);

    SDL_RenderPresent(renderer);

    return SDL_APP_CONTINUE;
}

void SDL_AppQuit(void* appstate, SDL_AppResult result) {}
