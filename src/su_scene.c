#include <su_scene.h>

struct SceneManager {
    Scene** scenes;
    int capacity;
    int count;
};

static struct SceneManager scene_manager = { NULL, 0, 0 };

void scene_init(Scene* scene,
                EcsWorld world, 
                Camera* camera, 
                EcsSequentialSystem* update, 
                EcsSequentialSystem* draw,
                EcsSequentialSystem* gui,
                SDL_bool free_systems,
                SDL_bool free_camera) 
{
    scene->world = world;
    scene->camera = camera;
    scene->update = update;
    scene->draw = draw;
    scene->gui = gui;
    scene->free_systems = free_systems;
    scene->free_camera = free_camera;
    scene->r = 0;
    scene->g = 0;
    scene->b = 0;
    scene->a = 255;
}

Scene* scene_create(EcsWorld world, 
                    Camera* camera, 
                    EcsSequentialSystem* update, 
                    EcsSequentialSystem* draw,
                    EcsSequentialSystem* gui,
                    SDL_bool free_systems,
                    SDL_bool free_camera)
{
    Scene* scene = su_malloc(sizeof(*scene));
    if(scene == NULL)
        return NULL;

    scene_init(scene, world, camera, update, draw, gui, free_systems, free_camera);
    return scene;
}

void scene_free_resources(Scene* scene) {
    if(scene->free_systems) {
        ecs_system_free_resources((EcsSystem*)scene->update);
        ecs_system_free_resources((EcsSystem*)scene->draw);
        ecs_system_free_resources((EcsSystem*)scene->gui);
        free(scene->update);
        free(scene->draw);
        free(scene->gui);
    }
    if(scene->free_camera) {
        camera_free(scene->camera);
    }

    ecs_world_free(scene->world);
}

void scene_free(Scene* scene) {
    scene_free_resources(scene);
    su_free(scene);
}

void scene_update(Scene* scene, float delta) {
    ecs_system_update((EcsSystem*)scene->update, delta);
}

void scene_draw(Scene* scene, float delta) {
    // TODO: Add error handling

    Texture* render_target = camera_get_render_target(scene->camera);
    SDL_SetRenderTarget(scene->camera->renderer, render_target);
    SDL_SetRenderDrawColor(scene->camera->renderer, scene->r, scene->g, scene->b, scene->a);
    SDL_RenderClear(scene->camera->renderer);
    SDL_RenderSetViewport(scene->camera->renderer, NULL);

    ecs_system_update((EcsSystem*)scene->draw, delta);

    SDL_SetRenderTarget(scene->camera->renderer, NULL);
    SDL_SetRenderDrawColor(scene->camera->renderer, scene->r, scene->g, scene->b, scene->a);
    SDL_RenderClear(scene->camera->renderer);
    SDL_RenderSetViewport(scene->camera->renderer, scene->camera->viewport);

    Point size = camera_get_size(scene->camera);

    SDL_RenderCopyEx(scene->camera->renderer, 
                     render_target, 
                     &(Rectangle){ 0, 0, size.x, size.y }, 
                     &(Rectangle){ 0, 0, scene->camera->viewport->w, scene->camera->viewport->h }, 
                     camera_get_rotation(scene->camera), 
                     NULL, 
                     SDL_FLIP_NONE);

    ecs_system_update((EcsSystem*)scene->gui, delta);

    SDL_RenderPresent(scene->camera->renderer);
}

SDL_bool scene_set_background(Scene* scene, Uint32 color) {
    SDL_PixelFormat* format = SDL_AllocFormat(scene->camera->pixel_format);
    if(format == NULL)
        return SDL_FALSE;

    SDL_GetRGBA(color, format, &scene->r, &scene->g, &scene->b, &scene->a);

    SDL_FreeFormat(format);
    return SDL_TRUE;
}

Uint32 scene_get_background(Scene* scene) {
    SDL_PixelFormat* format = SDL_AllocFormat(scene->camera->pixel_format);
    if(format == NULL)
        return 0;

    Uint32 pixel = SDL_MapRGBA(format, scene->r, scene->g, scene->b, scene->a);

    SDL_FreeFormat(format);
    return pixel;
}

void scene_push(Scene* scene) {
    ECS_ARRAY_RESIZE(scene_manager.scenes, scene_manager.capacity, scene_manager.count+1, sizeof(Scene));
    scene_manager.scenes[scene_manager.count++] = scene;
}

void scene_change(Scene* scene) {
    while(scene_manager.count > 0)
        scene_pop(true);
    scene_push(scene);
}


Scene* scene_pop(bool free_scene) {
    Scene* scene = scene_manager.scenes[--scene_manager.count];
    if(free_scene)
        scene_free(scene);
    return scene;
}

Scene* scene_current(void) {
    if(scene_manager.count == 0)
        return NULL;
    return scene_manager.scenes[scene_manager.count - 1];
}