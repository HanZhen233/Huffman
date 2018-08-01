#ifndef HUFFMAN_H
#define HUFFMAN_H
struct HTNode
{
	int nWeight;
	int nParent;
	int nLChild;
	int nRChild;
};
typedef HTNode *HTree;
typedef char **HCode;
int HuffmanTree(HTree &pHT,int *aWeight);
//选择Huffman数中父母结点为零且，权值最小的结点，返回其序号。
int Select(HTree pHT,int nSize);
//遍历Huffman树，生成Huffman编码
int HuffmanCoding(HCode &pHC,HTree pHT);

#endif
