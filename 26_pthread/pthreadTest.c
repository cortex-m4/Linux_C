/*
	多线程测试demo
*/
#include<stdio.h>
#include<pthread.h>
#include<unistd.h>

void *thread_run(void* arg)
{

    while(1)
    {
        printf("new thread,thread is :%u,pid:%d\n",pthread_self(),getpid());
		usleep(10000);
		//pthread_exit(NULL);
    }
}

int main()
{
	int counter=0;
    pthread_t tid;
    pthread_create(&tid,NULL,thread_run,NULL);
    while(1)
    {	
		//pthread_self()是获取线程id
        printf("main thread,thread is :%u,pid:%d\n",pthread_self(),getpid())    ;
        sleep(1);
		counter++;
        if(counter==10){
			pthread_cancel(pthread_self());//杀死自己
			pthread_cancel(tid);
		}
    }

    return 0;
}


