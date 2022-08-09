#include<iostream>
#include<vector>
#include<cmath>
#include<SFML/Graphics.hpp>

#include"header_files/tools.hpp"
#include"header_files/raycaster.hpp"


//GLOBALE VARIABLES
const int cell_size=30;
const int cell_number=20;
int width=cell_number*cell_size*2;
int  height=cell_number*cell_size;
int half_height=int(height/2);
int half_width=int(width/2);
float fov=M_PI_2;
int sc_dist=int(half_width/std::tan(fov/2));


int rays=int(width/2);
int scale=int(width/rays);
double* DeltaTime=new double;

std::vector<std::vector<int>> map{{1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1},
                                    {1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
                                    {1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
                                    {1,0,0,0,0,0,0,0,0,0,1,0,0,0,0,0,0,0,0,1},
                                    {1,0,0,0,0,0,0,0,0,0,1,0,0,0,0,0,0,0,0,1},
                                    {1,0,0,0,0,0,0,0,0,0,1,0,0,0,0,0,0,0,0,1},
                                    {1,0,0,0,0,0,0,0,0,0,1,0,0,0,0,0,0,0,0,1},
                                    {1,0,0,0,0,1,1,1,1,1,1,0,0,0,0,0,0,0,0,1},
                                    {1,0,0,0,0,1,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
                                    {1,0,0,0,0,1,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
                                    {1,0,0,0,0,1,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
                                    {1,0,0,0,0,1,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
                                    {1,0,0,0,0,1,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
                                    {1,0,0,0,0,1,1,1,1,1,1,1,1,1,1,1,1,0,0,1},
                                    {1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
                                    {1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
                                    {1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
                                    {1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
                                    {1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
                                    {1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1},};


int main(){

    //WINDOW INITIALISATION
    sf::RenderWindow window(sf::VideoMode(width,height),"test");
    //window.setFramerateLimit(60);
    sf::Clock clock;
    sf::Texture brick_wall;
    if(!brick_wall.loadFromFile("..\\..\\textures\\1.png"))
    std::cout<<"failed to load texture";

    //VECTORS
    std::vector<sf::RectangleShape> tiles;
    std::vector<sf::RectangleShape> small_tiles;
    std::vector<std::vector<float>> strip;

    //ceiling and floor
    sf::RectangleShape sky,bottom;
    sky.setSize(sf::Vector2f(float(width),float(half_height)));
    bottom.setSize(sf::Vector2f(float(width),float(half_height)));
    sky.setPosition(0,0);
    bottom.setPosition(0,half_height);
    sky.setFillColor(sf::Color(84,84,84));
    bottom.setFillColor(sf::Color(150,150,150));

    //CAMERA POSITION
    sf::Vector2f pos(260,260);
    float r=15.f;
    Player player1(r,pos,fov,rays,width,height);
    
    //LOOP THROUGH THE MAP TO FIND WALLS
    for (int i=0;i<20;i++){
        for(int j=0;j<20;j++)
        {
            if (map[i][j]>0){
                sf::RectangleShape rect;
                rect.setSize(sf::Vector2f(float(cell_size-1),float(cell_size-1)));
                rect.setPosition(j*cell_size,i*cell_size);
                rect.setFillColor(sf::Color(0,255,0));
                tiles.push_back(rect);

                sf::RectangleShape small_rect;
                small_rect.setSize(sf::Vector2f(float(10-1),float(10-1)));
                small_rect.setPosition(j*10,i*10);
                small_rect.setFillColor(sf::Color(255,255,255));
                small_tiles.push_back(small_rect);
            }
        }
    }


    //GAME LOOP
    while(window.isOpen()){
        sf::Event ev;
        while(window.pollEvent(ev)){
            if (ev.type==sf::Event::Closed)
                window.close();}
        window.clear();
        window.draw(sky);
        window.draw(bottom);
        strip=player1.update(window,DeltaTime,cell_size,map,rays,sc_dist);
        for (int i=0;i<strip.size();i++){
            float offset=strip[i][0];
            float proj_height=strip[i][1];
            sf::Sprite sprite;
            sprite.setTexture(brick_wall);
            sprite.setTextureRect(sf::IntRect((offset)*(64-scale),0,float(scale),64));
            sprite.scale(sf::Vector2f(4,(proj_height/64)));
            sprite.setPosition(sf::Vector2f(i*scale,half_height-proj_height/2));
            window.draw(sprite);
        }
        draw_minimap(window,tiles,small_tiles,player1,10,r,cell_size);
        window.display();
        print_fps(clock,DeltaTime);
    }
    return 0;
}