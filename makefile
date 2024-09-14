all: compile create link clean

compile: 
	g++ -Isrc/include -c code/*.cpp

create: 
	createlibrary.bat

link:
	g++ *.o -o build/PhysicsEngine -Lsrc/lib -lsfml-graphics-d -lsfml-window-d -lsfml-system-d -Lplain -lplain

clean:
	del main.o