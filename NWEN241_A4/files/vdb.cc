#include "vdb.hh"
#include <iostream>
#include <vector>

using namespace std; 
using namespace dbms2; 

namespace dbms2{
    /**
     * Creates a constructor:
     * Intialises the vector 
     */  
    VectorDbTable::VectorDbTable(){
        vec.reserve(50);
    }

    /**
     * Creates a constructor:
     * Intialises the vector 
     */  
    VectorDbTable::~VectorDbTable(){
        vec.clear();
    }
    /**
     * Rows returns the number of rows in the table.
     */
    int VectorDbTable::rows() const{
        return vec.size();
    }

     /**
     * Shows a given row in the table by printing out each value
     * If the row is invalid (<0 or >number of rows) it prints an error
     */
    bool VectorDbTable::show(int rowNum)const{
        if (rowNum<=rows()-1 && rowNum>=0){ // check it is a valid row
        cout << "ID:" << vec[rowNum].id << endl;
        cout << "Title:" << vec[rowNum].title << endl;
        cout << "Director:" << vec[rowNum].director << endl;
        cout << "Year:" << vec[rowNum].year << endl;
        return true;
    }
    cout << "Row cannot be found:" << rowNum << endl;
    return false; 
    }

    /**
    * Adds a record into the table. Returns a boolean if a record was sucessfully added.
    */
    bool VectorDbTable::add(movie m){
        int size = rows();
        
        vec.push_back(m); // add the movie to the end of the vector
        if (rows()>size){
            return true; // added successfully
        }
        return false;// could not add the movie
    }

    /**
    * Removes a record from the table, if it matches the given id.
    * Returns a boolean if a record was sucessfully added.
    */
    bool VectorDbTable::remove(unsigned long int id){
        // check all the rows in the vector for a matching ID
        for (int i=0; i < rows() ; i++) { //checks all the row
            if (vec[i].id == id){  //if it is a matching id, remove this movie
                 vec.erase(vec.begin() + i);
                return true; // remove was successful
            }
         }  
         return false; // could not find the ID  
    }

        /**
        * Gets a record from the table, given a particualr row
        * Returns a pointer to the movie structure.
        */
     const movie* VectorDbTable::get(int rowNum)const{
       if (rowNum<=rows()-1 && rowNum>=0){ // check it is a valid row
            const movie * m=vec.data() + rowNum; 
            return m;
        }
        return NULL; // not a valid row. 
     }
   
} //dbms2