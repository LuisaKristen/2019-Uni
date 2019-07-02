#include "editor2.hh"

using namespace std;

namespace editor2{
     
     int EditorUtilities::countWords(char *buffer, int BUFFERSIZE){
         int wordCount=0;
         bool charFound=false;
        for (int i=0; i<BUFFERSIZE; i++){
            if(isalpha(*(buffer+i))||isdigit(*(buffer+i))){ // checks if the letter is a digit or letter
                charFound=true; 
            }
            if (charFound && (isspace(*(buffer+i))||*(buffer+i)=='\t'||*(buffer+i)=='\n'|| *(buffer+i)== '\v'||*(buffer+i)=='\f'||*(buffer+i)=='\r')){ //if the last one was a letter and this is a "space", then count a word
                charFound=false;
                wordCount++;
            }
        }
        if (charFound){ // last word
         wordCount++;
        }
         return wordCount;
     }

     int EditorUtilities::searchMultipleNoCase(char *buffer,int BUFFERSIZE, std::string str, int *pos, int POSSIZE){
        int occurances=0;// occurances
        bool foundWord=false; // acts as a boolean
        int stringSize=str.length();
    
        const char *stp = str.c_str();

        for (int i=0;i<BUFFERSIZE;i++){
             foundWord=0;
          if (occurances<POSSIZE){ // still occurances left
          char bufferChar=toupper(*(buffer+i));

          char strChar=toupper(*stp);
             if (bufferChar==strChar){
                 foundWord=1;
                    for (int j=0; j<stringSize; j++){
                        bufferChar=toupper(*(buffer+i));
                        if (bufferChar!=strChar){
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
}