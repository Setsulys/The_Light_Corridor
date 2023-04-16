# $(BIN) est le nom du binaire généré
BIN = bin/corridor
# FLAG
FLAGS = -Wall -O3
# INCLUDES
INC = -I./ -Iinclude/
# INCLUDES
LIBS = -lopengl32 -lsfml-system -lsfml-graphics -lsfml-window -lglu32
# INCLUDES
LIBDIR = -Llib/ 
# Compilateur
GCC = g++
# $(OBJECTS) sont les objets qui seront générés après la compilation
OBJECTS =  obj/corridor.o #gldrawing.o create_obj_pt.o

default: $(BIN)

all: $(OBJECT)

$(BIN): $(OBJECTS)
	@echo "**** PHASE DE LIEN ****"
	$(GCC) $(OBJECTS) $(FLAGS) -o $(BIN) $(LIBDIR) $(LIBS) 

obj/corridor.o: src/corridor.c includes/corridor.h
	@echo "**** $@ ****"
	$(GCC) $(INC) $(FLAGS) -c $< -o $@

#gldrawing.o: gldrawing.c gldrawing.h
#	@echo "**** $@ ****"
#	$(GCC) $(INC) $(FLAGS) -c $< -o $@

#create_obj_pt.o: create_obj_pt.c create_obj_pt.h
#	@echo "**** $@ ****"
#	$(GCC) $(INC) $(FLAGS) -c $< -o $@

clean:
	rm -f *.o $(BIN)
	find . -name "*~" -exec rm {} \;
