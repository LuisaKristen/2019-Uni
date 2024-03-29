#include "dbms2.hh"
#include <iostream>
#include <vector>


using namespace std; 
using namespace dbms2; 

namespace dbms2{
    class VectorDbTable : public AbstractDbTable{
        private:
        vector <movie> vec;
        
        public:
        VectorDbTable(); // constructor
        ~VectorDbTable(); // destructor


        /**
        * A pure virtual function that when implemented will 
        * return the number of rows in the table.
        * Pure virtual due to the keyword virtual and = 0
        * Cannot modify any member variables due to keyword const
        */
        virtual int rows() const;

        /**
        * A pure virtual function that when implemented will
        * print out all of the fields in the row specified
        * by the parameter.  Returns a boolean indicating if the record number exists.
        * Pure virtual due to the keyword virtual and = 0
        * Cannot modify any member variables due to keyword const
        */
        virtual bool show(int rowNum) const;

        /**
        * A pure virtual function that when implemented will
        * add a record into the table. Returns a boolean if a record was sucessfully added.
        * Pure virtual due to the keyword virtual and = 0
        */
        virtual bool add(movie m);

        /**
        * A pure virtual function that when implemented will
        * remove a record from the table, if it matches the given id.
        * Returns a boolean if a record was sucessfully added.
        * Pure virtual due to the keyword virtual and = 0
        */
        virtual bool remove(unsigned long int id);


        /**
        * A pure virtual function that when implemented will
        * get a record from the table, given a particualr row
        * Returns a pointer to the movie structure.
        * Pure virtual due to the keyword virtual and = 0
        * Cannot modify any member variables due to keyword const
        */
        virtual const movie* get(int row)const;
    };
} //dbms2