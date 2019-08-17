#include <su_camera.h>

SDL_bool camera_init(Camera* camera, SDL_Renderer* renderer, int width, int height, Rectangle* viewport, Uint32 pixel_format) {
    camera->render_target = SDL_CreateTexture(renderer, pixel_format, SDL_TEXTUREACCESS_TARGET, width, height);
    if(camera->render_target == NULL)
        return SDL_FALSE;

    camera->rotation = 0;
    camera->view.x = 0;
    camera->view.y = 0;
    camera->view.w = width;
    camera->view.h = height;
    camera->renderer = renderer;
    camera->viewport = viewport;
    camera->pixel_format = pixel_format;
    return SDL_TRUE;
}

Camera* camera_create(SDL_Renderer* renderer, int width, int height, Rectangle* viewport, Uint32 pixel_format) {
    Camera* camera = su_malloc(sizeof(Camera));
    if(camera == NULL)
        return NULL;

    if(!camera_init(camera, renderer, width, height, viewport, pixel_format)) {
        su_free(camera);
        return NULL;
    }

    return camera;
}

SDL_bool camera_set_size(Camera* camera, Point size) {
    // Early exit if the size didn't change in order to avoid
    // expensive reallocation of SDL_Texture.
    if (camera->view.w == size.x && camera->view.h == size.y)
        return SDL_TRUE;

    camera->view.w = size.x;
    camera->view.h = size.y;

    SDL_Texture* texture = SDL_CreateTexture(camera->renderer, camera->pixel_format, SDL_TEXTUREACCESS_TARGET, size.x, size.y);
    if (texture == NULL)
        return SDL_FALSE;

    SDL_DestroyTexture(camera->render_target);
    camera->render_target = texture;

    return SDL_TRUE;
}

SDL_bool camera_set_width(Camera* camera, int width) {
    if (camera->view.w == width)
        return SDL_TRUE;

    camera->view.w = width;

    SDL_Texture* texture = SDL_CreateTexture(camera->renderer, camera->pixel_format, SDL_TEXTUREACCESS_TARGET, width, camera->view.h);
    if (texture == NULL)
        return SDL_FALSE;

    SDL_DestroyTexture(camera->render_target);
    camera->render_target = texture;

    return SDL_TRUE;
}

SDL_bool camera_set_height(Camera* camera, int height) {
    if (camera->view.h == height)
        return SDL_TRUE;

    camera->view.h = height;

    SDL_Texture* texture = SDL_CreateTexture(camera->renderer, camera->pixel_format, SDL_TEXTUREACCESS_TARGET, camera->view.w, height);
    if (texture == NULL)
        return SDL_FALSE;

    SDL_DestroyTexture(camera->render_target);
    camera->render_target = texture;

    return SDL_TRUE;
}