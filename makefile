NAME_SERVER =uchat_server
NAME_CLIENT =uchat
LIB=libs
SERVER=server
CLIENT=client
CJSON=cjson
LIB_DIR = libriari/inc libriari/lib
CLIENTS=$(CLIENT)/$(NAME_CLIENT)
SERVERS=$(SERVER)/$(NAME_SERVER)
CJSONDIR=$(LIB)/$(CJSON)
PROFALAGS = -std=c11 -g -Wall -Wextra -Werror -Wpedantic
CC = gcc

all: $(CJSON) $(NAME_CLIENT) $(NAME_SERVER)

$(NAME_CLIENT): $(CLIENTS)
$(NAME_SERVER): $(SERVERS)

$(CLIENTS): $(CLIENT)
$(SERVERS): $(SERVER)
$(CJSON): $(CJSONDIR)

$(LIB_DIR):
	mkdir -p $(LIB_DIR)

$(CJSON): $(LIB_DIR)
	make -C $<

$(CLIENTS) $(SERVERS):
	make -C $<

uninstall: 
	rm -r $(NAME_CLIENT)
	rm -r $(NAME_SERVER)
	make -C $(SERVER)
	make -C $(CLIENT)

clean:
	make -C $(SERVER)
	make -C $(CLIENT)

reinstall: uninstall all
