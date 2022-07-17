#include "states/game/gamestates/GameInitState.hpp"

#include "engine/Assets.hpp"
#include "animations/Bezier.hpp"
#include "engine/Window.hpp"


GameInitState::GameInitState() {
	_boy.setTexture(&engine::Assets::getTexture("Environment/blue_player"));
	_boy.setPosition(360 - 500, 120 - 500);
	_boy.scale(8.f, 8.f);
	addObject(&_boy);
	renderer().push_basic(&_boy);
	auto animator = _boy.setComponent(std::make_unique<engine::Animator>());
	animator->addAnimation("in", std::make_unique<animations::Ease>());
	animator->findAnimation("in")->setDistance({ 500.f, 500.f });
	animator->findAnimation("in")->setTime(sf::seconds(3));

	_girl.setTexture(&engine::Assets::getTexture("Environment/green_player"));
	_girl.setPosition(sf::Vector2f(1320 + 500 - 20, 120 - 500 - 20));
	_girl.scale(10.f, 10.f);
	addObject(&_girl);
	renderer().push_basic(&_girl);
	animator = _girl.setComponent(std::make_unique<engine::Animator>());
	animator->addAnimation("in", std::make_unique<animations::Ease>());
	animator->findAnimation("in")->setDistance({ -500.f, 500.f });
	animator->findAnimation("in")->setTime(sf::seconds(3.5f));

	_grandpa.setTexture(&engine::Assets::getTexture("Environment/red_player"));
	_grandpa.setPosition(1290 + 500, 650 + 500);
	_grandpa.scale(12.f, 12.f);
	addObject(&_grandpa);
	renderer().push_basic(&_grandpa);
	animator = _grandpa.setComponent(std::make_unique<engine::Animator>());
	animator->addAnimation("in", std::make_unique<animations::Ease>());
	animator->findAnimation("in")->setDistance({ -500.f, -500.f });
	animator->findAnimation("in")->setTime(sf::seconds(4));

	_dog.setTexture(&engine::Assets::getTexture("Environment/yellow_player"));
	_dog.setPosition(sf::Vector2f(350 - 500, 700 + 500));
	_dog.scale(8.f, 8.f);
	addObject(&_dog);
	renderer().push_basic(&_dog);
	animator = _dog.setComponent(std::make_unique<engine::Animator>());
	animator->addAnimation("in", std::make_unique<animations::Ease>());
	animator->findAnimation("in")->setDistance({ 500.f, -500.f });
	animator->findAnimation("in")->setTime(sf::seconds(4.5f));

	// Happinesses
	_boyBarBack.setTexture(&engine::Assets::getTexture("UI/bar_background"));
	_boyBarBack.setPosition(50, 50 - 500);
	_boyBarBack.scale(4.f, 4.f);
	addObject(&_boyBarBack);
	renderer().push_basic(&_boyBarBack);
	animator = _boyBarBack.setComponent(std::make_unique<engine::Animator>());
	animator->addAnimation("in", std::make_unique<animations::Ease>());
	animator->findAnimation("in")->setDistance({ 0, 500.f });
	animator->findAnimation("in")->setTime(sf::seconds(6.f));

	_boyBar.setPosition(54, 54 - 500);
	addObject(&_boyBar);
	renderer().push_basic(&_boyBar);
	_boyBar.attach_parent(&_boyBarBack);
	_boyBar.setPrimaryColor(sf::Color(88, 193, 53, 255));
	_boyBar.setSecondaryColor(sf::Color(223, 63, 35, 255));

	_girlBarBack.setTexture(&engine::Assets::getTexture("UI/bar_background"));
	_girlBarBack.scale(4.f, 4.f);
	addObject(&_girlBarBack);
	renderer().push_basic(&_girlBarBack);
	animator = _girlBarBack.setComponent(std::make_unique<engine::Animator>());
	animator->addAnimation("in", std::make_unique<animations::Ease>());
	animator->findAnimation("in")->setDistance({ 0, 500.f });
	animator->findAnimation("in")->setTime(sf::seconds(6.f));

	addObject(&_girlBar);
	renderer().push_basic(&_girlBar);
	_girlBar.attach_parent(&_girlBarBack);
	_girlBar.setPrimaryColor(sf::Color(88, 193, 53, 255));
	_girlBar.setSecondaryColor(sf::Color(223, 63, 35, 255));

	_girlBarBack.rotate(180);
	_girlBarBack.setPosition(1870, 100 - 500);
	_girlBar.setPosition(1866, 96 - 500);

	_dogBarBack.setTexture(&engine::Assets::getTexture("UI/bar_background"));
	_dogBarBack.setPosition(50, 990 + 500);
	_dogBarBack.scale(4.f, 4.f);
	addObject(&_dogBarBack);
	renderer().push_basic(&_dogBarBack);
	animator = _dogBarBack.setComponent(std::make_unique<engine::Animator>());
	animator->addAnimation("in", std::make_unique<animations::Ease>());
	animator->findAnimation("in")->setDistance({ 0, -500.f });
	animator->findAnimation("in")->setTime(sf::seconds(6.f));

	_dogBar.setPosition(54, 994 + 500);
	addObject(&_dogBar);
	renderer().push_basic(&_dogBar);
	_dogBar.attach_parent(&_dogBarBack);
	_dogBar.setPrimaryColor(sf::Color(88, 193, 53, 255));
	_dogBar.setSecondaryColor(sf::Color(223, 63, 35, 255));

	_gradpaBarBack.setTexture(&engine::Assets::getTexture("UI/bar_background"));
	_gradpaBarBack.scale(4.f, 4.f);
	addObject(&_gradpaBarBack);
	renderer().push_basic(&_gradpaBarBack);
	animator = _gradpaBarBack.setComponent(std::make_unique<engine::Animator>());
	animator->addAnimation("in", std::make_unique<animations::Ease>());
	animator->findAnimation("in")->setDistance({ 0, -500.f });
	animator->findAnimation("in")->setTime(sf::seconds(6.f));

	addObject(&_grandpaBar);
	renderer().push_basic(&_grandpaBar);
	_grandpaBar.attach_parent(&_gradpaBarBack);
	_grandpaBar.setPrimaryColor(sf::Color(88, 193, 53, 255));
	_grandpaBar.setSecondaryColor(sf::Color(223, 63, 35, 255));

	_gradpaBarBack.rotate(180);
	_gradpaBarBack.setPosition(1870, 1030 + 500);
	_grandpaBar.setPosition(1866, 1026 + 500);

	////////////////
	// Background //
	////////////////
	_floor.setTexture(&engine::Assets::getTexture("Environment/floor"));
	_floor.scale(6.f, 6.f);
	renderer().push_background(&_floor);

	_table.setTexture(&engine::Assets::getTexture("Environment/table"));
	_table.setPosition(480, 270);
	_table.scale(6.f, 6.f);
	renderer().push_background(&_table);

	_table2.setTexture(&engine::Assets::getTexture("Environment/coffeetable"));
	_table2.setPosition(500, -120);
	_table2.scale(6.f, 6.f);
	renderer().push_background(&_table2);

	_croissant.setTexture(&engine::Assets::getTexture("Environment/croissant2"));
	_croissant.setPosition(740, -40);
	_croissant.scale(4.f, 4.f);
	renderer().push_background(&_croissant);

	_title.setTexture(&engine::Assets::getTexture("UI/title"));
	_title.setPosition(620, 18);
	_title.scale(7.5f / 5.f, 7.5f / 5.f);
	renderer().push_background(&_title);

	_plant.setTexture(&engine::Assets::getTexture("Environment/plant"));
	_plant.setPosition(1170, 82);
	_plant.scale(4.f, 4.f);
	renderer().push_background(&_plant);

	_coffee.setTexture(&engine::Assets::getTexture("Environment/coffee"));
	_coffee.setPosition(890, 30);
	_coffee.scale(4.f, 4.f);
	renderer().push_background(&_coffee);

	_plant2.setTexture(&engine::Assets::getTexture("Environment/plant2"));
	_plant2.setPosition(700, 900);
	_plant2.scale(4.f, 4.f);
	renderer().push_background(&_plant2);
}

int GameInitState::setup() {
	_storeInit = globalStore()->get("init");
	return 0;
}


void GameInitState::on_update() {
	if (!_init && *_storeInit == "true") {
		_init = true;
		// START ANIMATIONS
		_boy.getComponent<engine::Animator>()->findAnimation("in")->start();
		_girl.getComponent<engine::Animator>()->findAnimation("in")->start();
		_grandpa.getComponent<engine::Animator>()->findAnimation("in")->start();
		_dog.getComponent<engine::Animator>()->findAnimation("in")->start();

		_boyBarBack.getComponent<engine::Animator>()->findAnimation("in")->start();
		_girlBarBack.getComponent<engine::Animator>()->findAnimation("in")->start();
		_gradpaBarBack.getComponent<engine::Animator>()->findAnimation("in")->start();
		_dogBarBack.getComponent<engine::Animator>()->findAnimation("in")->start();
	}

	if (_clock.getElapsedTime() >= sf::seconds(6)) {
		*_storeInit = "false";
		_init = false;
		//changeState("Play");
	}
}

void GameInitState::on_draw() {
	renderer().render();
}
