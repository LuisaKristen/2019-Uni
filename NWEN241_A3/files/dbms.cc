#include "dbms.hh"
#include <iostream>

using namespace std; 
using namespace dbms; 

namespace dbms
{
    /**
     * Creates a constructor:
     * Sets rows used to 0; 
     * allocates 5 rows in total,
     * and intialises the table using calloc
     */  
DbTable::DbTable(){
    rowsUsed=0;
    rowsTotal=5;
    table=(struct album *) calloc (rowsTotal, sizeof(struct album));
}

/**
 * Destructor, deletes the table
 */ 
DbTable::~DbTable(){
 delete table;
}

/**
 * Prints out the information for a given row (passed in)
 * As long as the row is a valid row.
 * Returns true if the record exists, and false otherwise 
 */
bool DbTable::show(unsigned int row){
    if (row<=rows()-1 && row>=0){ // check it is a valid row
        cout << "ID:" << table[row].id << endl;
        cout << "Title:" << table[row].title << endl;
        cout << "Artist:" << table[row].artist << endl;
        cout << "Year:" << table[row].year << endl;
        return true;
    }
    cout << "Row cannot be found:" << row << endl;
    return false; 
}

/**
 *  Adds a record to the table
 *  Checks if the title or artist is null, in which case it does not add it, and returns false
 *  Otherwise, it adds the record, possibly increasing the size of the table if required, and returns true. 
 */
bool DbTable::add(album A){
    //No artist or title, so it should not add the row 
    if (A.title[0]=='\0' || A.artist[0]=='\0'){return false;}

    // room to add it without addind space, so just add and increment the row
    if (rows()<allocated()){
        table[rows()]=A;
        rowsIncrement();
    }
    //no space to add it as is, have to increase space
    else if (rows() == allocated()){
        // create a new table, with 5 more size than the last
        album* newTable=(album*) calloc (allocated()+5, sizeof(struct album));
        for (int i=0; i< rows(); i++){ // copy the content over from the old table
            *(newTable+i) = *(table+i);
        }
        delete table; 
        table=newTable; // set the new table to the old table

        allocatedIncrement(); // update the size variable 
        table[rows()]=A; // now we can add the row
        rowsIncrement(); 
    }

    if (rows() == allocated()){ // could not allocate more memory
        return false;
    }

    return true;
}

/**
 * Deletes the first instance of the ID, 
 * only the first instance as the id should be unique, and the handout specifies 
 * "Removes a record" meaning, a single record.
 * 
 * Returns true if it deleted the ID, and false if there is no matching ID
 */ 
bool DbTable::remove(unsigned long int id){
    // check all the rows in the table for a matching ID
    for (int i=0; i < allocated() ; i++) {
        if (table[i].id == id){ 

            //Delete the row by moving each line down one
            for (int j=i; j<allocated();j++){
             table[j]=table[j+1];
            }
            rowsDecrement(); // decrement the number of rows allocated

            // if there are 5 or more free rows, delete the last 5
            if ((allocated()-rows() >=5)){
                //make a new table, 5 smaller than the original table
                album* newTable=(album*) calloc (allocated()-5, sizeof(struct album));
                  for (int k=0; k< rows(); k++){ // copy each of the elements over
                    *(newTable+k) = *(table+k);
                }
                delete table;
                table=newTable; // and set the new table equal to the original one 

                allocatedDecrement(); // update the variable for size allocated
            }
            return true; // replacement successful
        }
    }  
    return false; // could not find the ID
}

} // dbms
