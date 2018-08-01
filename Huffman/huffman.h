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
//ѡ��Huffman���и�ĸ���Ϊ���ң�Ȩֵ��С�Ľ�㣬��������š�
int Select(HTree pHT,int nSize);
//����Huffman��������Huffman����
int HuffmanCoding(HCode &pHC,HTree pHT);

#endif
