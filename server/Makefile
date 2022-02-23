HEADERS=inc
OBJ=obj
FILES=src
NAME=uchat_server
PROFALAGS=-g -Wall
FLAGS=$(PROFALAGS) -I $(HEADERS)
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

reinstall: uninstall all

clean:
	rm -rf $(OBJ)

uninstall: clean
	rm -f $(NAME)
