#include "db.hh"
#include <iostream>
#include <fstream>
#include <stdlib.h>
#include <cstring>
#include <vector>

using namespace std; 
using namespace database; 

namespace database 
{
    movieDatabase::movieDatabase(){
        vec.reserve(50);
    }

    /**
     * Creates a constructor:
     * Intialises the vector 
     */  
    movieDatabase::~movieDatabase(){
        vec.clear();
    }
    /**
     * Rows returns the number of rows in the table.
     */
    int movieDatabase::rows(){
        return vec.size();
    }

     /**
     * Shows a given row in the table by printing out each value
     * If the row is invalid (<0 or >number of rows) it prints an error
     */
    bool movieDatabase::show(int rowNum){
        if (rowNum<=rows()-1 && rowNum>=0){ // check it is a valid row
        cout << "Title:" << vec[rowNum].title << endl;
        cout << "Director:" << vec[rowNum].director << endl;
        cout << "Year:" << vec[rowNum].year << endl;
        cout << "Location:" << vec[rowNum].location<<endl;
        cout << "Random:" << vec[rowNum].unknown << endl;

        return true;
    }
    cout << "Row cannot be found:" << rowNum << endl;
    return false; 
    }

    /**
    * Adds a record into the table. Returns a boolean if a record was sucessfully added.
    */
    bool movieDatabase::add(movie m){
        int size = rows();
        
        vec.push_back(m); // add the movie to the end of the vector
        if (rows()>size){
            return true; // added successfully
        }
        return false;// could not add the movie
    }

        /**
        * Gets a record from the table, given a particualr row
        * Returns a pointer to the movie structure.
        */
    const movie* movieDatabase::get(int rowNum){
       if (rowNum<=rows()-1 && rowNum>=0){ // check it is a valid row
            const movie * m=vec.data() + rowNum; 
            return m;
        }
        return NULL; // not a valid row. 
     }
   /**
    * Loads a CSV file into the table 
    * Returns true when all of the rows in the file contain all required information
    * Returns false otherwise, or if the file could not be opened
    */
    bool movieDatabase::loadCSV(){
        string temp;
        ifstream openFile("files/scifi.csv"); // open the file
        if (!openFile.is_open()){ // if the file couldnt be opened, return false now!
            return false;
        }

        while (!openFile.eof()){
            movie * m = new movie(); // make a new movie to add for each row

            // assign each of the elements
            getline(openFile,temp,','); // get the line between where we are and the next ','
            if (temp.empty()) // if its empty, its an invalid row and we should return 
                return false;
            strcpy(m->title, temp.c_str());

            getline(openFile,temp,',');
            if (temp.empty())
                return false;
            strcpy(m->director, temp.c_str());

            getline(openFile,temp,',');
            if (temp.empty())
                return false;
            unsigned short year=(unsigned short) strtoul (temp.c_str(), NULL, 0);
            m->year= year;

            //repeat process for remaining values 
            getline(openFile,temp,',');
            if (temp.empty())
                return false;
            unsigned short random = strtoul (temp.c_str(), NULL, 0); //cast the string to a long int 
            m->unknown= random;

            getline(openFile,temp,'\n');
            if (temp.empty())
                return false;
            strcpy(m->location, temp.c_str());



            //add the movie to the table
            add(*m);
            //Delete m so that we can re-create it next iteration (or not, if theres no more)
            delete m;
        }
        openFile.close();
        return true;
    }
}
    int main(){
        database::movieDatabase * d = new database::movieDatabase();

        d->loadCSV();
        d-> show(1);

        return 0;
    }


