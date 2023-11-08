#include "../smart_calc.h"
#include "math.h"
#include "stack.h"
void s21_setValueStack(const double number, const char *sign,
                       const int priority, s21_stack *st) {
  st->number = number;

  if (sign)
    st->sign = malloc(strlen(sign) + 1); // Выделяем память для строки
  if (st->sign != NULL) {
    strcpy(st->sign, sign); // Копируем строку
  }
  st->priority = priority;
}

void s21_printStack(s21_stack *top) {
  if (top == NULL) {
    printf("Стек пуст.\n");
    return;
  }

  s21_stack *current = top;
    printf("\tSTACK\n");
  while (current != NULL) {
    printf("Number: %f, Sign: '%s', Priority: %d\n", current->number,
           current->sign, current->priority);
    current = current->next;
  }
}

