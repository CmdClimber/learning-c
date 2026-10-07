#include <stdio.h>
#include <stdbool.h>

// The code below defines three functions to check the stack growth direction.
// Each function uses a different method to determine whether the stack grows upwards or downwards.
// For educational purposes, you can compile it with different flags (e.g.,gcc -O0 StackExercise.c, gcc -O2 StackExercise.c)
// or use another compiler (e.g.,clang) to see how compiler optimizations may affect the results.

// Function 1: Simple variable comparison but the result is compiler-dependent
// and might not work as expected due to optimizations,
// also addresses are compared in the same frame, so the result may not be reliable.
// Comparison &y > &x should be true if the stack grows downwards.
bool check_simple_variables(){
	int x, y;
	if (&y > &x) {
		return true;
	}
	else {
		return false;
	}
}

// Function 2: Checks the stack growth direction by using recursion.
// Function takes a pointer to an integer as an argument.
// If the pointer is NULL, it creates a local variable
// and calls itself recursively with the address of that variable.
// If the pointer is NOT NULL, it compares the address of a new local variable
// with the passed pointer to determine the stack growth direction.
// Compiler still may optimize the code and remove the recursion.
bool check_by_recursion(int *stackPointer) {
	int x;
	if (!stackPointer) {
		return check_by_recursion(&x);
	}
	else {
		return &x > stackPointer;
	}
}

// Copmrared to previous function, this one uses a slightly different approach.
// Besides creating second local variable, it also uses the volatile keyword
// to prevent the compiler from optimizing code execution and storing our variables in registers.
// This version is still depending on ABI build.
bool check_by_recursion_fixed(int *stackPointer) {
	volatile int a;
	if (stackPointer) {
		return &a > stackPointer;
	}
	volatile int b;
	return check_by_recursion_fixed((int *)&b);
}

// Most compilers will optimize the code and remove the recursion,
// so we can use the noinline attribute to prevent the compiler from inlining the function.
// That way we can ensure, every call to the function will create its own separate stack frame.
static _Bool check_direction(int *stackPointer);

__attribute__((noinline))
static _Bool check_direction(int *stackPointer) {
	volatile int first;
	if (stackPointer) {
		return &first > stackPointer;
	}
	volatile int second;
	return check_direction((int *)&second);
}

_Bool check_by_forced_attribute(void){
	return check_direction(NULL);
}

// Other approaches to check the stack growth direction could be implemented
// using preprocessor directives to check the architecture and define a macro accordingly.
// However, this approach is not as reliable as the previous methods,
// as it depends on the specific architecture and may not work for all cases:
// #ifdef __x86_64__
//  #define STACK_DIRECTION_UP 0
// #elif defined(__arm__)
//  #define STACK_DIRECTION_UP 1
// ...
// #endif

int main()
{
	printf("Stack growth direction check by variable: %s\n", check_simple_variables() ? "UP":"DOWN");
	printf("Stack growth direction check by recursion: %s\n", check_by_recursion(NULL) ? "UP":"DOWN");
	printf("Stack growth direction check by frames: %s\n", check_by_recursion_fixed(NULL) ? "UP":"DOWN");
	printf("Stack growth direction check by noinline attribute: %s\n", check_by_forced_attribute() ? "UP":"DOWN");
	return 0;
}