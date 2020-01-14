//
// Created by vhundef on 09.01.2020.
//

#ifndef DNCOURSEWORK_UI_FUNCTIONS_HPP
#define DNCOURSEWORK_UI_FUNCTIONS_HPP


#include "ui_base.hpp"
#include "ui_button.hpp"
#include "ui_text_field.hpp"
#include <list>
#include <utility>
#include <random>


class uiFunctionsRecord {
    string function;
    SDL_Color color{};
    uiButton *deleteBtn{};
public:
    [[nodiscard]] uiButton *getDeleteBtn() const {
        return deleteBtn;
    }

private:
    SDL_Rect colorRef{};
    bool remove{false};
public:
    void setRemove(bool _remove) {
        uiFunctionsRecord::remove = _remove;
    }

public:
    [[nodiscard]] bool isRemove() {
        return !deleteBtn->isEnabled();
    }

private:
    int x{}, y{};
public:
    int getY() const {
        return y;
    }

public:
    [[nodiscard]] const string &getFunction() const {
        return function;
    }

    [[nodiscard]] const SDL_Color &getColor() const {
        return color;
    }

    uiFunctionsRecord(UI_Manager *ui_Manager, string _function, int _x, int _y) {
        uiManager = ui_Manager;
        function = std::move(_function);
        x = _x;
        y = _y;
        colorRef.x = ui_Manager->getWindowResolutionX() - 90;
        colorRef.y = y;
        colorRef.w = 50;
        colorRef.h = 30;
        deleteBtn = new uiButton("X", uiManager, ui_Manager->getWindowResolutionX() - 35, y, 30, 30, 25);
        //deleteBtn->setEnabled(false);
        randomiseColor();
    }

    void draw() {
        if (!remove) {
            deleteBtn->setXandY(uiManager->getWindowResolutionX() - 35, y);
            SDL_RenderDrawRect(uiManager->getRenderer(), &colorRef);
            SDL_SetRenderDrawColor(uiManager->getRenderer(), color.r, color.g, color.b, 255);
            SDL_FillRect(SDL_GetWindowSurface(uiManager->getWindow()), &colorRef, UI_Manager::rgbToHex(color));
            SDL_RenderFillRect(uiManager->getRenderer(), &colorRef);
            uiManager->printText(function, 10, y, color, 25);
            deleteBtn->draw(uiManager->getInputManager()->getMouseCoords().x,
                            uiManager->getInputManager()->getMouseCoords().y);
            if (deleteBtn->isHover() && uiManager->getInputManager()->getMouseState() & SDL_BUTTON_LMASK) {
                deleteBtn->setEnabled(false);

            }
        }
    }

    static bool recordRemovalCheck(const uiFunctionsRecord &record) {
        //cout << !record.getDeleteBtn()->isEnabled() << endl;
        return !record.getDeleteBtn()->isEnabled();
    }

private:
    UI_Manager *uiManager;

    void randomiseColor() {
        color.r = randIntInRange(0, 200);
        color.g = randIntInRange(0, 200);
        color.b = randIntInRange(0, 200);
        color.a = 255;
    }

    static int randIntInRange(int min, int max) {
        std::random_device rd;     // only used once to initialise (seed) engine
        std::mt19937 rng(rd());    // random-number engine used (Mersenne-Twister in this case)
        std::uniform_int_distribution<int> uni(min, max); // guaranteed unbiased
        auto random_integer = uni(rng);
        return random_integer;
    }
};


class ui_Functions : private virtual UI_Base {
private:
    uiButton *add_btn{};
    uiButton *newGraph_btn{};
    list <uiFunctionsRecord> functions;

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

    void checkForRemovals() {
        functions.remove_if(uiFunctionsRecord::recordRemovalCheck);
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
        int i = 0;
        uiManager->printText("Used Functions:", 10, 150, {196, 79, 79}, 25);
        for (uiFunctionsRecord function:functions) { ;
            function.draw();
            i++;
        }
    }

    uiFunctionsRecord *act() {
        if (addNewGraph) {
            addNewGraph = false;
            textField->setInputText("");
            return nullptr;
        } else if (!addNewGraph && newGraph_btn->isHover() &&
                   uiManager->getInputManager()->getMouseState() & SDL_BUTTON_LMASK) {
            addNewGraph = true;
            uiTextField::enable();
            show();
            string input = getText();
            if (!input.empty() || input != " ") {
                int i = 0;
                while (!isYAvailable(180 + 30 * i)) { i++; }
                functions.emplace_back(uiManager, input, 10, 180 + 30 * i);
                return &functions.back();
            }
        }
        return nullptr;
    }

    bool isYAvailable(int y) {
        for (const uiFunctionsRecord &func:functions) {
            if (func.getY() == y)return false;
        }
        return true;
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
