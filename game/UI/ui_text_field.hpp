//
// Created by vhundef on 09.01.2020.
//

#ifndef DNCOURSEWORK_UI_TEXT_FIELD_HPP
#define DNCOURSEWORK_UI_TEXT_FIELD_HPP


#include "ui_base.hpp"

class uiTextField {
private:
    SDL_Rect body{};
    SDL_Color hoverColor{89, 150, 74};
    UI_Manager *uiManager{};
    string text;
    //Set text color as black
    SDL_Color textColor = {0, 0, 0, 0xFF};

    //The current input text.
    std::string inputText = "";
public:
    void setInputText(const string &inputText) {
        uiTextField::inputText = inputText;
    }

public:
    const string &getInputText() const {
        return inputText;
    }

private:

    InputManager *inputManager;

public:
    uiTextField(UI_Manager *_uiManager, SDL_Window *window, int x, int y, int width, int height,
                InputManager *_inputManager) {
        if (_uiManager == nullptr) {
            std::string error = "UIButton->Constructor->uiManager is null";
            SDL_LogCritical(SDL_LOG_CATEGORY_ERROR, "%s", error.c_str());
            throw std::runtime_error("Unable to button uiManager is null");
        }
        uiManager = _uiManager;
        body.x = x;
        body.y = y;
        body.w = width;
        body.h = height;

        inputManager = _inputManager;
    }

    static void enable() {
        //Enable text input
        SDL_StartTextInput();
    }

    static void disable() {
        //Enable text input
        SDL_StopTextInput();
    }

    void draw() {
        SDL_RenderDrawRect(uiManager->getRenderer(), &body);
        if (inputManager->getEvent().type == SDL_KEYDOWN) {
            //Handle backspace
            if (inputManager->getEvent().key.keysym.sym == SDLK_BACKSPACE && inputText.length() > 0) {
                //lop off character
                inputText.pop_back();
            }
                //Handle copy
            else if (inputManager->getEvent().key.keysym.sym == SDLK_c && SDL_GetModState() & KMOD_CTRL) {
                SDL_SetClipboardText(inputText.c_str());
            }
                //Handle paste
            else if (inputManager->getEvent().key.keysym.sym == SDLK_v && SDL_GetModState() & KMOD_CTRL) {
                inputText = SDL_GetClipboardText();
            }
        }
            //Special text input event
        else if (inputManager->getEvent().type == SDL_TEXTINPUT) {
            //Not copy or pasting
            if (!(SDL_GetModState() & KMOD_CTRL &&
                  (inputManager->getEvent().text.text[0] == 'c' || inputManager->getEvent().text.text[0] == 'C' ||
                   inputManager->getEvent().text.text[0] == 'v' || inputManager->getEvent().text.text[0] == 'V'))) {
                //Append character
                inputText += inputManager->getEvent().text.text;
            }
        }

        SDL_SetRenderDrawColor(uiManager->getRenderer(), 235, 169, 70, 255);
        SDL_RenderFillRect(uiManager->getRenderer(), &body);
        uiManager->printText(inputText, body.x + 5, body.y + uiManager->getTextSize(text, 20).b / 2, {255, 255, 255},
                             20);
    }
};


#endif //DNCOURSEWORK_UI_TEXT_FIELD_HPP
