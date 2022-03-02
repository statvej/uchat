NAME_SERVER =uchat_server
NAME_CLIENT =uchat
LIB=libs
SERVER=server
CLIENT=client
CJSON=cJSON
LIB_DIR = libs/inc libs/lib
CLIENTS=$(CLIENT)/$(NAME_CLIENT)
SERVERS=$(SERVER)/$(NAME_SERVER)
CJSONDIR=$(LIB)/$(CJSON)
PROFALAGS = -std=c11 -g -Wall -Wextra -Werror -Wpedantic
CC = gcc

all: $(CJSONDIR) $(NAME_CLIENT) $(NAME_SERVER)

$(NAME_CLIENT): $(CLIENTS)
$(NAME_SERVER): $(SERVERS)


$(CLIENTS): $(CLIENT)
$(SERVERS): $(SERVER)

$(LIB_DIR):
	mkdir -p $(LIB_DIR)

$(CJSONDIR): $(LIB_DIR)
	make -C $@

$(CLIENTS) $(SERVERS):
	make -C $<

uninstall: 
	make -C $(SERVER) $@
	make -C $(CLIENT) $@
	make -C $(CJSONDIR) $@

clean:
	make -C $(SERVER) $@
	make -C $(CLIENT) $@
	make -C $(CJSONDIR) $@

reinstall: uninstall all
