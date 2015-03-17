EXE 		= Carrefour

#Directives du préprocesseur pour les #ifdef
VERBOSE     = VERBOSE
#VERBOSE    = NO_VERBOSE
#MAP         = MAP
MAP        = NO_MAP
DEFINE      = -D$(VERBOSE) -D$(MAP)

# Compilateur et editeur de lien
COMP		= @g++
LINK		= @g++

#Dossiers
SRC_DIR		= src
OBJ_DIR		= obj
LIB_DIR		= lib
EXE_DIR		= TP-Multitache


#Librairies
LIBS 		= -ltp -ltcl -lncurses
INCLUDE		= -I./lib


# Options de compilation et editions de liens
CPPFLAGS	= $(DEFINE) -Wall -ansi -ggdb -std=c++11
EDLFLAGS	= -L./lib $(LIBS)

#Fichiers
INTERFACES_FILES		= 						
INT 		            = $(addprefix $(SRC_DIR)/, $(INTERFACES_FILES))					# construit le chemin des sources
OBJ			            = $(addprefix $(OBJ_DIR)/, $(INTERFACES_FILES:.h=.o))			# Génération du nom des fichiers obj
MAIN_OBJ             	= $(OBJ_DIR)/main.o 											# .o du fichier ou se trouve le main

#Autres commandes et message
ECHO		= @echo
RM			= @rm
MESSAGE		= "Compilation réussie"


$(EXE_DIR)/$(EXE): $(OBJ) $(MAIN_OBJ)
	$(LINK) -o $(EXE_DIR)/$(EXE) $^ $(EDLFLAGS) 
	$(ECHO) $(MESSAGE)
	

#Mettre les dependances particulieres ici

#Generation des fichiers obj
$(OBJ_DIR)/%.o:$(SRC_DIR)/%.cpp
	$(ECHO) "Compilation de $< (generation de $@)"
	$(COMP) -o $@ -c $< $(CPPFLAGS) $(INCLUDE) 

.PHONY: clean

clean:
	$(ECHO) "Nettoyage..."
	$(RM) -fvr $(OBJ_DIR)/*.o $(EXE_DIR)/$(EXE)
	
