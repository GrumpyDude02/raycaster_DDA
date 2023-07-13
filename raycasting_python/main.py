import pygame, sys
from settings import *
from texture_loader import texture_list
from stuff import circle_rect_collisions, display_fps
from raycaster import raycaster

pygame.init()

objects = []
ray_coordonates = []


map = [
    [1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1],
    [1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1],
    [1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1],
    [1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1],
    [1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1],
    [1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1],
    [1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1],
    [1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1],
    [1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1],
    [1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1],
    [1, 0, 0, 1, 0, 2, 0, 3, 0, 4, 0, 5, 0, 6, 0, 7, 0, 0, 0, 1],
    [1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1],
    [1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1],
    [1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1],
    [1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1],
    [1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1],
    [1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1],
    [1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1],
    [1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1],
    [1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1],
]


def draw_minimap(map, camera, ray_coordonates):
    pygame.draw.rect(main_surface, (0, 0, 0), (0, 0, len(map) * 10, len(map) * 10))
    map_pos = {"x": (camera.pos.x / cell_size) * 10, "y": (camera.pos.y / cell_size) * 10}
    pygame.draw.circle(main_surface, (255, 0, 0), (map_pos["x"], map_pos["y"]), 2)
    for ray in range(0, len(ray_coordonates), 4):
        pygame.draw.line(
            main_surface,
            (0, 255, 0),
            (map_pos["x"], map_pos["y"]),
            (map_pos["x"] + ray_coordonates[ray]["x"], map_pos["y"] + ray_coordonates[ray]["y"]),
        )

    # checking surrounding walls for collisions to save on performance

    starting_cell_x = max(0, (camera.pos.x // cell_size) - 2)
    ending_cell_x = min(len(map) - 1, (camera.pos.x // cell_size) + 2)
    starting_cell_y = max(0, (camera.pos.y // cell_size) - 2)
    ending_cell_y = min(len(map) - 1, (camera.pos.y // cell_size) + 2)

    for i in range(len(map)):
        for j in range(len(map[0])):
            if map[i][j] != 0:
                square = pygame.Rect((j) * cell_size, (i) * cell_size, (cell_size) - 1, cell_size - 1)
                if (
                    square.x >= starting_cell_x * cell_size
                    and square.x <= ending_cell_x * cell_size
                    and square.y >= starting_cell_y * cell_size
                    and square.y <= ending_cell_y * cell_size
                ):
                    circle_rect_collisions(camera.pos, square, 10, cell_size, cell_size, True)
                mini_square = pygame.Rect((j) * 10, (i) * 10, 9, 9)
                pygame.draw.rect(main_surface, (WHITE), mini_square)


def render_walls(list):
    for objects in list:
        texture_offset = objects[1]
        projected_height = objects[0]
        texture_index = objects[2]
        texture = texture_list[str(texture_index)]
        wall_column = texture.subsurface(texture_offset * (TEXTURE_SIZE - camera.scale), 0, camera.scale, TEXTURE_SIZE)
        wall_column = pygame.transform.scale(wall_column, (camera.scale, projected_height))
        index = list.index(objects)
        column_pos = (camera.scale * index, half_height - projected_height // 2 + offset[0])
        main_surface.blit(wall_column, column_pos)


camera = raycaster((4, 4), casted_rays)

import time

previous_time = time.time()
toggle = True
visibility = False
max_dt = 0.066

while 1:
    event = pygame.event.poll()
    if event.type == pygame.QUIT:
        sys.exit()
    if event.type == pygame.KEYDOWN:
        if event.key == pygame.K_ESCAPE:
            toggle = not toggle
            visibility = not visibility
    dt = time.time() - previous_time
    if dt >= 0.066:
        dt = 0.066
    previous_time = time.time()
    main_surface.fill((0, 0, 0))
    sky = pygame.Rect(0, 0, 1200, 300 + offset[0])
    floor = pygame.Rect(0, 300 + offset[0], 1200, 300 - offset[0])
    pygame.draw.rect(main_surface, GREY, sky)
    pygame.draw.rect(main_surface, DARKER_GREY, floor)
    camera.update(dt, toggle, offset, visibility)
    objects, ray_coordonates = camera.cast_rays(map, 10)
    render_walls(objects)
    draw_minimap(map, camera, ray_coordonates)
    clock.tick(60)
    fps = clock.get_fps()
    display_fps(clock, main_surface, (1150, 20))
    pygame.display.flip()
