#include "../inc/client.h"

int u_id = 91345228;
char* u_name = "Fedia";

char *read_input() {
    char *buf = (char *)malloc(sizeof(char) * 1024);
    int c;
    int i = 0;
    do {
        c = getchar();
        if (c == -1) {
            free(buf);
            exit(EXIT_SUCCESS);
        }

        buf[i] = c;
        i++;
        if (i >= 1024) {
            buf = (char *)realloc(buf, sizeof(char) * (i + 1024));
        }
    } while (c != '\n');
    buf[i] = '\0';

    return buf;
}
char * parse_msg_to_json(char * msg){
    cJSON * message = cJSON_CreateObject();

    cJSON_AddStringToObject(message, "message_text", msg);
    free(msg);
    cJSON_AddNumberToObject(message, "user_id", u_id);
    cJSON_AddStringToObject(message, "user_name", u_name);
    char * ret = cJSON_Print(message);
    cJSON_free(message);
    return ret;
}
int main(int argc, char const *argv[]) {
    while (true) {
        argc++;
        int sock = 0;
        struct sockaddr_in serv_addr;
        if ((sock = socket(AF_INET, SOCK_STREAM, 0)) < 0) {
            printf("\n Socket creation error \n");
            return -1;
        }

        serv_addr.sin_family = AF_INET;
        serv_addr.sin_port = htons(PORT);

        // Convert IPv4 and IPv6 addresses from text to binary form
        if (inet_pton(AF_INET, argv[1], &serv_addr.sin_addr) <= 0) {
            printf("\nInvalid address/ Address not supported \n");
            return -1;
        }

        if (connect(sock, (struct sockaddr *)&serv_addr, sizeof(serv_addr)) < 0) {
            printf("\nConnection Failed \n");
            return -1;
        }
        char * hello = read_input();
        hello = parse_msg_to_json(hello);
        send(sock, hello, strlen(hello), 0);

        close(sock);
    }
    return 0;
}
