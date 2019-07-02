#include "lldb.hh"
#include <iostream>

using namespace std; 
using namespace dbms2; 

namespace dbms2{
    /**
     * Creates a constructor:
     * Intialises the head of the linked list to null 
     */  
    LinkedListDbTable::LinkedListDbTable(){
        head=NULL;        
    }

    /**
     * Creates a destructor:
     * Deletes all the nodes. 
     */  
    LinkedListDbTable::~LinkedListDbTable(){
        node * counter=head;
        while (counter!=NULL){
            node * prev=counter;
            counter=counter->next;
            delete prev;
        }
    }
    /**
     * Rows returns the number of rows in the table.
     */
    int LinkedListDbTable::rows() const{
        int i = 0; 
        node * counter=head;
        while (counter!=NULL){ //Null means we have reached the end of the list
            i++; 
            counter=counter->next; // get the next node in the list
        }
        return i;
    }

     /**
     * Shows a given row in the table by printing out each value
     * If the row is invalid (<0 or >number of rows) it prints an error
     */
    bool LinkedListDbTable::show(int rowNum)const{
        if (rowNum>rows()-1 && rowNum<0){ // check it is a valid row
         cout << "Row cannot be found:" << rowNum << endl;
         return false;
        }

        int i = 0;
        node *counter=head;
        while (counter != NULL && i!=rowNum){ // find the "rowNum"th node in the list 
            i++;
            counter=counter->next;
        }
        if (counter == NULL) //Null means that rowNum is outside the list
            return false;

        // get the data and print it on the screen 

        movie m = counter->data;
        cout << "ID:" << m.id << endl;
        cout << "Title:" << m.title << endl;
        cout << "Director:" << m.director << endl;
        cout << "Year:" << m.year << endl;
        return true;
    }

    /**
    * Adds a record into the table. Returns a boolean if a record was sucessfully added.
    */
    bool LinkedListDbTable::add(movie m){
        if (head==NULL){ // The first record to add 
            // Initialise the head node, set the next one to null, and insert the movie
            head = new node(); 
            head->next = NULL;
            head->data=m;
            return true; //Successfull add
        }
        else{ // Not the first node in the list
            node * current = head; 
            while(current->next != NULL){ //Loop through until the end of the list
                current = current -> next;
            }
            //Same process as above, adding the movie to the last node. 
            current -> next = new node ();
            current = current -> next;
            current -> data = m;
            return true;
        }
        return true;
    }

    /**
    * Removes a record from the table, if it matches the given id.
    * Returns a boolean if a record was sucessfully added.
    */
    bool LinkedListDbTable::remove(unsigned long int id){
        node * counter=head;
        while (counter->next != NULL && counter->next->data.id != id){ //Find the matching id
            counter=counter->next; 
        }
        if (counter->next==NULL) //Could not find the matching id, return false
            return false;

        node *prev = counter;
        node *toRemove = counter->next; 
        counter = counter->next;
        node *next = counter->next; 

        // set the next one into the spot of the one to remove
        prev->next = next;
        delete toRemove; // delete the node we're removing 
        return true; 
    }

    /**
    * Returns a record from the table, if it matches the given row.
    * Returns a pointer to the movie structure.
    */
    const movie* LinkedListDbTable::get(int rowNum)const{
       if (rowNum<=rows()-1 && rowNum>=0){ // check it is a valid row
            int i = 0;
            node * counter=head;

            while (i!=rowNum){ // find the node in the list to get
                i++;
                counter=counter->next;
            }

            return &counter->data; //return the movie 
        }
        return NULL; //Not a valid row
     }
   
} //dbms2