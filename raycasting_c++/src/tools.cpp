#include <SFML\Graphics.hpp>
#include <iostream>
#include <cmath>
#include <tools.h>
#include <raycaster.h>

bool collision(sf::CircleShape &circle, sf::RectangleShape &rect, float rect_width)
{
    float temp_x, temp_y;
    float circle_radius = circle.getRadius();
    float c_x = circle.getPosition().x + circle_radius;
    float c_y = circle.getPosition().y + circle_radius;
    float r_x = rect.getPosition().x;
    float r_y = rect.getPosition().y;

    if (c_x <= r_x)
    {

        temp_x = r_x;
    }
    else
    {

        temp_x = r_x + rect_width;
    }
    if (c_y <= r_y)
    {

        temp_y = r_y;
    }
    else
    {

        temp_y = r_y + rect_width;
    }
    sf::Vector2f np = sf::Vector2f(c_x - temp_x, c_y - temp_y);
    float distance = sqrtf(np.x * np.x + np.y * np.y);
    float overlap = circle_radius - distance;

    if (distance <= circle_radius)
    {
        return true;
    }

    return false;
}

void cir_rect_collision(sf::CircleShape &circle, sf::RectangleShape &rect, float circle_radius, float rw, float rh)
{
    float nearestX = circle.getPosition().x + circle_radius;
    float nearestY = circle.getPosition().y + circle_radius;
    nearestX = std::clamp(nearestX, rect.getPosition().x, rect.getPosition().x + rw);
    nearestY = std::clamp(nearestY, rect.getPosition().y, rect.getPosition().y + rh);

    sf::Vector2f nearestV(circle.getPosition().x + circle_radius - nearestX, circle.getPosition().y + circle_radius - nearestY);
    float dist = sqrt((nearestV.x * nearestV.x) + (nearestV.y * nearestV.y));

    if (dist <= circle_radius)
    {
        float overlap = circle_radius - dist;
        sf::Vector2f Dir(nearestV.x / dist, nearestV.y / dist);
        circle.move(Dir.x * overlap, Dir.y * overlap);
    }
}

void draw_minimap(sf::RenderWindow &screen, std::vector<sf::RectangleShape> &tiles, std::vector<sf::RectangleShape> &small_tiles, Raycaster &player, sf::CircleShape &p_map_pos, int scale, int cell_size)
{
    sf::Vector2f position = player.shape.getPosition();
    float radius = player.shape.getRadius();

    int position_cell_x = int((position.x + radius) / cell_size);
    int position_cell_y = int((position.y + radius) / cell_size);

    int starting_cell_x = std::max(0, position_cell_x - 2);
    int ending_cell_x = std::min(19, position_cell_x + 2);
    int starting_cell_y = std::max(0, position_cell_y - 2);
    int ending_cell_y = std::min(19, position_cell_y + 2);

    sf::RectangleShape rect;
    rect.setSize(sf::Vector2f(20 * scale, 20 * scale));
    rect.setPosition(sf::Vector2f(0, 0));
    rect.setFillColor(sf::Color(0, 0, 0));
    screen.draw(rect);
    for (int i = 0; i < tiles.size(); i++)
    {
        if (tiles[i].getPosition().x >= starting_cell_x * cell_size && tiles[i].getPosition().x <= ending_cell_x * cell_size && tiles[i].getPosition().y >= starting_cell_y * cell_size && tiles[i].getPosition().y <= ending_cell_y * cell_size)
        {
            cir_rect_collision(player.shape, tiles[i], radius, cell_size, cell_size);
        }
        screen.draw(p_map_pos);
        screen.draw(small_tiles[i]);
    }
}

void print_fps(sf::Clock &clock, double *dt, sf::RenderWindow &window, sf::Font &DefaultFont)
{
    static sf::RectangleShape bg;
    bg.setSize(sf::Vector2f(40.0f, 20.0f));
    bg.setPosition(sf::Vector2f(0, 0));
    bg.setFillColor(sf::Color(255, 255, 255));
    sf::Text FPS(std::to_string(int(1 / (*dt))), DefaultFont, 18);
    FPS.setStyle(sf::Text::Bold);
    FPS.setFillColor(sf::Color::Black);
    FPS.setPosition(sf::Vector2f(0.0f, 0.0f));
    window.draw(bg);
    window.draw(FPS);
}
int partition(std::vector<std::vector<float>> &values, int left, int right)
{
    int pivotIndex = left + (right - left) / 2;
    float pivotValue = values[pivotIndex][2];
    int i = left, j = right;
    std::vector<float> temp;
    while (i <= j)
    {
        while (values[i][2] < pivotValue)
        {
            i++;
        }
        while (values[j][2] > pivotValue)
        {
            j--;
        }
        if (i <= j)
        {
            temp = values[i];
            values[i] = values[j];
            values[j] = temp;
            i++;
            j--;
        }
    }
    return i;
}
void quicksort(std::vector<std::vector<float>> &values, int left, int right)
{
    if (left < right)
    {
        int pivotIndex = partition(values, left, right);
        quicksort(values, left, pivotIndex - 1);
        quicksort(values, pivotIndex, right);
    }
}

int partition_sprite(std::vector<sf::Sprite> &values, int left, int right)
{
    int pivotIndex = left + (right - left) / 2;
    float pivotValue = values[pivotIndex].getScale().y;
    int i = left, j = right;
    sf::Sprite temp;
    while (i <= j)
    {
        while (values[i].getScale().y < pivotValue)
        {
            i++;
        }
        while (values[j].getScale().y > pivotValue)
        {
            j--;
        }
        if (i <= j)
        {
            temp = values[i];
            values[i] = values[j];
            values[j] = temp;
            i++;
            j--;
        }
    }
    return i;
}
void quicksort_sprite(std::vector<sf::Sprite> &values, int left, int right)
{
    if (left < right)
    {
        int pivotIndex = partition_sprite(values, left, right);
        quicksort_sprite(values, left, pivotIndex - 1);
        quicksort_sprite(values, pivotIndex, right);
    }
}