#include <stdio.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <arpa/inet.h>
#include <string.h>
#include <unistd.h>
#include <pthread.h>
#include <sys/select.h>
#include <sys/time.h>

#define PORT 8888

void *handl_client(void *v)
{
		int ret;
		fd_set nfds;
		long client_socket = (long)v;

		char buf[1024] = {"liutaifutestsocket"};
		
		struct timeval tv;

		while(1)
		{
				FD_ZERO(&nfds);
				FD_SET(client_socket,&nfds);

				tv.tv_sec = 5;
				tv.tv_usec = 0;
				printf("client_socket :%ld\n",client_socket);
				ret = select(client_socket + 1,&nfds,NULL,NULL,&tv);
				if ( -1 == ret )
				{
						perror("select() is error!\n");
				}
				else if (ret)
				{
						printf("client_socket is set :%d\n",(FD_ISSET(client_socket,&nfds)));
						if(FD_ISSET(client_socket,&nfds))
						{				
								memset(buf,0,sizeof(buf));
								int ret = read(client_socket,buf,sizeof(buf) - 1);
								if( -1 == ret )
								{						
										perror("read error!\n");
										break;
								}
								if ( 0 == ret )
								{
										printf("client offline!\n");
										break;
								}

								buf[ret] = '\0';
								printf("recv data : %s ret:%d\n",buf,ret);
								
								int i ; 
								for(i = 0 ; i < ret - 1 ; i++)
								{
										if ( buf[i] == '\0' )
										{
												printf("0 data :%d\n",i);
												break;
										}
										if ((buf[i] >= 'A')&& (buf[i] <= 'Z') ||
														(buf[i] >= 'a')&& (buf[i] <= 'z'))
												buf[i] += 'A' - 'a';
								}
								printf("effective data :%d\n",i);
								
								write(client_socket,buf,ret);
						}
						else
						{
								perror("client_socket is not set!\n");
						}
				}
				else
				{
						perror("waiting!\n");
				}
		}
}

int init()
{
		int listen_socket = socket(AF_INET,SOCK_STREAM,0);

		if ( -1 == listen_socket )
		{
				perror("create socket failed!\n");
				return -1;
		}

		struct sockaddr_in addr;

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

		ret = listen(listen_socket,5);
		if( -1 == ret)
		{
				perror("listen failed!\n");
				return -1;
		}

		return listen_socket;
}

int myAccept(int listen_socket)
{
		struct sockaddr_in client_addr;
		socklen_t len = sizeof(client_addr);

		int client_socket = accept(listen_socket,(struct sockaddr *)&client_addr,&len);
		if( -1 == client_socket )
		{
				perror("accept failed!\n");
				return -1;
		}

		printf("client ip: %s, port: %d\n",inet_ntoa(client_addr.sin_addr),
						ntohs(client_addr.sin_port));

		return client_socket;
}


int main(int argc,char *argv[])
{
		int listen_socket = init();

		if ( -1 == listen_socket )
		{
				perror("init failed!\n");
				return -1;
		}

		while(1)
		{
				long client_socket = myAccept(listen_socket);

				if ( -1 == client_socket )
				{
						continue;
				}

				pthread_t thread;

				pthread_create(&thread,NULL,handl_client,(void*)client_socket);

				pthread_detach(thread);

		}

		close(listen_socket);

		return 0;
}
