DEBUG ?= 0
CURRENTLD ?= 0

STEPS = compile create link clean

ifeq ($(CURRENTLD), 1)
	STEPS = compile link clean
else
	STEPS = compile create link clean
endif

ifeq ($(DEBUG), 1)
    LDFLAGS += -Lsrc/lib -lsfml-graphics-d -lsfml-window-d -lsfml-system-d -lsfml-audio-d
    EXETYPE = debug
else
    LDFLAGS += -Lsrc/lib -lsfml-graphics -lsfml-window -lsfml-system -lsfml-audio
    EXETYPE = release
endif

all: $(STEPS)

compile:
	@g++ -Icode/sourcecode/plainengine -Icode/sourcecode/plainphysics -Isrc/include  -c code/*.cpp

create:
	@clib code/sourcecode/plainphysics lib/plainphysics libplain-physics.a

link:
	@g++ *.o -o build/$(EXETYPE)/PhysicsEngine -Llib/plainengine -lplain-engine -Llib/plainphysics -lplain-physics $(LDFLAGS)

clean:
	@del *.o
