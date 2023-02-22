#include <iostream>
#include <vector>
#include <cmath>
#include <SFML/Graphics.hpp>
#include <filesystem>

#include "header_files/tools.hpp"
#include "header_files/raycaster.hpp"

// GLOBALE VARIABLES
const int cell_size = 30;
const int cell_number = 20;
int width = cell_number * cell_size * 2;
int height = cell_number * cell_size;
int half_height = int(height / 2);
int half_width = int(width / 2);
float fov = 1.570796f;
int sc_dist = int(half_width / std::tan(fov / 2));

int rays = int(width / 2);
int scale = int(width / rays);
double *DeltaTime = new double;

std::vector<std::vector<int>> map{
    {1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1},
    {1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1},
    {1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1},
    {1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 1},
    {1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1},
    {1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 2, 0, 0, 0, 0, 0, 0, 0, 0, 1},
    {1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1},
    {1, 0, 0, 0, 0, 1, 0, 0, 0, 0, 3, 0, 0, 0, 0, 0, 0, 0, 0, 1},
    {1, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1},
    {1, 0, 0, 0, 0, 1, 0, 0, 0, 0, 4, 0, 0, 0, 0, 0, 0, 0, 0, 1},
    {1, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1},
    {1, 0, 0, 0, 0, 1, 0, 0, 0, 0, 5, 0, 0, 0, 0, 0, 0, 0, 0, 1},
    {1, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1},
    {1, 0, 0, 0, 0, 1, 0, 0, 0, 0, 6, 0, 0, 0, 0, 0, 0, 0, 0, 1},
    {1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1},
    {1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 7, 0, 0, 0, 0, 0, 0, 0, 0, 1},
    {1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1},
    {1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1},
    {1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1},
    {1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1},
};

sf::Texture loadtexture(std::string index)
{
    sf::Texture texture;
    if (!texture.loadFromFile("..\\..\\textures\\" + index + ".png"))
        std::cout << "Failed to load texture\n";
    return texture;
}

int main()
{

    // LOADING TEXTURES
    int files_num = 0;
    std::vector<sf::Texture> texture_list;
    std::string path = "..\\..\\textures";
    for (const auto &entity : std::filesystem::directory_iterator(path))
    {
        files_num++;
    }
    for (int i = 1; i <= files_num; i++)
    {
        sf::Texture texture;
        texture = loadtexture(std::to_string(i));
        texture_list.push_back(texture);
    }

    // WINDOW INITIALISATION
    sf::RenderWindow window(sf::VideoMode(width, height), "test");
    // window.setFramerateLimit(60);
    sf::Clock clock;
    sf::Texture brick_wall;
    brick_wall = loadtexture("1");

    // VECTORS
    std::vector<sf::RectangleShape> tiles;
    std::vector<sf::RectangleShape> small_tiles;
    std::vector<std::vector<float>> strip;

    // ceiling and floor
    sf::RectangleShape sky, bottom;
    sky.setSize(sf::Vector2f(float(width), float(half_height)));
    bottom.setSize(sf::Vector2f(float(width), float(half_height)));
    sky.setPosition(0, 0);
    bottom.setPosition(0, half_height);
    sky.setFillColor(sf::Color(84, 84, 84));
    bottom.setFillColor(sf::Color(150, 150, 150));

    // CAMERA POSITION
    sf::Vector2f pos(260, 260);
    float r = 15.f;
    Raycaster camera(r, pos, fov, rays, width, height);
    sf::CircleShape map_pos;
    map_pos.setRadius(5.f);
    map_pos.setFillColor(sf::Color(255, 0, 0));
    int small_scale = 10;

    // LOOP THROUGH THE MAP TO FIND WALLS
    for (int i = 0; i < 20; i++)
    {
        for (int j = 0; j < 20; j++)
        {
            if (map[i][j] > 0)
            {
                sf::RectangleShape rect;
                rect.setSize(sf::Vector2f(float(cell_size - 1), float(cell_size - 1)));
                rect.setPosition(j * cell_size, i * cell_size);
                tiles.push_back(rect);

                sf::RectangleShape small_rect;
                small_rect.setSize(sf::Vector2f(float(10 - 1), float(10 - 1)));
                small_rect.setPosition(j * small_scale, i * small_scale);
                small_rect.setFillColor(sf::Color(255, 255, 255));
                small_tiles.push_back(small_rect);
            }
        }
    }

    // GAME LOOP
    while (window.isOpen())
    {
        map_pos.setPosition((camera.shape.getPosition().x / cell_size) * 10, (camera.shape.getPosition().y / cell_size) * 10);
        sf::Event ev;
        while (window.pollEvent(ev))
        {
            if (ev.type == sf::Event::Closed)
                window.close();
        }
        window.clear();
        window.draw(sky);
        window.draw(bottom);
        strip = camera.update(window, DeltaTime, cell_size, map, rays, sc_dist);
        std::sort(strip.begin(), strip.end());
        for (int i = 0; i < strip.size(); i++)
        {
            float offset = strip[i][0];
            int index = strip[i][1];
            float proj_height = strip[i][2];
            int x_pos = strip[i][3];
            sf::Sprite sprite;
            sprite.setTexture(texture_list[index - 1]);
            // std::cout<<index<<"\n";
            sprite.setTextureRect(sf::IntRect((offset) * (64 - scale), 0, (scale), 64));
            sprite.setScale(sf::Vector2f(scale, (proj_height / 64)));
            sprite.setPosition(sf::Vector2f(x_pos * scale, half_height - proj_height / 2));
            window.draw(sprite);
        }
        draw_minimap(window, tiles, small_tiles, camera, map_pos, small_scale, cell_size);
        window.display();
        print_fps(clock, DeltaTime);
    }
    return 0;
    system("pause");
}