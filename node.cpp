#include "node.h"

Node::Node(int data) :m_data(data), left_node(nullptr), right_node(nullptr), weight(1){}

Node::~Node(){
    if(left_node){
        delete left_node;
    }
    if(right_node){
        delete right_node;
    }
}

Node* Node::insert(Node *node, int data, Distribution type){
    if(!node){
        return new Node(data);
    }

    if(type == Distribution::UNIFORM && rand() % (node->weight + 1) == 0){
        return insert_root(node, data);
    }

    std::uniform_int_distribution<int> distribution_normal(0, node->weight);
    if(type == Distribution::NORMAL && distribution_normal(generator_for_normal)){
        return insert_root(node, data);
    }

    if(type == Distribution::UNBALANCED){
        return insert_root(node, data);
    }

    if(node->m_data > data){
        node->left_node = insert(node->left_node, data, type);
    }
    else{
        node->right_node = insert(node->right_node, data, type);
    }
    node->weight = get_weight(node->left_node) + get_weight(node->right_node) + 1;
    return node;
}

Node* Node::insert_root(Node* node, int data){
    if(!node){
        return new Node(data);
    }
    if(node->m_data > data){
        node->left_node = insert_root(node->left_node, data);
        node->weight = get_weight(node->left_node) + get_weight(node->right_node) + 1;
        return rotate_right_node(node);
    }
    else{
        node->right_node = insert_root(node->right_node, data);
        node->weight = get_weight(node->left_node) + get_weight(node->right_node) + 1;
        return rotate_left_node(node);
    }
}

int Node::get_length(Node *node, int length){
    if(node){
        length++;
        return length + get_length(node->left_node, length) + get_length(node->right_node, length);
    }
    return 0;
}

#include <ctime>

double Node::get_worst_time(Node *node){
    clock_t start = clock();
    while(node){
        if(node->get_depth(node->left_node) > node->get_depth(node->right_node)){
            node = node->left_node;
        }
        else{
            node = node->right_node;
        }
    }
    clock_t end = clock();
    return (double)(end - start) / CLOCKS_PER_SEC * 1000;
}

int Node::get_depth(Node *node){
    if(node){
        return std::max(get_depth(node->left_node), get_depth(node->right_node)) + 1;
    }
    else{
        return 0;
    }
}

Node* Node::rotate_left_node(Node* node){
    Node* ptr = node->right_node;
    if(!ptr){
        return node;
    }
    node->right_node = ptr->left_node;
    ptr->left_node = node;
    ptr->weight = node->weight;
    node->weight = get_weight(node->left_node) + get_weight(node->right_node) + 1;
    return ptr;
}

Node* Node::rotate_right_node(Node* node){
    Node* ptr = node->left_node;
    if(!ptr){
        return node;
    }
    node->left_node = ptr->right_node;
    ptr->right_node = node;
    ptr->weight = node->weight;
    node->weight = get_weight(node->left_node) + get_weight(node->right_node) + 1;
    return ptr;
}

int Node::get_weight(Node* node){
    if(node){
        return node->weight;
    }
    return 0;
}
