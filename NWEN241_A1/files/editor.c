/**
* editor.c
*
* You must implement the functions in editor.h in this file.
* Consult the assignment handout for the detailed specifications of each of the functions.
*
* Student ID:300444458
* Name: Luisa Kristen
*/
#include "editor.h"
#include <stdio.h>
#include <string.h>

/**
*editor_insert_char inserts a single character into the editing buffer, at postition pos.
* All characters after the inserted one are moved one over (furter down the list)
*/
int editor_insert_char(char *editing_buffer, char to_insert, int pos)
{
  for (int i = EDITING_BUFLEN - 1; i > pos; i--)
  {                                            // starts at the end, and goes until it reaches the 'pos'
    editing_buffer[i] = editing_buffer[i - 1]; // sets the current one equal to the one before it.
  }
  editing_buffer[pos] = to_insert; //inserts the character into the position
  if (editing_buffer[pos] == to_insert)
  { // if the above code was succsessful, it will return 1
    return 1;
  }
  return 0;
}

/**
* editor_delete_char deletes the first occurence of the character, starting at position 'offset'
* all following characters are then moved down 1 space
*/
int editor_delete_char(char *editing_buffer, char to_delete, int offset)
{
  int found = 0; // an integer acting as a boolean, with either value 0 or 1
  char hold;
  if (offset < 0 || offset > EDITING_BUFLEN)
  {
    return 0;
  }
  for (int i = offset; i < EDITING_BUFLEN - 1; i++)
  {                           //starting at the offset, find the character you wish to delete
    hold = editing_buffer[i]; // save the current character
    if (editing_buffer[i] == to_delete)
    {            // if it is the one you want to delete
      found = 1; // set the 'boolean' to true, the character to delete has been found
    }
    else if (found == 1)
    {
      editing_buffer[i - 1] = hold; //put the one you saved in the spot before it.
    }
  }
  if (found == 1)
  {
    editing_buffer[EDITING_BUFLEN - 1] = '\0'; // make the last character a null character
    return 1;                                  // deletion succsessful
  }
  return 0;
}


/**
*editor_replace_str replaces the String 'str' with the string 'replacement'
*(the characters in the array corresponding to that string)
* from the given position, offset
*/
int editor_replace_str(char *editing_buffer, const char *str, const char *replacement, int offset)
{
  int occured = 0;
  int strLength = strlen(str);
  int repLength = strlen(replacement);

  for (int i = offset; i < EDITING_BUFLEN - 1; i++)
  {
    if (editing_buffer[i] == str[0])
    {
      occured = 1; // found the first letter of the string to replacae
      for (int j = 1; j < strLength; j++) //checks if the remainder of the string is there
      {
        if (editing_buffer[i + j] != str[j]) //if it is not the 'str' string, break.
        {
          occured = 0;
          break;
        }
      }
      if (occured == 1) // found the whole string to replace
      {
        if (strLength > repLength)
        { // str bigger than replace
          int sizeDiff = (strLength - repLength);
          int k;
          for (k = 0; k < repLength; k++)
          {
            editing_buffer[i + k] = replacement[k]; // insert replacement string
          }
          i = i + k;
          for (int l = 0; l < sizeDiff; l++)
          {
            editor_delete_char(editing_buffer, editing_buffer[i + l], i + l); // delete the remainging characters
          }
        }

        else if (strLength < repLength)
        { // replace bigger than str
          int sizeDiff = repLength - strLength;
          int k;
          for (k = 0; k < strLength; k++)
          {
            editing_buffer[i + k] = replacement[k];// replace the string 
          }

          for (int l = 0; l < sizeDiff; l++)
          {
            editor_insert_char(editing_buffer, replacement[i + l + k], i + l + k); //insert the extra characters
          }
        }
        else //same size
        {
          for (int k = 0; k < strLength; k++)
          {
            editing_buffer[i + k] = replacement[k]; // just need to replace them
          }
        }
        return 1;
      }
    }
  }
  return 0;
}

/**
*This method makes the editing buffer into a 2D viewing buffer, 
* with the words either being wrapped, or not
*/
void editor_view(char **viewing_buffer, const char *editing_buffer, int wrap)
{
  char *ptr = *viewing_buffer;
  for (int i = 0; i < VIEWING_ROWS; i++)
  { // makes them all null
    for (int j = 0; j < VIEWING_COLS; j++)
    {
      *(ptr + i * VIEWING_COLS + j) = '\0';
    }
  }

  int count = 0; //the current value of the editing buffer that we are on 
  for (int i = 0; i < VIEWING_ROWS; i++)
  {
    for (int j = 0; j < VIEWING_COLS; j++)
    {
      if (editing_buffer[count] == '\n') // if its a new line char, reset the cols, add one row, 
      {
        j = 0;
        i++;
        count++;
      }
      if (j == VIEWING_COLS - 1 && wrap == 0) // end of the row, not wrapping
      {
        while (editing_buffer[count] != '\n' && editing_buffer[count] != '\0') 
        {
          count++;// throw away chars until a new line or end is encountered
        }
      }
      if (editing_buffer[count] == '\n' && wrap != 0){
				j = -1; // a new line and wrapped
				i++;
			}
     if (j == VIEWING_COLS-1 && wrap != 0) // end of line and wrapped
      {
       break;
      }

     if (editing_buffer[count] != '\0')//not a null character
      { 
        *(ptr + i * VIEWING_COLS + j) = editing_buffer[count];
      }
      if (editing_buffer[count] == '\0') //is a null character, en 'else' would suffice, but makes it unclear
      {
        return;
      }
     if (count < EDITING_BUFLEN - 1) // not the end of the buffer
      {
        count++;
      }
      
    }
  }
}

