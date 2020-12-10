//
// Created by 黎明杰 on 2020/12/2.
//

#ifndef UNTITLED_FOLDER_LEAVE_H
#define UNTITLED_FOLDER_LEAVE_H
#include <iostream>
#include<algorithm>
#include<queue>
#include<vector>
#include<assert.h>
#include<limits.h>
#define red true;
#define black false;
using namespace std;
class leave{
public:
    int node;
    leave *leftchild;
    leave *rightchild;
    leave(int &node1){
        node=node1;
        leftchild=rightchild=NULL;
    }
};
class tree{
public:
    leave *root;
    int n;
    int *a;
    tree(int &n1,int *a1):n(n1){
        a=new int [n1];
        for(int i=0;i<n1;i++)
            a[i]=a1[i];
    }
    void true_insert(){
        root=NULL;
        for(int i=0;i<n;i++)
            root=insert(root,a[i]);
    }
    static bool find(leave *root,int &key){
        if(root==NULL) return 0;
        if(root->node==key)
            return 1;
        else if(key<root->node)
            find(root->leftchild,key);
        else find(root->rightchild,key);
        return 0;
    }
    leave * insert(leave *root, int node1){
        if(root==NULL)
        {
            root= new leave(node1);
            return root;
        }
        if(node1<root->node)
        {
            root->leftchild=insert(root->leftchild, node1);
        }
        else
        {
            root->rightchild=insert(root->rightchild, node1);
        }
        return root;
    }
    leave* Delete(leave* root, int node)
    {
        if(!root)
            return NULL;
        if(node == root->node)
        {
            if(root->rightchild == NULL)
            {
                leave* temp = root;
                root = root->leftchild;
                delete(temp);
                return root;
            }
            else
            {
                leave* temp = root->rightchild;
                while(temp->leftchild)
                    temp = temp->leftchild;
                root->node = temp->node;
                root->rightchild = Delete(root->rightchild, temp->node);
            }
        }
        else if(node < root->node)
            root->leftchild = Delete(root->leftchild, node);
        else
            root->rightchild = Delete(root->rightchild, node);
        return root;
    }
};
#endif //UNTITLED_FOLDER_LEAVE_H
