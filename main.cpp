#include "Game.h"
#include "View.h"
#include "Scene.h"

int main(){
	//Game game;
	//game.start();

    GameView* pGameView = NewGameView({ 800, 600 });
    GameScene* pGameScene = NewGameScene();
    EnterGameLoop(*pGameView, UpdateGameScene, DrawGameScene, pGameScene);

	return 0;
}
