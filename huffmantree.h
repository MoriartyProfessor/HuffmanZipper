#ifndef HUFFMANTREE_H
#define HUFFMANTREE_H
#include <node.h>
#include <heap.h>
#include <map>

class HuffmanTree
{
public:
    Node* root;
    std::map<int, std::string> mapCode;
    void preOrder(Node* node);
    void visualize(Node*node);
    void levelOrder();
    void traverseLevel(Node* node,int i);
    std::map<int, std::string> getCodeMap();
    void assignCodes(Node* node);
    HuffmanTree(Node* node);
};

#endif // HUFFMANTREE_H
