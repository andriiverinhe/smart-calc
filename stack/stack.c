#include "stack.h"
#include "../smart_calc.h" // Этот путь включает заголовочный файл smart_calc.h

s21_stack *s21_push(s21_stack *top, double number, const char *sign,
                    int priority) {
  s21_stack *new_node =
      (s21_stack *)malloc(sizeof(s21_stack)); // Выделение памяти под новый узел

  if (new_node == NULL) {
    // Обработка ошибки: не удалось выделить память
    // Можно выбрасывать исключение или вернуть NULL
    return NULL;
  }
  s21_setValueStack(number, sign, priority, new_node);
  new_node->next = top; // Новый узел указывает на предыдущий top
  return new_node; // Возвращаем указатель на новый узел как новую вершину стека
}

s21_stack *s21_pop(s21_stack *top) {
  if (top == NULL) {
    printf("Стек пуст, невозможно выполнить операцию pop.\n");
    return NULL;
  }
  s21_stack *temp = top;
  top = top->next; // Обновляем top на предыдущий элемент
  if (temp) {
    if (temp->sign)
      free(temp->sign); // Освобождаем память, выделенную под строку
    free(temp); // Освобождаем память, выделенную под узел
  }

  return top; // Возвращаем обновленную вершину стека
}

void s21_clearStack(s21_stack *top) {
  while (top != NULL) {
    top = s21_pop(top);
  }
}

s21_stack *s21_reverseStack(s21_stack *top) {
  s21_stack *reversedTop =
      NULL; // Создаем новый стек для перевернутых элементов

  while (top != NULL) {
    s21_stack *temp = top;
    top = top->next; // Удаляем верхний элемент из исходного стека
    temp->next = reversedTop; // Добавляем этот элемент в перевернутый стек
    reversedTop = temp; // Обновляем вершину перевернутого стека
  }

  return reversedTop; // Возвращаем перевернутый стек
}
