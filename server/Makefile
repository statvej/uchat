#-Og -g3 -fsanitize=address
all:
	clang -o uchat_server -lpthread  src/main.c src/queue.c src/server.c ../libs/cJSON/cJSON.c