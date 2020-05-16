#include <stdio.h>
#include <stdlib.h>
#include "avlTree.h"
#include "stringBuilder.h"

static avlTreeNode* Add(avlTreeNode* subtree, int value)
{
  if(subtree == NULL) return NULL;

  if(value == subtree->value) return subtree;

  if(value < subtree->value)
  {
    if(subtree->left == NULL)
    {
      subtree->left = (avlTreeNode*)malloc(sizeof(avlTreeNode));
      subtree->left->value = value;
      subtree->left->left = NULL;
      subtree->left->right = NULL;
    }
    else
    {
      return Add(subtree->left, value);
    }
  }
  else
  {
    if(subtree->right == NULL)
    {
      subtree->right = (avlTreeNode*)malloc(sizeof(avlTreeNode));
      subtree->right->value = value;
      subtree->right->left = NULL;
      subtree->right->right = NULL;
    }
    else
    {
      return Add(subtree->right, value);
    }
  }
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
