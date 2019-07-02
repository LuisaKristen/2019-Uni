#include "editor2.h"

 int editor_count_lines (char *buffer, int BUFFERSIZE){
     int counter=0; //number of lines
     for (int i=0; i<BUFFERSIZE; i++){
         if (*(buffer+i)=='\n'){
             counter++;
         }
     }
    return counter;
 }

  int editor_search_multiple (const char *buffer, int BUFFERSIZE, const char *word, int *pos , int  POSSIZE){
    int occurances=0;// occurances
    int letterUpTo=0; //letter up to in word
    int foundWord=0; // acts as a boolean

    int wordSize=0;
    while (*(word+wordSize)!='\0'){
        wordSize++;
    }
    wordSize++; // the string is one longer than the counter


    for (int i=0;i<BUFFERSIZE;i++){
        letterUpTo=0;
        foundWord=0;
        if (occurances<POSSIZE){ // still occurances left
            if (*(buffer+i)==*(word+letterUpTo)){
                foundWord=1;
                for (int j=0; j<wordSize; j++){
                    if (*(buffer+i+j)!=*(word+j)){
                        foundWord=0;
                        break;
                    }
                }
                *(pos+occurances)=i;
                occurances++;
            }
        }
    }
    return occurances;
  }

