/**
 * myeditor.cc
 *
 * You must implement the member functions, including constructors, of your class defined in myeditor.hh.
 * Consult the assignment handout for the detailed specifications of each of the member functions.
 *
 * Student ID: 300444458
 * Name: Luisa Kristen
 */

#include "myeditor.hh"
#include "editor.hh"

#define VIEWING_COLS 11
#define VIEWING_ROWS 8

extern "C"
{
#include "editor.h"
}
namespace editor
{
/**
 *Replaces the character at the offset with the replacement char
 */
bool MyEditingBuffer::replace(char c, char replacement, int offset)
{
  for (int i = offset; i < BUFFER_LEN; i++)
  { // starts at the offset, goes until Buffer length
    if (buffer[i] == c)
    {
      buffer[i] = replacement;
      return true;
    }
  }
  return false;
}

/**
 * Replaces a string with another string from the position offset
 * A very similar method to editor_replace_str in editor.c
 */
int MyEditingBuffer::replace(std::string str, std::string replacement, int offset)
{
  int bigger; // checks which string is bigger, or if theyre the same
  if (sizeof(str) > sizeof(replacement))
  {
    bigger = 0;
  }
  else if (sizeof(str) < sizeof(replacement))
  {
    bigger = 1;
  }
  else
  {
    bigger = 2;
  } // checks which is bigger, str or replacement

  bool foundSTR = false;

  for (int i = offset; i < BUFFER_LEN; i++)
  { // starts at the offset, goes until Buffer length
    if (buffer[i] == str.at(0))
    {
      foundSTR = true;
      for (int j = 1; j < str.length(); j++)
      {
        if (buffer[i + j] != str.at(j))
        {
          foundSTR = false;
          break;
        }
      }

      if (foundSTR)
      { // found the string 'str'
        if (bigger == 2)
        { // str size the same as replacement size
          for (int k = 0; k < str.length(); k++)
          {
            if (i + k == BUFFER_LEN - 1)
            {
              return BUFFER_LEN - 1; // didnt make it to the end of the replacement, at the end of the buffer
            }
            buffer[i + k] = replacement.at(k); // replace the char
          }
          return i + str.length(); // return the last char
        }
        else if (bigger == 0)
        { // str bigger than the replacement
          int sizeDiff = str.length() - replacement.length();
          int k;
          for (k = 0; k < replacement.length(); k++)
          {
            buffer[i + k] = replacement.at(k); // replaces the string
          }
          i = i + k;
          for (int l = 0; l < sizeDiff; l++)
          {
            if (i + k == BUFFER_LEN - 1)
            {
              return BUFFER_LEN - 1;
            }
            for (int i = l; i < strlen(buffer); i++)
            {
              buffer[i] = buffer[i + 1]; // moves them all down one letter
            }
          }
          return i;
        }
        else if (bigger == 1)
        { // could be an else, but in case another option is introduced later, it is better to be clear
          int sizeDiff = str.length() - replacement.length();
          int k;
          for (k = 0; k < str.length(); k++)
          {
            buffer[i + k] = replacement.at(k); // replaces the string
          }
          i = i + k;
          for (int l = 0; l < sizeDiff; l++)
          {
            for (int j = i + l; i < strlen(buffer); j++)
            {
              buffer[j + 1] = buffer[j]; // moves them all up one
            }
            buffer[i + l] = replacement.at(l);
          }
        }
      }
    }
  }
  return -1; // couldnt find the replacement
}

/**
 * inserts a character into an array
 * Helper method for "justify"
 */
void MyEditingBuffer::insertChar(char *editing_buffer, char to_insert, int pos, int length)
{
  for (int i = length - 1; i > pos; i--)
  {                                            // starts at the end, and goes until it reaches the 'pos'
    editing_buffer[i] = editing_buffer[i - 1]; // sets the current one equal to the one before it.
  }
  editing_buffer[pos] = to_insert; //inserts the character into the position
}

/**
 * Justifies a viewing buffer
 * essentially adds white spaces in the middle of a row to avoid white spaces at the end
 */
void MyEditingBuffer::justify(char **viewingBuffer, int rows, int cols)
{
  char *ptr = *viewingBuffer;

  for (int row = 0; row < rows; row++)
  {
    if (*(ptr + row * cols) == '\0')
    { //check first element of the row, if it is \0, the whole row will be
      break;
    }
    else if (*(ptr + row * cols + cols - 2) == ' ') // a white space at the end of the row
    {
      int count = 3;
      int spaces = 1;
      while (*(ptr + row * cols + cols - count) == ' ')
      { //count the number of spaces at the end of the row
        count++;
        spaces++;
      }
      count = 0;
      int oldSpaces = spaces;

      while (spaces > 0)
      {
        if (*(ptr + row * cols + count) == ' ') // if the current one is a space, we can add another one!
        {
          char rowArray[cols];
          for (int i = 0; i < cols; i++)
          {
            rowArray[i] = *(ptr + row * cols + i); // make a 1D array of the row
          }

          insertChar(rowArray, ' ', count, cols);

          rowArray[cols - 1] = '\0'; // make the last char a null character again

          for (int i = 0; i < cols; i++)
          {
            *(ptr + row * cols + i) = rowArray[i]; // Set the Array back to the 2D array row.
          }

          count++;  //skip over the space just added
          spaces--; // one less white space to add
        }
        count++; //letter
        if (count == cols - 1)
        {
          if (oldSpaces == spaces)
          { // no spaces added in the row, no room or single word
            break;
          }
          count = 0; // set count back to 0 if not broken out of the loop;
        }
      }
    }
  }
}
}; // namespace editor
