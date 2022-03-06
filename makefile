NAME_SERVER =uchat_server
NAME_CLIENT =uchat
LIB=libs
SERVER=server
CLIENT=client
CJSON=cJSON
SQL=SQL
LIB_DIR = libs/inc libs/lib
CLIENTS=$(CLIENT)/$(NAME_CLIENT)
SERVERS=$(SERVER)/$(NAME_SERVER)
CJSONDIR=$(LIB)/$(CJSON)
SQL3DIR=$(LIB)/$(SQL)
PROFALAGS = -std=c11 -g -Wall -Wextra -Werror -Wpedantic
CC = gcc

all: $(CJSON) $(SQL) $(NAME_CLIENT) $(NAME_SERVER)

$(NAME_CLIENT): $(CLIENTS)
$(NAME_SERVER): $(SERVERS)


$(CLIENTS): $(CLIENT)
$(SERVERS): $(SERVER)
$(CJSON) : $(CJSONDIR)
$(SQL) : $(SQL3DIR)


$(LIB_DIR):
	@mkdir -p $(LIB_DIR)

$(CJSON) $(SQL): | $(LIB_DIR)
	@make -C $<

$(CLIENTS) $(SERVERS):
	@make -C $<

uninstall: 
	@rm -rf $(LIB_DIR)
	@rm -rf $(NAME_CLIENT)
	@rm -rf $(NAME_SERVER)
	@make -C $(SERVER) $@
	@make -C $(CLIENT) $@
	@make -C $(CJSONDIR) $@
	@make -C $(SQL3DIR) $@
	@printf "Oh shit,"
	@printf " here we go again"

clean:
	make -C $(SERVER) $@
	make -C $(CLIENT) $@
	make -C $(CJSONDIR) $@
	make -C $(SQL3DIR) $@

reinstall: uninstall all
