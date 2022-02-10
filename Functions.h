#ifndef FUNCTIONS_H
#define FUNCTIONS_H
#include <QtCore>
#include <iostream>
#include <fstream>
#include <vector>
#include <node.h>
#include <heap.h>
#include <huffmantree.h>
#include <cstdlib>

std::vector<int> freqList(std::string fileName);
void displayFreqList(std::vector<int> list);
float check(std::map<int,std::string> mapCode);
float compressionRatio(std::vector<int> freqList, std::map<int,std::string> mapCode);
std::string chooseFileName(std::string originalName, std::string extension);
void encodeFile(std::string fileName);
Node* constructHuffmanTree(std::vector<int> freqList);
void storeTree (Node* node,std::ofstream& file);
Node* decodeTree(std::ifstream& file);
void decodeFile(std::string fileName);

template<typename K, typename V>
std::map<V,K> inverseMap(std::map<K,V> &map)
{
    std::map<V,K> inv;
    std::for_each(map.begin(), map.end(),
                [&inv] (const std::pair<K,V> &p)
                {
                    inv.insert(std::make_pair(p.second, p.first));
                });
    return inv;
}



#endif // FUNCTIONS_H
