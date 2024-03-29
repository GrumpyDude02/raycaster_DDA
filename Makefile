all: compile link

compile:
	g++ -c -Og -std=c++17 raycasting_c++/main/main.cpp 	-o raycasting_c++/main/main.o 		-IC:/Users/youss/Documents/SFML-2.5.1/include 		-IC:/Users/youss/Bureau/info/raycaster2.0/raycasting_c++
	g++ -c -Og  -std=c++17 raycasting_c++/src/tools.cpp 	-o raycasting_c++/src/tools.o 		-IC:/Users/youss/Documents/SFML-2.5.1/include 		-IC:/Users/youss/Bureau/info/raycaster2.0/raycasting_c++
	g++ -c -Og -std=c++17 raycasting_c++/src/raycaster.cpp -o raycasting_c++/src/raycaster.o 	-IC:/Users/youss/Documents/SFML-2.5.1/include 		-IC:/Users/youss/Bureau/info/raycaster2.0/raycasting_c++

link:
	g++ raycasting_c++/main/main.o	raycasting_c++/src/tools.o 	raycasting_c++/src/raycaster.o 	-o raycasting_c++/executable/raycaster	-LC:/Users/youss/Documents/SFML-2.5.1/lib -lsfml-graphics -lsfml-window -lsfml-system
