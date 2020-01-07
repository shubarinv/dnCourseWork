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
		if (_renderer == nullptr) {
			throw std::runtime_error("Graph::Graph() renderer is NULL");
		}
		renderer = _renderer;
		graphBG.x = 0;
		graphBG.y = 0;
		graphBG.w = windowX;
		graphBG.h = windowY;
		windowWidth=windowX;
		windowHeight=windowY;
		addLine({-windowWidth/2,0,windowWidth/2,0},{0,0,0,255});
		addLine({0,-windowHeight/2,0,windowHeight/2},{0,0,0,255});
	}

	bool addLine(Line::Coords lineCoords, SDL_Color color) {
		if (lineCoords.x1 > windowWidth/ 2 || lineCoords.x1 < -windowWidth/2 || lineCoords.x2 > windowWidth / 2 ||
		    lineCoords.x2 < -windowWidth / 2 || lineCoords.y1 > windowHeight / 2 || lineCoords.y1 < -windowHeight / 2 ||
		    lineCoords.y2 > windowHeight / 2 || lineCoords.y2 < -windowHeight / 2) {
			return false;
		}
		lines.emplace_back(translateToWindowCoords(lineCoords), color);
		return true;
	}


	void draw() {
		SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255);
		SDL_RenderDrawRect(renderer, &graphBG);
		SDL_RenderFillRect(renderer, &graphBG);
		for (auto line : lines) {
			line.draw(renderer);
		}
	}

private:
	Line::Coords translateToWindowCoords(Line::Coords coords) {
		Line::Coords tmp{};
		if (coords.x1 > 0) tmp.x1 = coords.x1 + windowWidth / 2;
		if (coords.x2 > 0) tmp.x2 = coords.x2 + windowWidth / 2;
		if (coords.y1 > 0) tmp.y1 = coords.y1 + windowHeight / 2;
		if (coords.y2 > 0) tmp.y2 = coords.y2 + windowHeight / 2;
		if (coords.x1 < 0) tmp.x1 = windowWidth / 2 + coords.x1;
		if (coords.x2 < 0) tmp.x2 = windowWidth / 2 + coords.x2;
		if (coords.y1 < 0) tmp.y1 = windowHeight / 2 + coords.y1;
		if (coords.y2 < 0) tmp.y2 = windowHeight / 2 + coords.y2;
		if (coords.x1 == 0)tmp.x1 = windowWidth / 2;
		if (coords.x2 == 0)tmp.x2 = windowWidth / 2;
		if (coords.y1 == 0)tmp.y1 = windowHeight / 2;
		if (coords.y2 == 0)tmp.y2 = windowHeight / 2;
		return tmp;
	}
};


#endif //DNCOURSEWORK_GRAPH_HPP
