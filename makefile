DEBUG ?= 0

ifeq ($(DEBUG), 1)
    LDFLAGS += -Lsrc/lib -lsfml-graphics-d -lsfml-window-d -lsfml-system-d -lsfml-audio-d
    EXETYPE = debug
else
    LDFLAGS += -Lsrc/lib -lsfml-graphics -lsfml-window -lsfml-system -lsfml-audio
    EXETYPE = release
endif

all: compile create link clean

compile:
	@g++ -Isrc/include -c code/*.cpp

create:
	@clib code/sourcecode/plain lib/plain libplain.a
	@clib code/sourcecode/game lib/game libgame.a

link:
	@g++ *.o -o build/$(EXETYPE)/PhysicsEngine -Llib/plain -lplain -Llib/game -lgame  $(LDFLAGS)

clean:
	@del *.o
