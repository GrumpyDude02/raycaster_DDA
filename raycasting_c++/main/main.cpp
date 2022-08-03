#include<iostream>
#include<vector>
#include<cmath>
#include<algorithm>
#include<SFML/Graphics.hpp>

#include"header_files/utilities.hpp"
#include"header_files/player.hpp"

const int cell_size=30;
const int cell_number=20;
const int width=cell_number*cell_size;
const int  height=cell_number*cell_size;
int rays=int(width/2);
int** map=new int*[20];
double* DeltaTime=new double;


int main(){
    sf::RenderWindow window(sf::VideoMode(600,600),"test");
    window.setFramerateLimit(60);
    sf::Clock clock;

    for(int i=0;i<20;i++){
        map[i]=new int[20];
    }
    for(int i=0;i<20;i++){
        map[i][0]=1;
        map[0][i]=1;
        map[19][i]=1;
        map[i][19]=1;}
    map[4][8]=1;
    map[6][8]=1;

    std::vector<sf::RectangleShape> tiles;
    std::vector<int> rect_pos;

    for (int i=0;i<20;i++){
        for(int j=0;j<20;j++)
        {
            if (map[i][j]==1){
                sf::RectangleShape rect;
                rect.setSize(sf::Vector2f(float(cell_size-1),float(cell_size-1)));
                rect.setPosition(j*cell_size,i*cell_size);
                rect.setFillColor(sf::Color(0,255,0));
                tiles.push_back(rect);
                rect_pos.push_back((i+j*cell_size));
            }
        }
    }

    
    
    sf::Vector2f pos(260,260);
    float r=15.f;
    Player player1(r,pos,M_PI_2,rays);

    while(window.isOpen()){
        sf::Event ev;
        while(window.pollEvent(ev)){
            if (ev.type==sf::Event::Closed)
                window.close();}
        window.clear();
        
        sf::Vector2f position=player1.shape.getPosition();
        int position_cell_x=int((position.x+r)/cell_size);
        int position_cell_y=int((position.y+r)/cell_size);

        int starting_cell_x=std::max(0,position_cell_x-2);
        int ending_cell_x=std::min(19,position_cell_x+2);
        int starting_cell_y=std::max(0,position_cell_y-2);
        int ending_cell_y=std::min(19,position_cell_y+2);           
        std::vector<int>::iterator it;
        
        for (auto & rectangle : tiles){
            window.draw(rectangle);
            if (rectangle.getPosition().x>=starting_cell_x*cell_size && rectangle.getPosition().x<=ending_cell_x*cell_size && rectangle.getPosition().y>=starting_cell_y*cell_size && rectangle.getPosition().y<=ending_cell_y*cell_size){
            cir_rect_collision(player1.shape,rectangle,r,cell_size,cell_size);
        }}
        player1.update(window,DeltaTime,cell_size,map,rays);
        window.display();
        print_fps(clock,DeltaTime);
    }
    return 0;
}