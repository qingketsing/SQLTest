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
    
}