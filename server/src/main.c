#include "../inc/server.h"


int main(int argc, char const *argv[]) {
    server_init_data_t server_data = init_server((char *)argv[1]);
    server_loop(server_data);
    return 0;
}
