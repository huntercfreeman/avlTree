#include <stdio.h>
#include <stdlib.h>
#include "avlTree.h"
#include "stringBuilder.h"

int height(avlTreeNode* N)
{
  if(N == NULL)
    return 0;
  return N->height;
}

int GetBalance(struct avlTreeNode* N)
{
  if(N == NULL)
    return 0;
  return height(N->left) - height(N->right);
}

static int Max(int a, int b)
{
  return (a > b) ? a : b;
}

static avlTreeNode* RightRotate(avlTreeNode* y)
{
  avlTreeNode* x = y->left;
  avlTreeNode* T2 = x->right;

  // Perform rotation
  x->right = y;
  y->left = T2;

  // Update heights
  y->height = Max(height(y->left), height(y->right)) + 1;
  x->height = Max(height(x->left), height(x->right)) + 1;

  // Return new root
  return x;
}

static avlTreeNode* LeftRotate(avlTreeNode* x)
{
  avlTreeNode* y = x->right;
  avlTreeNode* T2 = y->left;

  // Perform rotation
  y->left = x;
  x->right = T2;

  // Update heights
  x->height = Max(height(x->left), height(x->right)) + 1;
  y->height = Max(height(y->left), height(y->right)) + 1;

  // Return new Root
  return y;
}

static avlTreeNode* Add(avlTreeNode* subtree, int value)
{
  if(subtree == NULL) return avlTreeAPI.Constructor(value);

  if(value < subtree->value)
    subtree->left = Add(subtree->left, value);
  else if(value > subtree->value)
    subtree->right = Add(subtree->right, value);
  else // No equal values
    return subtree;

  // Update height of this ancestor node
  subtree->height = 1 + Max(height(subtree->left), height(subtree->right));

  // Get the balance factor of this ancestor
  // node to check whether this node became unbalanced
  int balance = GetBalance(subtree);

  // If this node becomes unbalanced,
  // then there are 4 cases

  // Left Left Case
  if(balance > 1 && value < subtree->left->value)
    return RightRotate(subtree);

  // Right Right Case
  if(balance < -1 && value > subtree->right->value)
    return LeftRotate(subtree);

  // Left Right Case
  if(balance > 1 && value > subtree->left->value)
  {
    subtree->left = LeftRotate(subtree->left);
    return RightRotate(subtree);
  }

  // Right Left Case
  if(balance < -1 && value < subtree->right->value)
  {
    subtree->right = RightRotate(subtree->right);
    return LeftRotate(subtree);
  }

  // return the (unchanged) node pointer
  return subtree;
}

static avlTreeNode* Remove(avlTreeNode* subtree, int value)
{

}

static void Print(avlTreeNode* subtree)
{

}

// Preorder (Root, Left, Right)
char* ToStringPreorder(avlTreeNode* root, stringBuilder* stringBuilder)
{
  stringBuilderAPI.AppendInt(stringBuilder, root->value);
  stringBuilderAPI.AppendChars(stringBuilder, " ");

  if(root->left != NULL)
    ToStringPreorder(root->left, stringBuilder);

  if(root->right != NULL)
    ToStringPreorder(root->right, stringBuilder);

  return stringBuilder->string;
}

// Inorder (Left, Root, Right)
char* ToStringInorder(avlTreeNode* root, stringBuilder* stringBuilder)
{
  if(root->left != NULL)
    ToStringInorder(root->left, stringBuilder);

  stringBuilderAPI.AppendInt(stringBuilder, root->value);
  stringBuilderAPI.AppendChars(stringBuilder, " ");

  if(root->right != NULL)
    ToStringInorder(root->right, stringBuilder);

  return stringBuilder->string;
}

// Postorder (Left, Right, Root)
char* ToStringPostorder(avlTreeNode* root, stringBuilder* stringBuilder)
{
  if(root->left != NULL)
    ToStringPostorder(root->left, stringBuilder);

  if(root->right != NULL)
    ToStringPostorder(root->right, stringBuilder);

  stringBuilderAPI.AppendInt(stringBuilder, root->value);
  stringBuilderAPI.AppendChars(stringBuilder, " ");

  return stringBuilder->string;
}

static char* ToString(avlTreeNode* root, traversalType traversalType)
{
  switch(traversalType)
  {
    case preorder:
      return ToStringPreorder(root, stringBuilderAPI.Constructor());
      break;
    case inorder:
      return ToStringInorder(root, stringBuilderAPI.Constructor());
      break;
    case postorder:
      return ToStringPostorder(root, stringBuilderAPI.Constructor());
      break;
  }
  return "Provide a valid traversal type\n";
}

avlTreeNode* Constructor(int value)
{
  avlTreeNode* temporary = (avlTreeNode*)malloc(sizeof(avlTreeNode));

  temporary->left = NULL;
  temporary->right = NULL;
  temporary->value = value;
  temporary->height = 1;

  return temporary;
}

avlTreeAPIStruct const avlTreeAPI =
{
  Add,
  Remove,
  Print,
  ToString,
  Constructor
};
