OBJ=obj
FILES=src
NAME=uchat
PROFALAGS=-g -Wall 
LIB_PATH=-L../libs/lib -lsqlite3 -lpthread -lcjson
FLAGS=$(PROFALAGS) -Iinc -I../libs/inc
CC=gcc
OBJS=$(patsubst $(FILES)/%.c, $(OBJ)/%.o, $(ALL_CFILES))
ALL_CFILES=$(wildcard $(FILES)/*.c)
ALL_HFILES=$(wildcard $(HEADERS)/*.h)

all: $(NAME)

$(OBJ):
	@mkdir -p $@

$(OBJ)/%.o: $(FILES)/%.c $(OBJ) 
	@$(CC) $(FLAGS) -c $< -o $@ $(LIB_PATH)

$(NAME): $(OBJ) $(OBJS)
	@$(CC) $(FLAGS) $(OBJS) -o $@ $(LIB_PATH)
	@mv $@ ../

reinstall: uninstall all

clean:
	@rm -rf $(OBJ)

uninstall: clean
	@rm -f $(NAME)

