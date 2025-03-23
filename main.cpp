#define SDL_MAIN_USE_CALLBACKS 1
#include <vector>
#include <SDL3/SDL.h>
#include <SDL3/SDL_main.h>

#include "Boid.h"

using namespace BoidSimulation2D;

#define WINDOW_WIDTH 640
#define WINDOW_HEIGHT 480

#define HALF_WINDOW_WIDTH 320
#define HALF_WINDOW_HEIGHT 240

#define BOID_START_AMOUNT 10

static SDL_Window* window = nullptr;
static SDL_Renderer* renderer = nullptr;

static std::vector<Boid> boids;

SDL_AppResult SDL_AppInit(void** appstate, int argc, char* argv[]) {
    if (!SDL_CreateWindowAndRenderer("Boid Simulation 2D", WINDOW_WIDTH, WINDOW_HEIGHT, NULL, &window, &renderer)) {
        SDL_Log("Couldn't create window and/or renderer: %s", SDL_GetError());
        return SDL_APP_FAILURE;
    }

    for (int i = 0; i < BOID_START_AMOUNT; i++) {
        boids.emplace_back(Vector2(HALF_WINDOW_WIDTH + 5 * i, HALF_WINDOW_HEIGHT + 5 * i),
            Vector2(5, 0), Vector2::Zero, 10, 10);
    }

    return SDL_APP_CONTINUE;
}

SDL_AppResult SDL_AppEvent(void* appstate, SDL_Event* event) {
    if (event->type == SDL_EVENT_KEY_DOWN ||
        event->type == SDL_EVENT_QUIT) {
        return SDL_APP_SUCCESS;
        }

    return SDL_APP_CONTINUE;
}

SDL_AppResult SDL_AppIterate(void* appstate) {
    for (Boid& boid : boids) {
        boid.update(boids);
    }

    SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255);
    SDL_RenderClear(renderer);

    SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);

    for (Boid& boid : boids) {
        SDL_RenderPoint(renderer, boid.position.x, boid.position.y);
    }

    SDL_RenderPresent(renderer);

    return SDL_APP_CONTINUE;
}

/* This function runs once at shutdown. */
void SDL_AppQuit(void* appstate, SDL_AppResult result) {}
