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
  avlTreeNode* temporary = avlTreeAPI.Constructor(5);
  Dump(temporary);

  temporary = avlTreeAPI.Add(temporary, 10);
  Dump(temporary);

  temporary = avlTreeAPI.Add(temporary, 2);
  Dump(temporary);
}
