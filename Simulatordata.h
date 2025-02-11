#ifndef SIMULATORDATA_H
#define SIMULATORDATA_H
#define STACK_SIZE 1000 // defining size
#define MAX_SIZE 500
#define MEMORY_SIZE 100
#define TABLE_SIZE 100

int simulatorInstructionSet(char *FileName);
struct Stack    //initialisin the stack
{
    int data[STACK_SIZE];//initialising data
    int top;//initialising top of stack as integer
};
void startStack(struct Stack *stack); // for starting stack
int stackFull(struct Stack *stack); // to check if stack is full
int stackEmpty(struct Stack *stack); // to check if stack is empty
void pushStack(struct Stack *stack, int val); // to push into stack
int popStack(struct Stack *stack); // to pop into stack
int peekStack(struct Stack *stack); // to peek the top of stack

// hash table functions
typedef struct AddressValue // struct for hashtable pair
{
    int address;    // addresses as integer type
    int value;      // values in integer type
    struct AddressValue *next;
}AddressValue;

typedef struct Table    // defining a structure table
{
    AddressValue *table[TABLE_SIZE];    
}Table;
Table *create(); // to create table
unsigned int hash(int key); // for hashing
void insert(Table *htable, int address, int value); // to insert value at a adress in table
int retrieve(Table *htable, int address);   // to retrieve value from a particular address
void changeValue(Table *htable,  int addr, int newVal); // to change value at a address

typedef enum // enum for MSI state 
{
    Invalid = -1,
    Modified = 1,
    Shared = 0
} MSI_State;

typedef struct CacheNode // for node creation
{
    struct CacheNode *prev, *next;
    char* dataEntered;  // this is for containing the string or variable
} CacheNode;
 
typedef struct CacheQueue // for queue implementation
{
    unsigned count;  
    unsigned VarCount; // variable count initialisation
    CacheNode *front, *rear; // queue entities initialisation
} CacheQueue;

CacheNode* newCacheNode(char* dataEntered); // declaration for newNode creation
CacheQueue* createCacheQueue(int VarCount);// for creating cache queue
int CacheMemoryFull(CacheQueue* CacheQueue);// for checking memory status
int isCacheQueueEmpty(CacheQueue* CacheQueue);// for checking if queue is empty
void DeCacheQueue(CacheQueue* CacheQueue);// for deleting element
int VariableThere(CacheQueue* CacheQueue, char* dataEntered);// for checking if queue has that variable
void EnCacheQueue(CacheQueue* CacheQueue, char* dataEntered); // for inserting element
void CacheMemory(CacheQueue* CacheQueue, char* dataEntered);//LRU functionality
void printCacheQueue(CacheQueue* CacheQueue);// printing queue

#endif
