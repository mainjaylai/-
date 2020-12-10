//
// Created by 黎明杰 on 2020/12/2.
//

#ifndef UNTITLED_FOLDER_AVL_H
#define UNTITLED_FOLDER_AVL_H

#include <iostream>
#include<algorithm>
#include<queue>
#include<vector>
#include<assert.h>
using namespace std;
class AVLleave{
public:
    int node;//节点数字
    int height;//节点高度;
    AVLleave *leftchild;
    AVLleave *rightchild;
    AVLleave(int &node1){
        node=node1;
        height=0;
        leftchild=rightchild=NULL;
    }
    friend AVLleave *RR_Rotate(AVLleave *root){
        AVLleave *temp=root->leftchild;
        root->leftchild=temp->rightchild;
        temp->rightchild=root;
        root=temp;
        return root;
    }
    friend AVLleave *LL_Rotate(AVLleave *root){
        AVLleave *temp=root->rightchild;
        root->rightchild=temp->leftchild;
        temp->leftchild=root;
        root=temp;
        return root;
    }
    friend  AVLleave *LR_Rotate(AVLleave *root){
        root->leftchild=LL_Rotate(root->leftchild);
        root=RR_Rotate(root);
        return root;
    }
    friend AVLleave *RL_Rotate(AVLleave *root)
    {
        root->rightchild=RR_Rotate(root->rightchild);
        root=LL_Rotate(root);
        return root;
    }
    friend int getHeight(AVLleave* node);
};
int getHeight(AVLleave* root)
{
    if(root == NULL)
        return 0;
    int l = getHeight(root->leftchild);
    int r = getHeight(root->rightchild);
    return max(l, r) + 1;
}
class AVLtree{
public:
    AVLleave *root;
    int n;
    int *a;
    AVLtree(int &n1,int *a1):n(n1){
        a=new int [n1];
        for(int i=0;i<n1;i++)
            a[i]=a1[i];
    }
    void true_insert(){
        root=NULL;
        for(int i=0;i<n;i++)
            root=insert(root,a[i]);
    }
   static bool find(AVLleave *root,int &key){
        if(root==NULL) return 0;
        if(root->node==key)
            return 1;
        else if(key<root->node)
            find(root->leftchild,key);
        else find(root->rightchild,key);
       return 0;
    }
    AVLleave * insert(AVLleave *root, int &node1){
        if(root==NULL)
        {
            root= new AVLleave(node1);
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
        int lh=getHeight(root->leftchild);
        int rh=getHeight(root->rightchild);
        if(lh-rh==2)
        {
            if(node1<root->leftchild->node)
                root=RR_Rotate(root);
            else root=LR_Rotate(root);
        }
        if(rh-lh==2)
        {
            if(node1<root->rightchild->node)
                root=RL_Rotate(root);
            else
                root=LL_Rotate(root);
        }
        return root;
    }
    AVLleave* Delete(AVLleave* root, int node)
    {
        if(!root)
            return NULL;
        if(node == root->node)
        {
            if(root->rightchild == NULL)
            {
                AVLleave* temp = root;
                root = root->leftchild;
                delete(temp);
                return root;
            }
            else
            {
                AVLleave* temp = root->rightchild;
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

        root->height = max(getHeight(root->leftchild), getHeight(root->rightchild)) + 1;
        if(getHeight(root->rightchild) - getHeight(root->leftchild) == 2)
        {
            if(getHeight(root->rightchild->rightchild) >= getHeight(root->rightchild->leftchild))
                root = LL_Rotate(root);
            else
                root = RL_Rotate(root);
        }
        else if(getHeight(root->leftchild) - getHeight(root->rightchild) == 2)
        {
            if(getHeight(root->leftchild->leftchild) >= getHeight(root->leftchild->rightchild))
                root = RR_Rotate(root);
            else
                root = LR_Rotate(root);
        }
        return root;
    }
};
#endif //UNTITLED_FOLDER_AVL_H
