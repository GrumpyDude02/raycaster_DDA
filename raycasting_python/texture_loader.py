import os,pygame
from settings import TEXTURE_SIZE

num=0
for file in os.listdir("textures"):
    num+=1
    
texture_list={}
def load_texture(index):
    texture=pygame.image.load(f'textures/{str(index)}.png').convert()
    texture=pygame.transform.scale(texture,(TEXTURE_SIZE,TEXTURE_SIZE))
    return texture

for i in range(1,num+1):
    texture_list[str(i)]=load_texture(i)

