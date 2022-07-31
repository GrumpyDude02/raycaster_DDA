#include<SFML\Graphics.hpp>
#include<iostream>
#include<cmath>
#include"header_files\utilities.hpp"

void print_fps(sf::Clock& clock,double* dt){
    *dt=clock.restart().asSeconds();
    std::cout<<1.f/(*dt)<<std::endl;
}

bool collision(sf::CircleShape& circle,sf::RectangleShape& rect,float rect_width){
    float temp_x,temp_y;
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
    sf::Vector2f np=sf::Vector2f(c_x-temp_x,c_y-temp_y);
    float distance=sqrtf(np.x*np.x+np.y*np.y);
    float overlap=circle_radius-distance;


    if (distance<=circle_radius){
        return true;}

    return false;
}

void cir_rect_collision(sf::CircleShape& circle,sf::RectangleShape& rect,float circle_radius,float rw,float rh){

    float nearestX=std::max(rect.getPosition().x,std::min(circle.getPosition().x+circle_radius,rect.getPosition().x+rw));
    float nearestY=std::max(rect.getPosition().y,std::min(circle.getPosition().y+circle_radius,rect.getPosition().y+rh));

    sf::Vector2f nearestV(circle.getPosition().x+circle_radius-nearestX,circle.getPosition().y+circle_radius-nearestY);
    float dist=sqrt((nearestV.x*nearestV.x)+(nearestV.y*nearestV.y));

    if(dist<=circle_radius) {
        float overlap=circle_radius-dist;
        sf::Vector2f Dir(nearestV.x/dist,nearestV.y/dist);
        circle.move(Dir.x*overlap,Dir.y*overlap);
        }

}
