#include <stdlib.h>
#include <stdio.h>
#include "avlTree.h"

void Dump(avlTreeNode* temporary)
{
  printf("%s\n", avlTreeAPI.ToString(temporary, preorder));
  printf("%s\n", avlTreeAPI.ToString(temporary, inorder));
  printf("%s\n", avlTreeAPI.ToString(temporary, postorder));
}

int main()
{
  avlTreeNode* temporaryOne = avlTreeAPI.Constructor(5);
  Dump(temporaryOne);

  temporaryOne = avlTreeAPI.Add(temporaryOne, 10);
  Dump(temporaryOne);

  temporaryOne = avlTreeAPI.Add(temporaryOne, 2);
  Dump(temporaryOne);

  avlTreeNode* temporaryTwo = avlTreeAPI.Constructor(1);
  temporaryTwo = avlTreeAPI.Add(temporaryTwo, 2);
  temporaryTwo = avlTreeAPI.Add(temporaryTwo, 3);
  temporaryTwo = avlTreeAPI.Add(temporaryTwo, 4);
  temporaryTwo = avlTreeAPI.Add(temporaryTwo, 5);
  temporaryTwo = avlTreeAPI.Add(temporaryTwo, 6);
  temporaryTwo = avlTreeAPI.Add(temporaryTwo, 7);
  temporaryTwo = avlTreeAPI.Add(temporaryTwo, 8);
  temporaryTwo = avlTreeAPI.Add(temporaryTwo, 9);
  temporaryTwo = avlTreeAPI.Add(temporaryTwo, 10);
  temporaryTwo = avlTreeAPI.Add(temporaryTwo, 11);
  Dump(temporaryTwo);
}
