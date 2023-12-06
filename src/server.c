#include <arpa/inet.h>
#include <netinet/in.h>
#include <signal.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/socket.h>
#include <unistd.h>

#include "content.h"

static int srv_fd = 0;
static int cli_fd = 0;

int bind_srv(int port, char *addr)
{
    srv_fd = socket(AF_INET, SOCK_STREAM, 0);

    if (srv_fd < 0)
    {
        perror("Could not open socket\n");
        return -1;
    }

    struct sockaddr_in srv_addr;
    memset(&srv_addr, 0, sizeof(srv_addr));
    srv_addr.sin_family = AF_INET;
    srv_addr.sin_port = htons(port);

    if (inet_pton(AF_INET, addr, &(srv_addr.sin_addr)) < 1)
    {
        perror("Invalid address\n");
        return -1;
    }

    if (bind(srv_fd, (struct sockaddr *)&srv_addr, sizeof(srv_addr)) < 0)
    {
        perror("Could not bind to port/address\n");
        return -1;
    }

    if (listen(srv_fd, 1) < 0)
    {
        perror("Could not listen for connections\n");
        return -1;
    }

    printf("Listening\n");
    return 0;
}

void handle_conn()
{
    cli_fd = accept(srv_fd, 0, 0);

    if (cli_fd < 0)
    {
        perror("Could not accept connection\n");
        return;
    }

    printf("\tConnection\n");

    write_statusline(cli_fd);
    write_ct_header(cli_fd);
    write_cl_header(cli_fd);
    write_content(cli_fd);

    close(cli_fd);
}

void stop_srv()
{
    close(cli_fd);
    close(srv_fd);

    printf("Stopping\n");
    exit(0);
}

void kill_srv(int _)
{
    printf("Wizard was hit for 5hp!\n");
    stop_srv();
}

void serve(int port, char *addr)
{
    signal(SIGINT, kill_srv);
    signal(SIGTERM, kill_srv);
    signal(SIGKILL, kill_srv);

    if (bind_srv(port, addr) < 0)
    {
        perror("Could not start server\n");
        stop_srv();
    }

    while (1)
    {
        handle_conn();
    }
}
