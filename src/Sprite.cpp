#include "Sprite.hpp"
#include <stdexcept>
#include <vector>
#include <spdlog/spdlog.h>

Sprite::Sprite(const std::string& filepath, const int w, const int h, const int x, const int y, const int s) 
    : init_width{w}, width{w * s}, init_height{h}, height{h * s}, x{x}, y{y}  {
    sf::IntRect texture_rect(0, 0, this->init_width, this->init_height);
    this->set_texture(filepath, texture_rect);
    this->set_position(this->x, this->y);
    this->set_scale(s);  // Either the default or a user-specified value
}

void Sprite::set_texture(const std::string& filepath, sf::IntRect rect) {
    // Check texture file
    if (!this->texture.loadFromFile(filepath, rect)) {
        spdlog::error("Could not load texture from: {}", filepath);
        throw std::runtime_error("Could not load texture from: " + filepath);
    }

    this->sprite.setTexture(this->texture);
}

int Sprite::get_width() const {
    return this->width;
}

int Sprite::get_height() const {
    return this->height;
}

void Sprite::set_scale(const int scale) {
    // Scale the sprite by the same factor in both dimensions
    this->width = scale * this->init_width;
    this->height = scale * this->init_height;
    this->sprite.setScale(scale, scale);
}

int Sprite::get_scale() const {
    sf::Vector2f scales = this->sprite.getScale();
    int scale_x = static_cast<int>(scales.x);
    int scale_y = static_cast<int>(scales.y);
    if (scale_x != scale_y) {
        // Scale factor should be the same in both dimensions
        spdlog::error("Expected scale factor to be the same in both dimensions but instead found:\nx scale = {}\ny scale = {}", scale_x, scale_y);
        throw std::runtime_error("Expected scale factor to be the same in both dimensions but instead found:\nx scale = " + std::to_string(scale_x) + "\ny scale = " + std::to_string(scale_y));
    }
    
    return scale_x;
}

void Sprite::set_position(int x, int y) {
    this->x = x;
    this->y = y;
    this->sprite.setPosition(x, y);
}

int Sprite::get_x() const {
    return this->x;
}

int Sprite::get_y() const {
    return this->y;
}

void Sprite::draw(sf::RenderWindow& window) const {
    window.draw(this->sprite);
}