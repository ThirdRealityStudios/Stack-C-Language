#include <stdio.h>
#include <stdlib.h>

#define OUTPUT_LENGTH 5
#define NO_ELEMENT -1 // Only used if a query or operation on the stack failed because no element is on the stack. If you want to know "if" there is no element on the stack, use empty(..)

struct element
{
    int wert;
    struct element *darunter;
};

struct stapel
{
    struct element *top;
    int anzahlElemente;
};

/*
 * Creates a stack by allocating memory.
 */
struct stapel* create()
{
    struct stapel *new = malloc(sizeof(struct stapel));

    new -> top = NULL;
    new -> anzahlElemente = 0;

    return new;
}

/*
 * Pushes an element to the given stack and takes the specified value.
 */
void push(struct stapel *stapelRef, int wert)
{
    struct element *elementNeu = malloc(sizeof(struct element));

    elementNeu -> darunter = stapelRef -> top;
    elementNeu -> wert = wert;

    stapelRef -> top = elementNeu;

    stapelRef -> anzahlElemente++;
}

/*
 * Removes an element from the given stack and returns its value.
 * Returns NO_ELEMENT if no element on the stack.
 */
int pop(struct stapel *stapelRef)
{
    if(stapelRef -> top != NULL)
    {
        struct element *altesElement = stapelRef -> top;

        int geloeschterWert = altesElement -> wert;

        stapelRef -> top = altesElement -> darunter;

        free(altesElement);

        stapelRef -> anzahlElemente--;

        return geloeschterWert;
    }
    else
    {
        return NO_ELEMENT;
    }
}

/*
 * Returns 1 if stack is empty. Otherwise 0.
 */
int empty(struct stapel *stapelRef)
{
    return stapelRef -> anzahlElemente == 0;
}

/*
 * Pops all elements from the given stack, like, wtf is going on?!
 */
void popAll(struct stapel *stapelRef)
{
    while(!empty(stapelRef))
    {
        pop(stapelRef);
    }
}

/*
 * Prints all elements from a stack as a graphic to the console.
 */
void print(struct stapel *stapelRef)
{
    int i = 0;

    struct element *next = NULL;

    if((stapelRef -> anzahlElemente) > 0)
    {
        next = stapelRef -> top;

        puts("Stack:\n");

        for(i = 0; i < (stapelRef -> anzahlElemente); i++)
        {
            printf("\t%.*s\n", OUTPUT_LENGTH + 2, "----------------------------");
            printf("\t|%*d|\n", OUTPUT_LENGTH, next -> wert);
            printf("\t%.*s\n", OUTPUT_LENGTH + 2, "----------------------------");

            next = next -> darunter;
        }

        return;
    }

    puts("Stack: is empty.");
}

/*
 * Returns 1 if the test was successful. Otherwise 0.
 */
int testPopAll()
{
    struct stapel *bsp = create();

    push(bsp, 1);
    push(bsp, 2);
    push(bsp, 3);
    push(bsp, 4);
    push(bsp, 5);

    popAll(bsp);

    int testOK = bsp -> anzahlElemente == 0;

    free(bsp);

    return testOK;
}

/*
 * Returns 1 if the test was successful. Otherwise 0.
 */
int testPop()
{
    struct stapel *bsp = create();

    push(bsp, 1);
    pop(bsp);

    int testOK = bsp -> anzahlElemente == 0;

    push(bsp, 1);
    push(bsp, 2);

    pop(bsp);

    testOK &= bsp -> anzahlElemente == 1;

    pop(bsp);
    int elementValue = pop(bsp);

    testOK &= elementValue == NO_ELEMENT;

    free(bsp);

    return testOK;
}

/*
 * Returns 1 if the test was successful. Otherwise 0.
 */
int testEmpty()
{
    struct stapel *bsp = create();

    push(bsp, 1);
    pop(bsp);

    int testOK = empty(bsp);

    push(bsp, 1);
    push(bsp, 2);
    push(bsp, 3);
    popAll(bsp);

    testOK &= empty(bsp);

    free(bsp);

    return testOK;
}

/*
 * Returns 1 if the test was successful. Otherwise 0.
 */
int testPush()
{
    struct stapel *bsp = create();

    push(bsp, 1);
    int testOK = bsp -> anzahlElemente == 1;

    push(bsp, 1);
    testOK &= bsp -> anzahlElemente == 2;

    push(bsp, 2);
    testOK &= bsp -> anzahlElemente == 3;

    push(bsp, 3);
    testOK &= bsp -> anzahlElemente == 4;

    free(bsp);

    return testOK;
}

/*
 * Prints the test result of a function.
 *
 * char *functionName  Name of the tested function.
 * int testValue  Result of the test function (should be 0 if it failed, otherwise OK).
 */
void printTest(char *functionName, int testValue)
{
    printf("[INFO]: Test \"%s\" %s", functionName, testValue ? "OK\n" : "Failed\n");
}

int main(int argc, char **args)
{
    // Test here all methods and print the result to the console.

    printTest("push", testPush());
    printTest("pop", testPop());
    printTest("popAll", testPopAll());
    printTest("empty", testEmpty());

    return 0;
}