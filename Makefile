# $(BIN) est le nom du binaire généré
BIN = bin/corridor.out
# FLAG
FLAGS = -Wall -O3
# INCLUDES
INC = -I./ -Iinclude/
# INCLUDES
LIBS = -lglfw -lGLU -lGL -lm -lglut
# -lopengl32 -lsfml-system -lsfml-graphics -lsfml-window -lglu32 -lglew32 -lglfw3
# INCLUDES
LIBDIR = -Llib/ 
# Compilateur
GCC = g++

OBJDIR = obj/
INCDIR = includes/
SRCDIR = src/

# $(OBJECTS) sont les objets qui seront générés après la compilation
OBJECTS =  obj/draw_scene.o obj/3D_tools.o obj/corridor.o obj/corridorDrawing.o obj/level.o obj/lights.o obj/objects.o #obj/textures.o





default: $(BIN)
	
	bin/./corridor.out
	rm -f obj/*.o $(BIN)

all: 
	$(OBJECT) 
	#bin/./corridor.out
	

$(BIN): $(OBJECTS)
	@echo "**** PHASE DE LIEN ****"
	$(GCC) $(OBJECTS) $(FLAGS) -o $(BIN) $(LIBDIR) $(LIBS)

$(OBJDIR)%.o: $(SRCDIR)%.c $(INCDIR)*.h
	@echo "**** $@ ****"
	$(GCC) $(INC) $(FLAGS) -c $< -o $@

clean:
	rm -f obj/*.o $(BIN)
	find . -name "*~" -exec rm {} \;
