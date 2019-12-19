#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <unistd.h>
#include <pthread.h>
#include <string.h>
#include <arpa/inet.h>

//#define PORT 8888
#define THREAD_MAX 10

typedef struct {
		char **argv;
		int socket;
} udp_data;

typedef struct {
		pthread_t thread;
		int num_thread;
//		void *thread_start(void *);
		void *data;
} udp_thread;

void *Read_data(void *v)
{
		udp_data *data = (udp_data *)v;
		int client_socket = data->socket;
		int _port = atoi(data->argv[2]);
		char *_ip = data->argv[1];

		char buf[1024];
		struct sockaddr_in addr;
		memset(&addr,0,sizeof(struct sockaddr_in));
		socklen_t len = sizeof(addr);

		addr.sin_family = AF_INET;
		addr.sin_port = htons(_port);
		addr.sin_addr.s_addr = inet_addr(_ip);
		while(1)
		{
				ssize_t ret = recvfrom(client_socket,buf,1023,0,(struct sockaddr *)&client_socket,&len);
				if( -1 == ret )
				{
						perror("read data failed!\n");
				}
				if( 0 == ret )
				{
						printf("client offline!\n");
						break;
				}

				buf[ret] = '\0';
				printf("%s\n",buf);
		}
}


void *Write_data(void *v)
{
		udp_data *data = (udp_data *)v;
		int client_socket = data->socket;
		char buf[1024];
		int _port = atoi(data->argv[2]);
		char *_ip = data->argv[1];
		struct sockaddr_in addr;
		memset(&addr,0,sizeof(struct sockaddr_in));

		addr.sin_family = AF_INET;
		addr.sin_port = htons(_port);
		addr.sin_addr.s_addr = inet_addr(_ip);
		while(1)
		{
				fgets(buf,1024,stdin);
				sendto(client_socket,buf,sizeof(buf),0,(struct sockaddr *)&addr,sizeof(addr));
		}
}



int main(int argc,char *argv[])
{
		int i = 0;
		int conn_socket = socket(AF_INET,SOCK_DGRAM,0);

		if ( -1 == conn_socket )
		{
				perror("socket failed!\n");
				return -1;
		}

		udp_data u_data;
		u_data.argv = argv;
		u_data.socket = conn_socket;
		pthread_t thread;
		udp_thread u_thread[THREAD_MAX];
		/*u_thread[0].num_thread = 0;
		u_thread[0].data = (void *)&u_data;
		u_thread[0].thread_start = Write_data;

		u_thread[1].num_thread = 1;
		u_thread[1].data = (void *)&conn_socket;
		u_thread[1].thread_start = Read_data;

		for (i = 0 ; i < sizeof(u_thread)/sizeof(u_thread[0]);i++)
		{
				printf("%d\n",i);
				pthread_create(&(u_thread[i].thread),NULL,u_thread[i].thread_start,u_thread[i].data);
		}*/
		pthread_create(&thread,NULL,Write_data,(void *)&u_data);

		Read_data((void *)&u_data);

		close(conn_socket);
		return 0;
}
