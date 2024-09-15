all: compile create link clean

compile: 
	g++ -Isrc/include -c code/*.cpp

create: 
	createlibrary_plain.bat
	createlibrary_game.bat

link:
	g++ *.o -o build/PhysicsEngine -Llib\plain -lplain -Llib\game -lgame -Lsrc/lib -lsfml-graphics-d -lsfml-window-d -lsfml-system-d 

clean:
	del main.o