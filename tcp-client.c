#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <unistd.h>
#include <pthread.h>
#include <string.h>
#include <arpa/inet.h>

#define PORT 8888

void Read(int client_socket)
{
		char buf[1024] = {"liutaifuclient"};

		while(1)
		{
				memset(buf,0,sizeof(buf));
				int ret = read(client_socket,buf,sizeof(buf) - 1);
				if ( -1 == ret )
				{
						perror("read error!\n");
				}
				if ( 0 == ret )
				{
						perror("client offline!\n");
						break;
				}

				buf[ret] = '\0';
		
				printf("client data: %s ret:%d\n",buf,ret);
		}
}

void *Write(void *v)
{
		int client_socket = *(int *)v;
		char buf[1024];
		while(1)
		{
				fgets(buf,1024,stdin);
				ssize_t fd = write(client_socket,buf,sizeof(buf));
				if( 0 == fd )
				{
						perror("wirte failed!\n");
						break;
				}
		}
}

int main(int argc,char *argv[])
{
		int conn_socket = socket(AF_INET,SOCK_STREAM,0);

		if ( -1 == conn_socket )
		{
				perror("socket failed!\n");
				return -1;
		}

		struct sockaddr_in addr;
		memset(&addr,0,sizeof(struct sockaddr_in));

		addr.sin_family = AF_INET;
		addr.sin_port = htons(PORT);
		addr.sin_addr.s_addr = htonl(INADDR_ANY);

		int ret = connect(conn_socket,(const struct sockaddr *)&addr,sizeof(addr));
		if ( - 1 == ret )
		{
				perror("connect failed!\n");
				return -1;
		}
		pthread_t thread;
		pthread_create(&thread,NULL,Write,(void *)&conn_socket);

		Read(conn_socket);

		close(conn_socket);
		return 0;
}
