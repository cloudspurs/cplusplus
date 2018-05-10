#include <iostream>
#include <cstdlib>
#include <pthread.h>
#include <unistd.h>
 
using namespace std;
 
#define NUM_THREADS 5
 
void *wait(void *t)
{
   int tid = *((int*)t);
 
   sleep(1);
   cout << "Sleeping in thread!" << endl;
   cout << "Thread with id: " << tid << " ...exiting " << endl;
   pthread_exit(NULL);
}
 
int main ()
{
   pthread_t threads[NUM_THREADS];
   pthread_attr_t attr;
   void *status;
 
   // 初始化并设置线程为可连接的（joinable）
   pthread_attr_init(&attr);
   pthread_attr_setdetachstate(&attr, PTHREAD_CREATE_JOINABLE);
   
   int index[NUM_THREADS];
   for(int i = 0; i < NUM_THREADS; i++){
      index[i] = i;
      cout << "main() : creating thread, " << i << endl;
      int rc = pthread_create(&threads[i], NULL, wait, (void*)&(index[i]));
      if(rc){
         cout << "Error: unable to create thread," << rc << endl;
         exit(-1);
      }
   }
 
   // 删除属性，并等待其他线程
   pthread_attr_destroy(&attr);
   for(int i = 0; i < NUM_THREADS; i++){
      int rc = pthread_join(threads[i], &status);
      if (rc){
         cout << "Error:unable to join," << rc << endl;
         exit(-1);
      }
      cout << "Main: completed thread id :" << i ;
      cout << "  exiting with status :" << status << endl;
   }
 
   cout << "Main: program exiting." << endl;
   pthread_exit(NULL);
}

