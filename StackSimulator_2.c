#include <limits.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include<sys/wait.h>
#include <string.h>
#include "Simulatordata.h"


char LineWord[MAX_SIZE][100];   // CacheArray for storing the command words of instruction set 
char NextWord[MAX_SIZE][100];   // CacheArray for storing the arguments of instruction set
int count;                      // to track the line count
int memoryBUS[MEMORY_SIZE];     // Initialised memory BUS
    int eql=0;  
int store;                                              
int GlobalSegment = 0;          // Global Segment flag for .data 
int textSegment = 0;            // text Segment flag for .text
Table *htable;
CacheQueue* Cache_Memory;
// CacheQueue* MSI_State;

// function is to read the lines of the input file taking filename, Lineword, Nextword CacheArrays as arguments 
// this is to store the data of the file into these CacheArrays
int lineRead(char *filename, char LineWord[MAX_SIZE][100], char NextWord[MAX_SIZE][100])
{
    FILE *file = fopen(filename, "r"); // open a file  

    if (file == NULL)   // check if the file is opening
    {
        perror("Error opening file");
        return -1;
    }

    char line[100]; // variable to read line by line
    int count = 0;  // to track the line count

    while (fgets(line, sizeof(line), file) != NULL)
    {
        // scan each line and store first word in one CacheArray, and rest in others
        int scan = sscanf(line, "%s %[^\n]", LineWord[count], NextWord[count]);
        count++;

        if (count >= MAX_SIZE) // Check if the CacheArray is full
        {
            printf("Maximum number of instructions reached\n");
            break;
        }
    }

    fclose(file);   //close file
    return count;   // now our file content is in CacheArrays
}

int simulatorInstructionSet(char *FileName){
    htable = create();
    Cache_Memory = createCacheQueue(3);
    // MSI_State = createCacheQueue(3);
    count = lineRead(FileName, LineWord, NextWord); // calling function to read file and store data in respective CacheArrays
    if (count == -1)    // if no lines
    {
        return 1; // Error occurred
    }

    // Below lines will print the Arrays that store the instruction set
    //As it is not required for the output, it's commented
    // for (int i = 0; i < count; i++) {
    //     printf("%s\t%s\n", LineWord[i], NextWord[i]);
    // }

    struct Stack stack; // initialising a stack
    startStack(&stack); // starting stack


    int i = 0;
    while(i<count)  
    {
        if (strcmp(LineWord[i], "show") == 0)
        {
            // operation if first word is show
            // print the corresponding data in NewxtWord
            printf("%s\n", NextWord[i]);
                    
        }

        else if(strcmp(LineWord[i], "push")==0)
        {
            //operation if first word is push
            int digit = atoi(NextWord[i]);
            pushStack(&stack, atoi(NextWord[i]));//pushing the second value
            // CacheMemory( Cache_Memory, CacheStorage, digit);
            
        }

        else if(strcmp(LineWord[i], "pop")==0)
        {
            //operation if first word is pop
            int popped =  popStack(&stack);//popping the top value from stack
           // printf("peeked after pop %d", popped);
        }

        else if(strcmp(LineWord[i], "+")==0)
        {
            //operation if first word is '+'
            int a = popStack(&stack);   // pop element 1
            int b = popStack(&stack);   // pop element 2
            if(stackEmpty(&stack))  // if stack is empty
            {
            pushStack(&stack, a);   
            pushStack(&stack, b);
            int c = a+b;    // perform operation
            pushStack(&stack, c);   // and push result into stack
        printf("\nSum is : %d", peekStack(&stack));
        }

        else
        {   // if stack not empty
            int c = popStack(&stack);// pop element
            c = b + (a*32*8);//adding the elements (for 32 bit integer, therefore (32*8)=256, 8 for 1 bit)
            // that is manipulate address
            pushStack(&stack, c);//push updated temp
        }
    }

    else if (strcmp(LineWord[i], "-" )==0)//operation if first word is '-'
    {
        int b = popStack(&stack);   // pop elements
        int a = popStack(&stack);
       
        if(stackEmpty(&stack))
        {   // if stack empty
            int Difference = a - b; // perform operation
        // printf("\nDiff is : %d\n", Difference);
        pushStack(&stack, Difference);
        }
        else{
            int c = popStack(&stack);// pop element
            c = a - (b*32*8);//perform operation that is manipulate address
            pushStack(&stack, c);
        }
        
    }

        else if (strcmp(LineWord[i], "/") == 0)//operation if first word is '/'
    {
        int a = popStack(&stack);//pop elemets
        int b = popStack(&stack);
        int div = b / a;//perform operation
        pushStack(&stack, div);//push the result back
        // printf("%d", div);
    }

    else if (strcmp(LineWord[i], "<") == 0)
        // operation if first word is '<'
    {
        int a = popStack(&stack); //pop elements
        int b = popStack(&stack);
        pushStack(&stack, a);
        pushStack(&stack, b);
        if (b < a)
        {
            //perform operation
            pushStack(&stack, 1);//push back
        }
        else
        {
            pushStack(&stack, 0);
        }
    }
    else if (strcmp(LineWord[i], ">") == 0)//operation if first word is '>'
    {
        int a = popStack(&stack); // pop elements
        int b = popStack(&stack);   
        pushStack(&stack, a);
        pushStack(&stack, b);
        if (b > a)//perform operation
        {
            pushStack(&stack, 1); // push 0, if condition satisfy
        }
        else
        {
            pushStack(&stack, 0); // push 0, if condition satisfy  
        }
    }

    else if (strcmp(LineWord[i], "=") == 0)
    //operation if first word is '='
    {
        int a = popStack(&stack); // pop elements
        int b = popStack(&stack);
        pushStack(&stack, a);
        pushStack(&stack, b);
        if (b == a) // perform operation
        {
            pushStack(&stack, 1);//push result back
        }
        else
        {
            pushStack(&stack, 0);
        }
    }

    else if (strcmp(LineWord[i], "&") == 0)//operation if first word is '&'
    {
        int a = popStack(&stack);//pop elements
        int b = popStack(&stack);
        pushStack(&stack, a);
        pushStack(&stack, b);
        int c = b && a;//perform operation
        pushStack(&stack, c);//push element back
    }
    
    else if (strcmp(LineWord[i], "|") == 0)//operation if first word is '|'
    {
        int a = popStack(&stack);//pop elements
        int b = popStack(&stack);
        pushStack(&stack, a);
        pushStack(&stack, b);
        int c = b || a;//perform operation
        pushStack(&stack, c);//push elements to stack
    }
    else if (strcmp(LineWord[i], "!") == 0)//operation if first word is '!'
    {
        int a = popStack(&stack);//pop element
        pushStack(&stack, a);
        pushStack(&stack, !a);//push result
    }

    else if (strcmp(LineWord[i], "div") == 0)//operation if first word is 'div'
    {
        int a = popStack(&stack);//pop elements
        int b = popStack(&stack);
        pushStack(&stack, a);
        pushStack(&stack, b);

        int division = b % a;//perform operation
        pushStack(&stack, division);//push back
    }

     else if (strcmp(LineWord[i], "<>") == 0)//operation if first word is '<>'
    {
        int a = popStack(&stack);//pop
        int b = popStack(&stack);//pop
        pushStack(&stack, a);
        pushStack(&stack, b);
        if (a == b)//check condition
        {
            pushStack(&stack, 0);
        }
        else
        {
            pushStack(&stack, 1);
        }
    }
    else if (strcmp(LineWord[i], "<=") == 0)//operation if first word is '<='
    {
        int a = popStack(&stack);//pop elements
        int b = popStack(&stack);
        pushStack(&stack, a);
        pushStack(&stack, b);
        if (b <= a)//perform operation
        {
            pushStack(&stack, 1);//push back result
        }
        else
        {
            pushStack(&stack, 0);
        }
    }
    else if (strcmp(LineWord[i], ">=") == 0)//operation if first word is '>='
    {
        int a = popStack(&stack);//pop element
        int b = popStack(&stack);
        pushStack(&stack, a);
        pushStack(&stack, b);
        if (b >= a)//perform operation
        {
            pushStack(&stack, 1);
        }
        else
        {
            pushStack(&stack, 0);
        }
    }

    else if(strcmp(LineWord[i], "halt")==0)//operation if first word is halt
    {
        return 0;//the reading lines , the execution stops of simulator
    }

    else if(strcmp(LineWord[i], "copy")==0)//operation if first word is copy
    {
        int cpy = peekStack(&stack);//the top element is copied
        pushStack(&stack, cpy);//and again pushed back
    }

    else if(strcmp(LineWord[i], "print")==0)// operation if first word is print
    {
        int prt = peekStack(&stack);//see the top element and print it
        printf("%d\n", prt);//print statement
    
    }

    else if(strcmp(LineWord[i], "goto")==0) // if first word is goto
    {
        int j = 0;  // taking another variable for looping into CacheArrays again
        while(j<count) // loop until line count is greater than the index
        {
            if(strcmp(LineWord[j], "label")==0) // now within this, check if first word is label
            {
                if(strcmp(NextWord[j], NextWord[i])==0) // if it is label, 
                // then check if secondword of goto and label are same
                {
                    i=j;    // if they match then make the actual index i same to this line index
                    break;
                }
            }
            j++;
        }
    }

    else if(strcmp(LineWord[i], "call")==0) // if first word is call
    {
        store=i;    // to keep track of the index store it
        int j=0;    // repeat the process
        while(j<count)
        {
            if(strcmp(LineWord[j], "label")==0)
            {
                if(strcmp(NextWord[j], NextWord[i])==0)
                {
                    i=j;
                    break;
                }
            }
            j++;
        }
    }

    else if(strcmp(LineWord[i], "label")==0)
    {
        // i+1;
    }

    else if(strcmp(LineWord[i], "gotrue")==0)   // if first word is gotrue
    {
        int jump = popStack(&stack); // popstack
        if(jump != 1)
        {
            //jump if 1
            continue;
        }
    }

    else if(strcmp(LineWord[i], "gofalse")==0)  // if firstword is gofalse
    {
        int jump = popStack(&stack);//popstack
        if(jump != 0){//jump if 0
            continue;
        }
    }

   else if(strcmp(LineWord[i], "return")==0)    // if return
   {
    i=store + 1;
   }
   else if(strcmp(LineWord[i], "begin")==0) // if begin
   {
    int j=0;
    while(j<count)
    {
        if(strcmp(LineWord[j], "end") != 0) // need to run until end
        {
        break;
        }
    j++;
    }
   }
   else if(strcmp(LineWord[i], "end")==0) // if end stop the previous and contimue
   {
    continue;
   }

    else if(strcmp(LineWord[i], ".data")==0)    // if .data
    {
        GlobalSegment = 1;  // make globalsegment flag 1
        int global=0;
        memoryBUS[global] = atoi(NextWord[global+1]); // store the integer that can be accessed globally
    }

    else if(strcmp(LineWord[i], ".int")==0)
    {   
        // the characters converted to integers
        memoryBUS[i]  = atoi(NextWord[i]);  // And stored in memory locations
    }

    else if(strcmp(LineWord[i], ".text")==0)    // if .text
    {
        textSegment = 1;    // make textsegment flag 1
        
    }
    else if(strcmp(LineWord[i], "rvalue")==0)   // if rvalue
    {
        char* Variable = NextWord[i];
        int *address = (int*)NextWord[i];   // check the adress of the argument
        int retrievedVal = retrieve(htable, *address);  // get value from hashtable at that argument
        pushStack(&stack, retrievedVal);   // and push it into stack
        
        // this is when a variable is accessed
        CacheMemory( Cache_Memory, Variable); // storing variable in cache memory
        printCacheQueue(Cache_Memory); // printing the cache memory after storing the variable
    }

    else if(strcmp(LineWord[i], "lvalue")==0)   // if lavalue
    {
        char* Variable = NextWord[i];
        // printf("%s\n", Variable);
        int *address = (int*)NextWord[i];   // take address of the adjacent word
        memoryBUS[eql] = *address;  // store in bus. memory
        eql++;
        pushStack(&stack, (int) *address);//push address of word into stack   
        CacheMemory(Cache_Memory, Variable); // Storing the variable in the cache memory
        printCacheQueue(Cache_Memory);      // printing the cache memory after storing the variable
    }

        else if(strcmp(LineWord[i], ":&")==0)   // on this
        {
            int temp = peekStack(&stack); // check if the address is present in stack
        }

    else if(strcmp(LineWord[i], ":=")==0)   // on this
    {
      
      int a = popStack(&stack);   
        //pop first element which is value
        // then pop second which is address
      int b = popStack(&stack);
        if(stackEmpty(&stack))
        {
        insert(htable, b, a);   // if stack is not empty
        // then insert that value to that particular location
        }
        else
        {
            int c = popStack(&stack);// else pop another address
            changeValue(htable, c, a);// and change the value at that address 
            // this is after manipulation of address
        }
    }
    i++;    // update i        
    }
    
}

int main(int argc, char *argv[])
{
    char *FileName = argv[1];   // reveiving file name, given in console, via argv
    
    pid_t processID; // Creating process ID 
    processID = fork(); // forking to create two individual process that is two cores
    if(processID > 0) // core 2 creation
    {
        int condition;
        wait(&condition); // waiting for enabling synchrinization
        printf("\n\nProcess in Core 2 Done\n");
        simulatorInstructionSet(FileName);// performing operation in core
        printCacheQueue(Cache_Memory);//final cache at end
        exit(0);
    }
    else if(processID == 0) // core 1 creation
    {
        printf("Process in Core 1 Done\n");
        simulatorInstructionSet(FileName);// performing operation in core
        printCacheQueue(Cache_Memory);// final cache at end
        exit(0);
    }
    else
    {
        perror("Process Invalid\n"); // If process not created
        return -1;
    }
    wait(NULL); // waiting for synchronization
    printf("Both process executed");
    return 0;
}