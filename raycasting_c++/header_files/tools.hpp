#pragma once
#ifndef tools
#define tools
#include<SFML/Graphics.hpp>

void print_fps(sf::Clock& clock,double* dt);
bool collision(sf::CircleShape& ,sf::RectangleShape& ,float );
void cir_rect_collision(sf::CircleShape& circle,sf::RectangleShape& rect,float circle_radius,float rw,float rh);

#endif