#include<iostream>
#include<vector>
#include<cmath>
#include<SFML\Graphics.hpp>

#include"header_files\utilities.hpp"

const int cell_size=30;
const int cell_number=20;
int** map=new int*[20];
double* DeltaTime=new double;

class ray{
    public:
        sf::Vector2f dir;
        sf::Vector2f start_pos;
    ray(sf::Vector2f direction,sf::Vector2f starting_pos){
        start_pos=starting_pos;
        dir=direction;
    }
    float cast_rays(int** map){
       sf::Vector2f ray_step_size=sf::Vector2f(sqrt(1+(dir.y/dir.x)*(dir.y/dir.x)),sqrt(1+(dir.x/dir.y)*(dir.x/dir.y)));
       sf::Vector2f ray_length;
       int map_coor[]={int(start_pos.x/cell_size),int(start_pos.y/cell_size)};
       float dist;
       bool Tile_Found=false;
       int step_x,step_y;
        if(dir.x<0){
            step_x=-1;
            ray_length.x=(((start_pos.x+20)/cell_size)-float(map_coor[0]))*ray_step_size.x;
        }else{
            step_x=1;
            ray_length.x=(float((map_coor[0]+1))-((start_pos.x+20)/cell_size))*ray_step_size.x;
        }
        if(dir.y<0){
            step_y=-1;
            ray_length.y=(((start_pos.y+20)/cell_size)-float(map_coor[1]))*ray_step_size.y;
        }else{
            step_y=1;
            ray_length.y=(float((map_coor[1]+1))-((start_pos.y+20)/cell_size))*ray_step_size.y;
        }
       while(!Tile_Found && dist<20.f){
            if (ray_length.y<ray_length.x){
                map_coor[1]+=step_y;
                dist=ray_length.y;
                ray_length.y+=ray_step_size.y;
            }else{
                map_coor[0]+=step_x;
                dist=ray_length.x;
                ray_length.x+=ray_step_size.x;
            }
                if(map[map_coor[1]][map_coor[0]]==1){
                Tile_Found=true;}         
        }
        return dist;
    }
};

class player{
    public:
        double* angle;
        float radius;
        sf::CircleShape shape;
        sf::Vector2f pos;
        sf::Vector2f dir;
        sf::Vector2f vec;


    player(float r,sf::Vector2f position){
        *angle=M_PI;
        pos=position;
        radius=r;
        shape.setRadius(radius);
        shape.setPosition(pos.x,pos.y);
        shape.setFillColor(sf::Color(255,0,0));
        dir=sf::Vector2f(std::sin((*angle))*cell_size,std::cos((*angle))*cell_size);
    }

    void update(sf::RenderWindow& screen){
        dir=sf::Vector2f(std::sin((*angle))*cell_size,std::cos((*angle))*cell_size);
        screen.draw(shape);
        ray line(dir,pos);
        float distance=line.cast_rays(map);
        sf::Vertex ray[]={sf::Vector2f(pos.x+radius,pos.y+radius),sf::Vector2f(pos.x+radius+dir.x*distance,pos.y+radius+dir.y*distance)};
        screen.draw(ray, 2, sf::Lines);
        

        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Left)){
            *angle+=0.01f;
        }
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Right)){
            *angle-=0.01f;
        }
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Up)){
            shape.move(std::sin(*angle)*0.5f,std::cos(*angle));
            pos=shape.getPosition();
        }
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Down)){
            shape.move(-std::sin(*angle)*0.5f,-std::cos(*angle));
            pos=shape.getPosition();
            
        }

    }
};


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

    std::vector<sf::RectangleShape> tiles;

    for (int i=0;i<20;i++){
        for(int j=0;j<20;j++)
        {
            if (map[i][j]==1){
                sf::RectangleShape rect;
                rect.setSize(sf::Vector2f(float(cell_size-1),float(cell_size-1)));
                rect.setPosition(j*cell_size,i*cell_size);
                rect.setFillColor(sf::Color(0,255,0));
                tiles.push_back(rect);
            }
        }
    }

    sf::Vector2f pos(260,260);
    float r=20.f;
    player player1(r,pos);
    sf::RectangleShape rect;
    rect.setPosition(8*cell_size,4*cell_size);

    while(window.isOpen()){
        sf::Event ev;
        while(window.pollEvent(ev)){
            if (ev.type==sf::Event::Closed)
                window.close();}
        window.clear();
        for (auto & rectangle : tiles){
            window.draw(rectangle);
        }
        player1.update(window);
        window.display();
        std::cout<<collision(player1.shape,rect,cell_size)<<std::endl;
        print_fps(clock,DeltaTime);
    }
    return 0;
}