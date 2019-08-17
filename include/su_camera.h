#ifndef SDL_UTILS_CAMERA_H
#define SDL_UTILS_CAMERA_H

#include <SDL.h>
#include "su_data_types.h"
#include "su_utils.h"

typedef struct Camera {
    Rectangle view;
    double rotation;
    Rectangle* viewport;
    SDL_Renderer* renderer;
    Texture* render_target;
    Uint32 pixel_format;
} Camera;

/**
    Initializes a Camera allocated by the caller.

    \param camera The camera object to initialize.
    \param renderer The renderer for the camera to use.
    \param width The size of the view in the game world.
    \param height The height of the view in the game world.
    \param viewport A pointer to a rectangle that holds the bounds of the game window that is drawn to.
    \param pixel_format one of the enumerated values in SDL_PixelFormatEnum. Used to create a render target.
    \return SDL_TRUE on success, SDL_FALSE otherwise. Get the error using SDL_GetError.
*/
SDL_bool camera_init(Camera* camera, SDL_Renderer* renderer, int width, int height, Rectangle* viewport, Uint32 pixel_format);

/**
    Allocates and initializes a new Camera.

    \param renderer The renderer for the camera to use.
    \param width The size of the view in the game world.
    \param height The height of the view in the game world.
    \param viewport A pointer to a rectangle that holds the bounds of the game window that is drawn to.
    \param pixel_format One of the enumerated values in SDL_PixelFormatEnum. 
                        Used to create a render target.
    \return Allocated camera on success, NULL otherwise. Get the error using SDL_GetError.
*/
Camera* camera_create(SDL_Renderer* renderer, int width, int height, Rectangle* viewport, Uint32 pixel_format);

/**
    Frees the resources used by the camera, without freeing the camera itself.
*/
static inline void camera_free_resources(Camera* camera);

/**
    Frees the resources used by the camera, then frees the camera.
*/
static inline void camera_free(Camera* camera);

/**
    Moves the camera in the game world by the specified offset.
*/
static inline void camera_move(Camera* camera, Point offset);

/**
    Rotates the camera by the specified angle in degrees.

    \remark If the cameras rotation is 45, and delta_degrees is 45, the result 
            will be 90.
*/
static inline void camera_rotate(Camera* camera, double delta_degrees);

/**
    Moves the camera so that its center is located at the specified position
    in the game world.
*/
static inline void camera_lookat(Camera* camera, Point position);

/**
    Moves the camera so that its top-left corner is located at the specified 
    position in the game world.
*/
static inline void camera_set_position(Camera* camera, Point position);

/**
    Moves the camera so that its left edge is at the specified x coordinate
    in the game world.
*/
static inline void camera_set_x(Camera* camera, int x);

/**
    Moves the camera so that its top edge is at the specified y coordinate
    in the game world.
*/
static inline void camera_set_y(Camera* camera, int y);

/**
    Sets the size of the camera in the game world.
    Do not call this when drawing to the cameras render target.
*/
SDL_bool camera_set_size(Camera* camera, Point size);

/**
    Sets the width of the camera in the game world.
    Do not call this when drawing to the cameras render target.
*/
SDL_bool camera_set_width(Camera* camera, int width);

/**
    Sets the height of the camera in the game world.
    Do not call this when drawing to the cameras render target.
*/
SDL_bool camera_set_height(Camera* camera, int height);

/**
    Sets the cameras rotation in degrees.
*/
static inline void camera_set_rotation(Camera* camera, double degrees);

/**
    Gets the position of the top-left corner of the camera in the game world.
*/
static inline Point camera_get_position(Camera* camera);

/**
    Gets the x coordinate of the left edge of the camera in the game world.
*/
static inline int camera_get_x(Camera* camera);

/**
    Gets the y coordinate of the top edge of the camera in the game world.
*/
static inline int camera_get_y(Camera* camera);

/**
    Gets the width and height of the camera in the game world.
*/
static inline Point camera_get_size(Camera* camera);

/**
    Gets the width of the camera in the game world.
*/
static inline int camera_get_width(Camera* camera);

/**
    Gets the height of the camera in the game world.
*/
static inline int camera_get_height(Camera* camera);

/**
    Gets the rotation of the camera in degrees.
*/
static inline double camera_get_rotation(Camera* camera);

/**
    Gets the bounds of the camera in the game world.
*/
static inline Rectangle camera_get_bounds(Camera* camera);

/**
    Gets the texture that can be used to draw to with this camera.
*/
static inline Texture* camera_get_render_target(Camera* camera);

/**
    Converts a position on the game window to a position in the game world.
*/
static inline Point camera_screen_to_world(Camera* camera, Point screen_position, Rectangle viewport);

/**
    Converts a position in the game world to a position on the game window.
*/
static inline Point camera_world_to_screen(Camera* camera, Point world_position, Rectangle viewport);

static inline void camera_free_resources(Camera* camera) {
    SDL_DestroyTexture(camera->render_target);
}

static inline void camera_free(Camera* camera) {
    SDL_DestroyTexture(camera->render_target);
    su_free(camera);
}

static inline void camera_move(Camera* camera, Point direction) {
    camera->view.x += direction.x;
    camera->view.y += direction.y;
}

static inline void camera_rotate(Camera* camera, double delta_degrees) {
    camera->rotation += delta_degrees;
}

static inline void camera_lookat(Camera* camera, Point position) {
    camera->view.x = position.x - camera->view.w / 2;
    camera->view.y = position.y - camera->view.h / 2;
}

static inline void camera_set_position(Camera* camera, Point position) {
    camera->view.x = position.x;
    camera->view.y = position.y;
}

static inline void camera_set_x(Camera* camera, int x) {
    camera->view.x = x;
}

static inline void camera_set_y(Camera* camera, int y) {
    camera->view.y = y;
}

static inline void camera_set_rotation(Camera* camera, double degrees) {
    camera->rotation = degrees;
}

static inline Point camera_get_position(Camera* camera) {
    return (Point) { camera->view.x, camera->view.y };
}

static inline int camera_get_x(Camera* camera) {
    return camera->view.x;
}

static inline int camera_get_y(Camera* camera) {
    return camera->view.y;
}

static inline Point camera_get_size(Camera* camera) {
    return (Point) { camera->view.w, camera->view.h };
}

static inline int camera_get_width(Camera* camera) {
    return camera->view.w;
}

static inline int camera_get_height(Camera* camera) {
    return camera->view.h;
}

static inline double camera_get_rotation(Camera* camera) {
    return camera->rotation;
}

static inline Rectangle camera_get_bounds(Camera* camera) {
    return camera->view;
}

static inline Texture* camera_get_render_target(Camera* camera) {
    return camera->render_target;
}

static inline Point camera_screen_to_world(Camera* camera, Point screen_position, Rectangle viewport) {
    screen_position.x = (int)((float)(screen_position.x - viewport.x) * ((float)camera->view.w / (float)viewport.w)) + camera->view.x;
    screen_position.y = (int)((float)(screen_position.y - viewport.y) * ((float)camera->view.h / (float)viewport.h)) + camera->view.y;
    return screen_position;
}

static inline Point camera_world_to_screen(Camera* camera, Point world_position, Rectangle viewport) {
    world_position.x = (int)((float)(world_position.x - camera->view.x) * ((float)viewport.w / (float)camera->view.w)) + viewport.x;
    world_position.y = (int)((float)(world_position.y - camera->view.y) * ((float)viewport.h / (float)camera->view.h)) + viewport.y;
    return world_position;
}

#endif