 /*!*************************************************************************
\file       FileStrings.cpp
\author     Anthony Miller
\par        DP email: anthony.m\@digipen.edu
\par        course: CS170
\par        section: A
\par        assignment: Assignment #4
\date       04/12/2019

\brief
    Various overloaded functions to manipulate a points data
    
  + UpperCase
    Converts a string to upper case
    
  + WordWrap
    Breaks a string up into multiple lines
    
  + Tokenize
    Breaks up a string into tokens
    
  + SpellChecker
    Constructor for the spellchecker class
    
  + GetInfo
    Get some general info about the dictionary
    
  + SpellCheck
    Check to see if a word is found in the dictionary or not
    
  + WordLengths
    Check how many words are under a given length in the dictionary
    
  + WordsStartingWith
    Find out how many words start with a given letter in the dictionary
    
  + AcronymToWord
    Look through a dictionary for words containing a passed in acronym
    
    Hours spent on this assignment: 4

  Specific portions that gave you the most trouble:The word wrap and acronym
  methods were what I found hardest. They both had a lot of edge cases to
  concider, so it took extra time.
**************************************************************************/

#include <fstream>        // ifstream
#include "FileStrings.h"  // SpellChecker, StringUtils, DictionaryInfo

namespace CS170
{ 
  /***********************************************************************/
  /*!
   \brief
    Converts a string to upper case
        
  \param string
    String to convert to upper case

  \return 
    String converted to upper case
  */
  /***********************************************************************/
  std::string& StringUtils::UpperCase(std::string& string)
  {
    std::string::iterator it;
    for (it = string.begin(); it != string.end(); ++it)
      if (*it >= 'a' && *it <= 'z')
        *it = static_cast<char>(*it - SPACE);

    return string;
  }
  
  /***********************************************************************/
  /*!
  \brief
    Breaks a string up into multiple lines
        
  \param words
    String to break up into multiple lines
    
  \param line_length
    Max length of a given line, 0 equals no max length

  \return 
    Vetor with strings up to the passed in line length
  */
  /***********************************************************************/
  std::vector<std::string> StringUtils::WordWrap
                           (const std::string& words, size_t line_length)
  {
    std::vector<std::string> holder;  // Hold each line of the passed in string
    std::string line;                 // String to collect words for the vector
    size_t start = 0;               // Begining position of a word in words
    size_t end = 0;                 // Ending position of a word in words
    
      // While there are still words left to find
    while (start < words.length())
    {
        // Find the next words end location
      end = words.find_first_of(' ', start);
      
        // Store the next word in a string
      std::string next = words.substr(start, end - start);
      
        // If the line + word is shorter than the max & there issomething to add
      if (line.length() + next.length() > line_length && line.length())
      {
          // Add the line to the end of the vector
        holder.push_back(line.substr(0, line.length() - 1));
          // Make the line empty to start adding words again
        line.clear();
      }
        // Append the next word to the line
      line += next + ' ';
        // Set the start of the next word to right after the last word
      start = end + 1;
      
        // if no position was returned
      if (end == std::string::npos)
      {
        start = words.length();  //set start to break the loop
      }
    }
    
      // If there is still something to add to the vector, add it
    if(line.length())
    {
      holder.push_back(line.substr(0, line.length() - 1));
    }
    
    return holder;
  }
  
  /***********************************************************************/
  /*!
   \brief
    Breaks up a string into tokens
        
  \param words
    String to be broken into tokens

  \return 
    Vector containing the passed in string broken into tokens
  */
  /***********************************************************************/
  std::vector<std::string> StringUtils::Tokenize(const std::string& words)
  {
    std::vector<std::string> holder;  // Vector to hold all the tokens
    unsigned start = 0;               // Start of the next token
    
      // Itterate through the passed in string
    for (unsigned i = 0 ; i < words.length(); ++i)
    {
        // If the char being ooked at is a space
      if(words.at(i) == ' ')
      {
          // If the char before the one we are looking at is not a space
        if (i > 0 && words.at(i - 1) != ' ')
        {
            // Add the word to the vector
          holder.push_back(words.substr(start, i - start));
        }
          // Set the start of the next token to be right after the space
        start = i + 1;
      }
    }
      // If the start is less than the length, there is still a token to push
    if (start < words.length())
      {
          // Add the remaining token to the vector
        holder.push_back(words.substr(start, words.length() - start));
      }
    return holder;
  }

  /***********************************************************************/
  /*!
   \brief
    Constructor for the spellchecker class
        
  \param dictionary
    Dictionary to use

  */
  /***********************************************************************/
  SpellChecker::SpellChecker(const std::string &dictionary)
  {
    //Constructor. A dictionary (filename) must be supplied. 
    dictionary_ = dictionary;
    
    
  }
  
  /***********************************************************************/
  /*!
   \brief
    Get some general info about the dictionary
        
  \param info
    Object to store info about the dictionary

  \return 
    If the file opened correctly or not
  */
  /***********************************************************************/
  SpellChecker::SCResult SpellChecker::GetInfo(DictionaryInfo &info) const
  {
    std::ifstream file(dictionary_.c_str());  // Open a dictionary file
    
      // Set initial values for the dictionary info
    info.shortest = static_cast<size_t>(-1);  // Largest number possible
    info.longest = 0;
    info.count = 0;
    
      // If the file didn't open, return an error
    if (!file.is_open())
    {
      return scrFILE_ERR_OPEN;
    }
    
    char holder[256];  // Buffer to hold an string from the file
    
      // While there is still stuff to read from the file
    while (file.getline(holder, 256))
    {
      std::string word(holder);  // String to hold the incoming line

        // If current word is longer than the longest so far
      if (word.length() > info.longest)
      {
        info.longest = word.length();  // Set the longest words length
      }
      
        // If current wordis shorted than the shortest so far
      if (word.length() < info.shortest)
      {
        info.shortest = word.length();  // Set the shortest words length
      }
      info.count++; // Increment the count of words in the dictionary
    }
    return scrFILE_OK;
  }
  
  /***********************************************************************/
  /*!
   \brief
    Check to see if a word is found in the dictionary or not
        
  \param word
    Word to check the spelling of

  \return 
    If the file opened correctly or not or if the word was found or not
  */
  /***********************************************************************/
  SpellChecker::SCResult SpellChecker::SpellCheck(const std::string& word) const
  {
    std::ifstream file(dictionary_.c_str());  // Open a dictionary file
    
      // If the file didn't open, return an error
    if (!file.is_open())
    {
      return scrFILE_ERR_OPEN;
    }
    
    char holder[256];         // Buffer to hold an string from the file
    std::string copy = word;  // Copy of the passed in word
    
      // While there is still stuff to read from the file
    while (file.getline(holder, 256))
    {
      std::string current(holder);  // String to hold the incoming line
      
        // Cast the current dictionary word to upper case
      StringUtils::UpperCase(current);
      
        // If the two words are the same
      if (current.compare(StringUtils::UpperCase(copy)) == 0)
      {
        return scrWORD_OK;
      }
      
        // If the dictionary word is past what we are looking for
      if (toupper(copy.at(0)) < current.at(0))
      {
        return scrWORD_BAD;
      }
    }
    return scrWORD_BAD;
  }
  
  /***********************************************************************/
  /*!
   \brief
    Check how many words are under a given length in the dictionary
        
  \param lengths
    A list of the words under the given length

  \param count
    The max length a word can be
    
  \return 
    If the file opened correctly or not
  */
  /***********************************************************************/
  SpellChecker::SCResult SpellChecker::WordLengths(std::vector<size_t>& lengths,
                                                   size_t count) const
  {
    std::ifstream file(dictionary_.c_str());  // Open a dictionary file

      // If the file didn't open, return an error
    if (!file.is_open())
    {
      return scrFILE_ERR_OPEN;
    }
    
    char holder[256];  // Buffer to hold an string from the file
    
      // While there is still stuff to read from the file
    while (file.getline(holder, 256))
    {
      std::string word(holder);  // String to hold the incoming line
      
        // If the word is not to long
      if (word.length() <= count)
      {
          // Increment the count for words that long
        ++lengths[word.length()];
      }
    }
    return scrFILE_OK;
  }
  
  /***********************************************************************/
  /*!
   \brief
    Find out how many words start with a given letter in the dictionary
        
  \param letter
    Letter for words to start with

  \param count
    How many letters start with the given word
    
  \return 
    If the file opened correctly or not
  */
  /***********************************************************************/
  SpellChecker::SCResult SpellChecker::WordsStartingWith
                          (char letter, int& count) const
  {
    std::ifstream file(dictionary_.c_str());  // Open a dictionary file
    
      // If the file didn't open, return an error
    if (!file.is_open())
    {
      return scrFILE_ERR_OPEN;
    }
    
    char holder[256];  // Buffer to hold an string from the file
    
      // While there is still stuff to read from the file
    while (file.getline(holder, 256))
    {
      std::string word(holder);  // String to hold the incoming line
      
        // If the first letter of the word is what we are looking for
      if (toupper(word.at(0)) == toupper(letter))
      {
        ++count;  // Increment count
      }
      
        // Otherwise if the word is past the letter we are looking for
      else if (toupper(word.at(0)) > toupper(letter))
      {
        return scrFILE_OK; // Return early
      }
    }
    return scrFILE_OK;
  }
  
  /***********************************************************************/
  /*!
   \brief
    Look through a dictionary for words containing a passed in acronym
        
  \param acronym
    String containing letters of an acronym to look for

  \param words
    Vector to store words containing the passed in acronym
  
  \param maxlen
    Max length of words to look for. 0 is no max length
    
  \return 
    If the file opened correctly or not
  */
  /***********************************************************************/
  SpellChecker::SCResult SpellChecker::AcronymToWord(const std::string& acronym,
                          std::vector<std::string>& words, size_t maxlen) const
  {
     std::ifstream file(dictionary_.c_str());  // Open a dictionary file
    
      // If the file didn't open, return an error
    if (!file.is_open())
    {
      return scrFILE_ERR_OPEN;
    }
    
    std::string test(acronym);  // Copy of the acronym string to manipulate
    char holder[256];           // Buffer to hold an string from the file
    
      // Convert the test string to upper case
    StringUtils::UpperCase(test);
    
      // While there is still stuff to read from the file
    while (file.getline(holder, 256))
    {
      std::string word(holder);  // String to hold the incoming line
      
        // Convert the string from the file to upper case
      StringUtils::UpperCase(word);

        // If the read in word is past what we are looking for
      if (test.at(0) < word.at(0))
      {
          // Exit early
        return scrFILE_OK;
      }
      
        // If length is winthin the length and starts with the correct letter
      if ((word.length() <= maxlen || maxlen == 0) && test.at(0) == word.at(0))
      {
        unsigned i = 1;    // Loop variable
        size_t pos = 1;  // Starting position of acronym letter
        
          // While we have not reached the end of the acronym
        while (i < test.length())
        {
            // Find the position of the next letter of the acronym in the word
          pos = word.find_first_of(test.at(i), pos);

            // If the next letter of the acronym was not found
          if (pos == std::string::npos)
          {
            break;
          }
          
            //increment the loop counter and position
          ++i;
          ++pos;
        }
        
          // You got through the word and found all the letters in the acronym
        if (pos != std::string::npos)
        {
            // Add the word to the vector
          words.push_back(holder);
        }
      }
    }
    return scrFILE_OK;
  }
}
