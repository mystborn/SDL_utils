#ifndef SDL_UTILS_INPUT_H
#define SDL_UTILS_INPUT_H

#include <SDL.h>

/**
    Defines some extra values to allow specific stick directions to be
    used like other controller buttons by the input manager.
*/
typedef enum SDL_GameControllerButtonExtension {
    SDL_CONTROLLER_BUTTON_EXTENSION_INVALID = -1,
    SDL_CONTROLLER_BUTTON_LEFTSTICKUP = SDL_CONTROLLER_BUTTON_MAX,
    SDL_CONTROLLER_BUTTON_LEFTSTICKLEFT,
    SDL_CONTROLLER_BUTTON_LEFTSTICKDOWN,
    SDL_CONTROLLER_BUTTON_LEFTSTICKRIGHT,
    SDL_CONTROLLER_BUTTON_RIGHTSTICKUP,
    SDL_CONTROLLER_BUTTON_RIGHTSTICKLEFT,
    SDL_CONTROLLER_BUTTON_RIGHTSTICKDOWN,
    SDL_CONTROLLER_BUTTON_RIGHTSTICKRIGHT,
    SDL_CONTROLLER_BUTTON_LEFTTRIGGER,
    SDL_CONTROLLER_BUTTON_RIGHTTRIGGER,
    SDL_CONTROLLER_BUTTON_EXTENSION_MAX
} SDL_GameControllerButtonExtension;

/**
    A tpye to make the intentions more clear when a mouse button is desired.
*/
typedef Uint32 MouseButton;

/**
    Checks if the specified key is currently down.
*/
SDL_bool key_check(SDL_Scancode key);

/**
    Checks if the specfied key has just been pressed during the last update.
*/
SDL_bool key_check_pressed(SDL_Scancode key);

/**
    Checks if the specified key has just been released during the last update.
*/
SDL_bool key_check_released(SDL_Scancode key);

/**
    Checks if the specified button is currently down.
*/
SDL_bool mouse_check(MouseButton button);

/**
    Checks if the specified button has just been pressed during
    the last update.
*/
SDL_bool mouse_check_pressed(MouseButton button);

/**
    Checks if the specified button has just been released during
    the last update.
*/
SDL_bool mouse_check_released(MouseButton button);

/**
    Checks if the mouse has moved at all during the last frame.
*/
SDL_bool mouse_moved(void);

/**
    Checks if the specified button is currently down.

    \param index The gamepad index retrieved from the SDL_ControllerDeviceEvent,
                 or -1. If it's -1, it will use the first controller plugged in.
*/
SDL_bool gamepad_check_index(Uint32 button, int index);

/**
    Checks if the specified button has just been pressed during
    the last update.

    \param index The gamepad index retrieved from the SDL_ControllerDeviceEvent,
                 or -1. If it's -1, it will use the first controller plugged in.
*/
SDL_bool gamepad_check_pressed_index(Uint32 button, int index);

/**
    Checks if the specified button has just been released during
    the last update.

    \param index The gamepad index retrieved from the SDL_ControllerDeviceEvent,
                 or -1. If it's -1, it will use the first controller plugged in.
*/
SDL_bool gamepad_check_released_index(Uint32 button, int index);

/**
    Gets the axis value of a controller stick, between
    SDL_MIN_INT16 and SDL_MAX_INT16.

    \param index The gamepad index retrieved from the SDL_ControllerDeviceEvent,
                 or -1. If it's -1, it will use the first controller plugged in.
*/
Uint16 gamepad_axis_value_index(SDL_GameControllerAxis axis, int index);

/**
    Sets the deadzone in which a controller stick is not recognized as active
    even if it's coordinates aren't exactly (0, 0). Used to combat the innate
    inaccuracy in most controller sticks. Defaults to 15%.
*/
void gamepad_set_deadzone(Uint16 value);

/**
    Gets the current deadzone value.
*/
Uint16 gamepad_get_deadzone(void);

/**
    Checks if the specified button is currently down.

    \remark Convenience macro for gamepad_check_index to automatically
            check the controller that's been plugged in the longest.
*/
#define gamepad_check(button) gamepad_check_index((button), -1)

/**
    Checks if the specified button has just been pressed during
    the last update.

    \remark Convenience macro for gamepad_check_pressed_index to automatically
            check the controller that's been plugged in the longest.
*/
#define gamepad_check_pressed(button) gamepad_check_pressed_index((button), -1)

/**
    Checks if the specified button has just been released during
    the last update.

    \remark Convenience macro for gamepad_check_released_index to automatically
            check the controller that's been plugged in the longest.
*/
#define gamepad_check_released(button) gamepad_check_released_index((button), -1)

/**
    Gets the axis value of a controller stick, between
    SDL_MIN_INT16 and SDL_MAX_INT16.

    \remark Convenience macro for gamepad_check_released_index to automatically
            check the controller that's been plugged in the longest.
*/
#define gamepad_axis_value(axis) gamepad_axis_value_index((axis), -1)

/**
    Set a key to be checked by an action.

    \param action The action that checks the key.
    \param key The key to check.
    \param key_index The index of the key in the action. Can be 0 or 1.

    \remarks The two possible indeces are used to allow multiple keys
             to be bound the the same action.
*/
void action_set_key(Uint32 action, SDL_Scancode key, int key_index);

/**
    Set a gamepad button to be checked by an action.

    \param action The action that checks the button.
    \param button The button to check.
    \param button_index The index of the button in the action. Can be 0 or 1.

    \remarks The two possible indeces are used to allow multiple buttons
             to be bound the the same action.
*/
void action_set_button(Uint32 action, Sint32 button, int button_index);

/**
    Set a mouse button to be checked by an action.

    \param action The action that checks the button.
    \param button the button to check.
*/
void action_set_mouse(Uint32 action, MouseButton button);

/**
    Checks if any of the inputs bound to the action are currently triggered.

    \param The action id to check.
*/
SDL_bool action_check(Uint32 action);

/**
    Checks if any of the inputs bound to the action were just pressed.

    \param The action id to check.
*/
SDL_bool action_check_pressed(Uint32 action);

/**
    Checks if any of the inputs bound to the action were just released.

    \param The action id to check.
*/
SDL_bool action_check_released(Uint32 action);

/**
    Initializes the input manager with the specified amount of actions.

    \param action_count The number of actions to be used by the input manager.

    \return SDL_TRUE on success, SDL_FALSE otherwise. Check the error
            with SDL_GetError().

    \remark If you wish to use the action api, there is a one time heap 
            allocation. If that's to be avoided at all cost, or you 
            just don't want to use the action api, just pass 0 for 
            action_count and it'll be ignored.
*/
SDL_bool input_manager_init(int action_count);

/**
    Update the input manager. Needs to be called every frame.
*/
void input_manager_update(void);

/**
    Modifies the internal state of the input manager depending on the
    specified controller event. (This just determines what controllers 
    are plugged/unplugged and how to handle their input).
*/
void input_manager_event(SDL_ControllerDeviceEvent* event);

/**
    Frees any allocated storage used by the input manager.
*/
void input_manager_free(void);

#endif