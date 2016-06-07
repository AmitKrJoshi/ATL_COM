/*
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
*/

//>>>> Let's Start COM

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
	Push(100);	//Pushing 100
	Push(200);	//Pushing 200
	Push(300);

	int item = Pop();
	printf("%d\n", item);
	printf("%d\n", item);
	//Problem...?  
	// we should call pop 2 or 3 times depending on how many value we want to see
}