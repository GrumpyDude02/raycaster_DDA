#include <SFML/Graphics.hpp>

class ray
{
    sf::Vector2f dir;
    sf::Vector2f start_pos;

public:
    ray(sf::Vector2f &direction, sf::Vector2f &starting_pos);
    float cast_ray(int **, float &, int &);
};
