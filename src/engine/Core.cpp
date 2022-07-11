#include <sstream>
#include <iomanip>
#include "Core.hpp"

#include "Assets.hpp"
#include "Window.hpp"

using namespace engine;


Core::Core() {
	addStore(&_store);

	_loadingText.setString("Loading...");
	_loadingFont.loadFromFile(Assets::ASSETS_PATH + "fonts/AlbertSans-ExtraLight.ttf");
	_loadingText.setFont(_loadingFont);
	_loadingText.setCharacterSize(100);
	sf::FloatRect textRect = _loadingText.getLocalBounds();
	_loadingText.setOrigin(textRect.left + textRect.width / 2.f, textRect.top + textRect.height / 2.f);
	_loadingText.setPosition(Window::getSize() / 2.f);
	_loadingText.setFillColor(sf::Color::White);
}


int Core::setup() const {
	// Open window before loading assets duo to SFML bug: https://en.sfml-dev.org/forums/index.php?topic=25907.0
	Window::open();

	// Show a "Loading" sign until assets are being loaded
	Window::clear();
	Window::draw(_loadingText);
	Window::display();

	// Load assets
	if (Assets::load() != 0) {
		return 1;
	}

	return 0;
}

void Core::run() {
    // Performance data
    sf::Clock clk;
    static int counter = 0;
#ifdef ENGINE_DEBUG
    static float ta0 = 0, ta1 = 0, ta2 = 0, ta3 = 0, ta4 = 0, ta5 = 0;
#endif
    static float frameTimeAcc = 0;
    const int SAMPLE_RATE = 30;
    static sf::Text fpsText{ "FPS: ", Assets::getFont("CourierNewBold"), 15 };

	// Game loop
	sf::Event event;
	while (Window::isOpen()) {
        float t0 = clk.getElapsedTime().asSeconds();

		// Switch between states
		processChanges();

#ifdef ENGINE_DEBUG
        float t1 = clk.getElapsedTime().asSeconds();
#endif

		// Poll and handle events
		while (Window::poll_event(event)) {
			if (event.type == sf::Event::Closed) {
				Window::close();
			}
			operator->()->handle_event(event);
		}

#ifdef ENGINE_DEBUG
        float t2 = clk.getElapsedTime().asSeconds();
#endif

		// Run general updates
		operator->()->update();

#ifdef ENGINE_DEBUG
        float t3 = clk.getElapsedTime().asSeconds();
#endif

		// Draw to the window
		Window::clear();

#ifdef ENGINE_DEBUG
        float t4 = clk.getElapsedTime().asSeconds();
#endif

		operator->()->draw();

        // Display performance data
        Window::draw(fpsText);

#ifdef ENGINE_DEBUG
        float t5 = clk.getElapsedTime().asSeconds();
#endif

		Window::display();

        float t6 = clk.getElapsedTime().asSeconds();

        // Update performance data
        counter++;
#ifdef ENGINE_DEBUG
        ta0 += t1 - t0;
        ta1 += t2 - t1;
        ta2 += t3 - t2;
        ta3 += t4 - t3;
        ta4 += t5 - t4;
        ta5 += t6 - t5;
#endif
        frameTimeAcc += t6 - t0;

        if (counter == SAMPLE_RATE) {
            std::stringstream text;
            text << std::fixed << std::setprecision(3);
            text << "FPS: " << (int) (1 / (frameTimeAcc / SAMPLE_RATE)) << std::endl;
#ifdef ENGINE_DEBUG
            //text << "State switching: " << ta0 / SAMPLE_RATE * 1000 << " ms" << std::endl;
            text << "Event handling: " << ta1 / SAMPLE_RATE * 1000 << " ms" << std::endl;
            text << "State update: " << ta2 / SAMPLE_RATE * 1000 << " ms" << std::endl;
            //text << "Window clear: " << ta3 / SAMPLE_RATE * 1000 << " ms" << std::endl;
            text << "State draw: " << ta4 / SAMPLE_RATE * 1000 << " ms" << std::endl;
            text << "Window display: " << ta5 / SAMPLE_RATE * 1000 << " ms" << std::endl;
#endif
            fpsText.setString(text.str());

            counter = 0;
#ifdef ENGINE_DEBUG
            ta0 = 0; ta1 = 0; ta2 = 0; ta3 = 0; ta4 = 0; ta5 = 0;
#endif
            frameTimeAcc = 0;
        }
	}
}
