#ifndef NODE_H
#define NODE_H
#include <string>
#include <iostream>

struct Node
{
public:
    int frequency;
    int character;
    bool container;
    std::string code;
    Node* left;
    Node* right;
    static int height(Node* node);
    Node();
    bool operator==(Node& node);
    bool operator<(Node& node);
    bool operator>(Node& node);
    bool operator<=(Node& node);
    bool operator>=(Node& node);
    friend std::ostream& operator<<(std::ostream& is, Node& node);
};

#endif // NODE_H
