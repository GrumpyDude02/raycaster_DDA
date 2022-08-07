from pygame.math import Vector2 as vc
from math import cos,sin,tan,atan,sqrt
from settings import *
from stuff import mouse_control

#ray class to cast a single ray

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
      
class raycaster():
    def __init__(self,pos,casted_rays):
        self.pos=vc(pos[0]*cell_size,pos[0]*cell_size)
        self.casted_rays=casted_rays
        self.angle=PI
        self.fov=PI/2
        self.step=self.fov/casted_rays
        self.scale=width//casted_rays
        self.sc_distance=half_width/tan(self.fov/2)
        
    def cast_rays(self,map,scale):
        ray_coordonates=[]
        objects=[]
        start_angle=self.angle-self.fov/2
        for rays in range(1,self.casted_rays+1):
            ray_start={'x':self.pos.x/cell_size,'y':self.pos.y/cell_size}
            ray_step_unit=vc()
            map_cell={'x':int(ray_start['x']),'y':int(ray_start['y']) }
            Ray_length=vc(0,0)
            cos_a,sin_a=cos(start_angle),sin(start_angle)
            
            if cos_a<0:
                dx=-1
                ray_step_unit.x=dx/(cos_a)
                Ray_length.x=(ray_start['x']-map_cell['x'])*ray_step_unit.x
            else:
                dx=1
                ray_step_unit.x=dx/(cos_a)
                Ray_length.x=(-ray_start['x']+map_cell['x']+1)*ray_step_unit.x
            if sin_a<0:
                dy=-1
                ray_step_unit.y=dy/(sin_a)
                Ray_length.y=(ray_start['y']-map_cell['y'])*ray_step_unit.y
            else:
                dy=1
                ray_step_unit.y=dy/(sin_a)
                Ray_length.y=(-ray_start['y']+map_cell['y']+1)*ray_step_unit.y 
            while True:
                if Ray_length.x<Ray_length.y:
                    map_cell['x']+=dx
                    dist=Ray_length.x
                    hor=True
                    Ray_length.x+=ray_step_unit.x
                else:
                    map_cell['y']+=dy
                    hor=False
                    dist=Ray_length.y
                    Ray_length.y+=ray_step_unit.y
                if map_cell['x']>=0 and map_cell['x']<len(map) and map_cell['y']>=0 and map_cell['y']<len(map):
                    if map[map_cell['y']][map_cell['x']]!=0:
                        displacement=(ray_start['y']+sin_a*dist)%1 if hor==True else (ray_start['x']+cos_a*dist)%1
                        break
                else:
                    break
            ray_coordonates.append({'x':cos_a*dist*scale,'y':sin_a*dist*scale})
            dist*=cos(start_angle-self.angle)
            projected_height=self.sc_distance/(dist+0.0001)
            objects.append((projected_height,displacement,map[map_cell['y']][map_cell['x']]))
            start_angle=atan(((self.scale*rays-half_width)/self.sc_distance))+self.angle
        
        return objects,ray_coordonates
            
    def update(self,dt,switch,offset,visibility):
        speed=50
        keys=pygame.key.get_pressed()
        cos_a=cos(self.angle)
        sin_a=sin(self.angle)
        vel_v=vc()
        vel_h=vc()
        if keys[pygame.K_z]:
            vel_v.y=sin_a
            vel_v.x=cos_a
        if keys[pygame.K_s]:
            vel_v.y=-sin_a
            vel_v.x=-cos_a
        if keys[pygame.K_d]:
            vel_h.y=cos_a
            vel_h.x=-sin_a
        if keys[pygame.K_q]:
            vel_h.y=-cos_a
            vel_h.x=sin_a
        if keys[pygame.K_UP]:
            offset[0]+=50*dt
        if keys[pygame.K_DOWN]:
            offset[0]-=50*dt
        
        dir=vc((vel_v.x+vel_h.x),(vel_v.y+vel_h.y))
        norm=sqrt((vel_v.x+vel_h.x)*(vel_v.x+vel_h.x)+(vel_v.y+vel_h.y)*(vel_v.y+vel_h.y))
        if norm!=0:
            dir=vc(((vel_v.x+vel_h.x)/norm),((vel_v.y+vel_h.y)/norm))
        self.pos+=dir*dt*speed
        pygame.mouse.set_visible(visibility)
        if switch:
            visibility=False
            mouse_control(self,BORDERS,center,50,0.35,dt,offset)
        if self.angle>=2*PI:
            self.angle=0.01