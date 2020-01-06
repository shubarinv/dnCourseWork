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
		int a1{}, b1{}, a2{}, b2{};
	};

	Line(Coords location, SDL_Color _color) {
		coords = location;
		color = _color;
	}
	void draw(SDL_Renderer* renderer){
		if(renderer== nullptr){
			throw std::runtime_error("Line::draw renderer is NULL!");
		}
		SDL_SetRenderDrawColor(renderer, color.r, color.g, color.b, color.a);
		SDL_RenderDrawLine(renderer,coords.a1,coords.b1,coords.a2,coords.b2);
	}

private:
	SDL_Color color{};
	Coords coords{};
};


#endif //DNCOURSEWORK_LINE_HPP
