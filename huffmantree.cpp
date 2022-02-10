#include "huffmantree.h"

HuffmanTree::HuffmanTree(Node* node)
{
    root=node;
}

void HuffmanTree::preOrder(Node* node)
{
    if(node->left!=nullptr)
        preOrder(node->left);
    if(node->container==false)
        std::cout<<node->frequency<<'\t';
    if(node->right!=nullptr)
        preOrder(node->right);
}



void HuffmanTree::levelOrder()
{
    int h=Node::height(root);
    for(int i=1;i<=h;++i)
        traverseLevel(root,i);
    std::cout<<std::endl;
}

void HuffmanTree::traverseLevel(Node *node, int i)
{
    if(node==nullptr)
        return;
    if(i==1)
    {
        if(node->container)
            std::cout<<node->character<<'\t';
    }
    else
    {
        traverseLevel(node->left, i-1);
        traverseLevel(node->right, i-1);
    }
}

std::map<int, std::string> HuffmanTree::getCodeMap()
{
    root->code="";
    assignCodes(root);
    return mapCode;
}

void HuffmanTree::assignCodes(Node *node)
{
    if(node->container==true)
        mapCode.insert(std::pair<int,std::string>(node->character,node->code));
    if(node->left!=nullptr)
    {
        node->left->code.append(node->code);
        node->left->code.append("0");
        assignCodes(node->left);
    }
    if(node->right!=nullptr)
    {
        node->right->code.append(node->code);
        node->right->code.append("1");
        assignCodes(node->right);
    }
}

void HuffmanTree::visualize(Node*node)
{
    static int level=0;
    for (int ix = 0; ix < level; ++ix)
        std::cout << '\t';
            std::cout << node->character << std::endl;
            ++level;
            if (node->left!=nullptr)
            {
                visualize(node->left);
                --level;
            }
            if (node->right!=nullptr)
            {
                visualize(node->right);
                --level;
            }
}
