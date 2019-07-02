
#ifndef __VIEWBUFFER__
#define __VIEWBUFFER__

#include <iostream>
#include <cstring>

#define VIEWING_ROWS 25
#define VIEWING_COLS 80

namespace editor
{
class viewBuffer {

public:
    /**
     * loads a part of the main buffer into the viewing buffer (buffer) 
     * It is passed the viewing buffer, 
     * the row of the buffer from which it should be started 
     * as well as row of the buffer the loading should stop 
     * (not mentioned in the outline, but logical to have an end point)
     * 
     * starting from the row specified, the viewing buffer is filled character by character,
     * until it reaches the end, or the buffer is full (whatever occueres first)
     * 
     * The last space in the buffer on each row is not filled, this is to allow for line numbers to show/hide
     */
    void load(char **buffer, int row, int end);

    /**
     * Scrolls up the viewing buffer (buffer) by a given number of rows
     * Stats at the row passed, and moves it into the last viewable row,
     * moving every line above it down until it reaches the top of the buffer
     */
    void scrollUp(char **buffer, int rows);

  /**
     * Scrolls down the viewing buffer (buffer) by a given number of rows
     * Stats at the row passed, and moves it into the first viewable row,
     * moving every line above it up until it reaches the bottom of the buffer
     */
    void scrollDown(char **buffer, int rows);

    /**
     * Enables wrapping on the viewing buffer, this means that:
     * when the newline character is not encountered before the end of the current row,
     * sub- sequent text is copied to the next row.
     * 
     * 
     * The boolean passed, is the current wrap status, 
     * it is set to true at the start of this method as this indicates wrapped text, 
     * if it was already true, it simply returns without running the remaining method.
     * If it was false, the main buffer is referenced to see if any characters were disregarded when wrapping was disabled.
     * (this is to ensure no characters are lost)
     * ( call load again if necessary )
     * 
     * This is done by copying the viewing buffer into a temporary 2D array, and passed back, wrapped
     */  
    void enableWrapping (char **buffer,bool wrap);

    /**
     * Disables wrapping on the viewing buffer, this means that:
     * when the newline character is not encountered before the end of the current row
     * sub-sequent text is discarded until a new line character is encountered 
     * 
     * The boolean passed, is the current wrap status, 
     * it is set to false at the start of this method as this indicates non-wrapped text, 
     * if it was already false, it simply returns without running the remaining method.
     * 
     * This is done by copying the viewing buffer into a temporary 2D array, and passed back, not wrapped
     * 
     */  
    void disableWrapping (char **buffer, bool wrap);

    /**
     * Shows the line numbers, this is done by looping through the viewing buffer,
     *  and setting the last character of the buffer to the row number.
     * The last column is reserved for numbers in the loading stage
     */ 
    void showLineNum(char **buffer);

    /**
     * Hides the line numbers, this is done by looping through the viewing buffer,
     *  and setting the last character of the buffer to a null character.
     * The last column is reserved for numbers in the loading stage,
     *  and are simply hidden when this method is called
     */ 
    void hideLineNum(char **buffer);


protected:
char main_buffer[1000000];

};
} // namespace editor

#endif /* __EDITOR_HH__ */
