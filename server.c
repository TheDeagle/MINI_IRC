/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   server.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: TheDeagle <castlehaitham@gmail.com>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/22 08:16:27 by TheDeagle         #+#    #+#             */
/*   Updated: 2023/12/22 08:36:05 by TheDeagle        ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include <sys/socket.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <netinet/in.h>
#include <limits.h>

int main(void)
{
    int socket_fd;
    struct sockaddr_in addr;
    struct sockaddr_in client_addr;

    addr.sin_family = AF_INET;
    addr.sin_port = htons(666);

    socket_fd = socket(AF_INET, SOCK_STREAM, 0);
    if (socket_fd == -1)
    {
        perror("ERROR: BAD SOCKET FILE DESCRIPTOR RETURNED\n");
        exit(1);
    }
    printf("Socket has been created by the server\n");
    if (bind(socket_fd, (struct sockaddr *)&addr, sizeof(addr)) == -1)
    {
        perror("ERROR: COULDN'T INTIALIZE SOCKETS");
        exit(1);
    }
    printf("Socket has been initialized by the server\n");
    if (listen(socket_fd, 10) == -1)
    {
        perror("ERROR: COULDN'T LISTEN");
        exit(1);
    }
    printf("Server is listening on port 666\n");
    int client_fd;
    socklen_t client_length = sizeof(client_addr);
    client_fd = accept(socket_fd, (struct sockaddr *)&client_addr, &client_length);
    if (client_fd == -1)
    {
        perror("ERROR: CONNECTION REFUSED\n");
        exit(0);
    }
    printf("Client connected to the server seccussfuly\n");

    while (1)
    {
        char *BUFFER = malloc(INT_MAX);
        recv(client_fd, BUFFER, sizeof(BUFFER), 0);
        printf("%s", BUFFER);
        free(BUFFER);
        char *BUFFER2 = malloc(INT_MAX);
        int length = read(0, BUFFER2, sizeof(BUFFER2));
        BUFFER2[length] = '\0';
        send(client_fd, BUFFER2, sizeof(BUFFER2), 0);
        free(BUFFER2);
    }
    close(socket_fd);
    close(client_fd);

}