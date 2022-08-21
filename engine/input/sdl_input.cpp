#include "sdl_input.h"

#include <iostream>

using namespace ::nim;

void SDLInput::Init() {
}

// TODO: Implement some kind of agnostic event system to notify
// other systems that a key or event was thrown.
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
    return lastKeyEvent.key == ConvertNimKeyToSDLKey(key);
}

bool SDLInput::GetKeyUp(Key key) {
    return !lastKeyEvent.isKeyDown && lastKeyEvent.key == ConvertNimKeyToSDLKey(key);
}

bool SDLInput::GetKeyDown(Key key) {
    return lastKeyEvent.isKeyDown && lastKeyEvent.key == ConvertNimKeyToSDLKey(key);
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
        default:
            return SDL_KeyCode::SDLK_UNKNOWN;
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