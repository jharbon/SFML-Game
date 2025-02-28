#include <filesystem>
#include <iostream>
#include <memory>
#include <spdlog/spdlog.h>
#include <spdlog/sinks/stdout_color_sinks.h>
#include <spdlog/sinks/basic_file_sink.h>
#include <SFML/Graphics.hpp>
#include "Sprite.hpp"

const std::string ASSETS_DIR_NAME = "assets";
const std::string CONFIG_DIR_NAME = "config";
const std::string LOGS_DIR_NAME = "logs";
const std::string LOG_FILE_NAME = "log.txt";

const unsigned int DISPLAY_WIDTH = sf::VideoMode::getDesktopMode().width;
const unsigned int DISPLAY_HEIGHT = sf::VideoMode::getDesktopMode().height;
constexpr float WINDOW_SCALE = 0.75f;  // Scale each dimension by the same factor to maintain the aspect ratio
const unsigned int INIT_WINDOW_WIDTH = static_cast<unsigned int>(WINDOW_SCALE * DISPLAY_WIDTH);
const unsigned int INIT_WINDOW_HEIGHT = static_cast<unsigned int>(WINDOW_SCALE * DISPLAY_HEIGHT);
constexpr unsigned int FRAME_RATE = 60;  // FPS

const std::filesystem::path PLAYER_SPRITE_REL_PATH = std::filesystem::path(ASSETS_DIR_NAME) / "sprites" / "player.png"; 
constexpr int PLAYER_SCALE = 10;
constexpr int PLAYER_WIDTH = 32;  // Pixels
constexpr int PLAYER_HEIGHT = 32;  // Pixels

void enforce_dir_existence(std::filesystem::path dir);
void configure_logger(std::filesystem::path project_dir);

int main(int argc, char* argv[]) {
    // Get project root path
    const std::filesystem::path project_dir = std::filesystem::canonical(argv[0]).parent_path().parent_path();
    // Configure multi-logger as default
    configure_logger(project_dir);
    // Throw exception if assets or config directories do not exist in project root
    enforce_dir_existence(project_dir / ASSETS_DIR_NAME);
    enforce_dir_existence(project_dir / CONFIG_DIR_NAME);

    // Render a centered window
    sf::RenderWindow window(sf::VideoMode(INIT_WINDOW_WIDTH, INIT_WINDOW_HEIGHT), "SFML Game");
    window.setFramerateLimit(FRAME_RATE);
    sf::Vector2i window_centered_pos (
        static_cast<int>((DISPLAY_WIDTH - window.getSize().x) / 2),
        static_cast<int>((DISPLAY_HEIGHT - window.getSize().y) / 2)
    ); 
    window.setPosition(window_centered_pos);
    sf::Vector2u window_size = window.getSize();
    spdlog::info("Initialized window with {}x{} resolution and {} FPS cap", window_size.x, window_size.y, FRAME_RATE);

    // Render player character sprite in center of window
    Sprite player_sprite(project_dir / PLAYER_SPRITE_REL_PATH, PLAYER_WIDTH, PLAYER_HEIGHT, 0, 0, PLAYER_SCALE); 
    player_sprite.set_position((window_size.x - player_sprite.get_width())/2, (window_size.y - player_sprite.get_height())/2);
    spdlog::info("Initialized player sprite with:\ninitial (width, height) = ({}, {})\nscale factor = {}\n(x, y) = ({}, {})",
        PLAYER_WIDTH, PLAYER_HEIGHT, player_sprite.get_scale(), player_sprite.get_x(), player_sprite.get_y()
    );

    // Keep running the program while the window exists 
    while (window.isOpen()) {
        window.clear(sf::Color::Black);
        player_sprite.draw(window);
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

void enforce_dir_existence(std::filesystem::path dir) {
    if (!std::filesystem::exists(dir)) {
        spdlog::error("Required directory '{}' is missing. Ensure this directory exists before running the program", dir.string());
        throw std::runtime_error("Required directory '" + dir.string() + "' is missing. Ensure this directory exists before running the program");
    }
}

void configure_logger(std::filesystem::path project_dir) {
    std::filesystem::path logs_dir = project_dir / LOGS_DIR_NAME;
    bool log_to_file = true;
    // Create logs directory if it does not already exist
    if (!std::filesystem::exists(logs_dir)) {
        try {
            std::cerr << "WARNING: Creating logs directory with path '" << logs_dir.string() << "'\n"; 
            std::filesystem::create_directory(logs_dir);
        }
        catch (const std::filesystem::filesystem_error& e) {
            std::cerr << "ERROR: Failed to create logs directory with path '" << logs_dir.string() << "': " << e.what() << "\n";
            log_to_file = false;
        }
    }
    
    // Use logger sinks to create multi-logger which simultaneously logs to both console and file 
    auto console_sink_sptr = std::make_shared<spdlog::sinks::stdout_color_sink_mt>();
    console_sink_sptr->set_pattern("%^[%Y-%b-%d %H:%M:%S] [%l] - %v%$");
    std::vector<spdlog::sink_ptr> sinks{console_sink_sptr};
    std::filesystem::path log_path = logs_dir / LOG_FILE_NAME;
    if (log_to_file) {
        // Create valid sink for logging to file
        auto file_sink_sptr = std::make_shared<spdlog::sinks::basic_file_sink_mt>(log_path.string(), false);
        file_sink_sptr->set_pattern("[%Y-%b-%d %H:%M:%S] [%l] - %v");
        sinks.push_back(file_sink_sptr);
    }
    auto multi_logger_sptr = std::make_shared<spdlog::logger>("multi-logger", sinks.begin(), sinks.end());  
    // Set multi-logger as default for easy logging across program 
    spdlog::set_default_logger(multi_logger_sptr);
    spdlog::set_level(spdlog::level::info);  // Log everything with severity of INFO and higher
    spdlog::flush_on(spdlog::level::warn);  // Immediate log flushing for severity of WARN and higher
    
    if (!log_to_file) {
        spdlog::warn("Logging to file disabled. Logging to console only");
    }
}