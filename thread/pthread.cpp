#include <iostream>
#include <pthread.h>
 
using namespace std;
 
#define NUM_THREADS 5
 
void* say_hello(void* id)
{
    int tid = *((int*)id);
    cout << "ID: " << tid  << ", Hello Runoob！" << endl;
    pthread_exit(NULL);
}
 
int main()
{
    //定义线程的id变量，多个变量使用数组
    pthread_t tids[NUM_THREADS];
    int indexes[NUM_THREADS];

    for(int i = 0; i < NUM_THREADS; ++i)
    {
        indexes[i] = i;
        //参数依次是：创建的线程id，线程参数，调用的函数，传入的函数参数
        int ret = pthread_create(&tids[i], NULL, say_hello, (void*)&(indexes[i]));
//        int ret = pthread_create(&tids[i], NULL, say_hello, (void*)&(i));
        if (ret != 0)
        {
           cout << "pthread_create error: error_code=" << ret << endl;
        }
    }

    //等各个线程退出后，进程才结束，否则进程强制结束了，线程可能还没反应过来；
    pthread_exit(NULL);
}
