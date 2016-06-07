/*****************************************************************************************
Void main () -> this will be marked as entry point of the application and the 
main will be called by someone else. 
[Ques.]Now who calls the main?
[Ans.]The exe code itself calls the main means your code itself calls the main 
but we never write that code 
[Ques.] who writes that code? 
[Ans.]C++ Compiler will inject this code and that will call the main. 
[Ques.] What is that code? 
[Ans.]That code is mainCRTStartUp() also called as stub code.
*/

//>>>>>How main is called

/* kernel32.dll - Windows OS calls
	mainCRTStartup() ;
*/

/* C++ Compiler will inject this code
void mainCRTStartUp() // Stub Code
{
	//Before main gets called Global Variables are created
	main();
}
*****************************************************************************************/

//>>>> Let's Start COM
//----------------------

/*--------------------------------------|
|                                       |
|************* DESIGN 1 ****************|
|       SINGLE INSTANCE DESIGN          |
|--------------------------------------*/

#if 0

int items[100]; // global (single instance)
int top = 0; // global (single instance)

/*
Push has accepted the value. What it will do after accepting the value? 
It has to store it somewhere in such a way that it keeps track of the 
Last one. So we'll create an array "items".
*/

/*
We have made array item global. Anything global only gets created once. 
We can call it single instance.

Ok. So we'll store it in the array, but where in the array. So we’ll 
create another variable and well call it “top” So
top = 0
that too global hence single instance.
*/


void Push(int item)
{
	items[top] = item;
	top++;
}
/*
Problem with Push => parameter fixed as int
*/

int Pop()
{
	top--;
	return items[top];
}
/*
Problem with Pop => return type is fixed as int
*/

//-----------------------------------------------------

#include <stdio.h>
void main()
{
	//Set 1 - push
	Push(100);	//Pushing 100
	Push(200);	//Pushing 200
	Push(300);

	//All the above Push goes in 1 stack. What if someone wants to push in different way

	//Set 2 - push
	Push(1000);	//Pushing 100
	Push(2000);	//Pushing 200
	Push(3000);


	int item = Pop();
	printf("%d\n", item);
	//printf("%d\n", item);
	//Problem...?  
	// we should call pop 2 or 3 times depending on how many value we want to see
	item = Pop();
	printf("%d\n", item);

	item = Pop();
	printf("%d\n", item);

}

/*
Right now in above design all of push will go in 1 stack. How to make it like below –

Issue with Design 1 => If I call Pop for first time it should pop from set1, 2nd time pop from set2, 3rd time set1 and so on.
Stack is single instance. Problem is in the design. This design is Single instance Design.
This code is single stack code. 
How to make a code multi Stack ?

*/

#endif

/*--------------------------------------|
|                                       |
|************* DESIGN 2 ****************|
|       MULTIPLE INSTANCE DESIGN        |
|--------------------------------------*/
/* There was issue with the design in Design 1. Can we fix it?
Whenever we create global variable that is single instance program.
When we want to go for Single stack go for global otherwise don't.

How to make multiple instances of stack?
[Ans]: Use struct
*/

#if 1
/* Struct helps us to creates a new data type. No allocation happen. 
 but if there is a global variable allocation will happen immediately before main.
 For a data type there is no allocation.
 When will allocation happen?
 [Ans]:When we create variable of that Data type
 */
struct Stack // New Data Type (No allocation here)
{
	int items[100]; // global (single instance)
	int top = 0; // global (single instance)
};


/* When we are creating this code we don't know whether there is going
to be s1 or s2 or s3 [variables of Stack [objects]].. We don't know that.
Hence I cannot write push which is specific to s1 or s2
But we want push to work on anything whether s1 or s2
Same for Pop
How to achieve that?
[Ans]: Accept there address. Design the function to accept the address of s1 or s2.
Same thing for Pop.

We have changed the Design. This is MULTIPLE INSTANCE DESIGN

Multiple Instance Design => Don't make global variable. 
                            Create Data type.
                            Make global variable part of Data type.
							Let multiple instance of data type to be created.
							And design the function or push is such a way that it works on any instance of datatype

*/
void Push(Stack *s, int item)
{
	s->items[s->top] = item;
	s->top++;
}

int Pop(Stack *s)
{
	s->top--;
	return s->items[s->top];
}

//-----------------------------------------------------

#include <stdio.h>
void main()
{
	//Creating variable of data type Struct. This will do the allocation
	// s1 and s2 are INSTANCES of data type
	Stack s1, s2; // allocations
	//Total bytes allocated => 
	// for s1 => 100*4 + 4 = 404 bytes
	// for s2 => 100*4 + 4 = 404 bytes
	//Total => 808 bytes

	Push(&s1, 100);
	Push(&s1, 200);
	Push(&s1, 300);

	Push(&s2, 10000);
	Push(&s2, 20000);
	Push(&s2, 30000);

	int item = Pop(&s1);
	printf("%d\n", item);

	item = Pop(&s2);
	printf("%d\n", item);
}

#endif