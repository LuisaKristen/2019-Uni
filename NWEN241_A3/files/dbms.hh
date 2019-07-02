namespace dbms
{

    /**
     * Structure "Album"
     * Creates an instance of a row in the dynamically allocated table
     * Each variable is a column
     */ 
    struct album
    {
        unsigned long id;
        char title [100];
        unsigned short year ;
        char artist [100];
    };

    /**
     * Creates an instance of a table
     * Contains a pointer to a table, integers for rowsTotal and rowsUsed
     * And public methods for a constructor, and two getters, returning the rowsTotal and rowsUsed
     */ 
    class DbTable{
        private:
        album *table;
        unsigned int rowsTotal;
        unsigned int rowsUsed;

        public:
        DbTable(); // constructor
        ~DbTable(); // destructor
        bool show(unsigned int); 
        bool add(album);
        bool remove(unsigned long int);

        /**
         * Simple methods for incrementing and decrementing 
         * both the number of rows used, and the total number of allocated rows, 
         * as well as returning both of these values 
         */ 
        inline int rows(){return rowsUsed;}
        inline int allocated(){return rowsTotal;}
        inline void rowsIncrement(){rowsUsed++;}
        inline void rowsDecrement(){rowsUsed--;}
        inline void allocatedIncrement(){rowsTotal+=5;}
        inline void allocatedDecrement(){rowsTotal-=5;}

    };
} // dbms
