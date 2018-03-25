CC	= gcc
CFLAGS	= -Wall 
LDFLAGS	=
EXEC	= Lexique
SRC	= $(wildcard *.c)
OBJ	= $(SRC:.c=.o)

all: $(EXEC)

Lexique: $(OBJ)
	@$(CC) -o $@ $^ $(LDFLAGS)
	@echo "--------------------------------------------------------------"
	@echo "  to execute type: ./Lexique [-l] [-r <Mot>] [-s] [-S] [-d] nomFichier  "
	@echo "	 for help type ./Lexique -h 	"
	@echo "--------------------------------------------------------------"

Lexique.o : ui.h fichier.h arbre.h

%.o: %.c
	@echo "compile $@"
	@$(CC) -o $@ -c $< $(CFLAGS)
	@echo "done..."

.PHONY: clean mrproper

clean :	
	@echo "**************************"
	@echo "CLEAN"
	@echo "**************************"
	$(RM) *~ $(OBJ) $(EXEC) 

tar : clean 
	@echo "**************************"
	@echo "TAR"
	@echo "**************************"
	cd .. && tar cvfz $(BACKUP) $(DIRNAME)