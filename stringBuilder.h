#ifndef stringBuilderHeader
#define stringBuilderHeader

typedef struct stringBuilder {
  char* string;
  int length;
  int capacity;
  int maxCapacity;
} stringBuilder;

typedef struct stringBuilderAPIStruct {
  stringBuilder* (* const AppendChars)(stringBuilder *stringBuilder, char* value);
  stringBuilder* (* const AppendInt)(stringBuilder *stringBuilder, int value);
  stringBuilder* (* const Constructor)();
} stringBuilderAPIStruct;

stringBuilderAPIStruct const stringBuilderAPI;

#endif
