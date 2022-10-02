#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

//If you are given an expression in the form of a string comprising of variables, operaters, functions and paranthesis.
//WE want to write a program that checks if the parathensis are balanced or not
//Balanced paranthesis means that corresponding to any opening parenthesis we should have a closing counterpart in correct order
//e.g (A+B), {(A+B)+(C+D)}      <-- these are balanced
//e.g {(x+y)*(z), [2*3]+(A)]    <-- not balanced
//In this problem what we really care about are the paranethesis, anything else isn't really important
//Also )( and [(]) are not balanced. They must be something like [()]

//Solution would be something like:
//Scan from left to right
//If opening symbol, add it to a list
//if closing symbol, remove last opening symbol in the list
//Continue this untill it is checked if it is balanced or not

//With this solution, it is always the last element in the list that is being removed or added. Guess what, that's a stack :3


struct node{                                        //Creating the structure of a stack node
    char data;
    struct node *next;
};

struct node *top = NULL;

void push(char x){
    struct node *temp = (struct node*)malloc(sizeof(struct node));          //Creating a new node

    if(temp == NULL){
        printf("Stack overflow\n");                 //Statement if list is overflowing
        return;
    }

    temp -> data = x;                               //Sets the temporary nodes value to the vairable x
    temp -> next = top;                             //Makes it so the node after this temp node is the current top node
    top = temp;                                     //Moves top to where temp is, as temp is now the new top node
}

int pop(){
    struct node *temp = top;
    char res;

    if(top == NULL){
        printf("Stack Overflow\n");
        return 0;
    }
    temp = top;
    res = top -> data;
    top = temp -> next;
    free(temp);
    return res;
}

bool matchingPair(char c1, char c2){                //Returns 1 if c1 and c2 are matching brackets
    if (c1 == '(' && c2 == ')') return 1;
    else if (c1 == '{' && c2 == '}') return 1;
    else if (c1 == '[' && c2 == ']') return 1;
    else return 0;
}

bool bracketsBalanced(char c[]){                    //Returns 1 if expression (whatever you want to check is balanced) is balanced
    int i = 0;

    struct node *temp = NULL;                       //Declaring an empty variable

    while(c[i]){
        if(c[i] == '{' || c[i] == '(' || c[i] == '[')               //If the character is an opening bracket, push onto the stack
        push(c[i]);

        else if(c[i] == ']' || c[i] == ')' || c[i] == '}'){         //If character is a closed bracket run the following
            if(!matchingPair(pop(), c[i]))                          //There is two things happening here. Since when put pop() as an argument for matchingPair, it will also run the pop function which will return a character
            return 0;                                               //One the pop function is ran and character is returned, that character will then be used as an argument for matchingPair to check if we find a matching pair
        }
        i++;
    }

    if(temp == NULL) return 1;
    else return 0;
}

int main(){
    char c[100];                                                    //Set to 100 just as a max size
    printf("Enter set of paranthesis without spaces:\n");
    scanf("%s", c);

    if(bracketsBalanced(c))
        printf("Balanced \n");
    else
        printf("Not balanced \n");
    return 0;
}
