#ifndef SDL_UTILS_SCENE_H
#define SDL_UTILS_SCENE_H

#include <ecs.h>
#include <SDL.h>

#include "su_camera.h"

typedef struct Scene {
    EcsSequentialSystem* update;
    EcsSequentialSystem* draw;
    EcsSequentialSystem* gui;
    Camera* camera;
    EcsWorld world;
    SDL_bool free_systems;
    SDL_bool free_camera;
    Uint8 r;
    Uint8 g;
    Uint8 b;
    Uint8 a;
} Scene;

void scene_init(Scene* scene,
                EcsWorld world, 
                Camera* camera, 
                EcsSequentialSystem* update, 
                EcsSequentialSystem* draw,
                EcsSequentialSystem* gui,
                SDL_bool free_systems,
                SDL_bool free_camera);

Scene* scene_create(EcsWorld world, 
                    Camera* camera, 
                    EcsSequentialSystem* update, 
                    EcsSequentialSystem* draw,
                    EcsSequentialSystem* gui,
                    SDL_bool free_systems,
                    SDL_bool free_camera);

void scene_free_resources(Scene* scene);
void scene_free(Scene* scene);
void scene_update(Scene* scene, float delta);
void scene_draw(Scene* scene, float delta);
SDL_bool scene_set_background(Scene* scene, Uint32 color);
Uint32 scene_get_background(Scene* scene);

void scene_push(Scene* scene);
void scene_change(Scene* scene);
Scene* scene_pop(bool free_scene);
Scene* scene_current(void);

#endif