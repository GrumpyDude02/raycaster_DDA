#pragma once
#ifndef raycaster
#define raycaster
#include<SFML/Graphics.hpp>

class Player{
    double angle;
    float start_angle,FOV,step;
    int scale,width;
    float radius;
    public:
        sf::CircleShape shape;
        sf::Vector2f pos;
        sf::Vector2f dir;
        sf::Vector2f vec;
        Player(float radius,sf::Vector2f position,float fov,int& rays_num,int width,int height);
        std::vector<std::vector<float>> update(sf::RenderWindow& window,double* dt,int cell_size,std::vector<std::vector<int>>& map,int& rays_num,int& sc_distance);
    };

#endif