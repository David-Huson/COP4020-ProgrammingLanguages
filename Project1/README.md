# Project 1 - Recursive-descent Parser

## Project Description

- You will implement this program in the C programming language.
- You must provide a makefile and your program must run on the ssh server in Linux.
- Your application must take one command-line argument, the name of the file to be checked.
- The file will contain a number of assignment statements.
    - Each assignment statement will be terminated by a semicolon (;). 
    - Each group of assignment statements must be delimited by the "begin"  and "end" reserved words with a dot (.) after the "end" token.
    - Indentations do not matter,
    - Multiple statements are permitted on a line
    - A statement may appear on multiple lines (with no continuation character).
- Finally, your program must include a capability to provide comments. Comments will be on a single line and they will start with a tilda:

>[!Note]
>In [part 2](https://github.com/David-Huson/COP4020-ProgrammingLanguages/tree/main/project2) of thie project, we will build an Intermediate representation for this grammar

`~ this is a comment`

You will parse the statements, keeping track of where you are in the string, and report whether or not the input program is legal. Your program will report either

- The program is legal: "success".
- Line `<integer>` contains error `<errormsg>` (missing ']', missing ')', expected assignment operator, expected operator, etc)

If all statements are legal, you must report all the identifiers that were used. Therefore, you will need at symbol table. Your symboltable can be implemented however you wish, but a hashtable is the logical choice. If the program is illegal, you do not need to list the identifiers.

You will implement both a **lexical analyzer** and a **parser**. These are clearly different functions and they should be implemented in different physical files. 

- The lexical analyzer will simply decide what comes next in the token stream and return it. 
- The parser will decide if the token is OK at that spot.

In your program, you will need to have an `int lookahead;` that always holds the next token.

The structure of **Number** and **Identifier**

You should detect whether or not a character string comprises an integer.

These are valid numbers: `123, 1234567, 456789, etc ...`
 

A legal <identifier> will start with a letter followed by combinations of letters, numbers, and underscores, subject to the following two rules:

1. You cannot have consecutive underscores
2. An identifier cannot end with an underscore.

These are valid identifiers:
     `e123, e, qwert5yuio, a_b_7`

These are not: `e__7, abc_,  7yght, _iuh`

Typical  Statements (legal and illegal)
```
a = b;
a=af+=
a=;
a_5 = 2;
6 = j;
a=d*
dd5=((3+5*8);
%iii=0
a=b2-(((x_yz + 99)* abc)*d);
qwerty=((6 - abcd)*(a + b));
 xyz = (9*8*7*6)/(a+b+c);

A legal program

~ a typical, minimal legal program
begin
  qwerty=((6 - ab_cd)*(a + b));
  xyz = (9*8*7765*6)/(a+b+c);
end
```
## Deliverables

1. A User's Manual "`UsersManual.docx`"
2. Your source code
3. A makefile
4. The eight programs provided with the assignment.
5. A script named "run" to execute all your programs (legal and illegal)

## Submission:  

1. Compile and run your program one last time before submitting it. Your program must compile with a makefile in the Linux lab and run with your script.
2. Place every file in your submission in a SINGLE DIRECTORY named <last name><firstInitial>. For instance, I would create directory:
     coffeyj.
3. zip that FOLDER into a .zip file with the SAME NAME. This means that inside your zip file, you will have exactly one folder (from the example: coffeyj) showing at the top level. Inside that folder will be ALL the files in your project.
4. DO NOT make separate folders for documentation and source files (or anything else) inside the main folder. Having such a setup simply necessitates more navigation time to get where we need to go to grade.
5. The script and input files should be in the top-level folder along with the source code.

So, this is how your submission should be structured (if your name were John Coffey) for this project:

coffeyj.zip

    coffeyj                // the folder holding all your files

        file1.h            // with the actual names of your files,

        file1.c            // of course ...

        ...

        UserManual.docx

        Makefile

        a1, a2, ... , a8   // the test programs to be compiled
        run                // the script to run your program eight times

6. MacOS users - remove the _MacOS_ utility folder before you zip up the file. If you cannot, delete it from the archive once the archive is created. It just takes up space and is not needed for anything we do with your submissions.
7. Login to UWF's Canvas system. Select our course.
8. Go to the appropriate assignment, choose your program file and click the "Upload Assignment" button.
9. Upload your file. Check to insure that the file was uploaded.
10. Be sure to review the university policy on academic dishonesty. This is an individual project

Please review the policy on ACADEMIC MISCONDUCT. This is an individual assignment.


