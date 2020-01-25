
#ifndef DNCOURSEWORK_WINDOWS_MANAGER_HPP
#define DNCOURSEWORK_WINDOWS_MANAGER_HPP


#include <SDL_video.h>
#include <SDL_render.h>
#include <string>
#include <SDL_log.h>
#include <stdexcept>

class WindowsManager {
    struct twoInt {
        int x, y;
    };
public:
    WindowsManager() {
        functionsWindow = SDL_CreateWindow("Functions", 0, 0, 350, 720, SDL_WINDOW_SHOWN);
        if (functionsWindow == nullptr) {
            std::string error = SDL_GetError();
            SDL_LogCritical(SDL_LOG_CATEGORY_ERROR, "%s", error.c_str());
            throw std::runtime_error("Unable to create Functions window");
        }
        graphWindow = SDL_CreateWindow("Graph", 350, 0, 720, 720, SDL_WINDOW_SHOWN);
        if (graphWindow == nullptr) {
            std::string error = SDL_GetError();
            SDL_LogCritical(SDL_LOG_CATEGORY_ERROR, "%s", error.c_str());
            throw std::runtime_error("Unable to create Graph window");
        }
        functionsWinRender = SDL_CreateRenderer(functionsWindow, -1, 0);
        if (functionsWinRender == nullptr) {
            SDL_DestroyWindow(functionsWindow);
            std::string error = SDL_GetError();
            SDL_LogCritical(SDL_LOG_CATEGORY_ERROR, "%s", error.c_str());
            throw std::runtime_error("Unable to create Functions render");
        }
        graphWinRender = SDL_CreateRenderer(graphWindow, -1, 0);
        if (graphWinRender == nullptr) {
            SDL_DestroyWindow(graphWindow);
            std::string error = SDL_GetError();
            SDL_LogCritical(SDL_LOG_CATEGORY_ERROR, "%s", error.c_str());
            throw std::runtime_error("Unable to create Graph render");
        }
    }
    [[nodiscard]] SDL_Window *getFunctionsWindow() const {
        return functionsWindow;
    }

    [[nodiscard]] SDL_Window *getGraphWindow() const {
        return graphWindow;
    }

    [[nodiscard]] SDL_Renderer *getFunctionsWinRender() const {
        return functionsWinRender;
    }

    [[nodiscard]] SDL_Renderer *getGraphWinRender() const {
        return graphWinRender;
    }

    static twoInt getWindowSize(SDL_Window *window) {
        twoInt winSize{};
        SDL_GetWindowSize(window, &winSize.x, &winSize.y);
        return winSize;
    }

    void clearRenderer(SDL_Renderer *ren) {
        if (SDL_RenderClear(ren) < 0) {
            SDL_DestroyWindow(graphWindow);
            SDL_DestroyWindow(functionsWindow);
            std::string error = SDL_GetError();
            SDL_LogCritical(SDL_LOG_CATEGORY_ERROR, "%s", error.c_str());
            throw std::runtime_error("Unable to clear render (SDL2)");
        }
    }

    SDL_Window *getFocusedWindow() {
        if (SDL_GetWindowFlags(functionsWindow) & SDL_WINDOW_MOUSE_FOCUS)return functionsWindow;
        if (SDL_GetWindowFlags(graphWindow) & SDL_WINDOW_MOUSE_FOCUS)return graphWindow;
        return nullptr;
    }

private:
    SDL_Window *functionsWindow{};
    SDL_Window *graphWindow{};
    SDL_Renderer *functionsWinRender{};
    SDL_Renderer *graphWinRender{};


};


#endif //DNCOURSEWORK_WINDOWS_MANAGER_HPP
