#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "stringBuilder.h"

static stringBuilder* AppendChars(stringBuilder *stringBuilder, char* value)
{
  if(stringBuilder->capacity == 0) stringBuilder->capacity = 16;
  if(stringBuilder->string == NULL) stringBuilder->string = (char*)malloc(sizeof(char) * stringBuilder->capacity);

  int argumentLength = strlen(value);
  int remainingSpace = stringBuilder->capacity - stringBuilder->length - 1;

  int capacityChanged = 0;

  while(remainingSpace - argumentLength < 0)
  {
    capacityChanged = 1;

    stringBuilder->capacity *= 2;

    remainingSpace = stringBuilder->capacity - stringBuilder->length - 1;
  }

  if(capacityChanged)
  {
    stringBuilder->string = (char*)realloc(stringBuilder->string, stringBuilder->capacity);
  }

  snprintf(stringBuilder->string + stringBuilder->length, remainingSpace + stringBuilder->length, "%s", value);
  stringBuilder->length += argumentLength;

  return stringBuilder;
}

static stringBuilder* AppendInt(stringBuilder *stringBuilder, int value)
{
  if(stringBuilder->capacity == 0) stringBuilder->capacity = 16;
  if(stringBuilder->string == NULL) stringBuilder->string = (char*)malloc(sizeof(char) * stringBuilder->capacity);

  int argumentLength = snprintf(NULL, 0,"%d", value);

  int remainingSpace = stringBuilder->capacity - stringBuilder->length - 1;

  int capacityChanged = 0;

  while(remainingSpace - argumentLength < 0)
  {
    capacityChanged = 1;

    stringBuilder->capacity *= 2;

    remainingSpace = stringBuilder->capacity - stringBuilder->length - 1;
  }

  if(capacityChanged)
  {
    stringBuilder->string = (char*)realloc(stringBuilder->string, stringBuilder->capacity);
  }

  snprintf(stringBuilder->string + stringBuilder->length, remainingSpace + stringBuilder->length, "%d", value);
  stringBuilder->length += argumentLength;

  return stringBuilder; 
}

static stringBuilder* Constructor()
{
  stringBuilder* stringBuilder = malloc(sizeof(stringBuilder));

  stringBuilder->capacity = 16;
  stringBuilder->string = (char*)malloc(sizeof(char) * stringBuilder->capacity);

  return stringBuilder;
}

stringBuilderAPIStruct const stringBuilderAPI = {AppendChars, AppendInt, Constructor};
