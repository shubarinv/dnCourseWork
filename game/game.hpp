//
// Created by vhundef on 24.12.2019.
//

#ifndef PROGONHLANG_GAME_HPP
#define PROGONHLANG_GAME_HPP


#include <SDL.h>
#include <iostream>
#include <stdexcept>
#include "UI/ui_manager.hpp"
#include "UI/ui_main_menu.hpp"
#include "input_manager.hpp"
#include "windows_manager.hpp"
#include "graph.hpp"
#include "graph_builder.hpp"


using namespace std;

class Game {
private:
    InputManager *inputManager{};
    WindowsManager *winManager{};
    UI_Manager *graphUI_Manger{};
    UI_Manager *functionsUI_Manger{};
    GraphBuilder *graphBuilder{};
    Graph *graph{};
	char state = 'm';///< r-playing game| p-pause| m-main_Menu| e-Editing field
public:
	Game() {
		std::cout << "Trying to init SDL2..." << std::endl;
		if (SDL_Init(SDL_INIT_VIDEO) != 0) {
			std::string error = SDL_GetError();
			SDL_LogCritical(SDL_LOG_CATEGORY_ERROR, "%s", error.c_str());
			throw std::runtime_error("Unable to init SDL2");
		}
		winManager = new WindowsManager();


        functionsUI_Manger = new UI_Manager(SDL_GetWindowSurface(winManager->getFunctionsWindow()),
                                            winManager->getFunctionsWinRender(), winManager->getFunctionsWindow(),
                                            nullptr); //init UI_Manager and font related stuff
        graphUI_Manger = new UI_Manager(SDL_GetWindowSurface(winManager->getGraphWindow()),
                                        winManager->getGraphWinRender(), winManager->getGraphWindow(),
                                        nullptr); //init UI_Manager and font related stuff
        inputManager = new InputManager();
        int h, w;
        SDL_GetWindowSize(winManager->getGraphWindow(), &w, &h);
        graph = new Graph(winManager->getGraphWinRender(), h, w);
        graphBuilder = new GraphBuilder(graph);
        SDL_LogInfo(SDL_LOG_CATEGORY_APPLICATION, "SDL2 init - Good\nGame Start");
        run(); // Starts the game
    }

private:
	int run() {
		Uint64 frameStart;
		Uint64 frameTime = 0;
		Uint64 curTime = 0;
		Uint64 endTime = 0;

		int frameDelay = 2;
        graphBuilder->buildGraph("x^2");
		while (!inputManager->quitEventCheck()) {
		    frameStart=SDL_GetTicks();
			winManager->clearRenderer(winManager->getGraphWinRender());
			winManager->clearRenderer(winManager->getFunctionsWinRender());
			SDL_SetRenderDrawColor(winManager->getFunctionsWinRender(), 84, 135, 133, 255);
			SDL_SetRenderDrawColor(winManager->getGraphWinRender(), 86, 135, 84, 255);
			inputManager->updateEvents();
			graph->draw();

			SDL_RenderPresent(winManager->getFunctionsWinRender());
			SDL_RenderPresent(winManager->getGraphWinRender());

			if (state == 'q') break;
			frameTime = SDL_GetTicks() - frameStart;
			if (frameDelay > frameTime) {
				SDL_Delay(frameDelay - frameTime);
			}
		}
		delete inputManager;
		free(graphUI_Manger);
		free(functionsUI_Manger);
		SDL_DestroyRenderer(winManager->getGraphWinRender());
		SDL_DestroyRenderer(winManager->getFunctionsWinRender());
		SDL_DestroyWindow(winManager->getGraphWindow());
		SDL_DestroyWindow(winManager->getFunctionsWindow());

		return 0;
	}
};


#endif //PROGONHLANG_GAME_HPP
