
//bst.h
// Binary Search Tree ADT header file.
#pragma once

//
// BST type declarations:
//
typedef char*  BSTKey;
typedef struct BSTValue
{
  char *X;
  long long Y;
} BSTValue;

typedef struct BSTNode
{
  BSTKey    Key;
  BSTValue  Value;
  struct BSTNode  *Left;
  struct BSTNode  *Right;
} BSTNode;

typedef struct BST
{
  BSTNode *Root;
  int      Count;
} BST;



// BST API: function prototypes
BST *BSTCreate();
int  BSTCompareKeys(BSTKey key1, BSTKey key2);
BSTNode *BSTSearch(BST *tree, BSTKey key);
int  BSTSearchDepth(BST *tree, BSTKey key);
int  BSTInsert(BST *tree, BSTKey key, BSTValue value);
void BSTPrintInorder(BST *tree, void(*pf)(BSTNode*));
void BSTPrintPreorder(BST *tree, void(*pf)(BSTNode*));
int       BSTCount(BSTNode *root);
int       BSTHeight(BST *tree);
BSTNode *InputFile(char *filename, int *numNodes);
BST *BuildTree(char *filename);
BSTNode *BSTSuggest(BST *tree, BSTKey key);
void BSTFillValues(BSTNode * root, char key[512], int *M, int size, BSTValue * values);
void BSTFindM(BSTNode * root, char key[512], int *M, int size);