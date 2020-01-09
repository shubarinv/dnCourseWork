//
// Created by vhundef on 09.01.2020.
//

#ifndef DNCOURSEWORK_UI_FUNCTIONS_HPP
#define DNCOURSEWORK_UI_FUNCTIONS_HPP


#include "ui_base.hpp"
#include "ui_button.hpp"
#include "ui_text_field.hpp"
#include <list>

class ui_Functions : private virtual UI_Base {
private:
    uiButton *add_btn{};
    uiButton *newGraph_btn{};
    list <string> functions;

private:
    uiTextField *textField{};
    bool addNewGraph = false;
public:
    ui_Functions(UI_Manager *ui_Manager, SDL_Window *window, std::string _locale) : UI_Base(ui_Manager, window,
                                                                                            std::move(_locale)) {
        add_btn = new uiButton("ADD", uiManager, uiManager->getWindowResolutionX() / 2 - 100, 70, 200, 50, 20);
        newGraph_btn = new uiButton("+", uiManager, uiManager->getWindowResolutionX() / 2 - 100, 10, 200, 50, 25);
        textField = new uiTextField(ui_Manager, window, 10,
                                    10, uiManager->getWindowResolutionX() - 20, 50, ui_Manager->getInputManager());
        uiTextField::enable();
    }


    void show() {
        if (addNewGraph) {
            uiManager->getInputManager()->updateEvents();
            add_btn->draw(uiManager->getInputManager()->getMouseCoords().x,
                          uiManager->getInputManager()->getMouseCoords().y);
            textField->draw();
            SDL_RenderPresent(uiManager->getRenderer());
        } else {
            newGraph_btn->draw(uiManager->getInputManager()->getMouseCoords().x,
                               uiManager->getInputManager()->getMouseCoords().y);
        }
        int i = 1;
        uiManager->printText("Used Functions:", 10, 150, {196, 79, 79}, 25);
        for (string function:functions) {
            uiManager->printText(function, 10, 150 + 30 * i, {196, 79, 79}, 25);
            i++;
        }
    }

    string act() {
        if (addNewGraph) {
            addNewGraph = false;
            textField->setInputText("");
            return "";
        } else if (!addNewGraph && newGraph_btn->isHover() &&
                   uiManager->getInputManager()->getMouseState() & SDL_BUTTON_LMASK) {
            addNewGraph = true;
            uiTextField::enable();
            show();
            string input = getText();
            if (!input.empty() || input != " ") {
                functions.push_back(input);
            }
            return input;
        }
        return "";
    }

    string getText() {
        while (SDL_WaitEvent(uiManager->getInputManager()->getEventAddress())) {
            show();
            if (add_btn->isHover() && uiManager->getInputManager()->getMouseState() & SDL_BUTTON_LMASK) {
                uiTextField::disable();
                return textField->getInputText();
            }
        }

    }
};


#endif //DNCOURSEWORK_UI_FUNCTIONS_HPP
