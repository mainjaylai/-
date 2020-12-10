//
// Created by 黎明杰 on 2020/12/2.
//

#ifndef UNTITLED1_REDBLACK_H
#define UNTITLED1_REDBLACK_H
#include<iostream>
using namespace std;

#define RED 1
#define BLACK 0

 class Node {
 public:
    int key;
    int color;
    struct Node *parent, *left, *right;
    Node(){}
    Node(int i){
        key = i;
        color = RED;
        parent = NULL;
        left = NULL;
        right = NULL;
    }
};

class rbTree {
private:
    Node *root;
    Node *Nil;
    int size;
public:
    rbTree();
    int n;
    int *a;
    rbTree(int &n1,int *a1):n(n1){
        a=new int [n];
        for(int i=0;i<n;i++)
            a[i]=a1[i];
    }
    void true_insert(){
        for(int i=0;i<n;i++)
            Insert(a[i]);
    }
    virtual ~rbTree();
    void InitRoot();
    bool Insert(int k);
    bool Delete(int k);
    Node *Search(int k);
    int getSize();
private:
    void Insert_fixup(Node *pNode);
    void Delete_fixup(Node *pNode);
    void LeftRotate(Node *pNode);
    void RightRotate(Node *pNode);
    void Swap(Node *pNode1, Node *pNode2);
    void Empty(Node *pNode);
};
#endif //UNTITLED1_REDBLACK_H
