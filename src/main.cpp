#include <SFML/Graphics.hpp>

const unsigned int DISPLAY_WIDTH = sf::VideoMode::getDesktopMode().width;
const unsigned int DISPLAY_HEIGHT = sf::VideoMode::getDesktopMode().height;
constexpr float WINDOW_SCALE = 0.75f;  // Scale each dimension by the same factor to maintain the aspect ratio
const unsigned int INIT_WINDOW_WIDTH = static_cast<unsigned int>(WINDOW_SCALE * DISPLAY_WIDTH);
const unsigned int INIT_WINDOW_HEIGHT = static_cast<unsigned int>(WINDOW_SCALE * DISPLAY_HEIGHT);
constexpr unsigned int FRAME_RATE = 60;  // FPS

int main() {
    // Render a centered window
    sf::RenderWindow window(sf::VideoMode(INIT_WINDOW_WIDTH, INIT_WINDOW_HEIGHT), "SFML Game");
    window.setFramerateLimit(FRAME_RATE);
    sf::Vector2i window_centered_pos (
        static_cast<int>((DISPLAY_WIDTH - window.getSize().x) / 2),
        static_cast<int>((DISPLAY_HEIGHT - window.getSize().y) / 2)
    ); 
    window.setPosition(window_centered_pos);
    sf::Vector2u window_size = window.getSize();
    // Render a basic circle
    sf::CircleShape circle(window_size.x / 4);
    circle.setFillColor(sf::Color::Red);
    circle.setPosition(window_size.x/2 - circle.getRadius(), window_size.y/2 - circle.getRadius());

    // Keep running the program while the window exists 
    while (window.isOpen()) {
        window.clear(sf::Color::Black);
        window.draw(circle);
        window.display();

        // Allow the window to be closed 
        sf::Event event;
        while (window.pollEvent(event)) {
            if (event.type == sf::Event::Closed) {
                window.close();
            }
        }
    }
    
    return 0;
}