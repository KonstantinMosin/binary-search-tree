#ifndef NODE_H
#define NODE_H

#include <random>

enum class Distribution{
    UNIFORM,
    NORMAL,
    UNBALANCED
};

class Node{
public:
    Node(int data);
    ~Node();
    Node* insert(Node* node, int data, Distribution type = Distribution::NORMAL);
    int get_length(Node *node, int lenght = 0);
    double get_worst_time(Node *node);
    int get_depth(Node *node);

private:
    Node* insert_root(Node* node, int data);
    Node* rotate_left_node(Node* node);
    Node* rotate_right_node(Node* node);
    int get_weight(Node* node);

private:
    int m_data;
    Node* left_node;
    Node* right_node;

    int weight;

    std::default_random_engine generator_for_normal;

};

#endif // NODE_H
