#ifndef INPUT_EVENTS_H
#define INPUT_EVENTS_H

#include "entity.h"
#include "SDL.h"

namespace nim {
    enum class Key {
        A = 0,
        B,
        C,
        D,
        E,
        F,
        G,
        H,
        I,
        J,
        K,
        L,
        M,
        N,
        O,
        P,
        Q,
        R,
        S,
        T,
        U,
        V,
        W,
        X,
        Y,
        Z,
        NUM_0,
        NUM_1,
        NUM_2,
        NUM_3,
        NUM_4,
        NUM_5,
        NUM_6,
        NUM_7,
        NUM_8,
        NUM_9,
        TAB,
        CAPS_LOCK,
        LEFT_SHIFT,
        LEFT_CTRL,
        LEFT_ALT,
        SPACE,
        RIGHT_ALT,
        RIGHT_CTRL,
        RIGHT_SHIFT,
        ENTER,
        BACKSPACE,
        BACKTICK,
        BACKSLASH,
        MINUS,
        PLUS,
        EQUALS,
        LEFT_SQUARE_BRACKET,
        RIGHT_SQUARE_BRACKET,
        SEMICOLON,
        APOSTROPHE,
        COMMA,
        DOT,
        SLASH,
        UP,
        DOWN,
        LEFT,
        RIGHT
    };

    struct KeyEvent {
        bool isKeyDown;
        SDL_Keycode key;
    };

    class Input : public Entity {
    public:
        virtual bool GetKeyDown(Key key) = 0;
        virtual bool GetKeyUp(Key key) = 0;

    protected:
        KeyEvent lastKeyEvent;
    };
}// namespace nim
#endif