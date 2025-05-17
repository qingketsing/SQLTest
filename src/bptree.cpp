/*
Date : 2025/5/15
Author : Liu jiawei
Description : B+树的实现 ADT
Reference: 《数据结构(C++版)》(清华大学出版社)
*/

#include "BPTree.h"
#include "Table.h"
#include <iostream>

template <typename K, typename V>
BPTree<K, V>::BPTree(int d) : deg(d), root(nullptr), head(nullptr) {} // 构造函数

template <typename K, typename V>
BPTree<K, V>::~BPTree() {
    delete root; // 删除根节点
} 

template <typename K, typename V>
void BPTree<K, V>::insert(const K &key,const V &value){
    // 空树情况
    if(root == nullptr){
        root = new LeafNode();
        head = static_cast<LeafNode*>(root); // 初始化头指针
        head->keys.push_back(key); // 插入第一个键
        head->values.push_back(value); // 插入第一个值
        return; 
    }

    // 非空情况
    // 先找到子节点，然后插入
    LeafNode *leaf = findLeafNode(key); // 找到叶子节点
    // 如果叶子节点已经满了，就需要分裂
    auto pos = std::lower_bound(leaf->keys.begin(), leaf->keys.end(), key);
    if(pos != leaf->keys.end() && *pos == key) {
        // 键已经存在，更新值
        size_t index = std::distance(leaf->keys.begin(), pos);
        leaf->values[index] = value;
        return;
    }else{
        // 键不存在，插入新键值对
        leaf->keys.insert(pos, key);
        leaf->values.insert(leaf->values.begin() + std::distance(leaf->keys.begin(), pos), value);
    }

    if(leaf->keys.size() > 2 * deg) { // 如果叶子节点满了，就需要分裂
        splitLeafNode(leaf);
    }
    return ;
}

template <typename K, typename V>
typename BPTree<K,V>::LeafNode* BPTree<K,V>::findLeafNode(const K &key) const{
    Node *cur = root;
    while(!cur->isLeaf){ // 如果不是叶子节点，就继续向下查找
        InterNode *interNode = static_cast<InterNode*>(cur);
        int i = 0;
        while(i < interNode->keys.size() && key > interNode->keys[i]){
            i++;
        }
        cur = interNode->children[i]; // 找到对应的子节点
    }
    return static_cast<LeafNode*>(cur);
}

template <typename K, typename V>
void BPTree<K,V>::splitLeafNode(LeafNode *l){
    LeafNode *leafnode = new LeafNode();
    int mid = deg; // 中间位置
    leafnode->keys.assign(l->keys.begin() + mid, l->keys.end());
    leafnode->values.assign(l->values.begin() + mid, l->values.end());
    l->keys.resize(mid);
    l->values.resize(mid);
    leafnode->next = l->next; // 连接链表
    l->next = leafnode; // 更新当前叶子节点的next指针
    if(l->p == nullptr){ // 如果当前节点是根节点
        InterNode *newRoot = new InterNode();
        newRoot->keys.push_back(leafnode->keys[0]); // 插入中间键
        newRoot->children.push_back(l); // 插入左子树
        newRoot->children.push_back(leafnode); // 插入右子树
        root = newRoot; // 更新根节点
        l->p = newRoot; // 更新父节点指针
        leafnode->p = newRoot;
    }else{
        InterNode *parent = static_cast<InterNode*>(l->p);
        auto pos = std::lower_bound(parent->keys.begin(), parent->keys.end(), leafnode->keys[0]);
        parent->keys.insert(pos, leafnode->keys[0]); // 插入中间键
        parent->children.insert(parent->children.begin() + std::distance(parent->keys.begin(), pos), leafnode); // 插入右子树
        leafnode->p = parent; // 更新父节点指针
        if(parent->keys.size() > 2 * deg){ // 如果父节点满了，就需要分裂
            splitInterNode(parent);
        }
    }
}

template <typename K, typename V>
void BPTree<K,V>::splitInterNode(InterNode *node){
    InterNode *interNode = new InterNode();
    int mid = deg; // 中间位置
    interNode->keys.assign(node->keys.begin() + mid + 1, node->keys.end());
    interNode->children.assign(node->children.begin() + mid + 1, node->children.end());
    node->keys.resize(mid);
    node->children.resize(mid + 1);
    if(node->p == nullptr){ // 如果当前节点是根节点
        InterNode *newRoot = new InterNode();
        newRoot->keys.push_back(node->keys[mid]); // 插入中间键
        newRoot->children.push_back(node); // 插入左子树
        newRoot->children.push_back(interNode); // 插入右子树
        root = newRoot; // 更新根节点
        node->p = newRoot; // 更新父节点指针
        interNode->p = newRoot;
    }else{
        InterNode *parent = static_cast<InterNode*>(node->p);
        auto pos = std::lower_bound(parent->keys.begin(), parent->keys.end(), node->keys[mid]);
        parent->keys.insert(pos, node->keys[mid]); // 插入中间键
        parent->children.insert(parent->children.begin() + std::distance(parent->keys.begin(), pos), interNode); // 插入右子树
        interNode->p = parent; // 更新父节点指针
        if(parent->keys.size() > 2 * deg){ // 如果父节点满了，就需要分裂
            splitInterNode(parent);
        }
    }
}

template <typename K, typename V>
BPTree<K,V>::LeafNode* BPTree<K,V>::findLeafNode(const K &key) const{
    Node *cur = root;
    while(!cur->isLeaf){
        InterNode *interNode = static_cast<InterNode*>(cur);
        int i = 0;
        while(i < interNode->keys.size() && key > interNode->keys[i]){
            i++;
        }
        cur = interNode->children[i]; // 找到对应的子节点
    }
    return static_cast<LeafNode*>(cur);
}

template <typename K, typename V>
void insert(const K &key,const V &value){
    if(root == nullptr){
        root = new LeafNode();
        head = static_cast<LeafNode*>(root); // 初始化头指针
        head->keys.push_back(key); // 插入第一个键
        head->values.push_back(value); // 插入第一个值
        return; 
    }else{
        LeafNode *leaf = findLeafNode(key); // 找到叶子节点
        auto pos = std::lower_bound(leaf->keys.begin(), leaf->keys.end(), key);
        if(pos != leaf->keys.end() && *pos == key) {
            size_t index = std::distance(leaf->keys.begin(), pos);
            leaf->values[index] = value;
            return;
        }else{
            leaf->keys.insert(pos, key);// 插入键
            leaf->values.insert(leaf->values.begin() + std::distance(leaf->keys.begin(), pos), value);// 插入值
        }
        if(leaf->keys.size() > 2 * deg) { // 如果叶子节点满了，就需要分裂
            splitLeafNode(leaf);
        }
    }
}

template <typename K, typename V>
V BPTree<K,V>::find(const K &key){
    LeafNode *leaf  = findLeafNode(key);
    auto pos = std::lower_bound(leaf->keys.begin(), leaf->keys.end(), key);
    if(pos != leaf->keys.end*() && *pos == key){
        size_t index = std::distance(leaf->keys.begin(), pos);
        return leaf->values[index]; // 返回对应的值
    }
    return V(); // 如果没有找到，返回默认值
}

template <typename K,typename V>
bool BPTree<K,V>::remove(const K &key){
    if(root == nullptr){
        return false; // 空树，删除失败
    }
    LeafNode *leaf = findLeafNode(key); // 找到叶子节点
    if(leaf == nullptr){
        return false; // 没有找到叶子节点，删除失败
    }else{
        auto pos = std::lower_bound(leaf->keys.begin(), leaf->keys.end(), key);
        
        if(pos != leaf->keys.end() && *pos == key){
            size_t index = std::distance(leaf->keys.begin(), pos);
            leaf->keys.erase(leaf->keys.begin() + index); // 删除键
            leaf->values.erase(leaf->values.begin() + index); // 删除值
        
            if(leaf->keys.size() < deg){ // 如果叶子节点的键数小于deg，就需要合并
                if(leaf->next != nullptr){ // 如果有兄弟节点
                    LeafNode *brother = leaf->next;
                    if(brother->keys.size() > deg){ // 如果兄弟节点的键数大于deg，就可以借一个
                        leaf->keys.push_back(brother->keys[0]); // 借一个键
                        leaf->values.push_back(brother->values[0]); // 借一个值
                        brother->keys.erase(brother->keys.begin()); // 删除兄弟节点的第一个键
                        brother->values.erase(brother->values.begin()); // 删除兄弟节点的第一个值
                    }else{ // 否则就需要合并
                        leaf->keys.insert(leaf->keys.end(), brother->keys.begin(), brother->keys.end());
                        leaf->values.insert(leaf->values.end(), brother->values.begin(), brother->values.end());
                        leaf->next = brother->next; // 更新链表指针
                        delete brother; // 删除兄弟节点
                    }
                }
            }
            return true; // 删除成功
        }
    }
}

template <typename K,typename V>
void BPTree<K,V>::printTree(){
    if(root == nullptr){
        std::cout << "Impty Tree" << std::endl;
        return ;
    }
    std::queue<Node*> q;
    q.push(root);
    while (!q.empty()){
        auto node = q.front();
        q.pop();
        if(!node->isLeaf){
            InterNode *internode = static_cast<InterNode*>(node);
            std::cout << "InterNode: ";
            for(auto key : internode->keys){
                std::cout << key << " ";
            }
            std::cout << std::endl;
            for(auto child : internode->children){
                q.push(child);
            }
        }else{
            LeafNode *leafNode = static_cast<LeafNode *>(node);
            std::cout << "LeafNode: ";
            for(auto key : LeafNode->keys){
                std::cout << key << " ";
            }
            std::cout << std::endl;
            for(auto value : LeafNode->values){
                std::cout << value << " ";
            }
        }
    }
    return ;
}