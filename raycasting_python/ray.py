import pygame
from pygame.math import Vector2 as vc

class ray:
    def __init__(self,direction,start_pos) :
        self.pos=start_pos
        self.dir=direction
        
    def cast_ray(self,map,cell_size):
        ray_start=[self.pos.x,self.pos.y]
        ray_step_unit=vc()
        map_cell=[int(ray_start[0]),int(ray_start[1])]
        Ray_length=vc(0,0)
        
        if (self.dir.y<0):
            step_y=-1
            ray_step_unit.y=step_y/self.dir.y
            Ray_length.y=(ray_start[1]-float(map_cell[1]))*ray_step_unit.y
        else :
            step_y=1
            ray_step_unit.y=step_y/self.dir.y
            Ray_length.y=(-ray_start[1]+float(map_cell[1]+1))*ray_step_unit.y
        
        if (self.dir.x<0):
            step_x=-1
            ray_step_unit.x=step_x/self.dir.x
            Ray_length.x=(ray_start[0]-float(map_cell[0]))*ray_step_unit.x
        else :
            step_x=1
            ray_step_unit.x=step_x/self.dir.x
            Ray_length.x=(-ray_start[0]+float(map_cell[0]+1))*ray_step_unit.x
            
        tilefound=False
        distance=0  
        max_distance=10
        while (not tilefound and distance<max_distance):
            if Ray_length.y<Ray_length.x:
                map_cell[1]+=step_y
                distance=Ray_length.y
                Ray_length.y+=ray_step_unit.y
            else:
                map_cell[0]+=step_x
                distance=Ray_length.x
                Ray_length.x+=ray_step_unit.x
            if map[(map_cell[1]//cell_size)][map_cell[0]//cell_size]==1:
                break
        return distance