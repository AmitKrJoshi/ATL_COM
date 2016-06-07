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

/* kernel32.dll - Windows OS
mainCRTStartup() ;
*/

/* C++ Compiler will inject this code
void mainCRTStartUp() // Stub Code
{
// Global Variables are created
main();
}
*/


void main()
{
}