all: compile link

compile:
	g++ raycasting_in_c++/main/main.cpp raycasting_in_c++/src/utilities.cpp -c -IC:/Users/youss/Documents/SFML-2.5.1/include -IC:/Users/youss/Bureau/info/raycaster2.0/raycasting_in_c++

link:
	g++ raycasting_in_c++/main/main.o raycasting_in_c++/src/utilities.o -o raycasting_in_c++/main -LC:/Users/youss/Documents/SFML-2.5.1/lib -lsfml-graphics -lsfml-window -lsfml-system