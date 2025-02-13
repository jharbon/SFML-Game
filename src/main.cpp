#include <filesystem>
#include <memory>
#include <spdlog/spdlog.h>
#include <spdlog/sinks/stdout_color_sinks.h>
#include <spdlog/sinks/basic_file_sink.h>
#include <SFML/Graphics.hpp>

const std::string LOGS_DIR_NAME = "logs";
const std::string LOG_FILE_NAME = "log.txt";

const unsigned int DISPLAY_WIDTH = sf::VideoMode::getDesktopMode().width;
const unsigned int DISPLAY_HEIGHT = sf::VideoMode::getDesktopMode().height;
constexpr float WINDOW_SCALE = 0.75f;  // Scale each dimension by the same factor to maintain the aspect ratio
const unsigned int INIT_WINDOW_WIDTH = static_cast<unsigned int>(WINDOW_SCALE * DISPLAY_WIDTH);
const unsigned int INIT_WINDOW_HEIGHT = static_cast<unsigned int>(WINDOW_SCALE * DISPLAY_HEIGHT);
constexpr unsigned int FRAME_RATE = 60;  // FPS

void enforce_dir_existence(std::filesystem::path dir, bool must_already_exist);
void configure_logger(std::filesystem::path log_path);

int main(int argc, char* argv[]) {
    // Get project directory path and enforce logs directory existence
    std::filesystem::path project_dir = std::filesystem::canonical(argv[0]).parent_path().parent_path();
    enforce_dir_existence(project_dir / LOGS_DIR_NAME, false);
    // Define log file path and configure multi-logger as default
    std::filesystem::path log_path = project_dir / LOGS_DIR_NAME / LOG_FILE_NAME;
    configure_logger(log_path);

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
    spdlog::info("Initialized window with {}x{} resolution and {} FPS cap", window_size.x, window_size.y, FRAME_RATE);

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
                spdlog::info("Window closed");
            }
        }
    }
    
    spdlog::info("Shutting down...");
    spdlog::shutdown();  // Final flush 
    return 0;
}

void enforce_dir_existence(std::filesystem::path dir, bool must_already_exist) {
    if (!std::filesystem::exists(dir)) {
        if (must_already_exist) {
            throw std::runtime_error("Required directory missing: '" + dir.string() + "'" );
        }

        try {
            std::filesystem::create_directory(dir);
        }
        catch (const std::filesystem::filesystem_error& e) {
            throw std::runtime_error("Failed to create directory: '" + dir.string() + "': " + e.what());
        }
    }
}

void configure_logger(std::filesystem::path log_path) {
    // Use logger sinks to create multi-logger which simultaneously logs to both console and file 
    auto console_sink_sptr = std::make_shared<spdlog::sinks::stdout_color_sink_mt>();
    console_sink_sptr->set_pattern("%^[%Y-%b-%d %H:%M:%S] [%l] - %v%$");
    auto file_sink_sptr = std::make_shared<spdlog::sinks::basic_file_sink_mt>(log_path.string(), false);
    file_sink_sptr->set_pattern("[%Y-%b-%d %H:%M:%S] [%l] - %v");
    std::vector<spdlog::sink_ptr> sinks{console_sink_sptr, file_sink_sptr};
    auto multi_logger_sptr = std::make_shared<spdlog::logger>("multi-logger", sinks.begin(), sinks.end());  
    // Set multi-logger as default for easy logging across program 
    spdlog::set_default_logger(multi_logger_sptr);
    spdlog::set_level(spdlog::level::info);  // Log everything with severity of INFO and higher
    spdlog::flush_on(spdlog::level::warn);  // Immediate log flushing for severity of WARN and higher
}