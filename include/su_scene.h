#ifndef SDL_UTILS_SCENE_H
#define SDL_UTILS_SCENE_H

#include <ecs.h>
#include <SDL.h>

#include "su_camera.h"

/**
    Defines a self contained game scene.

    \remark You can 'inherit' this via struct composition.
*/
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

/**
    Initializes a scene.

    \param scene The scene to initialize.
    \param world The world to be used by this scene.
    \param camera The camera to be used by this scene.
    \param update The update system to be used by this scene.
    \param draw The draw system to be used by this scene.
    \param gui The gui system to be used by this scene.
    \param free_systems Determines if freeing this scene also frees the
                        systems used by it.
    \param free_camera Determines if freeing this scene also frees the
                       camera used by it.
*/
void scene_init(Scene* scene,
                EcsWorld world, 
                Camera* camera, 
                EcsSequentialSystem* update, 
                EcsSequentialSystem* draw,
                EcsSequentialSystem* gui,
                SDL_bool free_systems,
                SDL_bool free_camera);

/**
    Allocates and initializes a scene. Returns NULL on failure.

    \param world The world to be used by this scene.
    \param camera The camera to be used by this scene.
    \param update The update system to be used by this scene.
    \param draw The draw system to be used by this scene.
    \param gui The gui system to be used by this scene.
    \param free_systems Determines if freeing this scene also frees the
                        systems used by it.
    \param free_camera Determines if freeing this scene also frees the
                       camera used by it.
*/
Scene* scene_create(EcsWorld world, 
                    Camera* camera, 
                    EcsSequentialSystem* update, 
                    EcsSequentialSystem* draw,
                    EcsSequentialSystem* gui,
                    SDL_bool free_systems,
                    SDL_bool free_camera);

/**
    Frees the resources specified by the scenes settings
    without freeing the scene itself.
*/
void scene_free_resources(Scene* scene);

/**
    Frees the resources specified by the scenes settings
    and frees the scene itself.
*/
void scene_free(Scene* scene);

/**
    Causes the scene to update.
*/
void scene_update(Scene* scene, float delta);

/**
    Causes the scene to draw.
*/
void scene_draw(Scene* scene, float delta);

/**
    Sets the background color used to clear any previous drawing. Defaults
    to black. Returns SDL_FALSE if there was a problem.
*/
SDL_bool scene_set_background(Scene* scene, Uint32 color);

/**
    Gets the current background color of the scene.
    Returns 0 if there was a problem.
*/
Uint32 scene_get_background(Scene* scene);

/**
    Pushes a scene to be the current scene.
*/
void scene_push(Scene* scene);

/**
    Pops and frees all scenes currently on the stack,
    then pushes the specified scene. Do not use if the scenes
    were not heap allocated, or if you don't want them freed.
*/
void scene_change(Scene* scene);

/**
    Pops the current scene from the stack, optionally freeing it.
*/
Scene* scene_pop(bool free_scene);

/**
    Gets the currently active scene.
*/
Scene* scene_current(void);

#endif