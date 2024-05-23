#include "Windows.h"

static void onExit() {
    auto& Glob = getGlobalState();
    Glob.setCurrWindow("exit");
}

static void onStartGame(int& level, int l) {
    level = l;
    auto& Glob = getGlobalState();
    Glob.setCurrWindow(GameWindow::Name);
}

static void onSettings() {
    auto& Glob = getGlobalState();
    Glob.setCurrWindow(SettingsWindow::Name);
}
static void onLevel() {
    auto& Glob = getGlobalState();
    Glob.setCurrWindow(LevelWindow::Name);
}

static void onMenu() {
    auto& Glob = getGlobalState();
    Glob.setCurrWindow(MenuWindow::Name);
}

static void onPause(bool &is_pause) {
    is_pause = false;
}

static void updatePauseScreen(sf::View& view, std::vector<std::unique_ptr<PushButton>>& Buttons, std::vector<std::unique_ptr<Object>>& Objects) {
    sf::Vector2f view_center = view.getCenter();
    Objects[1]->sprite.setPosition(view_center.x - view.getSize().x / 2, view_center.y - view.getSize().y / 2);
    for (int i = 0; i < Buttons.size(); ++i)
        Buttons[i]->setPosition(view_center.x + 128 * i - view.getSize().x / 4, view_center.y);
}
static void playMusic(sf::Music& music) {
    if (music.getStatus() != sf::Music::Playing) {
        auto& mvec = getGlobalState().getMusics();
        for (auto&& m : mvec)
            m->stop();
        music.play();
    }
}
static void upVolume() {
    auto& mvec = getGlobalState().getMusics();
    for (auto&& m : mvec) {
        float vol = m->getVolume();
        if (vol <= 90)
            m->setVolume(vol + 10.f);
    }
}
static void downVolume() {
    auto& mvec = getGlobalState().getMusics();
    for (auto&& m : mvec) {
        float vol = m->getVolume();
        if (vol >= 10)
            m->setVolume(vol - 10.f);
    }
}
//for the level with the value l, set the music from mvec and upload it to the scene
static void SetLevel(int level, int l, sf::Music& music, std::unique_ptr<GameScene> &gameScene) {
    if (level == l && music.getStatus() != sf::Music::Playing) {
        gameScene = std::make_unique<GameScene>("map/lvl" + std::to_string(level) + ".tmx");
        playMusic(music);
    }
}


void BaseWindow::input(const sf::RenderWindow& window, const sf::View& view) {
    for (auto&& Obj : Buttons)
        Obj->input(window, view);
}
void BaseWindow::update(sf::RenderWindow& window, sf::View& view, const sf::Vector2f windowSize) {
    for (auto&& Obj : Buttons)
        Obj->update(window, view);
}
void BaseWindow::draw(sf::RenderWindow& window) {
    for (auto&& Obj : Objects)
        Obj->draw(window);
    for (auto&& Obj : Buttons)
        Obj->draw(window);
}

MenuWindow::MenuWindow(GameWindow &GW) : GW{ GW } {
    auto& Gl = getGlobalState();
    menuMusic.openFromFile("audio/Pixel Music Pack/Ogg/Pixel 1.ogg");
    menuMusic.setLoop(true);
    Gl.recordMusic(&menuMusic);

    Objects.emplace_back(std::make_unique<Object>("images/Free Pixel Art Hill/ajys.png", 0.f, 0.f));

    auto& StartBtn = Buttons.emplace_back(std::make_unique<PushButton>("images/playBTN.png", sf::FloatRect(sf::Vector2f(100.f, 200.f), sf::Vector2f())));
    StartBtn->registerFunction(onStartGame, std::ref(GW.getCurrLvl()), 1);

    auto& LevelBtn = Buttons.emplace_back(std::make_unique<PushButton>("images/levelBTN.png", sf::FloatRect(sf::Vector2f(100.f, 350.f), sf::Vector2f())));
    LevelBtn->registerFunction(onLevel);

    auto& SettingsBtn = Buttons.emplace_back(std::make_unique<PushButton>("images/settingsBTN.png", sf::FloatRect(sf::Vector2f(100.f, 500.f), sf::Vector2f())));
    SettingsBtn->registerFunction(onSettings);

    auto& ExitBtn = Buttons.emplace_back(std::make_unique<PushButton>("images/exitBTN.png", sf::FloatRect(sf::Vector2f(100.f, 650.f), sf::Vector2f())));
    ExitBtn->registerFunction(onExit);
}

void MenuWindow::update(sf::RenderWindow& window, sf::View& view, const sf::Vector2f windowSize) {
    if (menuMusic.getStatus() != sf::Music::Playing) { //once when window changes
        playMusic(menuMusic);
        view.reset(sf::FloatRect(0.0f, 0.0f, windowSize.x, windowSize.y));
        GW.getPause() = false;
    }
    BaseWindow::update(window, view, windowSize);
}

GameWindow::GameWindow() {
    auto& Gl = getGlobalState();
    for (int i = 0; i <= num_levels; ++i) {
        gameMusic[i].openFromFile("audio/Pixel Music Pack/Ogg/Pixel " + std::to_string(i % 12 + 1) + ".ogg");
        gameMusic[i].setLoop(true);
        Gl.recordMusic(&gameMusic[i]);
    }
    SetLevel(CurrLvl, 1, gameMusic[0], gameScene);

    Objects.emplace_back(std::make_unique<Object>("images/light.png", 0.f, 80.f));
    Objects.emplace_back(std::make_unique<Object>("images/line.png", 0.f, 80.f));

    auto& PlayBtn = Buttons.emplace_back(std::make_unique<PushButton>("images/play96.png", sf::FloatRect(sf::Vector2f(100.f, 128.f), sf::Vector2f())));
    PlayBtn->registerFunction(onPause, std::ref(IsPause));

    auto& MenuBtn = Buttons.emplace_back(std::make_unique<PushButton>("images/menu96.png", sf::FloatRect(sf::Vector2f(250.f, 128.f), sf::Vector2f())));
    MenuBtn->registerFunction(onMenu);

    auto& ExitBtn = Buttons.emplace_back(std::make_unique<PushButton>("images/exit96.png", sf::FloatRect(sf::Vector2f(550.f, 128.f), sf::Vector2f())));
    ExitBtn->registerFunction(onExit);
}

void GameWindow::input(const sf::RenderWindow& window, const sf::View& view) {
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Escape))
        IsPause = true;
    if (IsPause)
        BaseWindow::input(window, view);
    gameScene->InputGameScene();
}
void GameWindow::update(sf::RenderWindow& window, sf::View& view, const sf::Vector2f windowSize) {
    sf::Vector2f view_center = view.getCenter();
    Objects[0]->sprite.setPosition(view_center.x - windowSize.x / 2 + 8, view_center.y - windowSize.y / 2 - 8);
    if (IsPause) {
        updatePauseScreen(view, Buttons, Objects);
        BaseWindow::update(window, view, windowSize);
        return;
    }
    for (int i = 1; i <= num_levels; ++i) {
        SetLevel(CurrLvl, i, gameMusic[i], gameScene);
    }

    if (view.getSize().x != window.getSize().x / 2)
        view.setSize(static_cast<float>(window.getSize().x) / 2, static_cast<float>(window.getSize().y) / 2);
    gameScene->Step();
    gameScene->UpdateGameScene(window, view, windowSize, CurrLvl);
}
void GameWindow::draw(sf::RenderWindow& window) {
    gameScene.get()->DrawGameScene(window);
    Objects[0]->draw(window);
    if (IsPause)
        BaseWindow::draw(window);
}
SettingsWindow::SettingsWindow() {

    auto& MenuBtn = Buttons.emplace_back(std::make_unique<PushButton>("images/backBTN.png", sf::FloatRect(sf::Vector2f(100.f, 768.f), sf::Vector2f())));
    MenuBtn->registerFunction(onMenu);

    auto& VolUp = Buttons.emplace_back(std::make_unique<PushButton>("images/sound_up.png", sf::FloatRect(sf::Vector2f(476.f, 200.f), sf::Vector2f())));
    VolUp->registerFunction(upVolume);

    auto& VolDown = Buttons.emplace_back(std::make_unique<PushButton>("images/sound_down.png", sf::FloatRect(sf::Vector2f(100.f, 200.f), sf::Vector2f())));
    VolDown->registerFunction(downVolume);

    for (float i = 0; i < 10; ++i)
        volume_set.emplace_back(std::make_unique<Object>("images/wbox.png", 220.f + 24 * i, 228.f));
}
void SettingsWindow::draw(sf::RenderWindow& window) {
    BaseWindow::draw(window);

    auto& Music = getGlobalState().getMusics().front();

    int vol = static_cast<int>(Music->getVolume() / 10.f);
    for (int i = 0; i < vol; ++i)
        volume_set[i]->draw(window);
}
LevelWindow::LevelWindow(GameWindow& GW) : GW{ GW } {
    auto& MenuBtn = Buttons.emplace_back(std::make_unique<PushButton>("images/backBTN.png", sf::FloatRect(sf::Vector2f(100.f, 768.f), sf::Vector2f())));
    MenuBtn->registerFunction(onMenu);

    for (int i = 1; i <= GameWindow::num_levels; ++i) {
        auto& Btn = Buttons.emplace_back(std::make_unique<PushButton>("images/" + std::to_string(i) + ".png", sf::FloatRect(sf::Vector2f(100.f + 200 * (i - 1), 100.f), sf::Vector2f())));
        Btn->registerFunction(onStartGame, std::ref(GW.getCurrLvl()), i);
    }
}