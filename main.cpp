//
// Created by 黎明杰 on 2020/12/2.
//
#include <iostream>
#include<algorithm>
#include <ctime>
#include <cstdlib>
#include"leave.h"
#include "AVL.h"
#include "redblack.h"
#include "B+.h"
#include<chrono>
#include<fstream>
#include<set>
#define SIZE 10000000
using namespace std;
int main(){
    ofstream file("/Users/limingjie/Desktop/text.txt");
    file<<"类别               时间                  随机或递增                   操作"<<endl;
    int N=10000;
    std::chrono::high_resolution_clock::time_point t1,t2;
    long double k1_time,k2_time;
    std::chrono::duration<long double, std::milli> time_span;
    std::chrono::duration<long double> seconds;
while(N<=500000) {
    file<<"N="<<N<<endl;
   /* srand((unsigned) time(NULL));
    list<int>::iterator it;//迭代器
    list<int> l;//定义链表，保存生成的随机数
    while (l.size() < N) {
        l.push_back(rand() % SIZE + 1);
        l.sort();//排序
        l.unique();//去除相邻的重复随机数中的第一个
    }
    int *a = new int[N];
    it = l.begin();
    for (int i = 0; i < N; i++, it++)
        a[i] = *it;*/
int *a=new int [N];
for(int i=0;i<N;i++)
    a[i]=i+1;
    /*for (int i = 0; i <N; i++)
    {
       int  index = rand() % (N - i) + i;
        if (index != i)
        {
            int tmp = a[i];
            a[i] = a[index];
            a[index] = tmp;
        }
    }*/

    AVLtree k1(N, a);
    set<int> k2;
    tree k3(N, a);
    BTree k4;
    t2 = std::chrono::high_resolution_clock::now();
    k1.true_insert();
    t1 = std::chrono::high_resolution_clock::now();
    time_span = t1 - t2;
    seconds = t1 - t2;
    file << "AVL          " << seconds.count() << "s" << "               递增                       插入" << endl;

    t2 = std::chrono::high_resolution_clock::now();
    for (int i = 0; i < N; i++) {
        k2.insert(a[i]);
    }
    t1 = std::chrono::high_resolution_clock::now();
    time_span = t1 - t2;
    seconds = t1 - t2;
    file << "RB           " <<seconds.count() << "s" << "               递增                       插入" << endl;

    t2 = std::chrono::high_resolution_clock::now();
    k3.true_insert();
    t1 = std::chrono::high_resolution_clock::now();
    time_span = t1 - t2;
    seconds = t1 - t2;
    file << "Tree         " << seconds.count() << "s"<< "               递增                       插入" << endl;

    t1 = std::chrono::high_resolution_clock::now();
    for (int i = 0; i < N; i++)
        k4.insert(a[i]);
    t2 = std::chrono::high_resolution_clock::now();
    time_span = t2 - t1;
    seconds = t2 - t1;
    file << "B            " << seconds.count() << "s"<< "               递增                       插入" << endl;

    int *b=new int[1000];
    for(int i=0;i<1000;i++)
        b[i]=rand()%N+1;
    t2 = std::chrono::high_resolution_clock::now();
    for(int i=0;i<1000;i++)
        AVLtree::find(k1.root,b[i]);
    t1 = std::chrono::high_resolution_clock::now();
    time_span = t1 - t2;
    seconds = t1 - t2;
    file << "AVL          " << seconds.count() << "s" << "              递增                       查找" << endl;

    t2 = std::chrono::high_resolution_clock::now();
    for(int i=0;i<1000;i++)
        k2.find(b[i]);
    t1 = std::chrono::high_resolution_clock::now();
    time_span = t1 - t2;
    seconds = t1 - t2;
    file << "RB           " << seconds.count() << "s" << "              递增                       查找" << endl;

    t2 = std::chrono::high_resolution_clock::now();
    for(int i=0;i<1000;i++)
        tree::find(k3.root,b[i]);
    t1 = std::chrono::high_resolution_clock::now();
    time_span = t1 - t2;
    seconds = t1 - t2;
    file << "Tree         " << seconds.count() << "s" << "               递增                       查找" << endl;

    t2 = std::chrono::high_resolution_clock::now();
    for(int i=0;i<1000;i++)
        k4.findNode(b[i]);
    t1 = std::chrono::high_resolution_clock::now();
    time_span = t1 - t2;
    seconds = t1 - t2;
    file << "B            " << seconds.count() << "s" << "               递增                       查找" << endl;

    t2 = std::chrono::high_resolution_clock::now();
    for(int i=0;i<N;i++)
        k1.Delete(k1.root,a[i]);
    t1 = std::chrono::high_resolution_clock::now();
    time_span = t1 - t2;
    seconds = t1 - t2;
    file << "AVL          " << seconds.count() << "s"<< "               递增                       删除" << endl;

    t2 = std::chrono::high_resolution_clock::now();
    for(int i=0;i<1000;i++)
        k2.erase(b[i]);
    t1 = std::chrono::high_resolution_clock::now();
    time_span = t1 - t2;
    seconds = t1 - t2;
    file << "RB           " << seconds.count() << "s" << "               递增                       删除" << endl;

    t2 = std::chrono::high_resolution_clock::now();
    for(int i=0;i<1000;i++)
        k3.Delete(k3.root,b[i]);
    t1 = std::chrono::high_resolution_clock::now();
    time_span = t1 - t2;
    seconds = t1 - t2;
    file << "Tree         " << seconds.count() << "s" << "               递增                       删除" << endl;

    t2 = std::chrono::high_resolution_clock::now();
    for(int i=0;i<1000;i++)
       k4.erase(a[i]);
    t1 = std::chrono::high_resolution_clock::now();
    time_span = t1 - t2;
    seconds = t1 - t2;
    file << "B            " << seconds.count() << "s" << "               递增                       删除" << endl;
    cout<<"N="<<N<<endl;
    file<<endl;
    N+=10000;
 }
}
