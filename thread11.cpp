#include <iostream>
#include <thread>
#include <cmath>

using namespace std;

void output(int i)
{
    cout << i << endl;
}

class Task {
    public:
        void operator() (int i) {
            cout << i << endl;
        }
};

class Work {
    public:
        void operator() () {
            cout << "xxx" << endl;
        }
};

int main()
{
    
    for(uint8_t i = 0; i < 4; i++) {
        thread t(output, i);
//        t.detach();
        t.join();
    }

    for(int i = 0; i < 4; i++) {
        thread t([i](){ cout << i << endl; });
        t.join(); 
    }

    for(uint8_t i = 0; i < 4; i++) {
        Task task;
        thread t(task, i);
        t.join(); 
    }

    for(uint8_t i = 0; i < 4; i++) {
        thread t{Work()};
        t.join(); 
    }

    auto fn = [](int *a) {
        for(int i = 0; i < 10; i++)
            cout << *a << endl;
    };

    [fn](){
        int a = 100;
        thread t(fn, &a);
        t.detach();
    }();
        
    getchar();
    return 0;
}

