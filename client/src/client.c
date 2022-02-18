#include "client.h"

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

int main(int argc, char const *argv[]) {
    while (true) {
        int sock = 0;
        struct sockaddr_in serv_addr;
        char buffer[1024] = {0};
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
        char *hello = read_input();
        send(sock, hello, strlen(hello), 0);
        //valread = read(sock, buffer, 1024);
        //printf("%s\n", buffer);
        close(sock);
    }
    return 0;
}
