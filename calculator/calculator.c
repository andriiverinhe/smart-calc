#include "calculator.h"
#include "../smart_calc.h" // Этот путь включает заголовочный файл smart_calc.h
#include "../stack/stack.h"


double s21_calc(char *input) {
  int code = 1;
  double result = 0;

  if (!input || strlen(input) == 0 || !s21_validator(input)) code = -1;
  else {
  s21_stack *main = NULL;

  main = s21_getStackFromStr(input, main);
  // s21_printStack(main);

  if(s21_checkX(main)) {
    s21_replacingXforValue(main, 1);
    // s21_printStack(main);
    
    main = getStackOnPolishNotation(main);
    result = s21_NewCalculator(main);

    printf("TRUE\n");
  } else {
    main = getStackOnPolishNotation(main);
    result = s21_NewCalculator(main);
  }


  if (main)
    s21_clearStack(main);
  }
  return code? result : code;
}

int main() {
  printf("result: %f\n", s21_calc("x^2"));
  printf("math: %f\n",2.);
}
