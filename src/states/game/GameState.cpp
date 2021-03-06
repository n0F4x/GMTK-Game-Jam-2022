#include <iostream>
#include "states/game/GameState.hpp"

#include "states/game/gamestates/GamePlayState.hpp"
#include "states/game/gamestates/GamePausedState.hpp"
#include "engine/Assets.hpp"
#include "animations/Bezier.hpp"


GameState::GameState() {
	addStateMachine(&_stateMachine);
	_stateMachine.addState("Play", std::make_unique<GamePlayState>());
	_stateMachine.addState("Paused", std::make_unique<GamePausedState>());

	_stateMachine.setInitialState("Play");

	_marker.setOrigin(5, 5);
	_marker.setScale(5.f, 5.f);
	renderer().push_priority(&_marker);

	background_setup();
	character_setup();
	postits_setup();
    game_board_setup();
	helper_setup();
}


void GameState::handle_event(const sf::Event& event) {
	_stateMachine->handle_event(event);
}

sf::Clock timer;
int state = 0;

void GameState::on_update() {
	_stateMachine->update();

    _boardGameManager.updateBoard();
    _boyBar.setProgress(_boardGameManager.getCharacter(BOY).getHappinessNormed());
    _girlBar.setProgress(_boardGameManager.getCharacter(GIRL).getHappinessNormed());
    _grandpaBar.setProgress(_boardGameManager.getCharacter(GRANDPA).getHappinessNormed());
    _dogBar.setProgress(_boardGameManager.getCharacter(DOGE).getHappinessNormed());

    if (_boardGameManager.getActiveCharacter().getType() == BOY) {
		_marker.setPosition(360, 140);
		_marker.setRotation(-45);
    }
    if (_boardGameManager.getActiveCharacter().getType() == GIRL) {
        _marker.setPosition(1570, 140);
		_marker.setRotation(45);
    }
    if (_boardGameManager.getActiveCharacter().getType() == GRANDPA) {
		_marker.setPosition(1570, 960);
		_marker.setRotation(135);
    }
    if (_boardGameManager.getActiveCharacter().getType() == DOGE) {
		_marker.setPosition(360, 935);
		_marker.setRotation(-135);
    }

    if (state == 0) {
        _timeDisplay.setProgress((3.f - timer.getElapsedTime().asSeconds()) / 3.f);
        if (timer.getElapsedTime().asSeconds() >= 3.f) {
            state = 1;
            *store().get("selector") = "Select";
            *store().get("dice") = "7";
        }
    } else if (state == 1) {
        *store().get("selector") = "LookAround";
        if (*store().get("dice") != "7") {
            int dice = (rand() % 6) + 1;
            std::cout << "dice " << *store().get("dice") << std::endl;
            if (*store().get("dice") != "0") dice = std::atoi(store().get("dice")->c_str());
            _boardGameManager.diceRoll(dice);
            state = 2;
        }
    } else if (state == 2) {
        if (!_boardGameManager.isBoardOccupied()) {
            state = 0;
            timer.restart();
        }
    }
}

void GameState::on_draw() {
	renderer().render();
	_stateMachine->draw();
}

void GameState::on_activate() {
    timer.restart();
    _boardGameManager.getCharacter(BOY).setHappiness(std::stoi(*globalStore()->get("boy_happiness")));
    _boardGameManager.getCharacter(BOY).setHappiness(std::stoi(*globalStore()->get("girl_happiness")));
    _boardGameManager.getCharacter(BOY).setHappiness(std::stoi(*globalStore()->get("grandpa_happiness")));
    _boardGameManager.getCharacter(BOY).setHappiness(std::stoi(*globalStore()->get("doge_happiness")));
}



void GameState::character_setup() {
	_boy.setTexture(&engine::Assets::getTexture("Environment/blue_player"));
	_boy.setPosition(360, 120);
	_boy.setScale(8.f, 8.f);
	addObject(&_boy);
	renderer().push_basic(&_boy);

	_girl.setTexture(&engine::Assets::getTexture("Environment/green_player"));
	_girl.setPosition(sf::Vector2f(1300, 100));
	_girl.setScale(10.f, 10.f);
	addObject(&_girl);
	renderer().push_basic(&_girl);

	_grandpa.setTexture(&engine::Assets::getTexture("Environment/red_player"));
	_grandpa.setPosition(1290, 650);
	_grandpa.setScale(12.f, 12.f);
	addObject(&_grandpa);
	renderer().push_basic(&_grandpa);

	_dog.setTexture(&engine::Assets::getTexture("Environment/yellow_player"));
	_dog.setPosition(sf::Vector2f(350, 700));
	_dog.setScale(8.f, 8.f);
	addObject(&_dog);
	renderer().push_basic(&_dog);

	// Happinesses
	_boyBarBack.setTexture(&engine::Assets::getTexture("UI/bar_background"));
	_boyBarBack.setPosition(50, 50);
	_boyBarBack.setScale(4.f, 4.f);
	addObject(&_boyBarBack);
	renderer().push_basic(&_boyBarBack);

	_boyBar.setPosition(54, 54);
	addObject(&_boyBar);
	renderer().push_basic(&_boyBar);
	_boyBar.attach_parent(&_boyBarBack);
	_boyBar.setPrimaryColor(sf::Color(88, 193, 53, 255));
	_boyBar.setSecondaryColor(sf::Color(223, 63, 35, 255));

	_girlBarBack.setTexture(&engine::Assets::getTexture("UI/bar_background"));
	_girlBarBack.setScale(4.f, 4.f);
	addObject(&_girlBarBack);
	renderer().push_basic(&_girlBarBack);

	addObject(&_girlBar);
	renderer().push_basic(&_girlBar);
	_girlBar.attach_parent(&_girlBarBack);
	_girlBar.setPrimaryColor(sf::Color(88, 193, 53, 255));
	_girlBar.setSecondaryColor(sf::Color(223, 63, 35, 255));

	_girlBarBack.rotate(180);
	_girlBarBack.setPosition(1870, 100);
	_girlBar.setPosition(1866, 96);

	_dogBarBack.setTexture(&engine::Assets::getTexture("UI/bar_background"));
	_dogBarBack.setPosition(50, 990);
	_dogBarBack.setScale(4.f, 4.f);
	addObject(&_dogBarBack);
	renderer().push_basic(&_dogBarBack);

	_dogBar.setPosition(54, 994);
	addObject(&_dogBar);
	renderer().push_basic(&_dogBar);
	_dogBar.attach_parent(&_dogBarBack);
	_dogBar.setPrimaryColor(sf::Color(88, 193, 53, 255));
	_dogBar.setSecondaryColor(sf::Color(223, 63, 35, 255));

	_gradpaBarBack.setTexture(&engine::Assets::getTexture("UI/bar_background"));
	_gradpaBarBack.setScale(4.f, 4.f);
	addObject(&_gradpaBarBack);
	renderer().push_basic(&_gradpaBarBack);

	addObject(&_grandpaBar);
	renderer().push_basic(&_grandpaBar);
	_grandpaBar.attach_parent(&_gradpaBarBack);
	_grandpaBar.setPrimaryColor(sf::Color(88, 193, 53, 255));
	_grandpaBar.setSecondaryColor(sf::Color(223, 63, 35, 255));

	_gradpaBarBack.rotate(180);
	_gradpaBarBack.setPosition(1870, 1030);
	_grandpaBar.setPosition(1866, 1026);
}


void GameState::background_setup() {
	_floor.setTexture(&engine::Assets::getTexture("Environment/floor"));
	_floor.setScale(6.f, 6.f);
	renderer().push_background(&_floor);

	_table.setTexture(&engine::Assets::getTexture("Environment/table"));
	_table.setPosition(480, 270);
	_table.setScale(6.f, 6.f);
	renderer().push_background(&_table);

	_table2.setTexture(&engine::Assets::getTexture("Environment/coffeetable"));
	_table2.setPosition(625, -120);
	_table2.setScale(6.f, 6.f);
	renderer().push_background(&_table2);

	_croissant.setTexture(&engine::Assets::getTexture("Environment/croissant2"));
	_croissant.setPosition(740, -40);
	_croissant.setScale(4.f, 4.f);
	renderer().push_background(&_croissant);

	_plant.setTexture(&engine::Assets::getTexture("Environment/plant"));
	_plant.setPosition(1170, 82);
	_plant.setScale(4.f, 4.f);
	renderer().push_background(&_plant);

	_coffee.setTexture(&engine::Assets::getTexture("Environment/coffee"));
	_coffee.setPosition(890, 30);
	_coffee.setScale(4.f, 4.f);
	renderer().push_background(&_coffee);

	_plant2.setTexture(&engine::Assets::getTexture("Environment/plant2"));
	_plant2.setPosition(700, 900);
	_plant2.setScale(4.f, 4.f);
	renderer().push_background(&_plant2);
}


void GameState::postits_setup() {
	_boyPostit.setTexture(&engine::Assets::getTexture("UI/boy_postit"));
	addObject(&_boyPostit);
	renderer().push_priority(&_boyPostit);
	_boyPostit.setScale(6.f, 6.f);
	_boyText.attach_parent(&_boyPostit);
	_boyText.setPosition(25, 135);
	_boyText.setFillColor(sf::Color::Black);
	renderer().push_priority(&_boyText);
	_boyPostit.setPosition(50, 125);

	_girlPostit.setTexture(&engine::Assets::getTexture("UI/girl_postit"));
	addObject(&_girlPostit);
	renderer().push_priority(&_girlPostit);
	_girlPostit.setScale(6.f, 6.f);
	_girlText.attach_parent(&_girlPostit);
	_girlText.setPosition(25, 135);
	_girlText.setFillColor(sf::Color::Black);
	renderer().push_priority(&_girlText);
	_girlPostit.setPosition(1600, 125);

	_dogPostit.setTexture(&engine::Assets::getTexture("UI/dog_postit"));
	addObject(&_dogPostit);
	renderer().push_priority(&_dogPostit);
	_dogPostit.setScale(6.f, 6.f);
	_dogText.attach_parent(&_dogPostit);
	_dogText.setPosition(25, 135);
	_dogText.setFillColor(sf::Color::Black);
	renderer().push_priority(&_dogText);
	_dogPostit.setPosition(50, 525);

	_grandpaPostit.setTexture(&engine::Assets::getTexture("UI/grandpa_postit"));
	addObject(&_grandpaPostit);
	renderer().push_priority(&_grandpaPostit);
	_grandpaPostit.setScale(6.f, 6.f);
	_grandpaText.attach_parent(&_grandpaPostit);
	_grandpaText.setPosition(25, 135);
	_grandpaText.setFillColor(sf::Color::Black);
	renderer().push_priority(&_grandpaText);
	_grandpaPostit.setPosition(1600, 525);
}

void GameState::game_board_setup() {
    renderer().push_basic(&_boardGameManager);
    addObject(&_boardGameManager);

    for (int i = 0; i < 4; ++i) {
        addObject(&_boardGameManager.getCharacter(static_cast<CharacterType>(i)));
        _boardGameManager.getCharacter(static_cast<CharacterType>(i)).setLoseCallback(loseCallback);
    }

    _boardGameManager.setGameOverCallback(gameOverCallback);
}


void GameState::helper_setup() {
	_tileInfoDisplay.setTexture(&engine::Assets::getTexture("UI/helper"));
	addObject(&_tileInfoDisplay);
	_tileInfoDisplay.setScale(6.f, 6.f);
	renderer().push_basic(&_tileInfoDisplay);
	_tileInfoDisplay.setPosition(1040, 885);

	_timeDisplay.setPosition(660, 840);
	_timeDisplay.setPrimaryColor(sf::Color(255, 255, 255, 100));
	_timeDisplay.setSecondaryColor(sf::Color(255, 255, 255, 100));
	addObject(&_timeDisplay);
	renderer().push_basic(&_timeDisplay);
}

