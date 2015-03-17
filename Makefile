EXE 		= Carrefour

# Compilateur et editeur de lien
COMP		= @g++
LINK		= @g++

#Dossiers
SRC_DIR		= 
OBJ_DIR		= 
LIB_DIR		= 
EXE_DIR		= TP-Multitache
BACKUP_DIR	= /share/public/tp/tp-multitache/Compte-Rendu/2015/4/B3425/


#Librairies
LIBS 		= -ltp -ltcl -lncurses
INCLUDE		= -I/share/public/tp/tp-multitache/


# Options de compilation et editions de liens
CPPFLAGS	= $(DEFINE) -Wall -ansi -ggdb -std=c++11
EDLFLAGS	= -L/share/public/tp/tp-multitache/ $(LIBS)

#Fichiers
INTERFACES_FILES		= 						
INT 		            = $(addprefix $(SRC_DIR)/, $(INTERFACES_FILES))					# construit le chemin des sources
OBJ			            = $(addprefix $(OBJ_DIR)/, $(INTERFACES_FILES:.h=.o))			# Génération du nom des fichiers obj
MAIN_OBJ             	= Mere.o 											# .o du fichier ou se trouve le main

#Autres commandes et message
ECHO		= @echo
RM			= @rm
MESSAGE		= "Compilation réussie"
CP			= @cp 


$(EXE_DIR)/$(EXE): $(OBJ) $(MAIN_OBJ)
	$(LINK) -o $(EXE_DIR)/$(EXE) $^ $(EDLFLAGS) 
	$(ECHO) $(MESSAGE)
	

#Mettre les dependances particulieres ici

#Generation des fichiers obj
%.o:%.cpp
	$(ECHO) "Compilation de $< (generation de $@)"
	$(COMP) -o $@ -c $< $(CPPFLAGS) $(INCLUDE) 

.PHONY: clean

clean:
	$(ECHO) "Nettoyage..."
	$(RM) -fvr *.o $(EXE_DIR)/$(EXE)
	
backup: clean
	$(ECHO) "Sauvegarde dela version actuelle..."
	$(CP) *.cpp *.h Makefile $(BACKUP_DIR)
	$(CP) -R TP-Multitache $(BACKUP_DIR)
	$(ECHO) "Sauvegarde terminee!"
	
