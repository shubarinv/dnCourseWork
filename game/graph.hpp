//
// Created by vhundef on 06.01.2020.
//

#ifndef DNCOURSEWORK_GRAPH_HPP
#define DNCOURSEWORK_GRAPH_HPP


#include <SDL_render.h>
#include <list>
#include "line.hpp"

class Graph {
private:
	SDL_Renderer *renderer{};
	std::list<Line> lines{};
	int windowHeight{0};
	int windowWidth{0};
	SDL_Rect graphBG{};
public:
	Graph(SDL_Renderer *_renderer, int windowX, int windowY) {
		if (renderer == nullptr) {
			throw std::runtime_error("Graph::Graph() renderer is NULL");
		}
		renderer = _renderer;
		graphBG.x = 0;
		graphBG.y = 0;
		graphBG.w = windowX;
		graphBG.h = windowY;
	}

	void addLine(Line::Coords lineCoords, SDL_Color color) {
		if (lineCoords.x1 > windowWidth || lineCoords.x2 > windowWidth || lineCoords.x1 < 0 || lineCoords.x2 < 0 ||
		    lineCoords.y1 < 0 || lineCoords.y1 > windowHeight || lineCoords.y2 < 0 || lineCoords.y2 > windowHeight) {
			throw std::runtime_error("Graph::addLine() coords are out of bounds");
		}
		lines.emplace_back(lineCoords, color);
	}

	void draw() {
		SDL_RenderDrawRect(renderer, &graphBG);
		SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255);
		SDL_RenderFillRect(renderer, &graphBG);
		for (auto line : lines) {
			line.draw(renderer);
		}
	}

};


#endif //DNCOURSEWORK_GRAPH_HPP
