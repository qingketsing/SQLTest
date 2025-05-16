
/*
Date : 2025/5/15
Author : Liu jiawei
Description : B+树的实现头文件 ADT
Reference: 《数据结构(C++版)》(清华大学出版社)
*/

#ifndef BPTREE_H
#define BPTREE_H

#include <vector>
#include <iostream>
#include <algorithm>

template <typename K,typename V>

class BPTree {
private :
    struct Node { // 节点基类
        bool isLeaf;
        Node *p; // 父节点
        virtrual ~Node() = default;
    }

    struct InterNode : public Node { // 内部节点,表示非最底层的节点
        /*
        key : 关键字
        children : 子节点(有可能指向叶子节点，也有可能指向内部节点)
        */
        std::vector<K> keys;
        std::vector<Node*> children;

        InterNode() : Node() { // 构造一个空的内部节点
            this.isLeaf = false;
            this.p = nullptr;
        }

        ~InterNode() {
            for (auto child : children) { // 递归删除子节点
                delete child;
            }
        }
    }

    struct LeafNode : public Node { // 叶子节点
        std::vector<K> keys;
        std::vector<V> values;
        LeafNode *next;

        LeafNode() : Node() { 
            this.isLeaf = true;
            next = nullptr;
        }
    };

    int deg; // 阶数
    Node *root; // 根节点
    LeafNode *head; // 头指针，指向最左边的叶子节点，构成链表结构

    void splitLeafNode(LeafNode *l);
    void splitInterNode(InterNode *node);
    void insertToParent(Node *parent,const K &key,Node *child);
    LeafNode* findLeafNode(const K &key) const;

public :
    BPTree(int d);
    ~BPTree();

    void insert(const K &key,const V &value);
    V find(const K &key);
    std::vector<V> rangeFind(const K &start,const K &end);
    bool remove(const K &key);
    void printTree();
};

#endif // BPTREE_H