#include <iostream>
#include <vector>

namespace database{
    using namespace std;

     struct movie {
        char title [50];
        char director[50];
        char location[50];
        unsigned short year;
        unsigned short unknown;
    };

    class movieDatabase{
         public:
        vector <movie> vec;
        movieDatabase(); // constructor
        ~movieDatabase(); // destructor

        int rows();
        bool show(int rowNum);
        bool add(movie m);
        bool remove(unsigned long int id);
        const movie* get(int row);
        bool loadCSV();
        bool saveCSV(const char *outfn);
    };
} //database