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

#if 0
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

	item = Pop(&s1);
	printf("%d\n", item);

	item = Pop(&s2);
	printf("%d\n", item);

	/* The output shows different this time Why? Because we end up creating 2 stack.
	 How many such stacks can be created? It depends on how many instances we have created
	 This is Multiple instance design.
	*/

}

*********In COM Microsoft follows multiple instance design whether we write code in C or C++ or any language.**********

#endif

/*--------------------------------------|
|                                       |
|************* DESIGN 3 ****************|
|MULTIPLE INSTANCE DESIGN-Better Approach|
|--------------------------------------*/

#if 1

/* Design 3 is just a better way to do what we are doing in Design 2 Include 
methods in structure. I.e. Now functions have gone inside the Data type means 
compiler can start helping us in very interesting way. What is that?
[A] We do not have to write the pointer. Then who will write the pointer. 
Compiler will write it. That is "this" pointer.
[Q] Why compiler is doing this now? While it was not injecting this earlier.
[A] Because that time functions was not part of data type, Hence compiler 
was not in position to decide what to put inside that function. But now 
function is part of data type so now compiler knows for which data type it 
has to work so it has to have the pointer.

C was lacking this feature.
But after compilation there is no difference whether c or c++.
*/


struct Stack // New Data Type (No allocation here)
{
	int items[100]; // global (single instance)
	int top = 0; // global (single instance)

	void Push ( int item ) // void Push(Stack *this, int item)  <= Compiler changes it to as showd
	{
		items[top] = item; // this->items[this->top] = item;
		top++; //  this->top++;
	}

	int Pop() // int Pop(Stack *this)
	{
		top--; //  this->top--;
		return items[top]; // return this->items[this->top];
	}
};

//-----------------------------------------------------

#include <stdio.h>
void main()
{
	Stack s1, s2; // allocations

	s1.Push(100); // Stack.Push(&s1, 100);
	s1.Push(200); // Stack.Push(&s1, 200);
	s1.Push(300); // Stack.Push(&s1, 300);

	s2.Push(10000); // Stack.Push(&s2, 10000);
	s2.Push(20000); // Stack.Push(&s2, 20000);
	s2.Push(30000); // Stack.Push(&s2, 30000);

	// Why it is better ? 

	int item = s1.Pop(); // Stack.Pop(&s1);
	printf("%d\n", item);

	item = s2.Pop(); // Stack.Pop(&s2);
	printf("%d\n", item);

	item = s1.Pop(); // Stack.Pop(&s2);
	printf("%d\n", item);

	item = s2.Pop(); // Stack.Pop(&s2);
	printf("%d\n", item);
}

/*
So what is happening here internally [Stack.Push(&s1, 100)] we are calling push then passing
address of s1 that means we are giving more importance to push rather than s1. But it feels
that s1 is more important [s1.Push(100)] than push coz whatever we use 1st has more importance.
Because this is more real world. Why ?
[A]: S1 is of type stack [Assume an s/w developer] and S2 is of type stack [Assume another s/w developer]
so we ask S1 to develop [function name=> develop] calendar [passed data=>calendar]...
App and S2 to develop calculator App.

So

S1.Develop (calendar)
S2.Develop (calculator)

Development happening. After 1 week S1 Test it. S2 Test it.

S1.Testit()
S2.Testit()

Notice here we have called 2 more methods. Now which app S1 will test? And which app S2 will test?
We did not tell S1 and S2 which app they need to test. They remembered it.

So here S1 and S2 remembering data.

We say S1 push then S2 push. Then we say S1 pop data and it pops the correct data which S1 has pushed.
We don’t have to mention which data. It remembers which data it needs to pop. Same for S2.

What is not important here is what operation we do. The more important thing is Which OBJECT does Which OPERATION.

So here we introduced concept of Object.

What is Object?
[A]: Object is an entity "performs the work" and object "remember the data".

***********COM FOLLOWS MULTIPLE INSTANCE DESIGN*********
***********COM FOLLOWS OBJECT ORIENTED RULES*********

*/

#endif