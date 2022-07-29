#include<SFML\Graphics.hpp>
#include<iostream>
#include"header_files\utilities.hpp"

void print_fps(sf::Clock& clock){
    sf::Time time=clock.getElapsedTime();
    std::cout<<1.f/time.asSeconds()<<std::endl;
    clock.restart().asSeconds();
}