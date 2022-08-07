all: compile link

compile:
	g++ -c raycasting_c++/main/main.cpp 	-o raycasting_c++/main/main.o 		-IC:/Users/youss/Documents/SFML-2.5.1/include 		-IC:/Users/youss/Bureau/info/raycaster2.0/raycasting_c++
	g++ -c raycasting_c++/src/utilities.cpp -o raycasting_c++/src/utilities.o 	-IC:/Users/youss/Documents/SFML-2.5.1/include 		-IC:/Users/youss/Bureau/info/raycaster2.0/raycasting_c++
	g++ -c raycasting_c++/src/Ray.cpp 		-o raycasting_c++/src/Ray.o 		-IC:/Users/youss/Documents/SFML-2.5.1/include 		-IC:/Users/youss/Bureau/info/raycaster2.0/raycasting_c++
	g++ -c raycasting_c++/src/raycaster.cpp -o raycasting_c++/src/raycaster.o 	-IC:/Users/youss/Documents/SFML-2.5.1/include 		-IC:/Users/youss/Bureau/info/raycaster2.0/raycasting_c++

link:
	g++ raycasting_c++/main/main.o 		raycasting_c++/src/utilities.o 		raycasting_c++/src/raycaster.o 	-o raycasting_c++/executable/raycaster 		-LC:/Users/youss/Documents/SFML-2.5.1/lib -lsfml-graphics -lsfml-window -lsfml-system