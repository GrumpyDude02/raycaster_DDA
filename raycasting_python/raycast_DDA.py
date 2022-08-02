import pygame,sys,math
from collisions import circle_rect_collisions
from pygame.math import Vector2 as vc

pygame.init()
GREY=(84,84,84)
WHITE=(255,255,255)

#RESOLUTION_VARIABLES
cell_size=30
cell_number=20
h_cell_number=40
width=cell_size*h_cell_number
half_width=width//2
height=cell_size*cell_number
half_height=height//2
casted_rays=width//2
ray_coordonates=[]
clock=pygame.time.Clock()

#DISPLAY_SURFACE
main_surface=pygame.display.set_mode((width,height))


class raycaster():
    def __init__(self,pos,casted_rays):
        self.pos=vc(pos[0]*cell_size,pos[0]*cell_size)
        self.casted_rays=casted_rays
        self.angle=math.pi
        self.fov=math.pi/2
        self.step=self.fov/casted_rays
        self.scale=width//casted_rays
        self.sc_distance=half_width/math.tan(self.fov/2)
        
    def update(self,map,surface):
        #pygame.draw.circle(main_surface,(255,0,0),self.pos,10)
        start_angle=self.angle-self.fov/2
        for rays in range(self.casted_rays):
            ray_start={'x':self.pos.x/cell_size,'y':self.pos.y/cell_size}
            ray_step_unit=vc()
            map_cell={'x':int(ray_start['x']),'y':int(ray_start['y']) }
            Ray_length=vc(0,0)
            cos_a,sin_a=math.cos(start_angle),math.sin(start_angle)
            
            if cos_a<0:
                dx=-1
                ray_step_unit.x=dx/cos_a
                Ray_length.x=(ray_start['x']-map_cell['x'])*ray_step_unit.x
            else:
                dx=1
                ray_step_unit.x=dx/cos_a
                Ray_length.x=(-ray_start['x']+map_cell['x']+1)*ray_step_unit.x
            if sin_a<0:
                dy=-1
                ray_step_unit.y=dy/sin_a
                Ray_length.y=(ray_start['y']-map_cell['y'])*ray_step_unit.y
            else:
                dy=1
                ray_step_unit.y=dy/sin_a
                Ray_length.y=(-ray_start['y']+map_cell['y']+1)*ray_step_unit.y 
            while True:
                if Ray_length.x<Ray_length.y:
                    map_cell['x']+=dx
                    dist=Ray_length.x
                    Ray_length.x+=ray_step_unit.x
                else:
                    map_cell['y']+=dy
                    dist=Ray_length.y
                    Ray_length.y+=ray_step_unit.y
                if dist>=15:
                    dist=15
                    break
                elif map_cell['x']>=0 and map_cell['x']<len(map) and map_cell['y']>=0 and map_cell['y']<len(map):
                    if map[map_cell['y']][map_cell['x']]==1:
                        break
                else:
                    break
            ray_coordonates.append({'x':cos_a*dist*10,'y':sin_a*dist*10})
            dist*=math.cos(start_angle-self.angle)
            projected_height=self.sc_distance/(dist+0.0001)
            c=1+dist*dist*0.02
            color=(255/c,255/c,255/c)
            pygame.draw.rect(surface,color,(rays*self.scale,half_height-projected_height//2,self.scale,projected_height))
            start_angle+=self.step
                
            
            
    def move(self,dt):
        keys=pygame.key.get_pressed()
        if keys[pygame.K_UP]:
            self.pos.y+=math.sin(self.angle)*50*dt
            self.pos.x+=math.cos(self.angle)*50*dt
        if keys[pygame.K_DOWN]:
            self.pos.y-=math.sin(self.angle)*50*dt
            self.pos.x-=math.cos(self.angle)*50*dt
        if keys[pygame.K_RIGHT]:
            self.angle+=5*dt
        if keys[pygame.K_LEFT]:
            self.angle-=5*dt   
               

map=[[1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1],
      [1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1],
      [1,0,0,0,0,0,0,0,0,0,1,1,0,0,0,0,0,0,0,1],
      [1,0,0,0,0,0,0,0,0,0,0,1,1,0,0,0,0,0,0,1],
      [1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1],
      [1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1],
      [1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1],
      [1,0,0,0,0,1,0,0,0,0,0,1,1,1,1,0,0,0,0,1],
      [1,0,0,0,0,1,1,0,0,0,0,0,0,0,1,0,0,0,0,1],
      [1,0,0,1,0,0,0,0,0,0,0,0,0,0,1,0,0,0,0,1],
      [1,0,0,1,0,1,0,0,1,1,0,0,0,0,0,0,0,0,0,1],
      [1,0,0,1,0,1,0,0,1,1,1,0,0,0,0,0,0,0,0,1],
      [1,0,0,0,0,1,0,0,1,1,0,0,0,0,0,0,0,0,0,1],
      [1,0,0,0,0,1,0,0,0,0,0,0,0,0,0,0,0,0,0,1],
      [1,0,0,0,0,1,1,0,0,0,0,0,0,1,0,0,0,0,0,1],
      [1,0,0,0,1,0,0,0,0,0,1,1,1,1,0,0,0,0,0,1],
      [1,0,0,0,0,0,0,0,0,0,1,0,0,0,0,0,0,0,0,1],
      [1,0,0,0,0,0,0,0,0,0,1,0,0,0,0,0,0,0,0,1],
      [1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1],
      [1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1],
      ]

def draw_minimap(map,player,casted_rays):
    global ray_coordonates
    pygame.draw.rect(main_surface,(0,0,0),(0,0,len(map)*10,len(map)*10))
    map_pos={'x':(player.pos.x/cell_size)*10,'y':(player.pos.y/cell_size)*10}
    pygame.draw.circle(main_surface,(255,0,0),(map_pos['x'],map_pos['y']),2)
    for ray in range(len(ray_coordonates)):
        pygame.draw.line(main_surface,(0,255,0),(map_pos['x'],map_pos['y']),(map_pos['x']+ray_coordonates[ray]['x'],map_pos['y']+ray_coordonates[ray]['y']))
    ray_coordonates=[]
    
    #checking surrounding walls for collisions to save on performance

    starting_cell_x=max(0,(player.pos.x//cell_size)-2)
    ending_cell_x=min(len(map)-1,(player.pos.x//cell_size)+2)
    starting_cell_y=max(0,(player.pos.y//cell_size)-2)
    ending_cell_y=min(len(map)-1,(player.pos.y//cell_size)+2)
    
    for i in range(len(map)):
        for j in range(len(map[0])):
            if map[i][j]==1:
                square=pygame.Rect((j)*cell_size,(i)*cell_size,(cell_size)-1,cell_size-1)
                if square.x>=starting_cell_x*cell_size and square.x<=ending_cell_x*cell_size and square.y>=starting_cell_y*cell_size and square.y<=ending_cell_y*cell_size:
                    circle_rect_collisions(player.pos,square,10,cell_size,cell_size,True)
                mini_square=pygame.Rect((j)*10,(i)*10,9,9)
                pygame.draw.rect(main_surface,(WHITE),mini_square)
    
player1=raycaster((4,4),casted_rays) 
            
def display_fps(clock,window):     
    font=pygame.font.Font(None,20)
    fps=font.render(str(int(clock.get_fps())),True,(255,255,255))
    window.blit(fps,(1150,40))
    

import time    
previous_time=time.time()
sky=pygame.Rect(0,0,1200,300)
floor=pygame.Rect(0,300,1200,300)

    
while True:
    event=pygame.event.poll()
    if event.type==pygame.QUIT:
        sys.exit()
    dt=time.time()-previous_time
    previous_time=time.time()
    main_surface.fill((0,0,0))
    pygame.draw.rect(main_surface,(0,150,255),sky)
    pygame.draw.rect(main_surface,(100,100,100),floor)
    player1.move(dt)
    player1.update(map,main_surface)
    draw_minimap(map,player1,casted_rays)
    clock.tick(60)
    fps=clock.get_fps()
    display_fps(clock,main_surface)
    pygame.display.flip()
