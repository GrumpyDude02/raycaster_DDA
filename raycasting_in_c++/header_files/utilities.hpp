#pragma once
#include<SFML/Graphics.hpp>

void print_fps(sf::Clock& clock,double* dt);
bool collision(sf::CircleShape&,sf::RectangleShape&,float rect_width);