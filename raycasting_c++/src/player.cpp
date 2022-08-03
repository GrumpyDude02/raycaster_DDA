
#include<SFML/Graphics.hpp>
#include<cmath>
#include"header_files/player.hpp"

Player::Player(float r,sf::Vector2f position,float fov,int& casted_rays){
    *angle=M_PI;
    FOV=fov;
    start_angle=FOV/2-(*angle);
    pos=position;
    radius=r;
    shape.setRadius(radius);
    shape.setPosition(pos.x,pos.y);
    shape.setFillColor(sf::Color(255,0,0));
    step=(FOV/casted_rays);
}

void Player::update(sf::RenderWindow& screen,double* dt,int cell_size,int** map,int& casted_rays){
    start_angle=(*angle)-(FOV/2);
        screen.draw(shape);

        for(int i=0;i<=casted_rays;i++){
            sf::Vector2f ray_start((pos.x+radius)/cell_size,(pos.y+radius)/cell_size);
            sf::Vector2f unit_step_size,Ray_length;
            int map_cell[]={int(ray_start.x),int(ray_start.y)};
            int dx,dy;
            float dist;
            float cos_a=std::cos(start_angle);
            float sin_a=std::sin(start_angle);

            if (cos_a<0){
                dx=-1;
                unit_step_size.x=dx/cos_a;
                Ray_length.x=(ray_start.x-float(map_cell[0]))*unit_step_size.x;
            }else{
                dx=1;
                unit_step_size.x=dx/cos_a;
                Ray_length.x=(float(map_cell[0]+1)-ray_start.x)*unit_step_size.x;
            }
            if (sin_a<0){
                dy=-1;
                unit_step_size.y=dy/sin_a;
                Ray_length.y=(ray_start.y-float(map_cell[1]))*unit_step_size.y;
            }else{
                dy=1;
                unit_step_size.y=dy/sin_a;
                Ray_length.y=(float(map_cell[1]+1)-ray_start.y)*unit_step_size.y;
            }
            while(1){
                if (Ray_length.x<Ray_length.y){
                    map_cell[0]+=dx;
                    dist=Ray_length.x;
                    Ray_length.x+=unit_step_size.x;
                }else{
                    map_cell[1]+=dy;
                    dist=Ray_length.y;
                    Ray_length.y+=unit_step_size.y;
                }
                if (dist>=10){
                    dist=10;
                    break;
                }
                else if(map_cell[0]>=0 && map_cell[0]<=19 && map_cell[1]>=0 && map_cell[1]<=19){
                    if(map[map_cell[1]][map_cell[0]]==1){
                        break;
                    }
                }
            }
            sf::Vertex line[]={
                sf::Vector2f(pos.x+radius,pos.y+radius),
                sf::Vector2f(pos.x+radius+cos_a*dist*cell_size,pos.y+radius+sin_a*dist*cell_size)
                };
            screen.draw(line,2,sf::Lines);
            start_angle+=step;
        }

        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Left)){
            *angle-=5*(*dt);
        }
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Right)){
            *angle+=5*(*dt);
        }
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Up)){
            shape.move(std::cos(*angle)*50*(*dt),std::sin(*angle)*50*(*dt));
            pos=shape.getPosition();
        }
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Down)){
            shape.move(-std::cos(*angle)*50*(*dt),-std::sin(*angle)*50*(*dt));
            pos=shape.getPosition();
            
        }

    }