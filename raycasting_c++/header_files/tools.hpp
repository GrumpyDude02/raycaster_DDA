#pragma once
#ifndef tools
#define tools
#include<SFML/Graphics.hpp>
#include<header_files/raycaster.hpp>
#include<iostream>
#include<vector>

void print_fps(sf::Clock& clock,double* dt);
bool collision(sf::CircleShape& ,sf::RectangleShape& ,float );
void cir_rect_collision(sf::CircleShape& circle,sf::RectangleShape& rect,float circle_radius,float rw,float rh);
void draw_minimap(sf::RenderWindow& screen,std::vector<sf::RectangleShape>& tiles,std::vector<sf::RectangleShape>& small_tiles,Player& player_pos,int scale,int radius,int cell_size);

#endif