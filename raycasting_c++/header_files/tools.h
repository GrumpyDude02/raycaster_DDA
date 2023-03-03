#pragma once
#include <SFML/Graphics.hpp>
#include <header_files/raycaster.h>
#include <iostream>
#include <vector>

void print_fps(sf::Clock &clock, double *dt, sf::RenderWindow &window, sf::Font &DFont);
bool collision(sf::CircleShape &, sf::RectangleShape &, float);
void cir_rect_collision(sf::CircleShape &circle, sf::RectangleShape &rect, float circle_radius, float rw, float rh);
void draw_minimap(sf::RenderWindow &screen, std::vector<sf::RectangleShape> &tiles, std::vector<sf::RectangleShape> &small_tiles, Raycaster &player_pos, sf::CircleShape &player_map_pos, int scale, int cell_size);

int partition(std::vector<std::vector<float>> &values, int left, int right);
void quicksort(std::vector<std::vector<float>> &values, int left, int right);

int partition_sprite(std::vector<sf::Sprite> &values, int left, int right);
void quicksort_sprite(std::vector<sf::Sprite> &values, int left, int right);
