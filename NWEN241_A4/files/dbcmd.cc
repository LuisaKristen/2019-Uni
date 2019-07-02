#include <iostream>
#include "vdb.hh"
using namespace std;
using namespace dbms2;


/**
* To COMPILE:
* g++ dbcmd.cc dbms2.cc vdb.cc -o dbcmd
* Run with ./dbcmd PARAMETERS
*/
int main(int argc, char *argv[]) {
    //Makes a new table and loads the default csv file into it. 
    VectorDbTable * db = new VectorDbTable(); 
    db -> loadCSV("default.csv");

    string first(argv[1]); // should either be showall or show NUM
    if (first=="showall"){
        cout<<"Showing all rows:";
        for(int i=0;i<db->rows();i++){ // loop through all the rows
            cout<<'\n';
            db->show(i); // print out the movie
        }
        delete db;  // delete the table 
        return 1;
    }
    else if(first=="show"){
        if (argc>=3){ // have to have at least 3 arguments to show a row
            try{
                string second(argv[2]);
                int rowNum = std::stoi(second); // convert the string to an int 
                db->show(rowNum); // show just that row
                delete db;
                return 1;
            }
            catch(std::invalid_argument & ia){ // 2nd argument was not an int 
                 cout<<"Wrong type of argument";
            }
        }
        else {// less than three arguments 
            cout<<"Invalid number of arguments"; 
            delete db;
            return 0;
        }

    }
    else { // neither show or showall
        cout<<"Invalid first argument";
            delete db;
            return 0;
    }
}