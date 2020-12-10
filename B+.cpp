#include<iostream>
#include<list>
#include<vector>
#include"B+.h"
bool  BNode::isLeaf()
{
    return child.empty() || (*child.begin()) == NULL;
}


bool  BNode::hasKey(int key){
    typename std::list<int>::iterator it_key;
    for(it_key=keys.begin();it_key!=keys.end();it_key++)
        if (*it_key==key)return true;
    return false;
}


bool  BNode::replace(int old_key, int new_key){
    typename std::list<int>::iterator it_key;
    for(it_key=keys.begin();it_key!=keys.end();it_key++)
        if (*it_key==old_key){
            *it_key = new_key;
            return true;
        }
    return false;
}


bool  BNode::eraseKey(int key){
    if(!hasKey(key))return false;
    typename std::list<int>::iterator it_key;
    for(it_key=keys.begin();it_key!=keys.end();it_key++)
        if (*it_key==key){
            keys.erase(it_key);
            break;
        }
    return true;
}


bool  BNode::eraseChild( BNode* p){
    typename std::list< BNode*>::iterator it_child;
    for(it_child=child.begin();it_child!=child.end();it_child++)
        if(*it_child==p){
            child.erase(it_child);
            return true;
        }
    return false;
}


BNode*  BNode::next(int data)
{
    typename std::list<int>::iterator it_key = keys.begin();
    typename std::list< BNode*>::iterator it_child = child.begin();
    while (it_key != keys.end() && data >= *it_key) {
        it_child++;
        it_key++;
    }
    return *it_child;
}


void  BNode::insertKey(int key,  BNode * child1,  BNode * child2)
{
    typename std::list<int>::iterator it_key = keys.begin();
    typename std::list<BNode*>::iterator it_child = child.begin();
    while (it_key != keys.end() && key > *it_key) {
        it_child++;
        it_key++;
    }
    keys.insert(it_key, key);
    if (!child.empty())it_child = child.erase(it_child);
    it_child = child.insert(it_child, child2);
    it_child = child.insert(it_child, child1);
}


void  BNode::updateChild(){
    typename std::list<BNode*>::iterator it_child;
    for(it_child=child.begin();it_child!=child.end();it_child++)
        if(*it_child)
            (*it_child)->fa=this;
}


void  BNode::print()
{
    typename std::list<int>::iterator it;
    for (it = keys.begin(); it != keys.end(); it++)cout << *it << ' ';
}


int  BNode::getKey(int pos)
{
    typename std::list<int>::iterator it = keys.begin();
    for (int i = 0; i < pos; ++i) {    //Òì³£´¦Àí
        ++it;
    }
    return *it;
}


int  BNode::size()
{
    return keys.size();
    return 0;
}


BNode::BNode()
{
    keys.clear();
    child.clear();
    fa = NULL;
}


BNode::BNode(int data)
{
    keys.push_back(data);
    child.push_back(NULL);
    child.push_back(NULL);
    fa = NULL;
}


BNode::~BNode()
{
    child.clear();
    keys.clear();
}

bool  BTree::insert(int key)
{
    BNode *p = root;
    if (root == NULL) {
        root = new  BNode(key);
        nsize++;
        return 1;
    }
    while (!p->isLeaf()) {
        if(p->hasKey(key))return false;
        p = p->next(key);
    }
    if(p->hasKey(key))return false;
    p->insertKey(key, NULL, NULL);
    maintainAfterInsert(p);
    nsize++;
    return 1;
}


bool  BTree::erase(int key){
    BNode* p = findNode(key);
    if(!p)return false; //未找到key
    if(!p->isLeaf()){
        int next_key;
        BNode* next_node = findNextNode(p, key, next_key);
        p->replace(key, next_key);
        key = next_key;
        p = next_node;
    }
    p->eraseKey(key);
    p->eraseChild(NULL);
    this->maintainAfterErase(p);
    nsize--;
    return true;
}


void  BTree::maintainAfterErase( BNode*p){
    BNode* fa = p->fa;
    if(p==root){
        if(p->size()==0){
            root=*(root->child.begin());
            if (root) root->fa = NULL;
        }
        return;
    }
    if(p->size()>=minKey)return;
    int father_key;
    BNode* brother_node;
    brother_node = findBrotherNode(p, father_key,0);//0左，1右

    if(brother_node)mergeNode(p,brother_node,father_key,0);//存在左节点则合并左节点
    else{
        brother_node = findBrotherNode(p, father_key,1);//0左，1右
        mergeNode(p,brother_node,father_key,1);
    }
    this->maintainAfterErase(fa);
}


void  BTree::mergeNode( BNode*p1, BNode*p2, int father_key, bool flag){
    BNode*fa = p1->fa;
    if (p2->size() > minKey) {
        int replace_key = flag ? *(p2->keys.begin()) : *(p2->keys.rbegin());
        BNode* replace_child = flag ? *(p2->child.begin()) : *(p2->child.rbegin());
        p2->eraseKey(replace_key);
        p2->eraseChild(replace_child);
        fa->replace(father_key, replace_key);
        if (flag == 0) {
            p1->keys.push_front(father_key);
            p1->child.push_front(replace_child);
        }
        else {
            p1->keys.push_back(father_key);
            p1->child.push_back(replace_child);
        }
        p1->updateChild();
    }
    else{
        fa->eraseKey(father_key);
        fa->eraseChild(p1);
        if(flag==0){
            p2->keys.push_back(father_key);
            p2->keys.splice(p2->keys.end(),p1->keys);
            p2->child.splice(p2->child.end(),p1->child);
        }
        else{
            p2->keys.push_front(father_key);
            p2->keys.splice(p2->keys.begin(),p1->keys);
            p2->child.splice(p2->child.begin(),p1->child);
        }
        fa->updateChild();
        p2->updateChild();
        delete p1;
    }
}


BNode*  BTree::findBrotherNode( BNode* p,int& key, bool flag){
    BNode* fa = p->fa;
    typename std::list<int>::iterator it_key = fa->keys.begin();
    typename std::list< BNode*>::iterator it_child = fa->child.begin();
    while(*it_child!=p){
        it_child++;it_key++;
    }
    if(flag==0){//左兄弟
        if(it_child==fa->child.begin())return NULL;
        key=*(--it_key);
        return *(--it_child);
    }
    else{
        if((++it_child)==fa->child.end())return NULL;
        key=*it_key;
        return  *it_child;
    }
}


BNode*  BTree::findNextNode( BNode*p, int key, int& next_key) {
    if (!p)return NULL;
    typename std::list<int>::iterator it_key;
    typename std::list< BNode*>::iterator it_child;
    do {
        it_key = p->keys.begin();
        it_child = p->child.begin();
        while (it_key != p->keys.end()) {
            if (key < *it_key)break;
            it_child++; it_key++;
        }
        if (it_key != p->keys.end())next_key = *it_key;
        if (*it_child == NULL)
            return p;
    } while (p = *it_child);
    return NULL;
}


BNode*  BTree::findPreNode( BNode* p, int key, int &pre_key)
{
    if (!p)return NULL;
    typename std::list<int>::reverse_iterator it_key;
    typename std::list< BNode*>::reverse_iterator it_child;
    do {
        it_key = p->keys.rbegin();
        it_child = p->child.rbegin();
        while (it_key != p->keys.rend()) {
            if (*it_key < key)break;
            it_child++; it_key++;
        }
        if (it_key != p->keys.rend())pre_key = *it_key;
        if (*it_child == NULL)
            return p;
    } while (p = *it_child);
    return NULL;
}



BNode*  BTree::findNode(int key){
    BNode* p = root;
    while(p&&!(p->hasKey(key))){
        p=p->next(key);
    }
    return p;
}


void  BTree::maintainAfterInsert( BNode *p)
{
    while (p->size() >= k) {
        BNode* left_node = splitLeftNode(p, (k - 1) / 2);
        BNode* right_node = splitRightNode(p, k - (k - 1) / 2 - 1);
        int key = p->getKey((k - 1) / 2);    //上移的值
        delete p;
        p = left_node->fa;    //父节点
        if (!p) {
            root = p = new  BNode();
            left_node->fa = right_node->fa = root;
        }
        p->insertKey(key, left_node, right_node);
    }
}


BNode *  BTree::splitLeftNode( BNode * p, int pos)
{
    BNode* node = new  BNode();
    node->fa = p->fa;
    typename std::list<int>::iterator it_key = p->keys.begin();
    typename std::list< BNode*>::iterator it_child = p->child.begin();
    node->child.push_back(*it_child);
    int i = 0;
    while (i++<pos) {
        it_child++;
        node->keys.push_back(*it_key);
        node->child.push_back(*it_child);
        it_key++;
    }
    node->updateChild();
    return node;
}


BNode *  BTree::splitRightNode( BNode *p, int pos)
{
    BNode* node = new  BNode();
    node->fa = p->fa;
    typename std::list<int>::reverse_iterator it_key = p->keys.rbegin();
    typename std::list< BNode*>::reverse_iterator it_child = p->child.rbegin();
    node->child.push_front(*it_child);
    int i = 0;
    while (i++<pos) {
        it_child++;
        node->keys.push_front(*it_key);
        node->child.push_front(*it_child);
        it_key++;
    }
    node->updateChild();
    return node;
}


int  BTree::size(){
    return nsize;
}


int  BTree::height()
{
    int i = 0;
    BNode *p = root;
    while (p) {
        p = *(p->child.begin());
        ++i;
    }
    return i;
}


BNode*  BTree::getRoot()
{
    return this->root;
}


void  BTree::deleteNode( BNode*p)
{
    if (!p)return;
    typename std::list< BNode*>::iterator it;
    for (it = p->child.begin(); it != p->child.end(); it++) {
        deleteNode(*it);
    }
    delete p;
}


BTree::BTree()
{
    k = 512;
    nsize = 0;
    maxKey = k - 1;
    minKey = (k - 1) / 2;
    root = NULL;
}


void  BTree::printArray() {
    print(root);
    cout << endl;
}


void  BTree::print( BNode*p) {
    if (p == NULL)return;
    typename std::list<int>::iterator it_key = p->keys.begin();
    typename std::list< BNode*>::iterator it_child = p->child.begin();
    print(*it_child);
    for (it_child++; it_child != p->child.end(); it_child++, it_key++) {
        cout << *it_key << ' ';
        print(*it_child);
    }
}


void  BTree::printRoot()
{
    if (!root)return;
    root->print();
    cout << endl;
}



int  BTree::getLen(int x)
{
    int cnt = 0;
    while (x) {
        cnt++; x /= 10;
    }
    return cnt;
    return 0;
}


void  BTree::GetDFS( BNode*p, int d, int* dep, int *tab, map<int, int>&mp, int& cnt) {
    ++cnt;
    int n = cnt;
    typename std::list<int>::iterator it_key = p->keys.begin();
    typename std::list< BNode*>::iterator it_child = p->child.begin();
    mp[*it_key] = cnt;
    int x = 0;
    if (*it_child != NULL) {
        for (; it_child != p->child.end(); it_child++) {
            if (*it_child == NULL)break;
            GetDFS(*it_child, d + 1, dep, tab, mp, cnt);
            BNode*q = *it_child;
            int num = mp[*q->keys.begin()];
            x += tab[num];
        }
        x /= p->child.size();
        tab[n] = x;

    }
    else {
        tab[n] = dep[d];
    }
    for (; it_key != p->keys.end(); it_key++) {
        dep[d] += 1 + getLen(int(*it_key));
    }
    dep[d] += 2;
}


BTree::~BTree()
{
    deleteNode(root);
}
