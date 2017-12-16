/*main.cpp*/

// Auto-complete search engine program using a binary search tree.


// ignore stdlib warnings if working in Visual Studio:
#define _CRT_SECURE_NO_WARNINGS

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <assert.h>
#include <ctype.h>
#include <stdio.h>

#include "bst.h"

//
// skipRestOfInput:
//
// Inputs and discards the remainder of the current line for the
// given input stream, including the EOL character(s).
//
void skipRestOfInput(FILE *stream)
{
  char restOfLine[256];
  int rolLength = sizeof(restOfLine) / sizeof(restOfLine[0]);

  fgets(restOfLine, rolLength, stream);
}

// getFileName: inputs a filename from the keyboard, make sure the file can be
// opened, and returns the filename if so.  If the file cannot be opened, an
// error message is output and the program is exited.
char *getFileName()
{
  char filename[512];
  int  fnsize = sizeof(filename) / sizeof(filename[0]);

  // input filename from the keyboard:
  fgets(filename, fnsize, stdin);
  filename[strcspn(filename, "\r\n")] = '\0';  // strip EOL char(s):

  // make sure filename exists and can be opened:
  FILE *infile = fopen(filename, "r");
  if (infile == NULL)
  {
    printf("**Error: unable to open '%s'\n\n", filename);
    exit(-1);
  }

  fclose(infile);

  // duplicate and return filename:
  char *s = (char *)malloc((strlen(filename) + 1) * sizeof(char));
  strcpy(s, filename);

  return s;
}


int main()
{
    char *filename;
    char  cmd[64];
    char  text[512];
    int   textsize = sizeof(text) / sizeof(text[0]);

    printf("** Starting Autocomplete **\n");

    filename = getFileName();
    BST* tree = BuildTree(filename);

    //
    // now interact with user:
    //

    printf("** Ready **\n");

    scanf("%s", cmd);

    while(strcmp(cmd, "exit") != 0)
    {
      if (strcmp(cmd, "stats") == 0)
      {
        int count = BSTCount(tree->Root);
        printf("**Tree count:  %d\n", count);
        int height = BSTHeight(tree);
        printf("**Tree Height: %d\n", height);
      }
      else if (strcmp(cmd, "add") == 0)
      {
          long long weight;
          char      part2[512];
          int       part2size = sizeof(part2) / sizeof(part2[0]);

      //
      // add weight text
      //
          scanf("%lld %s", &weight, text);
          fgets(part2, part2size, stdin);
          part2[strcspn(part2, "\r\n")] = '\0';  // strip EOL char(s):
          strcat(text, part2);

      //
      // TODO
      //
        BSTValue value;
        value.X = (char*) malloc((strlen(text) + 1) * sizeof(char));
        strcpy(value.X, text);
        value.Y = weight;

        if(BSTInsert(tree, value.X, value))
        {
            printf("**Added\n");
        }else{
        printf("**Not added...\n");
        }
    }
    else if (strcmp(cmd, "find") == 0)
    {
      char part2[512];
      int  part2size = sizeof(part2) / sizeof(part2[0]);

      //
      // find text
      //
      scanf("%s", text);
      fgets(part2, part2size, stdin);
      part2[strcspn(part2, "\r\n")] = '\0';  // strip EOL char(s):
      strcat(text, part2);

      //
      // TODO
      //
      BSTNode *returnNode = BSTSearch(tree, text);
      if(returnNode!=NULL)
      {
          //printf("** Found: \n");
          printf("%s: %lld\n", returnNode->Key, returnNode->Value.Y);
      }else{
            printf("**Not found...\n");
      }
    }
    else if (strcmp(cmd, "suggest") == 0)
    {
      int  k;
      char part2[512];
      int  part2size = sizeof(part2) / sizeof(part2[0]);

      //
      // suggest k text
      //
      scanf("%d %s", &k, text);
      fgets(part2, part2size, stdin);
      part2[strcspn(part2, "\r\n")] = '\0';  // strip EOL char(s):
      strcat(text, part2);

      //
      // TODO
      //

      //find first node that has the key
      BSTNode * SubtreeRoot = (BSTNode *)malloc(sizeof(BSTNode));

      SubtreeRoot = BSTSuggest(tree, text); //root of subtree
      int M = 0;
      BSTFindM(SubtreeRoot, text, &M, strlen(text));
      int numOfSuggestionMatches = M;
      if(M==0)
      {
          printf("**No suggestions...\n");
      }else{
      printf("** [Sub-tree root:  (%s", SubtreeRoot ->Value.X);
      printf(",%lld)]\n", SubtreeRoot ->Value.Y);
      printf("** [Sub-tree count: %d]\n", (BSTCount(SubtreeRoot )));
      printf("** [Num matches:    %d]\n", M);

      //now fill the values array:
      BSTValue * values = (BSTValue*) malloc(sizeof(BSTValue) * (M+1));
      BSTFillValues(SubtreeRoot, text, &M, strlen(text), values);

      //sort by weight:
      int i, j;
      for(i=1;i<=numOfSuggestionMatches;i++)
      {
          for(j = 1; j<=numOfSuggestionMatches; j++)
          {
              if(values[j].Y < values[i].Y)
              {
                  BSTValue *temp = (BSTValue*) malloc(sizeof(BSTValue));
                  *temp = values[j];
                  values[j] = values[i];
                  values[i] = *temp;
              }
          }
      }

      //sort by name if same weight:
      for(i=1;i<=numOfSuggestionMatches;i++)
      {
          for(j = 1; j<=numOfSuggestionMatches; j++)
          {
              if ((values[j].Y == values[i].Y) && (strcmp(values[j].X, values[i].X) > 0))
              {
                  //printf("\n same name: %s \n", values[j].Y);
                  BSTValue *temp = (BSTValue*) malloc(sizeof(BSTValue));
                  *temp = values[j];
                  values[j] = values[i];
                  values[i] = *temp;
              }
          }
      }
      int kk = 1;
      for(kk = 1; kk<=k; kk++)
      {
         if(values[kk].X == NULL)
         {
            break;
         }
          printf("%s: %lld\n", values[kk].X, values[kk].Y);
      }
//
//        int x = 1;
//        for(x=1;x<=numOfSuggestionMatches;x++)
//        {
//            printf("key: %s Y: %lld\n", values[x].X, values[x].Y);
//        }
      }
    }
    else
    {
      printf("**unknown cmd, try again...\n");
    }
    scanf("%s", cmd);
  }

  printf("** Done **\n");

  return 0;
}
