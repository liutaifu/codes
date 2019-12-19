#include <stdio.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <arpa/inet.h>
#include <string.h>
#include <unistd.h>
#include <pthread.h>

#define PORT 8888
#define SIZE 1024

void handle_client(char *buf)
{
		int i;
		for(i = 0 ; i < sizeof(buf) ; i++)
		{
				buf[i] += 'A' - 'a';
		}
}

int init(char *argv[])
{
		int listen_socket = socket(AF_INET,SOCK_DGRAM,0);

		if ( -1 == listen_socket )
		{
				perror("create socket failed!\n");
				return -1;
		}

		struct sockaddr_in addr;
		int _port = argv[2];
		char* _ip = argv[1];

		memset(&addr,0,sizeof(struct sockaddr_in));

		addr.sin_family = AF_INET;
		addr.sin_port = htons(PORT);
		addr.sin_addr.s_addr = htonl(INADDR_ANY);


		int ret = bind(listen_socket,(const struct sockaddr *)&addr,sizeof(addr));

		if( -1 == ret )
		{
				perror("bind socket failed!\n");
				return -1;
		}

		return listen_socket;
}

int main(int argc,char *argv[])
{
		int listen_socket = init(argv);

		if ( -1 == listen_socket )
		{
				perror("init failed!\n");
				return -1;
		}

		char buf[SIZE];
		while(1)
		{

				struct sockaddr_in addr;
				socklen_t len = sizeof(addr);

				ssize_t ret = recvfrom(listen_socket,buf,SIZE-1,0,(struct sockaddr *)&addr,&len);

				printf("%s\n",buf);
				buf[ret] = '\0';
	
				handle_client(buf);

				printf("%s\n",buf);
				sendto(listen_socket,buf,ret,0,(struct sockaddr *)&addr,len);
			/*	pthread_t thread;

				pthread_create(&thread,NULL,handl_client,(void*)client_socket);

				pthread_detach(thread);
*/
		}
		return 0;
}
