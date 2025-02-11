#include <limits.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "Simulatordata.h"


void startStack(struct Stack *stack)
{   //function to create stack
    stack->top= -1;//stack pointing top =-1
}

int stackFull(struct Stack *stack)//function to check if stack is full
{
    int ful = stack->top == STACK_SIZE -1; //checking condition
    int isFul;
    if(ful){
        isFul = 1;//if stack is full return 1
    }
        else{
            isFul = 0;//if not 0
        } 
    
    return isFul;
    }

int stackEmpty(struct Stack *stack)
{    //function to check if stack is empty
int  emp = stack ->top < 0;//checking condition
int isEmp;
if(emp)
{
    isEmp = 1;//if empty give 1 else 0
}
        else
        {
            isEmp = 0;
        }

return isEmp;
}

void pushStack(struct Stack *stack, int val)
{   //function to push a value into the stack
    if(stackFull(stack)){//first checking is stack is full
     
        printf("Stack overflow\n");//if stack is full 
        exit(1);  //exit if full
    }
    else
    {
        stack ->data[++stack -> top] = val;//if stack is not full then push a value
         
    }
}

int popStack(struct Stack *stack)//function to pop a variable from stack
{
    if(stackEmpty(stack))
    {
        //checking if stack is empty
        printf("Stack Underflow\n");//if empty say stack underflow
        exit(1);//exit out
    }
    else
    {
        return stack->data[stack->top--];//else pop a value thats on top
       
    }
}

int peekStack(struct Stack *stack){//to peek the top element of stack
    int peek;
    if(stackEmpty(stack)){
        printf("Stack is Empty\n");//see if empty
        return INT_MIN;
    }
    else{
         peek = stack ->data[stack -> top];//if not empty then peek for the value
             }
return peek;
}


unsigned int hash(int key)  // for hash
{
    return key % TABLE_SIZE;
}

Table *create() // for creating hash table
{
    Table *htable = (Table *) malloc(sizeof(Table));    // allocating memory
    for(int i = 0; i< TABLE_SIZE; i++)  // iterating based on table size
    {
        htable->table[i] = NULL;    
    }
    return htable;
}

void insert(Table *htable, int address, int value)  //function for inserting Address Value pair into hashtable
{
    unsigned int ind = hash(address);   
    AddressValue *new = (AddressValue *)malloc(sizeof(AddressValue)); // memory allocation
    new->address = address; // new address is address
    new->value=value;   // new value is value
    new->next=NULL; 
    if(htable->table[ind] == NULL)  
    {
        htable->table[ind]=new; 
    }
    else
    {
        AddressValue *curr = htable->table[ind];
        while(curr->next != NULL)
        {
            curr=curr->next;
        }
        curr->next=new;
    }
}

int retrieve(Table *htable, int address)    // to get the particular value fram a address
{
    unsigned int ind = hash(address);

    AddressValue *curr = htable->table[ind];
    while (curr != NULL) {  // if current element is not null
        if (curr->address == address) {
            return curr->value; // return
        }
        curr = curr->next;
    }

    return 0;
}

void changeValue(Table *htable,  int addr, int newVal)  // to change the value at a particular address
{
    unsigned int ind = hash(addr);

    AddressValue *curr = htable->table[ind];
    while (curr != NULL) {
        // compare address to the present address
        if (curr->address == addr) {
            // Update the value for the given key
            curr->value = newVal;
            return;
        }
        curr = curr->next;
    }
}

CacheNode* newCacheNode(char* dataEntered) // function to create node for queue operation
{
    CacheNode* tempVar=(CacheNode *)malloc(sizeof(CacheNode)); // allocation of memory
    tempVar->dataEntered=strdup(dataEntered); // copying entered variable
    tempVar->prev=tempVar->next=NULL;
    return tempVar;
}
 
CacheQueue* createCacheQueue(int VarCount) // function to create queue
{
    CacheQueue* cacheQueue = (CacheQueue *)malloc(sizeof(CacheQueue)); // allocating memory 
    cacheQueue->count = 0;
    cacheQueue->front = cacheQueue->rear = NULL;
    cacheQueue->VarCount = VarCount;
    return cacheQueue;
}
    
void printCacheQueue(CacheQueue* CacheQueue) // to print the queue contents
{
if (isCacheQueueEmpty(CacheQueue))  // checking if queue is empty
{
    printf("Cache Memory is Empty\n"); // prompting message if empty
    return;
}

    CacheNode* current = CacheQueue->front;
    printf("Cache Memory: "); 
    while (current != NULL) {
        printf("%s ", current->dataEntered); // printing
        current = current->next;
    }
    printf("\n");
}

int CacheMemoryFull(CacheQueue* CacheQueue) // to check if queue is full
{
    return CacheQueue->count == CacheQueue->VarCount;
}

int isCacheQueueEmpty(CacheQueue* CacheQueue) // to check if queue is empty
{
    return CacheQueue->rear == NULL;
}
 
void DeCacheQueue(CacheQueue* CacheQueue) // to remove variable from queue
{
    if( isCacheQueueEmpty(CacheQueue)) // checking if queue is empty
        return;
 
    if (CacheQueue->front == CacheQueue->rear)
        CacheQueue->front = NULL;
 
    CacheNode* dummy = CacheQueue->rear;
    CacheQueue->rear = CacheQueue->rear->prev;
 
    if (CacheQueue->rear)
        CacheQueue->rear->next = NULL;
    free(dummy->dataEntered);
    free(dummy);

    CacheQueue->count--;
}
 
int VariableThere(CacheQueue* CacheQueue, char* dataEntered) // checking if particular variable is precent
{
    CacheNode* reqData=CacheQueue->front;
    while(reqData != NULL)
    {
        if(strcmp(reqData->dataEntered,dataEntered)==0)
        {
            return 1;
        }
        else{
            reqData=reqData->next;
        }
    }
        return 0;
}
void EnCacheQueue(CacheQueue* CacheQueue,char* dataEntered) // for storing element into queue
{

    if (CacheMemoryFull (CacheQueue) || VariableThere(CacheQueue,dataEntered)) // checking condition
    {
        DeCacheQueue(CacheQueue); // deleting if condition satisfies
        printf("MSI State = INVALID as Variable is replaced\n"); // MSI state prompt
    }
 
    CacheNode* dummy = newCacheNode(dataEntered); // creating new node
    dummy->next = CacheQueue->front;
 
    if (isCacheQueueEmpty(CacheQueue)) // checking if cache is empty
        CacheQueue->rear = CacheQueue->front = dummy;
    else 
    {
        CacheQueue->front->prev = dummy;
        CacheQueue->front = dummy;
    }
    CacheQueue->count++;
    printf("MSI State = MODIFIED as Variable Loaded\n"); // MSI prompt
}

void CacheMemory(CacheQueue* CacheQueue, char* dataEntered) // function for LRU operation
{
    CacheNode* reqData = CacheQueue->front;
    while(reqData != NULL)
    {
        if(strcmp(reqData->dataEntered, dataEntered)==0)
        {
            if (reqData != CacheQueue->front)      
            {
                reqData->prev->next = reqData->next; // replacement
                if (reqData->next)
                {
                reqData->next->prev = reqData->prev;
                }
                if (reqData == CacheQueue->rear)
                {
                CacheQueue->rear = reqData->prev; // replacing with recently used variable
                CacheQueue->rear->next = NULL;
                printf("MSI State = SHARED\n"); // MSI prompt
                }
                reqData->next = CacheQueue->front;
                reqData->prev = NULL;
                reqData->next->prev = reqData;
                CacheQueue->front = reqData;
            
            }
            return;
        }
        reqData=reqData->next;
    }
EnCacheQueue(CacheQueue,dataEntered); // on condition disatisfy , entering variable to cache memory

}