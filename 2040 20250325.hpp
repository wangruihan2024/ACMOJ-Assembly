// n-ary tree to binary tree: "transform.cpp"
#ifndef NAryTree_To_BinaryTree
#define NAryTree_To_BinaryTree

#include "tree.hpp"

NAryTree* brother(const NAryTree *father, const int &index) {
    if(index + 1 >= father->children.size())
        return NULL;
    return father->children[index + 1];
}
BinaryTree* Transform_(const NAryTree *node, const NAryTree *father, const int &index) {
    if(node == NULL)
        return NULL;
    BinaryTree* bnode = new BinaryTree(node->val);
    if(node->children.empty())
        bnode->lson = NULL;
    else
        bnode->lson = Transform_(node->children[0], node, 0);
    if(brother(father, index) == NULL)
        bnode->rson = NULL;
    else
        bnode->rson = Transform_(brother(father, index), father, index + 1);
    return bnode;
}
BinaryTree* Transform(const NAryTree *node) //根节点
{
    if(node == NULL)
        return NULL;
    BinaryTree* bnode = new BinaryTree(node->val);
    if(node->children.empty())
        bnode->lson = NULL;
    else
        bnode->lson = Transform_(node->children[0], node, 0);
    return bnode;
}

#endif