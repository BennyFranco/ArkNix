#include "sdl_input.h"

#include <iostream>

using namespace ::nim;

void SDLInput::Init() {
}

void SDLInput::Update() {
    while (SDL_PollEvent(&event)) {
        switch (event.type) {
            case SDL_KEYUP:
                lastKeyEvent.isKeyDown = false;
                lastKeyEvent.key = event.key.keysym.sym;
                break;
            case SDL_KEYDOWN:
                lastKeyEvent.isKeyDown = true;
                lastKeyEvent.key = event.key.keysym.sym;
                break;
            case SDL_QUIT:
                lastKeyEvent.isKeyDown = false;
                lastKeyEvent.key = SDL_KeyCode::SDLK_UNKNOWN;
                onExitGameEvent.Invoke(false);
                return;
            default:
                lastKeyEvent.isKeyDown = false;
                lastKeyEvent.key = SDL_KeyCode::SDLK_UNKNOWN;
                break;
        }
    }
}

void SDLInput::Quit() {}

bool SDLInput::GetKey(Key key) {
    bool result = lastKeyEvent.key == ConvertNimKeyToSDLKey(key);
    if (result) {
        lastKeyEvent.isKeyDown = false;
        lastKeyEvent.key = SDL_KeyCode::SDLK_UNKNOWN;
    }
    return result;
}

bool SDLInput::GetKeyUp(Key key) {
    bool result = !lastKeyEvent.isKeyDown && lastKeyEvent.key == ConvertNimKeyToSDLKey(key);
    if (result) {
        lastKeyEvent.isKeyDown = false;
        lastKeyEvent.key = SDL_KeyCode::SDLK_UNKNOWN;
    }
    return result;
}

bool SDLInput::GetKeyDown(Key key) {
    const Uint8 *state = SDL_GetKeyboardState(NULL);
    return state[ConvertNimKeyToSDLScanCode(key)];
}

SDL_KeyCode SDLInput::ConvertNimKeyToSDLKey(Key key) {
    switch (key) {
        case Key::A:
            return SDL_KeyCode::SDLK_a;
        case Key::B:
            return SDL_KeyCode::SDLK_b;
        case Key::C:
            return SDL_KeyCode::SDLK_c;
        case Key::D:
            return SDL_KeyCode::SDLK_d;
        case Key::E:
            return SDL_KeyCode::SDLK_e;
        case Key::F:
            return SDL_KeyCode::SDLK_f;
        case Key::G:
            return SDL_KeyCode::SDLK_g;
        case Key::H:
            return SDL_KeyCode::SDLK_h;
        case Key::I:
            return SDL_KeyCode::SDLK_i;
        case Key::J:
            return SDL_KeyCode::SDLK_j;
        case Key::K:
            return SDL_KeyCode::SDLK_k;
        case Key::L:
            return SDL_KeyCode::SDLK_l;
        case Key::M:
            return SDL_KeyCode::SDLK_m;
        case Key::N:
            return SDL_KeyCode::SDLK_n;
        case Key::O:
            return SDL_KeyCode::SDLK_o;
        case Key::P:
            return SDL_KeyCode::SDLK_p;
        case Key::Q:
            return SDL_KeyCode::SDLK_q;
        case Key::R:
            return SDL_KeyCode::SDLK_r;
        case Key::S:
            return SDL_KeyCode::SDLK_s;
        case Key::T:
            return SDL_KeyCode::SDLK_t;
        case Key::U:
            return SDL_KeyCode::SDLK_u;
        case Key::V:
            return SDL_KeyCode::SDLK_v;
        case Key::W:
            return SDL_KeyCode::SDLK_w;
        case Key::X:
            return SDL_KeyCode::SDLK_x;
        case Key::Y:
            return SDL_KeyCode::SDLK_y;
        case Key::Z:
            return SDL_KeyCode::SDLK_z;
        case Key::NUM_0:
            return SDL_KeyCode::SDLK_0;
        case Key::NUM_1:
            return SDL_KeyCode::SDLK_1;
        case Key::NUM_2:
            return SDL_KeyCode::SDLK_2;
        case Key::NUM_3:
            return SDL_KeyCode::SDLK_3;
        case Key::NUM_4:
            return SDL_KeyCode::SDLK_4;
        case Key::NUM_5:
            return SDL_KeyCode::SDLK_5;
        case Key::NUM_6:
            return SDL_KeyCode::SDLK_6;
        case Key::NUM_7:
            return SDL_KeyCode::SDLK_7;
        case Key::NUM_8:
            return SDL_KeyCode::SDLK_8;
        case Key::NUM_9:
            return SDL_KeyCode::SDLK_9;
        case Key::TAB:
            return SDL_KeyCode::SDLK_TAB;
        case Key::CAPS_LOCK:
            return SDL_KeyCode::SDLK_CAPSLOCK;
        case Key::LEFT_SHIFT:
            return SDL_KeyCode::SDLK_LSHIFT;
        case Key::LEFT_CTRL:
            return SDL_KeyCode::SDLK_LCTRL;
        case Key::LEFT_ALT:
            return SDL_KeyCode::SDLK_LALT;
        case Key::SPACE:
            return SDL_KeyCode::SDLK_SPACE;
        case Key::RIGHT_ALT:
            return SDL_KeyCode::SDLK_RALT;
        case Key::RIGHT_CTRL:
            return SDL_KeyCode::SDLK_RCTRL;
        case Key::RIGHT_SHIFT:
            return SDL_KeyCode::SDLK_RSHIFT;
        case Key::ENTER:
            return SDL_KeyCode::SDLK_RETURN;
        case Key::BACKSPACE:
            return SDL_KeyCode::SDLK_BACKSPACE;
        case Key::BACKTICK:
            return SDL_KeyCode::SDLK_BACKQUOTE;
        case Key::BACKSLASH:
            return SDL_KeyCode::SDLK_BACKSLASH;
        case Key::MINUS:
            return SDL_KeyCode::SDLK_MINUS;
        case Key::PLUS:
            return SDL_KeyCode::SDLK_PLUS;
        case Key::EQUALS:
            return SDL_KeyCode::SDLK_EQUALS;
        case Key::LEFT_SQUARE_BRACKET:
            return SDL_KeyCode::SDLK_LEFTBRACKET;
        case Key::RIGHT_SQUARE_BRACKET:
            return SDL_KeyCode::SDLK_RIGHTBRACKET;
        case Key::SEMICOLON:
            return SDL_KeyCode::SDLK_SEMICOLON;
        case Key::APOSTROPHE:
            return SDL_KeyCode::SDLK_THOUSANDSSEPARATOR;
        case Key::COMMA:
            return SDL_KeyCode::SDLK_COMMA;
        case Key::DOT:
            return SDL_KeyCode::SDLK_DECIMALSEPARATOR;
        case Key::SLASH:
            return SDL_KeyCode::SDLK_SLASH;
        case Key::UP:
            return SDL_KeyCode::SDLK_UP;
        case Key::DOWN:
            return SDL_KeyCode::SDLK_DOWN;
        case Key::LEFT:
            return SDL_KeyCode::SDLK_LEFT;
        case Key::RIGHT:
            return SDL_KeyCode::SDLK_RIGHT;
        case Key::INTRO:
            return SDL_KeyCode::SDLK_KP_ENTER;
        case Key::ESCAPE:
            return SDL_KeyCode::SDLK_ESCAPE;
        default:
            return SDL_KeyCode::SDLK_UNKNOWN;
    }
}

SDL_Scancode SDLInput::ConvertNimKeyToSDLScanCode(Key key) {
    switch (key) {
        case Key::A:
            return SDL_SCANCODE_A;
        case Key::B:
            return SDL_SCANCODE_B;
        case Key::C:
            return SDL_SCANCODE_C;
        case Key::D:
            return SDL_SCANCODE_D;
        case Key::E:
            return SDL_SCANCODE_E;
        case Key::F:
            return SDL_SCANCODE_F;
        case Key::G:
            return SDL_SCANCODE_G;
        case Key::H:
            return SDL_SCANCODE_H;
        case Key::I:
            return SDL_SCANCODE_I;
        case Key::J:
            return SDL_SCANCODE_J;
        case Key::K:
            return SDL_SCANCODE_K;
        case Key::L:
            return SDL_SCANCODE_L;
        case Key::M:
            return SDL_SCANCODE_M;
        case Key::N:
            return SDL_SCANCODE_N;
        case Key::O:
            return SDL_SCANCODE_O;
        case Key::P:
            return SDL_SCANCODE_P;
        case Key::Q:
            return SDL_SCANCODE_Q;
        case Key::R:
            return SDL_SCANCODE_R;
        case Key::S:
            return SDL_SCANCODE_S;
        case Key::T:
            return SDL_SCANCODE_T;
        case Key::U:
            return SDL_SCANCODE_U;
        case Key::V:
            return SDL_SCANCODE_Y;
        case Key::W:
            return SDL_SCANCODE_W;
        case Key::X:
            return SDL_SCANCODE_X;
        case Key::Y:
            return SDL_SCANCODE_Y;
        case Key::Z:
            return SDL_SCANCODE_Z;
        case Key::NUM_0:
            return SDL_SCANCODE_0;
        case Key::NUM_1:
            return SDL_SCANCODE_1;
        case Key::NUM_2:
            return SDL_SCANCODE_2;
        case Key::NUM_3:
            return SDL_SCANCODE_3;
        case Key::NUM_4:
            return SDL_SCANCODE_4;
        case Key::NUM_5:
            return SDL_SCANCODE_5;
        case Key::NUM_6:
            return SDL_SCANCODE_6;
        case Key::NUM_7:
            return SDL_SCANCODE_7;
        case Key::NUM_8:
            return SDL_SCANCODE_8;
        case Key::NUM_9:
            return SDL_SCANCODE_9;
        case Key::TAB:
            return SDL_SCANCODE_TAB;
        case Key::CAPS_LOCK:
            return SDL_SCANCODE_CAPSLOCK;
        case Key::LEFT_SHIFT:
            return SDL_SCANCODE_LSHIFT;
        case Key::LEFT_CTRL:
            return SDL_SCANCODE_LCTRL;
        case Key::LEFT_ALT:
            return SDL_SCANCODE_LALT;
        case Key::SPACE:
            return SDL_SCANCODE_SPACE;
        case Key::RIGHT_ALT:
            return SDL_SCANCODE_RALT;
        case Key::RIGHT_CTRL:
            return SDL_SCANCODE_RCTRL;
        case Key::RIGHT_SHIFT:
            return SDL_SCANCODE_RSHIFT;
        case Key::ENTER:
            return SDL_SCANCODE_RETURN;
        case Key::BACKSPACE:
            return SDL_SCANCODE_BACKSPACE;
        case Key::BACKTICK:
            return SDL_SCANCODE_ESCAPE;
        case Key::BACKSLASH:
            return SDL_SCANCODE_BACKSLASH;
        case Key::MINUS:
            return SDL_SCANCODE_MINUS;
        case Key::PLUS:
            return SDL_SCANCODE_KP_PLUS;
        case Key::EQUALS:
            return SDL_SCANCODE_EQUALS;
        case Key::LEFT_SQUARE_BRACKET:
            return SDL_SCANCODE_LEFTBRACKET;
        case Key::RIGHT_SQUARE_BRACKET:
            return SDL_SCANCODE_RIGHTBRACKET;
        case Key::SEMICOLON:
            return SDL_SCANCODE_SEMICOLON;
        case Key::APOSTROPHE:
            return SDL_SCANCODE_THOUSANDSSEPARATOR;
        case Key::COMMA:
            return SDL_SCANCODE_COMMA;
        case Key::DOT:
            return SDL_SCANCODE_DECIMALSEPARATOR;
        case Key::SLASH:
            return SDL_SCANCODE_SLASH;
        case Key::UP:
            return SDL_SCANCODE_UP;
        case Key::DOWN:
            return SDL_SCANCODE_DOWN;
        case Key::LEFT:
            return SDL_SCANCODE_LEFT;
        case Key::RIGHT:
            return SDL_SCANCODE_RIGHT;
        case Key::INTRO:
            return SDL_SCANCODE_KP_ENTER;
        case Key::ESCAPE:
            return SDL_SCANCODE_ESCAPE;
        default:
            return SDL_SCANCODE_UNKNOWN;
    }
}

void SDLInput::PrintDebugKey(SDL_Event *event) {
    std::cout << "{" << std::endl;
    std::cout << "\tscancode=" << event->key.keysym.scancode << std::endl;
    std::cout << "\tsym=" << event->key.keysym.sym << std::endl;
    std::cout << "\tmod=" << event->key.keysym.mod << std::endl;
    std::cout << "\tKEY=" << SDL_GetKeyName(event->key.keysym.sym) << std::endl;
    std::cout << "}" << std::endl;
}