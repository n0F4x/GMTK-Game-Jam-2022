#include "states/menu/MenuState.hpp"

#include "engine/Window.hpp"
#include "animations/Bezier.hpp"
#include "animations/BezierScale.hpp"
#include "animations/BezierFillColor.hpp"
#include "animations/BezierOutlineColor.hpp"
#include "states/Settings.hpp"


MenuState::MenuState() {
	
}


void MenuState::handle_event(const sf::Event& event) {
	if (!_started && event.type == sf::Event::MouseButtonPressed && event.mouseButton.button == sf::Mouse::Left) {
		_startGame = true;
		_clock.restart();
	}
}


void MenuState::on_activate() {
	background_setup();
	character_setup();
	postits_setup();
	helper_setup();
	music_setup();

	_startGame = false;
	_started = false;
	_characterAnimations = false;

	if (Settings::soundOn) _menuMusic.play();
}

void MenuState::on_deactivate() {
    _menuMusic.stop();
}


void MenuState::on_update() {
	if (_startGame) {
		_fillPulseOnAnimation->stop();
		_fillPulseOffAnimation->stop();
		_outlinePulseOnAnimation->stop();
		_outlinePulseOffAnimation->stop();

		_clickText.getComponent<engine::Animator>()->findAnimation("fillColorOut")->start();
		_clickText.getComponent<engine::Animator>()->findAnimation("outlineColorOut")->start();


		_scaler.getComponent<engine::Animator>()->findAnimation("zoomOut")->start();
		_croissant.getComponent<engine::Animator>()->findAnimation("out")->start();
		_title.getComponent<engine::Animator>()->findAnimation("out")->start();
		_coffee.getComponent<engine::Animator>()->findAnimation("out")->start();
		_plant.getComponent<engine::Animator>()->findAnimation("out")->start();
		_boardGame.getComponent<engine::Animator>()->findAnimation("in")->start();
		_startGame = false;
		_started = true;
		_clock.restart();
	}

	if (!_started) {
		if (_pulseClock.getElapsedTime() >= sf::seconds(2)) {
			if (_pulseOn) {
				_fillPulseOnAnimation->stop();
				_fillPulseOnAnimation->start();
				_outlinePulseOnAnimation->stop();
				_outlinePulseOnAnimation->start();
			}
			else {
				_fillPulseOffAnimation->stop();
				_fillPulseOffAnimation->start();
				_outlinePulseOffAnimation->stop();
				_outlinePulseOffAnimation->start();
			}
			_pulseOn = !_pulseOn;
			_pulseClock.restart();
		}
	}
	else {
		if (_clock.getElapsedTime() >= sf::seconds(9.5f)) {
			changeState("Game");
		}
		if (_clock.getElapsedTime() >= sf::seconds(3.5f) && !_characterAnimations) {
			_characterAnimations = true;
			_boy.getComponent<engine::Animator>()->findAnimation("in")->start();
			_girl.getComponent<engine::Animator>()->findAnimation("in")->start();
			_grandpa.getComponent<engine::Animator>()->findAnimation("in")->start();
			_dog.getComponent<engine::Animator>()->findAnimation("in")->start();

			_boyBarBack.getComponent<engine::Animator>()->findAnimation("in")->start();
			_girlBarBack.getComponent<engine::Animator>()->findAnimation("in")->start();
			_gradpaBarBack.getComponent<engine::Animator>()->findAnimation("in")->start();
			_dogBarBack.getComponent<engine::Animator>()->findAnimation("in")->start();

			_boyPostit.getComponent<engine::Animator>()->findAnimation("in")->start();
			_girlPostit.getComponent<engine::Animator>()->findAnimation("in")->start();
			_grandpaPostit.getComponent<engine::Animator>()->findAnimation("in")->start();
			_dogPostit.getComponent<engine::Animator>()->findAnimation("in")->start();

			_tileInfoDisplay.getComponent<engine::Animator>()->findAnimation("in")->start();
		}
	}
}

void MenuState::on_draw() {
	renderer().render();
}


void MenuState::character_setup() {
	_boy.setTexture(&engine::Assets::getTexture("Environment/blue_player"));
	_boy.setPosition(360 - 500, 120 - 500);
	_boy.scale(8.f, 8.f);
	addObject(&_boy);
	renderer().push_basic(&_boy);
	auto animator = _boy.setComponent(std::make_unique<engine::Animator>());
	animator->addAnimation("in", std::make_unique<animations::Ease_In_Out>());
	animator->findAnimation("in")->setDistance({ 500.f, 500.f });
	animator->findAnimation("in")->setTime(sf::seconds(3));

	_girl.setTexture(&engine::Assets::getTexture("Environment/green_player"));
	_girl.setPosition(sf::Vector2f(1320 + 500 - 20, 120 - 500 - 20));
	_girl.scale(10.f, 10.f);
	addObject(&_girl);
	renderer().push_basic(&_girl);
	animator = _girl.setComponent(std::make_unique<engine::Animator>());
	animator->addAnimation("in", std::make_unique<animations::Ease_In_Out>());
	animator->findAnimation("in")->setDistance({ -500.f, 500.f });
	animator->findAnimation("in")->setTime(sf::seconds(3.5f));

	_grandpa.setTexture(&engine::Assets::getTexture("Environment/red_player"));
	_grandpa.setPosition(1290 + 500, 650 + 500);
	_grandpa.scale(12.f, 12.f);
	addObject(&_grandpa);
	renderer().push_basic(&_grandpa);
	animator = _grandpa.setComponent(std::make_unique<engine::Animator>());
	animator->addAnimation("in", std::make_unique<animations::Ease_In_Out>());
	animator->findAnimation("in")->setDistance({ -500.f, -500.f });
	animator->findAnimation("in")->setTime(sf::seconds(4));

	_dog.setTexture(&engine::Assets::getTexture("Environment/yellow_player"));
	_dog.setPosition(sf::Vector2f(350 - 500, 700 + 500));
	_dog.scale(8.f, 8.f);
	addObject(&_dog);
	renderer().push_basic(&_dog);
	animator = _dog.setComponent(std::make_unique<engine::Animator>());
	animator->addAnimation("in", std::make_unique<animations::Ease_In_Out>());
	animator->findAnimation("in")->setDistance({ 500.f, -500.f });
	animator->findAnimation("in")->setTime(sf::seconds(4.5f));

	// Happinesses
	_boyBarBack.setTexture(&engine::Assets::getTexture("UI/bar_background"));
	_boyBarBack.setPosition(50, 50 - 500);
	_boyBarBack.scale(4.f, 4.f);
	addObject(&_boyBarBack);
	renderer().push_basic(&_boyBarBack);
	animator = _boyBarBack.setComponent(std::make_unique<engine::Animator>());
	animator->addAnimation("in", std::make_unique<animations::Ease_In_Out>());
	animator->findAnimation("in")->setDistance({ 0, 500.f });
	animator->findAnimation("in")->setTime(sf::seconds(5.f));

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
	animator->addAnimation("in", std::make_unique<animations::Ease_In_Out>());
	animator->findAnimation("in")->setDistance({ 0, 500.f });
	animator->findAnimation("in")->setTime(sf::seconds(5.f));

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
	animator->addAnimation("in", std::make_unique<animations::Ease_In_Out>());
	animator->findAnimation("in")->setDistance({ 0, -500.f });
	animator->findAnimation("in")->setTime(sf::seconds(5.f));

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
	animator->addAnimation("in", std::make_unique<animations::Ease_In_Out>());
	animator->findAnimation("in")->setDistance({ 0, -500.f });
	animator->findAnimation("in")->setTime(sf::seconds(5.f));

	addObject(&_grandpaBar);
	renderer().push_basic(&_grandpaBar);
	_grandpaBar.attach_parent(&_gradpaBarBack);
	_grandpaBar.setPrimaryColor(sf::Color(88, 193, 53, 255));
	_grandpaBar.setSecondaryColor(sf::Color(223, 63, 35, 255));

	_gradpaBarBack.rotate(180);
	_gradpaBarBack.setPosition(1870, 1030 + 500);
	_grandpaBar.setPosition(1866, 1026 + 500);
}


void MenuState::background_setup() {
	_floor.setTexture(&engine::Assets::getTexture("Environment/floor"));
	_floor.scale(6.f, 6.f);
	renderer().push_background(&_floor);

	_table.setTexture(&engine::Assets::getTexture("Environment/table"));
	_table.setPosition(480, 270);
	_table.scale(6.f, 6.f);
	renderer().push_background(&_table);

	_table2.setTexture(&engine::Assets::getTexture("Environment/coffeetable"));
	_table2.setPosition(625, -120);
	_table2.scale(6.f, 6.f);
	renderer().push_background(&_table2);

	_croissant.setTexture(&engine::Assets::getTexture("Environment/croissant2"));
	_croissant.setPosition(800, 480);
	_croissant.scale(4.f, 4.f);
	renderer().push_background(&_croissant);

	_title.setTexture(&engine::Assets::getTexture("UI/title"));
	_title.setPosition(935, 480);
	_title.scale(1.5f);
	renderer().push_background(&_title);

	_plant.setTexture(&engine::Assets::getTexture("Environment/plant"));
	_plant.setPosition(1050, 350);
	_plant.scale(4.f, 4.f);
	renderer().push_background(&_plant);

	_coffee.setTexture(&engine::Assets::getTexture("Environment/coffee"));
	_coffee.setPosition(1050, 550);
	_coffee.scale(4.f, 4.f);
	renderer().push_background(&_coffee);

	_plant2.setTexture(&engine::Assets::getTexture("Environment/plant2"));
	_plant2.setPosition(700, 900);
	_plant2.scale(4.f, 4.f);
	renderer().push_background(&_plant2);

	_boardGame.setPosition(_boardGame.getPosition() + sf::Vector2f(0, 500));
	renderer().push_basic(&_boardGame);
	addObject(&_boardGame);

	engine::Animator* gameAnimator = _boardGame.setComponent(std::make_unique<engine::Animator>());
	_boardGame.getComponent<engine::Animator>()->addAnimation("in", std::make_unique<animations::Ease>());
	gameAnimator->findAnimation("in")->setDistance({ 0.f, -1678.f });
	gameAnimator->findAnimation("in")->setTime(sf::seconds(2));

	_scaler.setPosition(960, 540);
	_scaler.setOrigin(960, 540);
	_scaler.attach_child(&_floor);
	_scaler.attach_child(&_table);
	_scaler.attach_child(&_table2);
	_scaler.attach_child(&_croissant);
	_scaler.attach_child(&_plant);
	_scaler.attach_child(&_title);
	_scaler.attach_child(&_coffee);
	_scaler.attach_child(&_plant2);
	_scaler.attach_child(&_boardGame);
	_scaler.setScale(5, 5);

	engine::Animator* scaleAnimator = _scaler.setComponent(std::make_unique<engine::Animator>());
	_scaler.getComponent<engine::Animator>()->addAnimation("zoomOut", std::make_unique<animations::EaseScale>());
	scaleAnimator->findAnimation("zoomOut")->setScale({ -4.f, -4.f });
	scaleAnimator->findAnimation("zoomOut")->setTime(sf::seconds(3));

	engine::Animator* takerAnimator = _croissant.setComponent(std::make_unique<engine::Animator>());
	_croissant.getComponent<engine::Animator>()->addAnimation("out", std::make_unique<animations::Ease>());
	takerAnimator->findAnimation("out")->setDistance({ -150.f, -1300.f });
	takerAnimator->findAnimation("out")->setTime(sf::seconds(3));
	addObject(&_croissant);

	takerAnimator = _title.setComponent(std::make_unique<engine::Animator>());
	_title.getComponent<engine::Animator>()->addAnimation("out", std::make_unique<animations::EaseFillColor>());
	takerAnimator->findAnimation("out")->setFillColor({ 0, 0, 0, -255 });
	takerAnimator->findAnimation("out")->setTime(sf::seconds(4));

	addObject(&_title);

	takerAnimator = _coffee.setComponent(std::make_unique<engine::Animator>());
	_coffee.getComponent<engine::Animator>()->addAnimation("out", std::make_unique<animations::Ease>());
	takerAnimator->findAnimation("out")->setDistance({ -400.f, -1300.f });
	takerAnimator->findAnimation("out")->setTime(sf::seconds(3));
	addObject(&_coffee);

	takerAnimator = _plant.setComponent(std::make_unique<engine::Animator>());
	_plant.getComponent<engine::Animator>()->addAnimation("out", std::make_unique<animations::Ease>());
	takerAnimator->findAnimation("out")->setDistance({ 400.f, -900.f });
	takerAnimator->findAnimation("out")->setTime(sf::seconds(2));
	addObject(&_plant);

	addObject(&_scaler);

	_clickText.setOrigin(_clickText.getGlobalBounds().width / 2.f, _clickText.getGlobalBounds().height / 2.f);
	_clickText.setPosition(engine::Window::getSize().x / 2.f, engine::Window::getSize().y * 9.f / 10.f);
	_clickText.setOutlineThickness(3.f);
	_clickText.setFillColor(sf::Color{ 227, 230, 255 });
	_clickText.setOutlineColor(sf::Color::Black);
	engine::Animation* animation = _clickText.setComponent(std::make_unique<engine::Animator>())->addAnimation("fillColorOut", std::make_unique<animations::EaseFillColor>());
	animation->setTime(sf::seconds(2));
	animation->setFillColor({ 0.f, 0.f, 0.f, -255.f });
	animation = _clickText.getComponent<engine::Animator>()->addAnimation("outlineColorOut", std::make_unique<animations::EaseOutlineColor>());
	animation->setTime(sf::seconds(2));
	animation->setOutlineColor({ 0.f, 0.f, 0.f, -255.f });
	_fillPulseOnAnimation = _clickText.getComponent<engine::Animator>()->addAnimation("fillPulseOn", std::make_unique<animations::EaseFillColor>());
	_fillPulseOnAnimation->setTime(sf::seconds(2));
	_fillPulseOnAnimation->setFillColor({ 0.f, 0.f, 0.f, 255.f });
	_fillPulseOffAnimation = _clickText.getComponent<engine::Animator>()->addAnimation("fillPulseOff", std::make_unique<animations::EaseFillColor>());
	_fillPulseOffAnimation->setTime(sf::seconds(2));
	_fillPulseOffAnimation->setFillColor({ 0.f, 0.f, 0.f, -255.f });
	_outlinePulseOnAnimation = _clickText.getComponent<engine::Animator>()->addAnimation("outlinePulseOn", std::make_unique<animations::EaseOutlineColor>());
	_outlinePulseOnAnimation->setTime(sf::seconds(2));
	_outlinePulseOnAnimation->setOutlineColor({ 0.f, 0.f, 0.f, 255.f });
	_outlinePulseOffAnimation = _clickText.getComponent<engine::Animator>()->addAnimation("outlinePulseOff", std::make_unique<animations::EaseOutlineColor>());
	_outlinePulseOffAnimation->setTime(sf::seconds(2));
	_outlinePulseOffAnimation->setOutlineColor({ 0.f, 0.f, 0.f, -255.f });
	addObject(&_clickText);
	renderer().push_background(&_clickText);
}


void MenuState::postits_setup() {
	_boyPostit.setTexture(&engine::Assets::getTexture("UI/boy_postit"));
	addObject(&_boyPostit);
	renderer().push_priority(&_boyPostit);
	_boyPostit.scale(6.f, 6.f);
	_boyText.attach_parent(&_boyPostit);
	_boyText.setPosition(25, 135);
	_boyText.setFillColor(sf::Color::Black);
	renderer().push_priority(&_boyText);
	_boyPostit.setPosition(50 - 500, 125);
	auto animator = _boyPostit.setComponent(std::make_unique<engine::Animator>());
	animator->addAnimation("in", std::make_unique<animations::Ease>());
	animator->findAnimation("in")->setDistance({ 500, 0 });
	animator->findAnimation("in")->setTime(sf::seconds(5.f));

	_girlPostit.setTexture(&engine::Assets::getTexture("UI/girl_postit"));
	addObject(&_girlPostit);
	renderer().push_priority(&_girlPostit);
	_girlPostit.scale(6.f, 6.f);
	_girlText.attach_parent(&_girlPostit);
	_girlText.setPosition(25, 135);
	_girlText.setFillColor(sf::Color::Black);
	renderer().push_priority(&_girlText);
	_girlPostit.setPosition(1600 + 500, 125);
	animator = _girlPostit.setComponent(std::make_unique<engine::Animator>());
	animator->addAnimation("in", std::make_unique<animations::Ease>());
	animator->findAnimation("in")->setDistance({ -500, 0 });
	animator->findAnimation("in")->setTime(sf::seconds(5.f));

	_dogPostit.setTexture(&engine::Assets::getTexture("UI/dog_postit"));
	addObject(&_dogPostit);
	renderer().push_priority(&_dogPostit);
	_dogPostit.scale(6.f, 6.f);
	_dogText.attach_parent(&_dogPostit);
	_dogText.setPosition(25, 135);
	_dogText.setFillColor(sf::Color::Black);
	renderer().push_priority(&_dogText);
	_dogPostit.setPosition(50 - 500, 525);
	animator = _dogPostit.setComponent(std::make_unique<engine::Animator>());
	animator->addAnimation("in", std::make_unique<animations::Ease>());
	animator->findAnimation("in")->setDistance({ 500, 0 });
	animator->findAnimation("in")->setTime(sf::seconds(5.f));

	_grandpaPostit.setTexture(&engine::Assets::getTexture("UI/grandpa_postit"));
	addObject(&_grandpaPostit);
	renderer().push_priority(&_grandpaPostit);
	_grandpaPostit.scale(6.f, 6.f);
	_grandpaText.attach_parent(&_grandpaPostit);
	_grandpaText.setPosition(25, 135);
	_grandpaText.setFillColor(sf::Color::Black);
	renderer().push_priority(&_grandpaText);
	_grandpaPostit.setPosition(1600 + 500, 525);
	animator = _grandpaPostit.setComponent(std::make_unique<engine::Animator>());
	animator->addAnimation("in", std::make_unique<animations::Ease>());
	animator->findAnimation("in")->setDistance({ -500, 0 });
	animator->findAnimation("in")->setTime(sf::seconds(5.f));
}


void MenuState::helper_setup() {
	_tileInfoDisplay.setTexture(&engine::Assets::getTexture("UI/helper"));
	addObject(&_tileInfoDisplay);
	_tileInfoDisplay.scale(6.f, 6.f);
	renderer().push_basic(&_tileInfoDisplay);
	_tileInfoDisplay.setPosition(1040, 885 + 500);
	auto animator = _tileInfoDisplay.setComponent(std::make_unique<engine::Animator>());
	animator->addAnimation("in", std::make_unique<animations::Ease>());
	animator->findAnimation("in")->setDistance({ 0, -500 });
	animator->findAnimation("in")->setTime(sf::seconds(5.f));
}

void MenuState::music_setup() {
    _menuMusic.openFromFile(engine::Assets::ASSETS_PATH + "/music/menu.ogg");
    _menuMusic.setLoop(true);
}