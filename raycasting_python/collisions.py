import pygame,math


def circle_circle_collision(circle1,circle2):
    dx=circle1.pos.x-circle2.pos.x
    dy=circle1.pos.y-circle2.pos.y

    if abs(dx*dx+dy*dy)<=(circle1.radius+circle2.radius)*(circle1.radius+circle2.radius) :
        return [True,dx*dx+dy*dy]
    else:
        return [False,dx*dx+dy*dy]

def circle_rect_collisions(circle,rect,circle_radius,rect_width,rect_height,apply_movement):
    """for tile based games"""
    nearestX=max(rect.x,min(circle.x,rect.x+rect_width))
    nearestY=max(rect.y,min(circle.y,rect.y+rect_height))
    
    nearestV=pygame.math.Vector2(circle.x-nearestX,circle.y-nearestY)
    dist=math.sqrt(nearestV.x*nearestV.x+nearestV.y*nearestV.y)
    
    if(apply_movement):
        if (dist>0):
            if(dist<=circle_radius):
                overlap=circle_radius-dist
                dir=pygame.Vector2(nearestV.x/dist,nearestV.y/dist)
                circle.x+=dir.x*overlap
                circle.y+=dir.y*overlap
    

def SAT_collision():
    pass