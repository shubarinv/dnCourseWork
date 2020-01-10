//
// Created by vhundef on 06.01.2020.
//

#ifndef DNCOURSEWORK_LINE_HPP
#define DNCOURSEWORK_LINE_HPP


#include <SDL_pixels.h>
#include <SDL_render.h>
#include <stdexcept>

class Line {
public:
    struct Coords {
        int x1{}, y1{}, x2{}, y2{};
    };
    bool canBeRemoved = true;

    Line(Coords location, SDL_Color _color, uiFunctionsRecord *_owner) {
        coords = location;
        cout << "INT x1:" << coords.x1 << " y1:" << coords.y1 << " x2:" << coords.x1 << " y2:" << coords.y2 << endl;
        color = _color;
        owner = _owner;
        if (owner == nullptr) {
            canBeRemoved = false;
        }
    }

    void draw(SDL_Renderer *renderer) {
        if (renderer == nullptr) {
            throw std::runtime_error("Line::draw renderer is NULL!");
        }
        SDL_SetRenderDrawColor(renderer, color.r, color.g, color.b, color.a);
        SDL_RenderDrawLine(renderer, coords.x1, coords.y1, coords.x2, coords.y2);
    }

    static bool removalCheck(Line line) {
        if (line.canBeRemoved) {
            return (line.owner->isRemove());
        } else
            return false;
    }

private:
    SDL_Color color{};
    Coords coords{};
    uiFunctionsRecord *owner;
public:
    [[nodiscard]] uiFunctionsRecord *getOwner() const {
        return owner;
    }
};


#endif //DNCOURSEWORK_LINE_HPP
