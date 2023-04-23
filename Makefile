# $(BIN) est le nom du binaire généré
BIN = bin/corridor
# FLAG
FLAGS = -Wall -O3
# INCLUDES
INC = -I./ -Iinclude/
# INCLUDES
LIBS = -lopengl32 -lsfml-system -lsfml-graphics -lsfml-window -lglu32 -lglew32 -lglfw3
# INCLUDES
LIBDIR = -Llib/ 
# Compilateur
GCC = g++
# $(OBJECTS) sont les objets qui seront générés après la compilation
OBJECTS =  obj/corridor.o obj/corridorDrawing.o obj/create_obj_pt

default: $(BIN)
		bin/./corridor.exe

all: 
	$(OBJECT) 
	bin/./corridor.exe
	

$(BIN): $(OBJECTS)
	@echo "**** PHASE DE LIEN ****"
	$(GCC) $(OBJECTS) $(FLAGS) -o $(BIN) $(LIBDIR) $(LIBS) 

obj/corridor.o: src/corridor.c includes/corridor.h
	@echo "**** $@ ****"
	$(GCC) $(INC) $(FLAGS) -c $< -o $@

obj/corridorDrawing.o : src/corridorDrawing.c includes/corridorDrawing.h
	@echo "**** $@ ****"
	$(GCC) $(INC) $(FLAGS) -c $< -o $@

obj/create_obj_pt.o : src/create_obj_pt.c includes/create_obj_pt.h
	@echo "**** $@ ****"
	$(GCC) $(INC) $(FLAGS) -c $< -o $@

clean:
	rm -f *.o $(BIN)
	find . -name "*~" -exec rm {} \;
