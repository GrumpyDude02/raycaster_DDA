import math,pygame

GREY=(90,90,90)
DARKER_GREY=(150,150,150)
WHITE=(255,255,255)
PI=math.pi
TEXTURE_SIZE=256

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
BORDERS =(100,width-100,100,height-100)
offset=[0]
center=(half_width,half_height)


#DISPLAY_SURFACE
main_surface=pygame.display.set_mode((width,height))
sky=pygame.Rect(0,0,1200,300)
floor=pygame.Rect(0,300,1200,300)