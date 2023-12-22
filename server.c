/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   server.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hben-bou <hben-bou@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/22 08:16:27 by TheDeagle         #+#    #+#             */
/*   Updated: 2023/12/22 22:40:05 by hben-bou         ###   ########.fr       */
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

    socket_fd = socket(PF_INET, SOCK_STREAM, 0);
    addr.sin_family = PF_INET;
    addr.sin_addr.s_addr = INADDR_ANY;
    addr.sin_port = htons(9898);
    if (socket_fd == -1)
    {
        perror("ERROR: BAD SOCKET FILE DESCRIPTOR RETURNED\n");
        exit(1);
    }
    printf("Socket has been created by the server\n");
    if (bind(socket_fd, (struct sockaddr *)&addr, sizeof(addr)) == -1)
    {
        perror("ERROR: COULDN'T INTIALIZE SOCKETS\n");
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
        char BUFFER[2048];
        recv(client_fd, BUFFER, sizeof(BUFFER), 0);
        write(1, BUFFER, strlen(BUFFER));
        char BUFFER2[2048];
        int length = read(0, BUFFER2, sizeof(BUFFER2));
        BUFFER2[length] = '\0';
        send(client_fd, BUFFER2, sizeof(BUFFER2), 0);
    }
    close(socket_fd);
    close(client_fd);
}
