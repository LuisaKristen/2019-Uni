namespace dbms2 
{
    struct movie {
        unsigned long id;
        char title[50];
        unsigned short year;
        char director[50];
    };

    class AbstractDbTable{

        public:
        /**
        * A pure virtual function that when implemented will 
        * return the number of rows in the table.
        * Pure virtual due to the keyword virtual and = 0
        * Cannot modify any member variables due to keyword const
        */
        virtual int rows() const = 0;

        /**
        * A pure virtual function that when implemented will
        * print out all of the fields in the row specified
        * by the parameter.  Returns a boolean indicating if the record number exists.
        * Pure virtual due to the keyword virtual and = 0
        * Cannot modify any member variables due to keyword const
        */
        virtual bool show(int rowNum) const = 0;

        /**
        * A pure virtual function that when implemented will
        * add a record into the table. Returns a boolean if a record was sucessfully added.
        * Pure virtual due to the keyword virtual and = 0
        */
        virtual bool add(movie m) = 0;

        /**
        * A pure virtual function that when implemented will
        * remove a record from the table, if it matches the given id.
        * Returns a boolean if a record was sucessfully added.
        * Pure virtual due to the keyword virtual and = 0
        */
        virtual bool remove(unsigned long int id) = 0;


        /**
        * A pure virtual function that when implemented will
        * get a record from the table, given a particualr row
        * Returns a pointer to the movie structure.
        * Pure virtual due to the keyword virtual and = 0
        * Cannot modify any member variables due to keyword const
        */
        virtual const movie* get(int row) const = 0;

        /**
        * Loads a CSV file into the table when implemented
        * Returns true when all of the rows in the file contain all required information
        * Returns false otherwise, or if the file could not be opened
        */
        bool loadCSV(const char *infn);

        /**
        * Saves the current table to a CSV file.
        */
        bool saveCSV(const char *outfn);
    };
} // dbms2
