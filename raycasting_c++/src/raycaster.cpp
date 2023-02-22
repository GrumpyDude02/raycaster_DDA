#include <SFML/Graphics.hpp>
#include <cmath>
#include <iostream>
#include "header_files/raycaster.hpp"

Raycaster::Raycaster(float r, sf::Vector2f position, float fov, int &casted_rays, int width, int height)
    : angle(3.14159f),
      FOV(fov),
      width(width),
      radius(r),
      pos(position)
{
    start_angle = FOV / 2 - (angle);
    scale = int(width / casted_rays);
    shape.setRadius(radius);
    shape.setPosition(pos.x, pos.y);
    shape.setFillColor(sf::Color(255, 0, 0));
    step = (FOV / casted_rays);
}

std::vector<std::vector<float>> Raycaster::update(sf::RenderWindow &screen, double *dt, int cell_size, std::vector<std::vector<int>> &map, int &casted_rays, int &sc_distance)
{
    start_angle = (angle) - (FOV / 2);
    // screen.draw(shape);
    std::vector<std::vector<float>> strips;
    for (int i = 0; i <= casted_rays + 1; i++)
    {
        sf::Vector2f ray_start((pos.x + radius) / cell_size, (pos.y + radius) / cell_size);
        sf::Vector2f unit_step_size, Ray_length;
        int map_cell[] = {int(ray_start.x), int(ray_start.y)};
        bool horizontal, flag = true;
        int dx, dy, index;
        float dist, displacement;
        float cos_a = std::cos(start_angle);
        float sin_a = std::sin(start_angle);
        std::vector<float> data;

        if (cos_a < 0)
        {
            dx = -1;
            unit_step_size.x = dx / cos_a;
            Ray_length.x = (ray_start.x - float(map_cell[0])) * unit_step_size.x;
        }
        else
        {
            dx = 1;
            unit_step_size.x = dx / cos_a;
            Ray_length.x = (float(map_cell[0] + 1) - ray_start.x) * unit_step_size.x;
        }
        if (sin_a < 0)
        {
            dy = -1;
            unit_step_size.y = dy / sin_a;
            Ray_length.y = (ray_start.y - float(map_cell[1])) * unit_step_size.y;
        }
        else
        {
            dy = 1;
            unit_step_size.y = dy / sin_a;
            Ray_length.y = (float(map_cell[1] + 1) - ray_start.y) * unit_step_size.y;
        }
        while (flag)
        {
            if (Ray_length.x < Ray_length.y)
            {
                map_cell[0] += dx;
                dist = Ray_length.x;
                horizontal = true;
                Ray_length.x += unit_step_size.x;
            }
            else
            {
                map_cell[1] += dy;
                horizontal = false;
                dist = Ray_length.y;
                Ray_length.y += unit_step_size.y;
            }
            if (map_cell[0] >= 0 && map_cell[0] < map[0].size() && map_cell[1] >= 0 && map_cell[1] < map.size())
            {
                if (map[map_cell[1]][map_cell[0]] > 0)
                {
                    if (horizontal)
                    {
                        if (cos_a > 0)
                        {
                            displacement = fmod(ray_start.y + sin_a * dist, 1);
                        }
                        else
                        {
                            displacement = 1 - fmod(ray_start.y + sin_a * dist, 1);
                        }
                    }
                    else
                    {
                        if (sin_a > 0)
                        {
                            displacement = fmod(ray_start.x + cos_a * dist, 1);
                        }
                        else
                        {
                            displacement = 1 - fmod(ray_start.x + cos_a * dist, 1);
                        }
                    }
                    index = map[map_cell[1]][map_cell[0]];
                    data.push_back(displacement);
                    data.push_back(float(index));
                    flag = false;
                }
            }
        }
        dist *= std::cos(start_angle - (angle));
        float projected_height = float(sc_distance) / (dist + 0.0001);
        data.push_back(projected_height);
        data.push_back(i);
        start_angle = atan(((scale * i - float(width / 2)) / sc_distance)) + (angle);
        strips.push_back(data);
    }
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Left))
    {
        angle -= 5 * (*dt);
    }
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Right))
    {
        angle += 5 * (*dt);
    }
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Up))
    {
        shape.move(std::cos(angle) * 50 * (*dt), std::sin(angle) * 50 * (*dt));
        pos = shape.getPosition();
    }
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Down))
    {
        shape.move(-std::cos(angle) * 50 * (*dt), -std::sin(angle) * 50 * (*dt));
        pos = shape.getPosition();
    }
    return strips;
}