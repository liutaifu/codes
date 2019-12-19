#include <iostream>

#include <pthread.h>
#include <string.h>
#include <unistd.h>


using namespace std;

#define NUM_THREAD_ID 5
static int data = 0;

pthread_mutex_t thread_mutex;
pthread_cond_t thread_cond;

typedef struct 
{
		void *(*func)(void *arg);
		pthread_t tid;
}threadStr;

void * (* func)(void *arg);

void * printThread(void *arg)
{
		int index = *((int *)arg);
		while(1)
		{
						sleep(5);
				if(!data)
				{
						pthread_mutex_lock(&thread_mutex);
						data += 1;
						cout << "This is a Thread!" << " ID " << index << " data " << data<< endl;
						cout << endl;
						pthread_cond_signal(&thread_cond);
						pthread_mutex_unlock(&thread_mutex);
				}
		}
		pthread_exit(NULL);
}

void * changeThread(void * arg)
{
		while(1)
		{
						sleep(2);
				{
						pthread_mutex_lock(&thread_mutex);
						if(!data)
								pthread_cond_wait(&thread_cond,&thread_mutex);
						data -= 1;
						cout << "This is  changeThread!" << " data " << data<< endl;
						cout << endl;
						pthread_mutex_unlock(&thread_mutex);
				}
		}
}

int main(int argc,char **argv)
{
		int i = 0;
		pthread_t thread_id[NUM_THREAD_ID];
		int index_id[NUM_THREAD_ID];
		threadStr threadStr[NUM_THREAD_ID];

		cout << "argc " << argc << " argv  " << *argv<< endl;
		cout << endl;

		pthread_mutex_init(&thread_mutex,NULL);
		pthread_cond_init(&thread_cond,NULL);
		memset(threadStr,0,sizeof(threadStr));
		threadStr[0].func = printThread;
		threadStr[0].tid = 0;
		threadStr[1].func = changeThread;
		threadStr[1].tid = 1;
		index_id[0] = 0;

/*		for (i = 0 ; i < NUM_THREAD_ID; i++)
		{
				cout << "main create thread " << i <<  endl;
				cout << endl;
				threadStr[i].tid = thread_id[i];

				index_id[i] = i;
				pthread_create(&(threadStr[i].tid),NULL,(void *)&(threadStr[i].func),(void *)&(index_id[i]));
		}

//		while(1) ;
		sleep(1);
*/
		pthread_create(&(threadStr[1].tid),NULL,threadStr[1].func,(void *)&(index_id[0]));
		//pthread_create(&(threadStr[1].tid),NULL,changeThread,(void *)&(index_id[0]));
		pthread_create(&(threadStr[0].tid),NULL,printThread,(void *)&(index_id[0]));
		pthread_exit(NULL);

		return 0;
}
