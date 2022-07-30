#include<SFML\Graphics.hpp>
#include<iostream>
#include<cmath>
#include"header_files\utilities.hpp"

void print_fps(sf::Clock& clock,double* dt){
    *dt=clock.restart().asSeconds();
    std::cout<<1.f/(*dt)<<std::endl;
}

bool collision(sf::CircleShape& circle,sf::RectangleShape& rect,float rect_width){
    float temp_x;
    float temp_y;
    float circle_radius=circle.getRadius();
    float c_x=circle.getPosition().x+circle_radius;
    float c_y=circle.getPosition().y+circle_radius;
    float r_x=rect.getPosition().x;
    float r_y=rect.getPosition().y;

    if (c_x<=r_x){

        temp_x=r_x;

    }else{

        temp_x=r_x+rect_width;
    }
    if (c_y<=r_y)
    {

        temp_y=r_y;

    }else{

        temp_y=r_y+rect_width;
    }
    
    float distance=sqrtf((c_x-temp_x)*(c_x-temp_x)+(c_y-temp_y)*(c_y-temp_y));

    if (distance<=circle_radius){return true;}

    return false;
}