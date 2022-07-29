#include<iostream>
#include<vector>
#include<cmath>
#include<SFML\Graphics.hpp>

#include"header_files\utilities.hpp"

const int cell_size=30;
const int cell_number=20;

class player{
    public:
        double* angle;
        float radius;
        sf::CircleShape shape;
        sf::Vector2f pos;
        sf::Vector2f dir;
        sf::Vector2f vec;

    player(float r,sf::Vector2f position){
        *angle=0;
        pos=position;
        radius=r;
        shape.setRadius(radius);
        shape.setPosition(pos.x,pos.y);
        shape.setFillColor(sf::Color(255,0,0));
        dir=sf::Vector2f(std::cos((*angle)),std::sin((*angle)));

    }
    void drawplayer(sf::RenderWindow& screen){
        dir=sf::Vector2f(std::cos((*angle)),std::sin((*angle)));
        screen.draw(shape);
        sf::Vertex ray[]={sf::Vector2f(pos.x+radius,pos.y+radius),sf::Vector2f(pos.x+radius+dir.x*30,pos.y+radius+dir.y*30)};
        screen.draw(ray, 2, sf::Lines);
        *angle+=0.01f;
        if((*angle)>=2*M_PI)    *angle=0;
    }
};

int main(){
    sf::RenderWindow window(sf::VideoMode(600,600),"test");
    window.setFramerateLimit(60);
    sf::Clock clock;
    int** map=new int*[20];
    for(int i=0;i<20;i++){
        map[i]=new int[20];
    }
    for(int i=0;i<20;i++){
        map[i][0]=1;
        map[0][i]=1;
        map[19-i][19]=1;
        map[19][19-i];}
    std::vector<sf::RectangleShape> tiles;
    for (int i=0;i<20;i++){
        for(int j=0;j<14;j++)
        {
            if (map[i][j]==1){
                sf::RectangleShape rect;
                rect.setSize(sf::Vector2f(float(cell_size-1),float(cell_size-1)));
                rect.setPosition(j*cell_size,i*cell_size);
                rect.setFillColor(sf::Color(255,255,255));
                tiles.push_back(rect);
            }
        }
    }
    sf::Vector2f pos(260,260);
    float r=20.f;
    player player1(r,pos);
    while(window.isOpen()){
        sf::Event ev;
        while(window.pollEvent(ev)){
            if (ev.type==sf::Event::Closed)
                window.close();}
        window.clear();
        for (auto & rectangle : tiles){
            window.draw(rectangle);
        }
        player1.drawplayer(window);
        window.display();
        //print_fps(clock);
    }
    return 0;
}