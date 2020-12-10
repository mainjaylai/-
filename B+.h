#ifndef UNTITLED_B_H
#define UNTITLED_B_H
#include<iostream>
#include<list>
#include <map>
using namespace std;

class BNode
{
public:
    list <int> keys;    //键值表
    list < BNode*> child;    //子节点指针表
    BNode* fa;    //父节点指针

    BNode();
    BNode(int);
    ~BNode();
    bool isLeaf();    //判断是否是叶节点
    bool hasKey(int key);  //判断是否存在某一键值
    bool replace(int old_key, int new_key);  //替换键值
    bool eraseKey(int key);  //删除键值
    bool eraseChild( BNode*); //删除子节点指针
    void updateChild(); //子节点重定向
    void insertKey(int data,  BNode* child1,  BNode* child2);    //向节点插入某键值，并更新子节点指针
    void print();    //输出节点键值
    BNode* next(int key);    //获取key应该指向子节点的方向
    int getKey(int pos);    //获取节点第pos个键值
    int size();    //获取节点所存储键值数量
};

class BTree
{
public:
    BNode *root;//根节点指针
    int k=512;    //B树为k阶
    int minKey, maxKey; //最少键值和最多键值
    int nsize;  //B数结构元素（键值）总数
    void maintainAfterInsert( BNode *);    //插入元素后保持树形结构平衡
    void maintainAfterErase( BNode*);  //删出元素后保持树形结构平衡
    void mergeNode( BNode*,  BNode*, int, bool flag);//合并两个节点，flag为0时，表示合并左节点；否则合并右节点
    void deleteNode( BNode *);    //删除节点空间，用于析构
    void print( BNode*);    //输出节点
    BNode* splitLeftNode( BNode*, int);    //节点分裂得到左节点
    BNode* splitRightNode( BNode*, int);    //节点分裂得到右节点
    BNode* findBrotherNode( BNode*,int&,bool flag);//查找兄弟节点,flag为0时，查找左节点；否则为右节点
    BNode* findNode(int);    //获取存在该键值的节点
    BTree();
    ~BTree();
    //构造，传入B树阶数
    bool insert(int data);    //插入
    bool erase(int key);  //删除
    void printRoot();    //输出根节点
    void printArray();    //输出排序结果
    void printTree();    //输出树型
    void printWholeTree();    //输出完整树型
    BNode* findNextNode( BNode*p, int, int&);  //获取后继节点及键值
    BNode* findPreNode( BNode*p, int, int&);    //获取前驱节点及键值
    int size();    //获取树元素总数

private:
    int getLen(int);    //辅助函数，获取数字长度
    void GetDFS( BNode*p, int d, int* dep, int *tab, map<int, int>&mp, int& cnt);    //辅助函数，用于递归获取输出树型的信息
    BNode *getRoot();
    int height();
};
#endif 