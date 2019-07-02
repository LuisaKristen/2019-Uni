/**
 * editor2.hh
 */

#ifndef __EDITOR_HH2__
#define __EDITOR_HH2__

#include <iostream>

namespace editor2
{
    class EditorUtilities {
       
       public:
         static int countWords(char *buffer, int BUFFERSIZE);
         static int searchMultipleNoCase(char buffer [] ,int BUFFERSIZE, std::string str, int *pp, int POSSIZE);
    };
} // namespace editor2

#endif /* __EDITOR2_HH__ */
