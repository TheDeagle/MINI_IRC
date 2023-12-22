/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   client.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: TheDeagle <castlehaitham@gmail.com>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/22 08:16:24 by TheDeagle         #+#    #+#             */
/*   Updated: 2023/12/22 08:36:01 by TheDeagle        ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include <sys/socket.h>
#include <string.h>
#include <stdlib.h>
#include <unistd.h>
#include <limits.h>
#include <netinet/in.h>
#include <arpa/inet.h>

int main(void)
{
    int Socket_fd;
    struct sockaddr_in Server_addr;
    socklen_t length = sizeof(Server_addr);
    Socket_fd = socket(AF_INET, SOCK_STREAM, 0);
    if (Socket_fd == -1)
    {
        perror("ERROR: COULD'T CREAT A CLIENT SOCKET\n");
        exit(1);
    }
    printf("Client socket craeted successfuly\n");
    Server_addr.sin_family = AF_INET;
    Server_addr.sin_port = htons(666);
    Server_addr.sin_addr.s_addr = inet_addr("127.0.0.1");
    if (connect(Socket_fd, (struct sockaddr*)&Server_addr, length) == -1)
    {
        perror("ERROR: COULDN'T CONNECT TO SERVER\n");
        exit(1);
    }
    printf("Connected to the server successfuly\n");
    while (1)
    {
        char *BUFFER = malloc(INT_MAX);
        int length = read(0, BUFFER, sizeof(BUFFER));
        BUFFER[length] = '\0';
        send(Socket_fd, BUFFER, sizeof(BUFFER), 0);
        free(BUFFER);
        char *BUFFER2 = malloc(INT_MAX);
        recv(Socket_fd, BUFFER2, sizeof(BUFFER2), 0);
        printf("%s", BUFFER2);
        free(BUFFER2);
    }
    close(Socket_fd);
}