#include <SFML/Graphics.hpp>
#include <iostream>

void displayGameOverScreen(sf::RenderWindow *window) {
    // Reset the view to the default view
    sf::View defaultView = window->getDefaultView();
    window->setView(defaultView);
    window->clear();

    sf::RectangleShape background(sf::Vector2f(window->getSize().x, window->getSize().y));
    background.setFillColor(sf::Color(0, 0, 0, 255));
    window->draw(background);

    // Set up the "Game Over" text
    sf::Font font;
    if (!font.loadFromFile("fonts/arial.ttf")) {
        std::cout << "Error loading font" << std::endl;
    }

    sf::Text gameOverText;
    gameOverText.setFont(font);
    gameOverText.setString("You Died");
    gameOverText.setCharacterSize(64);
    gameOverText.setFillColor(sf::Color::Red);
    gameOverText.setStyle(sf::Text::Bold);

    // Center the "You Died" text on the window
    sf::FloatRect textRect = gameOverText.getLocalBounds();
    gameOverText.setOrigin(textRect.left + textRect.width / 2.0f, textRect.top + textRect.height / 2.0f);
    gameOverText.setPosition(sf::Vector2f(window->getSize().x / 2.0f, window->getSize().y / 3.0f));

    window->draw(gameOverText);
    window->display();

    sf::Event event;
    while (window->waitEvent(event)) {
        if (event.type == sf::Event::Closed || (event.type == sf::Event::KeyPressed && event.key.code == sf::Keyboard::Escape)) {
            window->close();
            break;
        }
    }
}


void displayPauseGame(sf::RenderWindow *window) {
    // Reset the view to the default view
    sf::View defaultView = window->getDefaultView();
    window->setView(defaultView);
    window->clear();


    sf::RectangleShape background(sf::Vector2f(window->getSize().x, window->getSize().y));
    background.setFillColor(sf::Color(0, 0, 0, 255));
    window->draw(background);

    // Set up the "Game Over" text
    sf::Font font;
    if (!font.loadFromFile("fonts/arial.ttf")) {
        std::cout << "Error loading font" << std::endl;
    }

    sf::Text pauseText;
    pauseText.setFont(font);
    pauseText.setString("Paused");
    pauseText.setCharacterSize(64);
    pauseText.setFillColor(sf::Color::White);
    pauseText.setStyle(sf::Text::Bold);

    // Center the "Game Over" text on the window
    sf::FloatRect textRect = pauseText.getLocalBounds();
    pauseText.setOrigin(textRect.left + textRect.width / 2.0f, textRect.top + textRect.height / 2.0f);
    pauseText.setPosition(sf::Vector2f(window->getSize().x / 2.0f, window->getSize().y / 3.0f));

    window->draw(pauseText);
    window->display();

    sf::Event event;
    while (window->waitEvent(event)) {
        if (event.type == sf::Event::Closed || (event.type == sf::Event::KeyPressed && event.key.code == sf::Keyboard::Escape)) {
            break;
        }
        // If escape key down, break out of the loop
        if (event.type == sf::Event::KeyPressed && event.key.code == sf::Keyboard::Escape) {
            return;
        }
    }

}
void displayWelcomeScreen(sf::RenderWindow *window) {
    // Reset the view to the default view
    sf::View defaultView = window->getDefaultView();
    window->setView(defaultView);
    window->clear();

    // Create a background
    sf::RectangleShape background(sf::Vector2f(window->getSize().x, window->getSize().y));
    background.setFillColor(sf::Color(0, 0, 0, 255));
    window->draw(background);

    // Load font
    sf::Font font;
    if (!font.loadFromFile("fonts/arial.ttf")) {
        std::cout << "Error loading font" << std::endl;
    }

    // Setup welcome text
    sf::Text welcomeText;
    welcomeText.setFont(font);
    welcomeText.setString("Welcome to the Game!");
    welcomeText.setCharacterSize(64);
    welcomeText.setFillColor(sf::Color::White);
    welcomeText.setStyle(sf::Text::Bold);

    // Center the welcome text on the window
    sf::FloatRect textRect = welcomeText.getLocalBounds();
    welcomeText.setOrigin(textRect.left + textRect.width / 2.0f, textRect.top + textRect.height / 2.0f);
    welcomeText.setPosition(sf::Vector2f(window->getSize().x / 2.0f, window->getSize().y / 4.0f));

    window->draw(welcomeText);

    // Setup controls text
    sf::Text controlsText;
    controlsText.setFont(font);
    controlsText.setString("Controls:\nW for Up\nA for Left\nS for Down\nD for Right\nSpace to Fire Bolt\nCursor to Place Bolt");
    controlsText.setCharacterSize(32);
    controlsText.setFillColor(sf::Color::White);
    controlsText.setStyle(sf::Text::Bold);

    // Center the controls text on the window
    sf::FloatRect controlsRect = controlsText.getLocalBounds();
    controlsText.setOrigin(controlsRect.left + controlsRect.width / 2.0f, controlsRect.top + controlsRect.height / 2.0f);
    controlsText.setPosition(sf::Vector2f(window->getSize().x / 2.0f, window->getSize().y / 2.0f));

    window->draw(controlsText);

    // Setup continue text
    sf::Text continueText;
    continueText.setFont(font);
    continueText.setString("Press any key to continue...");
    continueText.setCharacterSize(32);
    continueText.setFillColor(sf::Color::White);
    continueText.setStyle(sf::Text::Bold);

    // Center the continue text on the window
    sf::FloatRect continueRect = continueText.getLocalBounds();
    continueText.setOrigin(continueRect.left + continueRect.width / 2.0f, continueRect.top + continueRect.height / 2.0f);
    continueText.setPosition(sf::Vector2f(window->getSize().x / 2.0f, window->getSize().y / 1.3f));

    window->draw(continueText);
    window->display();

    sf::Event event;
    while (window->waitEvent(event)) {
        // If close window event or any key pressed, break out of the loop
        if (event.type == sf::Event::Closed || event.type == sf::Event::KeyPressed) {
            break;
        }
    }
}
