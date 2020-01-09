//
// Created by vhundef on 02.01.2020.
//

#ifndef PROGONHLANG_INPUT_MANAGER_HPP
#define PROGONHLANG_INPUT_MANAGER_HPP


#include <SDL_events.h>
#include <SDL.h>
#include "game.hpp"

class InputManager {
    struct mouseCoords {
        int x, y;
    };
private:
    SDL_Event event;
public:
    void setEvent(const SDL_Event &event);

private:
    Uint8 mouseState{};
public:
    Uint8 getMouseState() const;

    SDL_Event getEvent() {
        return event;
    }

    SDL_Event *getEventAddress() {
        return &event;
    }

private:
    mouseCoords mouseCoords;


public:
    void updateEvents() {
        SDL_PollEvent(&event);
        mouseState = SDL_GetMouseState(&mouseCoords.x, &mouseCoords.y);
    }

    bool quitEventCheck() {
        if (event.type == SDL_QUIT || (event.type == SDL_KEYDOWN && event.key.keysym.sym == SDLK_ESCAPE)) {
            SDL_LogInfo(SDL_LOG_CATEGORY_INPUT, "Got QUIT event");
            return true;
        }
        return false;
    }

    [[nodiscard]] const struct mouseCoords &getMouseCoords() const {

        return mouseCoords;
    }
};


Uint8 InputManager::getMouseState() const {
    return mouseState;
}

void InputManager::setEvent(const SDL_Event &event) {
    InputManager::event = event;
}


#endif //PROGONHLANG_INPUT_MANAGER_HPP
