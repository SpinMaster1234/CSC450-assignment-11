#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct lines
{
    char * * List;
    int Size;
    int Counter;
}Stack;

Stack create(int size);

void push(char * str, Stack *stack);

char * pop(Stack *stack);

char * peek(Stack *stack);

void destroy(Stack *stack);

int main(){
    //Create File information
    FILE * inputStream, * outputStream;
    inputStream = fopen("genesis.txt", "r");
    outputStream = fopen("genesis_reversed.txt", "w");
    int size=0;
    int x;

    //Find Size
    while((x = fgetc(inputStream)) != EOF){
        if ((char)x == '\n'){
            size = size + 1;
        }
    }

    //Create the Stack of text
    struct lines stack;
    stack = create(size);
    fseek(inputStream, 0, SEEK_SET);
    char * buffer;
    buffer = malloc(sizeof(char) * 1000);
    char * temp;
    while((temp = fgets(buffer, 1000, inputStream)) != NULL){
        push(buffer, &stack);
    }

    //Write Stack to new file
    while(stack.Counter > 0){
        temp = pop(&stack);
        if (temp != NULL){
            fputs(temp, outputStream);
        }
        free(temp);
    }

    //Close Everything
    destroy(&stack);
    fclose(inputStream);
    fclose(outputStream);


    return 0;
}

Stack create(int size){
    Stack s;
    s.List = malloc(sizeof(char *) * size);
    s.Counter = 0;
    s.Size = size;
    return s;
}

void push(char * str, Stack * stack){
    stack->List[stack->Counter] = malloc(1000);
    strcpy(stack->List[stack->Counter], str);
    stack->Counter = stack->Counter + 1;
}

char * pop(Stack *stack){
    char * ret;
    ret = stack->List[stack->Counter];
    stack->List[stack->Counter] = "";
    stack->Counter = stack->Counter - 1;
    return ret;
}

char * peek(Stack *stack){
    char * ret;
    strcpy(ret, stack->List[stack->Counter]);
    return ret;
}

void destroy(Stack *stack){
    free(stack->List);
}

