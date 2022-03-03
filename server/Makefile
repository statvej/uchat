OBJ=obj
FILES=src
NAME=uchat_server
PROFALAGS=-g -Wall
LIB_PATH=-L../libs/lib -lcjson
FLAGS=$(PROFALAGS) -Iinc -I../libs/inc $(LIB_PATH)
CC=gcc
OBJS=$(patsubst $(FILES)/%.c, $(OBJ)/%.o, $(ALL_CFILES))
ALL_CFILES=$(wildcard $(FILES)/*.c)
ALL_HFILES=$(wildcard $(HEADERS)/*.h)

all: $(NAME)

$(OBJ):
	@mkdir -p $@

$(OBJ)/%.o: $(FILES)/%.c $(OBJ) 
	$(CC) $(FLAGS) -c $< -o $@

$(NAME): $(OBJ) $(OBJS)
	$(CC) $(FLAGS) $(OBJS) -o $@
	mv $@ ../

reinstall: uninstall all

clean:
	rm -rf $(OBJ)

uninstall: clean
	rm -f $(NAME)
	
