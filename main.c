/*main.cpp*/

// Auto-complete search engine program using a binary search tree.

//Sean Walker

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
    int fnsize = sizeof(filename) / sizeof(filename[0]);

    // input filename from the keyboard:
    fgets(filename, fnsize, stdin);
    filename[strcspn(filename, "\r\n")] = '\0'; // strip EOL char(s):

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

void doShowStats(BST *tree)
{
    int count = BSTCount(tree->Root);
    printf("**Tree count:  %d\n", count);
    int height = BSTHeight(tree);
    printf("**Tree Height: %d\n", height);
}

void doAdd(BST *tree, char *text)
{
    long long weight;
    char part2[512];
    int part2size = sizeof(part2) / sizeof(part2[0]);

    //
    // add weight text
    //
    scanf("%lld %s", &weight, text);
    fgets(part2, part2size, stdin);
    part2[strcspn(part2, "\r\n")] = '\0'; // strip EOL char(s):
    strcat(text, part2);

    //
    // TODO
    //
    BSTValue value;
    value.X = (char *)malloc((strlen(text) + 1) * sizeof(char));
    strcpy(value.X, text);
    value.Y = weight;

    if (BSTInsert(tree, value.X, value))
    {
        printf("**Added\n");
    }
    else
    {
        printf("**Not added...\n");
    }
}

void doFind(BST *tree, char *text)
{
    char part2[512];
    int part2size = sizeof(part2) / sizeof(part2[0]);

    // find text
    scanf("%s", text);
    fgets(part2, part2size, stdin);
    part2[strcspn(part2, "\r\n")] = '\0'; // strip EOL char(s):
    strcat(text, part2);

    BSTNode *returnNode = BSTSearch(tree, text);
    if (returnNode != NULL)
    {
        //printf("** Found: \n");
        printf("%s: %lld\n", returnNode->Key, returnNode->Value.Y);
    }
    else
    {
        printf("**Not found...\n");
    }
}

void Sort(BSTValue *array, int sizeOfArray)
{
    int smallest;
    int i = 0;

    for (i = 0; i < sizeOfArray - 1; ++i)
    {

        smallest = i; // assume the first unsorted is the smaller:

        for (int j = i + 1; j < sizeOfArray; ++j) // look for a smaller one:
        {
            if (array[j].Y > array[smallest].Y) // smaller!
                smallest = j;
            else if (array[j].Y == array[smallest].Y) // same, so use Netid:
            {
                if (array[j].X > array[smallest].X) // smaller!
                    smallest = j;
            }
        }

        if (smallest != i) //swap:
        {
            BSTValue T = array[i];
            array[i] = array[smallest];
            array[smallest] = T;
        }
    } //for
} //Sort()

//************************************************************
//BSTSuggest()
// search the tree to return the node that contains a matching key:
//************************************************************
BSTNode *BSTSuggest(BST *tree, BSTKey key)
{
    BSTNode *cur = tree->Root;
    int size = strlen(key);
    while (cur != NULL)
    {
        if (strncmp(cur->Key, key, size) == 0) // found!
            return cur;
        else if (strncmp(cur->Key, key, size) > 0) // smaller, go left:
        {
            cur = cur->Left;
        }
        else // larger, go right:
        {
            cur = cur->Right;
        }
    }
    // if we get here, we traversed the entire tree and didn't find the suggestion starting, so:
    return NULL;
}

//function to find the number of nodes (M) that contain the same query prefix
//arguments:
// root: the root of the tree to search
// key: the prefix of the key we're searching for
// M: an integer to keep track of how many are found
// size: integer value that's the length of the prefix used in strncmp to only compare the length of the prefix with the key of the node being checked

/*void BSTFindMatches(BSTNode * root, char key[512], int sizeOfPrefix, int * numberOfMatches, BSTValue * values)
{
    if (root == NULL)  // base case: empty tree
        return;
    else  // recursive case: non-empty tree
    {
        BSTFindMatches(root->Left, key, &numberOfMatches, sizeOfPrefix, values);
        BSTFindMatches(root->Right, key, &numberOfMatches, sizeOfPrefix, values);
        if(strncmp(root->Key, key, sizeOfPrefix)==0) //found a node in the tree who's key starts with the prefix
        {
          values[*numberOfMatches] = root->Value;
          *numberOfMatches = *numberOfMatches + 1;
        }
    }
}*/

//this function collects all of the BSTValues in an array of BSTValues (values) from nodes that have the same prefix in the key.
//arguments:
//root of tree to search
//the key
//number Of Nodes With Prefix used for the array index to insert at. this is decremented each recursive call to move the the next array index

//
//recursive helper function:
//
void _CollectMatches(BSTNode *traverseTree, char key[512], int *numberOfNodesWithPrefix, int size, BSTValue *suggestions)
{
    if (traverseTree == NULL) // base case: empty tree
        return;
    else // recursive case: non-empty tree
    {
        if (strncmp(traverseTree->Key, key, size) == 0)
        {
            suggestions[*numberOfNodesWithPrefix] = traverseTree->Value;
            *numberOfNodesWithPrefix = *numberOfNodesWithPrefix + 1;
        }
        _CollectMatches(traverseTree->Left, key, numberOfNodesWithPrefix, size, suggestions);
        _CollectMatches(traverseTree->Right, key, numberOfNodesWithPrefix, size, suggestions);
    }
}

BSTValue *CollectMatches(BSTNode *traverse, char key[512], int *numberOfNodesWithPrefix, int size)
{
    BSTValue *suggestions = (BSTValue *)malloc(sizeof(BSTValue) * *numberOfNodesWithPrefix); //make array to store suggestions
    _CollectMatches(traverse, key, numberOfNodesWithPrefix, size, suggestions);              //recursive helper function
    return suggestions;
} //end CollectMatchesInValuesArray()

//print function used as function pointer in BSTPrintInOrder() function
void pf(BSTNode *cur)
{
    printf("%s\n", cur->Key);
    return;
}

//handles suggest command
//example: if the user enteres...
//suggest 5 Chi
//this means they want to see the be suggested the top 5 weighted queries that start with "Chi"
void doSuggest(BST *tree, char *text)
{
    int k; //number of results user wants to see for given query prefix (in the above example, this number is 5)

    // suggest k prefix
    scanf("%d %s", &k, text); //scanf again to get k and the prefix (in the above example, the prefix is "Chi")

    //find first node in the tree that has the key
    BSTNode *SubtreeRoot = (BSTNode *)malloc(sizeof(BSTNode));

    SubtreeRoot = BSTSuggest(tree, text); //find the first node in the tree who's key starts with the user entered prefix

    //now collect all of the suggestions in the values array:
    int numberOfMatches = 0;
    BSTValue *suggestions = CollectMatches(SubtreeRoot, text, &numberOfMatches, strlen(text));

    if (numberOfMatches == 0)
    {
        printf("**No suggestions...\n");
    }
    else
    {
        printf("** [Sub-tree root:  (%s", SubtreeRoot->Value.X);
        printf(",%lld)]\n", SubtreeRoot->Value.Y);
        printf("** [Sub-tree count: %d]\n", (BSTCount(SubtreeRoot)));
        printf("** [Num matches:    %d]\n", numberOfMatches);

        Sort(suggestions, numberOfMatches);

        //print k (ammount user entered) suggestions tree
        int x;
        for (x = 0; x < k; x++)
            printf("%s\n", suggestions[x]);
    }
} //end doSuggest()

int main()
{
    char *filename;
    char cmd[64];
    char text[512];

    printf("** Starting Autocomplete **\n");
    printf("Please enter a file name: \n cities.txt \n cities-by-population.txt \n fortune1000.txt \n fortune1000-by-revenue.txt \n");

    filename = getFileName();
    BST *tree = BuildTree(filename);

    //
    // now interact with user:
    //

    printf("** Ready **\n");

    scanf("%s", cmd);

    while (strcmp(cmd, "exit") != 0)
    {
        if (strcmp(cmd, "stats") == 0)
        {
            doShowStats(tree);
        }
        else if (strcmp(cmd, "add") == 0)
        {
            doAdd(tree, text);
        }
        else if (strcmp(cmd, "find") == 0)
        {
            doFind(tree, text);
        }
        else if (strcmp(cmd, "suggest") == 0)
        {
            doSuggest(tree, text);
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
