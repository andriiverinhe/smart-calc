#include "calculator.h"
#include "../smart_calc.h" // Этот путь включает заголовочный файл smart_calc.h
#include "../stack/stack.h"


double s21_calc(char *input, const int inputX) {
  int code = 1;
  double result = 0;

  if (!input || strlen(input) == 0 || !s21_validator(input)) code = -1;
  else {
  s21_stack *main = NULL;
  

  main = s21_getStackFromStr(input, main);
  if(s21_checkX(main)) {
    s21_replacingXforValue(main, inputX);
  }
  // s21_printStack(main);
  main = getStackOnPolishNotation(main);
  result = s21_NewCalculator(main);
  
  if (main)
    s21_clearStack(main);
  }
  return code? result : code;
}

int main() {
for(double x = -10; x < 11; x++) {
  printf("x: %f || f(x): %f\n", x, s21_calc("x^2", 2));
  
}

}
