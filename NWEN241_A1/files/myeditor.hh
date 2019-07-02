/**
 * myeditor.hh
 *
 * You must define a class that extends the EditingBuffer class in this file.
 * Consult the assignment handout for more information.
 *
 * Student ID: 300444458
 * Name: Luisa Kristen
 */
#include "editor.hh"

namespace editor
{
class MyEditingBuffer : public EditingBuffer //extends the editing buffer
{

public:
  // function prototypes

  /**
   *Replaces the character at the offset with the replacement char
   */
  bool replace(char c, char replacement, int offset);

  /**
   * Replaces a string with another string from the position offset
   * A very similar method to editor_replace_str in editor.c
   */
  int replace(std::string str, std::string replacement, int offset);

 /**
  * Justifies a viewing buffer
  * essentially adds white spaces in the middle of a row to avoid white spaces at the end
  */
  void justify(char **viewingBuffer, int rows, int cols);

 /**
  * inserts a character into an array
  * Helper method for "justify"
  */
  void insertChar(char *editing_buffer, char to_insert, int pos, int length);
};
} // namespace editor
