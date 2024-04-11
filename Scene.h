#pragma once
#include "TmxLevel.h"

/// ѕредварительное объ€вление (pre-declaration) структуры
///  позволит передавать и хранить указатели и ссылки на неЄ,
///  но не позволит пользоватьс€ или создавать,
///  поскольку мы ещЄ не знаем ни размер в байтах, ни свойства структуры.
struct GameView;

/// —труктура, абстрагирующа€ игровую сцену.
///   од ниже намеренно написан в процедурном стиле:
///  - используютс€ структуры
///  - используетс€ €вный вызов new и delete.
struct GameScene
{
    TmxLevel level;
    TmxObject player;
    std::vector<TmxObject> enemies;
    std::vector<TmxObject> coins;
};

GameScene* NewGameScene();
void UpdateGameScene(void* pData, GameView& view, float deltaSec);
void DrawGameScene(void* pData, GameView& view);
void DestroyGameScene(GameScene*& pScene);