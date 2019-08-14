# Author: Chyler Morrison
# All content © 2018 DigiPen (USA) Corporation, all rights reserved.

* After the program runs, there will be a file named "CodeCount.csv" that will
  contain the code count for all source files in your project, broken up by author.

Contents:
* cloc.bat - THIS IS WHAT YOU WANT TO RUN!!!
           - Runs the provided ClocByAuthor program
           - To properly set this script up for your repository, you need to modify
             the script by replacing "[path]" with the *relative* path from this
             directory to the directory of your source code. Given the example
             project file structure below, the relative path would be "../src/".

        Example file structure
        root
         |- src
         |   |-*.c
         |   |-*.h
         |
         |-scripts
              |-cloc.bat
              |-cloc.exe
              |-ClocByAuthor.exe
              |-README.txt

* cloc.exe - This is the "Count Lines Of Code" program that does the heavy lifting
             of counting how many lines of code, comments, and blank lines you've
             written.

* ClocByAuthor.exe - This is the program that will parse through your source code
                     and extract the different authors of each file to be counted
                     individually.

Usage:
* After setting the path in cloc.bat as described above, all that is needed to do
  to generate the line counts is to run the cloc.bat file everytime you need to
  update the line count, which can be done by double-clicking the file. This
  will generate CSV files in the same directory as these CLOC files.
