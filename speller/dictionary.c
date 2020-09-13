// Implements a dictionary's functionality

#include <stdio.h>
#include <string.h>
#include <stdbool.h>
#include <stdlib.h>


#include "dictionary.h"

// Represents a node in a hash table
typedef struct node
{
    char word[LENGTH + 1];
    struct node *next;
}
node;

// Number of buckets in hash table
const unsigned int N = 1;

// Number of word in dictionary
unsigned int DIC_COUNT=0;

// Hash table
node *table[N];

// Returns true if word is in dictionary else false
bool check(const char *word)
{
    // TODO
    unsigned int index = hash(word);
    node *tmp=table[index];
    while(tmp !=NULL)
    {
        if(strncmp(tmp->word, word ,LENGTH) == 0)
        {
             return true;
        }
        else
        {
           tmp=tmp->next;
        }
    }

    return false;
}

// Hashes word to a number
unsigned int hash(const char *word)
{
    unsigned int length = strnlen(word,LENGTH);
    unsigned int Hash_Value = 0;
    for(unsigned int i = 0 ; i < length;i++ )
    {
        Hash_Value += word[i];
        Hash_Value = ( Hash_Value * word[i] )%N;

    }
    return Hash_Value;
}

// Loads dictionary into memory, returning true if successful else false
bool load(const char *dictionary)
{
    // TODO
    FILE *fptr=fopen(dictionary,'r');
    if(fptr==NULL)
    {
        fprintf(stderr,"Coulden't open %S .\n",dictionary);
        return false;
    }

    char buffer[LENGTH+1];

    while(fscanf(fptr,%s,buffer) != EOF)
    {

      node *tmp=malloc(sizeof(node));
      strncpy(tmp->word,buffer,sizeof(buffer));

      int index = hash(buffer);

      if(table[index]==NULL)
      {
          table[index]=tmp;
      }
      else
      {
          tmp->next=table[index];
          table[index]=tmp;
      }
      DIC_COUNT++;
    }
    fclose(fptr);
    return true;
}

// Returns number of words in dictionary if loaded else 0 if not yet loaded
unsigned int size(void)
{
    // TODO
    return DIC_COUNT;
}

//destroy node
void destroy(node *head)
{
    if (head->next != NULL)
    {
        destroy(head->next);
    }
    free(head);
}

// Unloads dictionary from memory, returning true if successful else false
bool unload(void)
{
    // TODO
    for(unsigned int i =0 ;i<N;++i)
    {
        if(table[i] != NULL)
        {
            destroy(table[i]);
        }

    }

    return true;

}