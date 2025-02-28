#include <SFML/Graphics.hpp>
#include <string>
#include <vector>

class Sprite {
    private:
        sf::Sprite sprite;
        sf::Texture texture;
        int init_width, width, init_height, height;
        int x, y;
        
    public:
        Sprite(const std::string& filepath, const int w, const int h, const int x = 0, const int y = 0, const int s = 1);

        void set_texture(const std::string& filepath, sf::IntRect rect);
        int get_width() const;
        int get_height() const;
        void set_scale(const int scale);
        int get_scale() const;
        void set_position(int x, int y);
        int get_x() const;
        int get_y() const;

        void draw(sf::RenderWindow& window) const;
};