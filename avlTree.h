#ifndef avlTreeLibrary
#define avlTreeLibrary

typedef enum { preorder = 0, inorder = 1, postorder = 2 } traversalType;
typedef enum { left = -1, right = 1 } direction;

typedef struct avlTreeNode{
  int value;
  struct avlTreeNode* left;
  struct avlTreeNode* right;
} avlTreeNode;

typedef struct avlTreeAPIStruct {
  avlTreeNode* (* const Add)(avlTreeNode* subtree, int value);

  avlTreeNode* (* const Remove)(avlTreeNode* subtree, int value);

  void (* const Print)(avlTreeNode* subtree);

  char* (* const ToString)(avlTreeNode* subtree, traversalType traversalType);

  avlTreeNode* (* const Constructor)(int value);
} avlTreeAPIStruct;

avlTreeAPIStruct const avlTreeAPI;

#endif
