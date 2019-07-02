#include "dbms2.hh"
#include <iostream>
#include <fstream>
#include <stdlib.h>
#include <cstring>

using namespace std; 
using namespace dbms2; 

namespace dbms2 
{
    /**
    * Loads a CSV file into the table 
    * Returns true when all of the rows in the file contain all required information
    * Returns false otherwise, or if the file could not be opened
    */
    bool AbstractDbTable::loadCSV(const char *infn){
        string temp;
        ifstream openFile(infn); // open the file
        if (!openFile.is_open()){ // if the file couldnt be opened, return false now!
            return false;
        }

        while (!openFile.eof()){
            movie * m = new movie(); // make a new movie to add for each row

            // assign each of the elements
            getline(openFile,temp,','); // get the line between where we are and the next ','
            if (temp.empty()) // if its empty, its an invalid row and we should return 
                return false;
            unsigned long idAdd = strtoul (temp.c_str(), NULL, 0); //cast the string to a long int 
            m->id= idAdd;

            //repeat process for remaining values 
            getline(openFile,temp,',');
            if (temp.empty())
                return false;
            strcpy(m->title, temp.c_str());

            getline(openFile,temp,',');
            if (temp.empty())
                return false;
            unsigned short year=(unsigned short) strtoul (temp.c_str(), NULL, 0);
            m->year= year;

            getline(openFile,temp,'\n');
            if (temp.empty())
                return false;
            strcpy(m->director, temp.c_str());

            //add the movie to the table
            add(*m);
            //Delete m so that we can re-create it next iteration (or not, if theres no more)
            delete m;
        }
        openFile.close();
        return true;
    }

    /**
    * Saves the current table to a CSV file.
    */
    bool AbstractDbTable::saveCSV(const char *outfn){
        ofstream writingFile(outfn, ofstream::trunc); //open the file
        
        if (writingFile.is_open()){ //check it was opened 
            writingFile.clear(); // clear anything that was in it previously
             const movie* m;

             for (int i =0; i<rows();i++){// go through all the rows
                m=get(i); //get the movie

                 if (m!=NULL){ // if it is not null, write it to the file
                     writingFile<< m->id <<','<<m->title<<','<<m->year<<','<<m->director <<'\n';
                 }
                 else{ // otherwise close and return false, must be an error
                    writingFile.close();
                    return false;
                 }
            }
            writingFile.close(); // close and return true since all were successful 
            return true;
        }
        return false; // file could not open. 
    }
}