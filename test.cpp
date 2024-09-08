#include "MyVector.h"
#include "MyAllocator.h"
#include<iostream>
#include<vector>
using namespace std;


class A{
    public:
        A(){cout<<"A无参构造开始:"<<endl;};
        A(int pam):param(pam){cout<<"A有参构造开始:"<<param<<endl;};
        ~A(){cout<<"A析构开始:"<<endl;};
        A(const A& c):param(c.getpar()){cout<<"A拷贝构造函数开始:"<<endl;};
        int getpar() const {return param;};
    private:
        int param;
};


int main(){
    vector<A> test(1,A(0));
    vector<A> test1(test);
    vector<A> test2 = test1;

    cout<<"对象test1初始数据量:"<<test1.size()<<endl;
     cout<<"对象test2初始数据量:"<<test2.size()<<endl;

    return 0;
}