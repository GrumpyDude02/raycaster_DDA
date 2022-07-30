import numba
import pygame,sys,math
from pygame.math import Vector2 as vc

pygame.init()
GREY=(84,84,84)
WHITE=(255,255,255)
cell_size=30
cell_number=20
width=cell_size*cell_number
height=cell_size*cell_number
clock=pygame.time.Clock()


main_surface=pygame.display.set_mode((width,height))

class ray:
    def __init__(self,direction,start_pos) :
        self.pos=start_pos
        self.dir=direction
        
    def cast_ray(self,map):
        ray_start=[self.pos.x,self.pos.y]
        ray_step_unit=vc(math.sqrt(1+(self.dir.y/self.dir.x)*(self.dir.y/self.dir.x)),math.sqrt(1+(self.dir.x/self.dir.y)*(self.dir.x/self.dir.y)))
        map_cell=[int(ray_start[0]),int(ray_start[1])]
        Ray_length=vc(0,0)
        
        if (self.dir.y<0):
            step_y=-1
            Ray_length.y=(ray_start[1]-float(map_cell[1]))*ray_step_unit.y
        else :
            step_y=1
            Ray_length.y=(-ray_start[1]+float(map_cell[1]+1))*ray_step_unit.y
        
        if (self.dir.x<0):
            step_x=-1
            Ray_length.x=(ray_start[0]-float(map_cell[0]))*ray_step_unit.x
        else :
            step_x=1
            Ray_length.x=(-ray_start[0]+float(map_cell[0]+1))*ray_step_unit.x
            
        tilefound=False
        distance=0  
        max_distance=20
        while (not tilefound and distance<max_distance):
            if Ray_length.y<Ray_length.x:
                map_cell[1]+=step_y
                distance=Ray_length.y/cell_size
                Ray_length.y+=ray_step_unit.y
            else:
                map_cell[0]+=step_x
                distance=Ray_length.x/cell_size
                Ray_length.x+=ray_step_unit.x
            if map[(map_cell[1]//cell_size)][map_cell[0]//cell_size]==1:
                break
        return distance

class Player():
    def __init__(self,pos):
        self.pos=vc(pos[0]*cell_size,pos[0]*cell_size)
        self.angle=math.pi/6
        self.fov=self.angle/2
        self.dir=vc((math.sin(self.angle)),(math.cos(self.angle)))
        self.step=math.pi/240
        
    def draw_player(self,map):
        self.main_ray=ray(self.dir,self.pos)
        dst=self.main_ray.cast_ray(map)
        pygame.draw.circle(main_surface,(255,0,0),self.pos,10)
        casted_rays=120
        start_angle=self.angle-self.fov
        for rays in range(casted_rays):
            ray_direction=vc((math.sin(start_angle)*cell_size),(math.cos(start_angle))*cell_size)
            g_ray=ray(ray_direction,self.pos)
            dst0=g_ray.cast_ray(map)
            pygame.draw.line(main_surface,(0,255,0),self.pos,self.pos+g_ray.dir*dst0)
            start_angle+=self.step     
            
    def move_player(self,dt):
        keys=pygame.key.get_pressed()
        if keys[pygame.K_UP]:
            self.pos.y+=math.cos(self.angle)*50*dt
            self.pos.x+=math.sin(self.angle)*50*dt
        if keys[pygame.K_DOWN]:
            self.pos.y-=math.cos(self.angle)*50*dt
            self.pos.x-=math.sin(self.angle)*50*dt
        if keys[pygame.K_RIGHT]:
            self.angle-=5*dt
        if keys[pygame.K_LEFT]:
            self.angle+=5*dt
        self.dir=vc((math.sin(self.angle))*cell_size,(math.cos(self.angle))*cell_size)    
        
        
        
                
            
        

map=[[1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1],
      [1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1],
      [1,0,0,0,0,0,0,0,0,0,1,1,0,0,0,0,0,0,0,1],
      [1,0,0,0,0,0,0,0,0,0,0,1,1,0,0,0,0,0,0,1],
      [1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1],
      [1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1],
      [1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1],
      [1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1],
      [1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1],
      [1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1],
      [1,0,0,0,0,0,0,0,1,1,0,0,0,0,0,0,0,0,0,1],
      [1,0,0,0,0,0,0,0,1,1,1,0,0,0,0,0,0,0,0,1],
      [1,0,0,0,0,0,0,0,1,1,0,0,0,0,0,0,0,0,0,1],
      [1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1],
      [1,0,0,0,0,0,1,0,0,0,0,0,0,1,0,0,0,0,0,1],
      [1,0,0,0,0,0,0,0,0,0,0,0,1,1,0,0,0,0,0,1],
      [1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1],
      [1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1],
      [1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1],
      [1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1],
      ]

def everything(map):
    for i in range(len(map)):
        for j in range(len(map[0])):
            if map[i][j]==1:
                square=pygame.Rect((j)*cell_size,(i)*cell_size,(cell_size)-1,cell_size-1)
                pygame.draw.rect(main_surface,(WHITE),square)
            
player1=Player((4,4)) 
            
def display_fps(clock,window):     
    font=pygame.font.Font(None,20)
    fps=font.render(str(int(clock.get_fps())),True,(255,255,255))
    window.blit(fps,(550,40))
    

import time    
previous_time=time.time()

    
while True:
    event=pygame.event.poll()
    if event.type==pygame.QUIT:
        sys.exit()
    dt=time.time()-previous_time
    previous_time=time.time()
    main_surface.fill(GREY)
    everything(map)
    player1.move_player(dt)
    player1.draw_player(map)
    clock.tick()
    fps=clock.get_fps()
    display_fps(clock,main_surface)
    pygame.display.flip()
