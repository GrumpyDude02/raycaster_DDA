#include<SFML\Graphics.hpp>
#include<iostream>
#include<cmath>
#include<header_files/tools.hpp>
#include<header_files/raycaster.hpp>


void print_fps(sf::Clock& clock,double* dt){
    *dt=clock.restart().asSeconds();
    //std::cout<<int(1.f/(*dt))<<std::endl;
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
    float nearestX=circle.getPosition().x+circle_radius;
    float nearestY=circle.getPosition().y+circle_radius;
    nearestX=std::clamp(nearestX,rect.getPosition().x,rect.getPosition().x+rw);
    nearestY=std::clamp(nearestY,rect.getPosition().y,rect.getPosition().y+rh);

    sf::Vector2f nearestV(circle.getPosition().x+circle_radius-nearestX,circle.getPosition().y+circle_radius-nearestY);
    float dist=sqrt((nearestV.x*nearestV.x)+(nearestV.y*nearestV.y));

    if(dist<=circle_radius) {
        float overlap=circle_radius-dist;
        sf::Vector2f Dir(nearestV.x/dist,nearestV.y/dist);
        circle.move(Dir.x*overlap,Dir.y*overlap);
        }
}

void draw_minimap(sf::RenderWindow& screen,std::vector<sf::RectangleShape>& tiles,std::vector<sf::RectangleShape>& small_tiles,Player& player,int scale,int radius,int cell_size){
    sf::Vector2f position=player.shape.getPosition();

    int position_cell_x=int((position.x+radius)/cell_size);
    int position_cell_y=int((position.y+radius)/cell_size);

    int starting_cell_x=std::max(0,position_cell_x-2);
    int ending_cell_x=std::min(19,position_cell_x+2);
    int starting_cell_y=std::max(0,position_cell_y-2);
    int ending_cell_y=std::min(19,position_cell_y+2); 

    sf::RectangleShape rect;
    rect.setSize(sf::Vector2f(20*scale,20*scale));
    rect.setPosition(sf::Vector2f(0,0));
    rect.setFillColor(sf::Color(0,0,0));  
    screen.draw(rect);        
    for(int i=0;i<tiles.size();i++){
        if (tiles[i].getPosition().x>=starting_cell_x*cell_size && tiles[i].getPosition().x<=ending_cell_x*cell_size && tiles[i].getPosition().y>=starting_cell_y*cell_size && tiles[i].getPosition().y<=ending_cell_y*cell_size){
            cir_rect_collision(player.shape,tiles[i],radius,cell_size,cell_size); 
    }
    screen.draw(small_tiles[i]);
    
}}