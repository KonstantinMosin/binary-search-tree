#ifndef TREE_H
#define TREE_H

#include "node.h"

class Tree{
public:
    Tree();
    ~Tree();
    void insert(int data);
    void reset(Distribution type);
    void update_length();
    int get_count();
    int get_length();
    void update_worst_time();
    double get_worst_time();

private:
    Node *root;
    int count;
    int length;
    double worst_time;
    Distribution m_type;
};

#endif // TREE_H
