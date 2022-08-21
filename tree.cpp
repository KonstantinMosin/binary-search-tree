#include "tree.h"

Tree::Tree() : root(nullptr), count(0), length(0), worst_time(0) {}

Tree::~Tree(){
    if(root){
        delete root;
    }
}

void Tree::insert(int data){
    root = root->insert(root, data, m_type);
    count++;
}

void Tree::reset(Distribution type){
    if(root){
        delete root;
    }
    root = nullptr;
    count = 0;
    m_type = type;
}

void Tree::update_length(){
    length = root->get_length(root);
}

int Tree::get_count(){
    return count;
}

int Tree::get_length(){
    return length;
}

void Tree::update_worst_time(){
    worst_time = root->get_worst_time(root);
}

double Tree::get_worst_time(){
    return worst_time;
}
