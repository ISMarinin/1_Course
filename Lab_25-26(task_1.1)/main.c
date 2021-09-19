// КАК РАБОТАЕТ ПРОГРАММА:
// + добавить элемент
// - удалить элемент из стека
// p печать стека
// t задание(поиска и удаление макс элемента, сортировка выбором)
// ? проверка стека на пустоту

#include"functions.h"
#include <stdio.h>
#include <stdbool.h>
#include <stdlib.h>

int main() {

    Stack s;
    initStack(&s);
    char symbol;
    Token number;
    while ((symbol = getchar()) != EOF) {

        if (symbol == '+') {

            getchar();
            scanf("%d", &number.value);
            push(&s,number);
        }

        else if (symbol == '-') {

            pop(&s);

        }

        else if (symbol == '?') {

            if (isEmpty(&s)) {
                printf("Stack is empty\n");
            } 
            else 
                printf("Stack is not empty, size = %d\n", s.size);
        }

        else if (symbol == 'p') {

            printStack(&s);

        }

        else if (symbol == 't') {

            Task(&s);

        }
    }

    free(s.nodes);

}