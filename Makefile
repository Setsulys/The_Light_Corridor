# $(BIN) est le nom du binaire généré
BIN = bin/corridor.out
# FLAG
FLAGS = -Wall -O3
# INCLUDES
INC = -I./ -Iinclude/
# INCLUDES
LIBS = -lglfw -lGLU -lGL -lm
# -lopengl32 -lsfml-system -lsfml-graphics -lsfml-window -lglu32 -lglew32 -lglfw3
# INCLUDES
LIBDIR = -Llib/ 
# Compilateur
GCC = g++
# $(OBJECTS) sont les objets qui seront générés après la compilation
OBJECTS =  obj/draw_scene.o obj/3D_tools.o obj/corridor.o obj/corridorDrawing.o obj/level.o

default: $(BIN)
	bin/./corridor.out

all: 
	$(OBJECT) 
	bin/./corridor.out
	

$(BIN): $(OBJECTS)
	@echo "**** PHASE DE LIEN ****"
	$(GCC) $(OBJECTS) $(FLAGS) -o $(BIN) $(LIBDIR) $(LIBS) 

obj/corridor.o: src/corridor.c includes/corridor.h
	@echo "**** $@ ****"
	$(GCC) $(INC) $(FLAGS) -c $< -o $@

obj/corridorDrawing.o : src/corridorDrawing.c includes/corridorDrawing.h
	@echo "**** $@ ****"
	$(GCC) $(INC) $(FLAGS) -c $< -o $@
	
obj/3D_tools.o : src/3D_tools.c includes/3D_tools.h
	@echo "**** $@ ****"
	$(GCC) $(INC) $(FLAGS) -c $< -o $@

obj/draw_scene.o : src/draw_scene.c includes/draw_scene.h
	@echo "**** $@ ****"
	$(GCC) $(INC) $(FLAGS) -c $< -o $@

obj/level.o : src/level.c includes/level.h
	@echo "**** $@ ****"
	$(GCC) $(INC) $(FLAGS) -c $< -o $@

clean:
	rm -f *.o $(BIN)
	find . -name "*~" -exec rm {} \;
