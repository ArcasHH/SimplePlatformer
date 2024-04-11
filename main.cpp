#include "Game.h"
#include "View.h"
#include "Scene.h"
#include <iostream>

int main(){
	//Game game;
	//game.start();
    try
    {
        GameView* pGameView = NewGameView({ 800, 600 });
        GameScene* pGameScene = NewGameScene();

        EnterGameLoop(*pGameView, UpdateGameScene, DrawGameScene, pGameScene);
    }
    catch (const std::exception& ex)
    {
        std::cerr << ex.what() << std::endl;
        return 1;
    }
	return 0;
}
