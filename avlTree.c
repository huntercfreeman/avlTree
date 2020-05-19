#include <stdio.h>
#include <stdlib.h>
#include "avlTree.h"
#include "stringBuilder.h"

static avlTreeNode* MinValueNode(avlTreeNode* subtree)
{
  avlTreeNode* current = subtree;

  /* loop down to find the leftmost leaf */
  while(current->left != NULL)
    current = current->left;

  return current;
}

static int height(avlTreeNode* N)
{
  if(N == NULL)
    return 0;
  return N->height;
}

static int GetBalance(avlTreeNode* N)
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
  else
    return subtree;

  subtree->height = 1 + Max(height(subtree->left), height(subtree->right));

  int balance = GetBalance(subtree);

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
  if(subtree == NULL) return NULL;

  if(value < subtree->value)
    subtree->left = Remove(subtree->left, value);

  else if(value > subtree->value)
    subtree->right = Remove(subtree->right, value);

  else
  {
    if( (subtree->left == NULL) || (subtree->right == NULL) )
    {
      avlTreeNode* temporary = subtree->left ? subtree->left :
                                                subtree->right;
      if(temporary == NULL)
      {
        temporary = subtree;
        subtree = NULL;
      }
      else
        *subtree = *temporary;

      free(temporary);
    }
    else
    {
      avlTreeNode* temporary = MinValueNode(subtree->right);

      subtree->value = temporary->value;

      subtree->right = Remove(subtree->right, temporary->value);
    }
  }

  if(subtree == NULL)
    return subtree;

  subtree->height = 1 + Max(height(subtree->left), height(subtree->right));

  int balance = GetBalance(subtree);

  // Left Left case
  if(balance > 1 && GetBalance(subtree->left) >= 0)
    return RightRotate(subtree);

  // Left Right case
  if(balance > 1 && GetBalance(subtree->left) < 0)
  {
    subtree->left = LeftRotate(subtree->left);
    return RightRotate(subtree);
  }

  // Right Right Case
  if(balance < -1 && GetBalance(subtree->right) <= 0)
    return LeftRotate(subtree);

  // Right Left Case
  if(balance < -1 && GetBalance(subtree->right) > 0)
  {
    subtree->right = RightRotate(subtree->right);
    return LeftRotate(subtree);
  }

  return subtree;
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
