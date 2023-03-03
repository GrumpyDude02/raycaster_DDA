#include <SFML/Graphics.hpp>

#ifdef RAY_H
#include <cmath>
#include "header_files/Ray.h"

ray::ray(sf::Vector2f &direction, sf::Vector2f &starting_pos)
{
    start_pos = starting_pos;
    dir = direction;
}

float ray::cast_ray(int **map, float &radius, int &cell_size)
{
    sf::Vector2f ray_step_size(float(sqrt(1 + (dir.y / dir.x) * (dir.y / dir.x))), float(sqrt(1 + (dir.x / dir.y) * (dir.x / dir.y))));
    sf::Vector2f ray_length;
    int map_coor[] = {int((start_pos.x + radius)), int(start_pos.y + radius)};
    float dist;
    bool Tile_Found = false;
    int step_x, step_y;
    if (dir.x < 0)
    {
        step_x = -1;
        ray_length.x = (((start_pos.x + radius)) - float(map_coor[0])) * ray_step_size.x;
    }
    else
    {
        step_x = 1;
        ray_length.x = (float((map_coor[0] + 1)) - ((start_pos.x + radius))) * ray_step_size.x;
    }
    if (dir.y < 0)
    {
        step_y = -1;
        ray_length.y = (((start_pos.y + radius)) - float(map_coor[1])) * ray_step_size.y;
    }
    else
    {
        step_y = 1;
        ray_length.y = (float((map_coor[1] + 1)) - ((start_pos.y + radius))) * ray_step_size.y;
    }
    while (!Tile_Found)
    {
        if (ray_length.y < ray_length.x)
        {
            map_coor[1] += step_y;
            dist = ray_length.y / cell_size;
            ray_length.y += ray_step_size.y;
        }
        else
        {
            map_coor[0] += step_x;
            dist = ray_length.x / cell_size;
            ray_length.x += ray_step_size.x;
        }
        if (int(map_coor[1] / cell_size) >= 0 && int(map_coor[1] / cell_size) <= 19 && int(map_coor[0] / cell_size) >= 0 && int(map_coor[0] / cell_size) <= 19)
        {
            if (map[int(map_coor[1] / cell_size)][int(map_coor[0] / cell_size)] == 1)
            {
                Tile_Found = true;
            }
        }
        else
        {
            return dist;
        }
        if (dist >= 10)
        {
            dist = 10;
            Tile_Found = false;
        }
    }
    return dist;
}
#endif