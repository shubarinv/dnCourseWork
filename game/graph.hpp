

#ifndef DNCOURSEWORK_GRAPH_HPP
#define DNCOURSEWORK_GRAPH_HPP


#include <SDL_render.h>
#include <list>
#include "line.hpp"

class Graph {
private:
    SDL_Renderer *renderer{};
    UI_Manager *ui_Manager{};
    std::list<Line> lines{};
    int windowHeight{0};
    int windowWidth{0};
public:
    int getWindowHeight() const {
        return windowHeight;
    }

    int getWindowWidth() const {
        return windowWidth;
    }

private:
    SDL_Rect graphBG{};
public:
    Graph(SDL_Renderer *_renderer, int windowX, int windowY, UI_Manager *_uiManager) {
        if (_renderer == nullptr) {
            throw std::runtime_error("Graph::Graph() renderer is NULL");
        }
        renderer = _renderer;
        graphBG.x = 0;
        graphBG.y = 0;
        graphBG.w = windowX;
        graphBG.h = windowY;
        windowWidth = windowX;
        windowHeight = windowY;
        ui_Manager = _uiManager;
        addLine({-windowWidth / 2, 0, windowWidth / 2, 0}, {0, 0, 0, 255}, nullptr);
        addLine({0, -windowHeight / 2, 0, windowHeight / 2}, {0, 0, 0, 255}, nullptr);
    }

    bool addLine(Line::Coords lineCoords, SDL_Color color, uiFunctionsRecord *owner) {
        cout << "GOT x1:" << lineCoords.x1 << " y1:" << lineCoords.y1 << " x2:" << lineCoords.x1 << " y2:"
             << lineCoords.y2 << endl;
        if (lineCoords.y1 <= -2000000000 || lineCoords.y1 > 2000000000 || lineCoords.y2 <= -2000000000 ||
            lineCoords.y2 > 2000000000)
            return false; /*при достижении космического значения не добавляет линию в график*/
/*
        if (lineCoords.x1 > windowWidth / 2 || lineCoords.x1 < -windowWidth / 2 || lineCoords.x2 > windowWidth / 2 ||
            lineCoords.x2 < -windowWidth / 2 || lineCoords.y1 > windowHeight / 2 || lineCoords.y1 < -windowHeight / 2 ||
            lineCoords.y2 > windowHeight / 2 || lineCoords.y2 < -windowHeight / 2) {
            return false;
        }*/
        if (lineCoords.x1 > windowWidth / 2 || lineCoords.x1 < -windowWidth / 2 || lineCoords.x2 > windowWidth / 2 ||
            lineCoords.x2 < -windowWidth / 2) {
            return false;
        }
        if (lineCoords.y1 > windowHeight / 2 && lineCoords.y2 > windowHeight / 2)
            return false;
        if (lineCoords.y2 < -windowHeight / 2 && lineCoords.y1 < -windowHeight / 2)
            return false;

        if (lineCoords.y1 > windowHeight / 2 && lineCoords.y2 <= windowHeight / 2)
            lineCoords.y1 = windowHeight / 2;
        if (lineCoords.y1 < -windowHeight / 2 && lineCoords.y2 >= -windowHeight / 2)
            lineCoords.y1 = -windowHeight / 2;
        if (lineCoords.y2 > windowHeight / 2 && lineCoords.y1 <= windowHeight / 2)
            lineCoords.y2 = windowHeight / 2;
        if (lineCoords.y2 < -windowHeight / 2 && lineCoords.y1 >= -windowHeight / 2)
            lineCoords.y2 = -windowHeight / 2;
        lines.emplace_back(translateToWindowCoords(lineCoords), color, owner);

        return true;
    }

    void checkForRemovals() {
        lines.remove_if(Line::removalCheck);
    }

    void draw() {
        checkForRemovals();
        SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255);
        SDL_RenderDrawRect(renderer, &graphBG);
        SDL_RenderFillRect(renderer, &graphBG);
        for (auto line : lines) {
            line.draw(renderer);
        }
        drawNumerics();
    }

private:
    Line::Coords translateToWindowCoords(Line::Coords coords) {
        Line::Coords tmp{};


        tmp.x2 = coords.x2 + windowWidth / 2;
        tmp.y1 = windowHeight / 2 - coords.y1;
        tmp.y2 = windowHeight / 2 - coords.y2;
        tmp.x1 = coords.x1 + windowWidth / 2;

        return tmp;
    }

    void drawNumerics() {
        for (int i = -windowWidth / 20; i <= windowWidth / 20 + 1; i += 6) {
            ui_Manager->printText(to_string(i), i * 10 + windowWidth / 2, windowHeight / 2 - 7, {0, 0, 0}, 15, true);
        }
        for (int i = windowHeight / 20; i >= -windowHeight / 20; i -= 6) {
            if (i == 0)continue;
            ui_Manager->printText(to_string(i), windowWidth / 2 - 20, windowHeight / 2 - i * 10, {0, 0, 0}, 15, true);
        }
    }
};


#endif //DNCOURSEWORK_GRAPH_HPP
