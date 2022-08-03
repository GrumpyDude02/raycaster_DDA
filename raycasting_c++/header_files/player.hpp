#pragma once
#ifndef player
#define player
#include<SFML/Graphics.hpp>

class Player{
    double* angle;
    float start_angle,FOV,step;
    float radius;
    public:
        sf::CircleShape shape;
        sf::Vector2f pos;
        sf::Vector2f dir;
        sf::Vector2f vec;
        Player(float ,sf::Vector2f ,float,int&);
        void update(sf::RenderWindow&,double*,int,int**,int&);
    };

#endif