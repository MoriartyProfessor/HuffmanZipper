#include "node.h"

bool Node::operator==(Node& node)
{
    return frequency==node.frequency;
}

bool Node::operator<(Node& node)
{
    return frequency<node.frequency;
}

bool Node::operator>(Node& node)
{
    return frequency>node.frequency;
}

bool Node::operator<=(Node& node)
{
    return frequency<=node.frequency;
}

bool Node::operator>=(Node& node)
{
    return frequency>=node.frequency;
}

std::ostream& operator<<(std::ostream& os, Node& node)//just function for debugging
{
    os<<node.frequency;
    return os;
}



Node::Node()
{
    left=nullptr;
    right=nullptr;
}

int Node::height(Node* node)
{
    if(node==nullptr)
        return 0;
    int lHeight=height(node->left);
    int rHeight=height(node->right);

    if(rHeight>lHeight)
        return rHeight+1;
    else
        return lHeight+1;
}
