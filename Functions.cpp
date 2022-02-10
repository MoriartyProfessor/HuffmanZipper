#include <Functions.h>
std::string toBinary(int n)
{
    std::string r;
    while(n!=0) {r=(n%2==0 ?"0":"1")+r; n/=2;}
    return r;
}
std::vector<int> freqList(std::string fileName)
{
    std::vector<int> list(256);

    std::fstream file(fileName, std::ios::in | std::ios::out | std::ios::binary );
    int character;

    while(!file.eof())
    {
        character=file.get();
        if(character!=-1)
            list[character]++;
    }

    file.close();
    return list;
}


float check(std::map<int, std::string> mapCode)
{
    float sum=0;
    for (auto it = mapCode.begin(); it != mapCode.end(); ++it)
      {
          sum+=1/pow(2,it->second.length());
      }
    return sum;
}

void displayFreqList(std::vector<int> list)
{
    for(int i=0;i<list.size();++i)
    {
        if(list[i]!=0)
            std::cout<<char(i)<<'\t'<<list[i]<<std::endl;
    }
}

float compressionRatio(std::vector<int> freqList, std::map<int,std::string> mapCode)
{
    int originalSize=0;
    int compressedSize=0;
    for(int i=0;i<freqList.size();++i)
        originalSize+=8*freqList[i];
    for (auto it = mapCode.begin(); it != mapCode.end(); ++it)
    {
        std::cout<<freqList[it->first]<<"\t"<<it->second<<'\t'<<char(it->first)<<'\n';
        compressedSize+=freqList[it->first]*it->second.length();
    }
    return compressedSize/float(originalSize);
}

std::string chooseFileName(std::string originalName, std::string extension)
{
    std::string newFileName=originalName;
    while(true)
    {
        if(newFileName.back()!='.')
            newFileName.pop_back();
        else
            break;
    }
    for(int i=0;i<extension.size();++i)
    {
        newFileName.push_back(extension.at(i));
    }
    return newFileName;
}

Node* constructHuffmanTree(std::vector<int> freqList)
{
    int size=0;
    for(int i=0;i<freqList.size();++i)
    {
        if(freqList[i]>0)
            ++size;
    }
    std::vector<Node*> arrPtr(size);

    int j=0;
    for(int i=0;i<freqList.size();++i)
    {
        if(freqList[i]>0)
        {
            arrPtr[j] = new Node;
            arrPtr[j]->character=i;
            arrPtr[j]->frequency=freqList[i];
            arrPtr[j]->container=true;
            ++j;
        }
    }
    Heap<Node> minHeap(arrPtr);

    while(minHeap.size!=1)
    {
        Node* node=new Node;

        node->container=false;
        node->left=minHeap.extractMin();
        node->right=minHeap.extractMin();
        node->frequency=(node->left->frequency)+(node->right->frequency);
        minHeap.insert(node);
    }
    return minHeap.extractMin();
}

void storeTree (Node* node,std::ofstream& file) {
    if (node->container==true) {
        file.put('1');
        file.put(node->character);
    }
    else {
        file.put('0');
        storeTree (node->left,file);
        storeTree (node->right,file);
    }
}

Node* decodeTree(std::ifstream& file)
{
    char character;
    Node* newNode;
    character=file.get();
    if (character == '1')
        {
            newNode=new Node;
            newNode->character=file.get();
            newNode->container=true;
            return newNode;
        }
        else
        {
            Node* leftChild = decodeTree(file);
            Node* rightChild = decodeTree(file);
            newNode=new Node;
            newNode->container=false;
            newNode->left=leftChild;
            newNode->right=rightChild;
            return newNode;
        }
}

void encodeFile(std::string fileName)
{
    std::string newFileName=chooseFileName(fileName, "hzip");
    std::fstream sourse(fileName, std::ios::in | std::ios::out | std::ios::binary );
    std::ofstream zipped(newFileName, std::ios::binary );
    HuffmanTree tree(constructHuffmanTree(freqList(fileName)));
    storeTree(tree.root,zipped);
    std::map<int,std::string> mapCode=tree.getCodeMap();
    int character;
    int charBuffer=0;
    int buffSize=0;
    std::string* code;

    while(!sourse.eof())
    {
        character=sourse.get();
        if(character!=-1)
        {
            code=&(mapCode[character]);
            for(int i=0;i<code->size();++i,++buffSize)
            {
                if(buffSize==7)
                {
                    buffSize=0;
                    zipped.put(char(charBuffer));
                    charBuffer=0;
                }
                if(code->at(i)=='1')
                {
                    charBuffer+=1;
                }
                charBuffer=charBuffer<<1;
            }
        }
    }
    zipped<<character;
    sourse.close();
    zipped.close();
}

void decodeFile(std::string fileName)
{
    std::string newFileName=chooseFileName(fileName, "htxt");
    std::ifstream zipped(fileName, std::ios::binary );
    std::ofstream destination(newFileName, std::ios::binary);

    HuffmanTree tree(decodeTree(zipped));
    std::map<int,std::string> temp=tree.getCodeMap();
    std::map<std::string,int> mapCode=inverseMap(temp);
    char charBuffer=0;
    int buffSize=0;
    char mask=128;
    std::string code;
    code.reserve(32);
    charBuffer=zipped.get();
    while(!zipped.eof())
    {

        if(buffSize==7)
        {
            buffSize=0;
            charBuffer=zipped.get();
        }
        if(mapCode.find(code)!=mapCode.end())
        {
            destination.put(mapCode.at(code));
            code="";
        }
        if(mask&charBuffer)
        {
            code.push_back('1');
        }
        else
        {
            code.push_back('0');
        }
        charBuffer=charBuffer<<1;
        ++buffSize;
    }
    destination.close();
    zipped.close();
}
