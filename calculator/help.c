#include "../smart_calc.h"
#include "../stack/stack.h"
#include "calculator.h"

void s21_getNumber(const char *input, char *num) {
  size_t length = strcspn(input, "+-*/^() cstalm");
  for (size_t i = 0; i < length; i++) {
    num[i] = input[i];
  }
}

void s21_getSign(const char *input, char *sign) {
  if (input[0] == '*' || input[0] == '-' || input[0] == '+' ||
      input[0] == '/' || input[0] == '^' || input[0] == 'x') {
    sign[0] = input[0];
    sign[1] = '\0';
  } else {
    size_t length = strcspn(input, "()1234567890 ");
    for (size_t i = 0; i < length; i++) {
      sign[i] = input[i];
    }
  }
}

s21_stack *s21_getStackFromStr(const char *input, s21_stack *main) {
  for (int i = 0; input[i] != '\0';) {
    if (isspace(input[i])) {
      i++;
      continue;
    }
    if (isdigit(input[i])) {
      char num[1000] = "\0";
      s21_getNumber((input + i), num);
      main = s21_push(main, strtod(num, NULL), "NULL", NUMBER);
      i += (int)strlen(num);
    } else if (input[i] == '(' || input[i] == ')') {

      char sign[100] = "\0";
      sign[0] = input[i];
      main = s21_push(main, NAN, sign, 5);
      i++;

    } else {
      char sign[1000] = "\0";
      int plusUnary = 0;
      s21_getSign((input + i), sign);
      if(strcmp(sign, "-") == 0) {
        if(!main) strcpy(sign, "~");
        else if(main->priority == BRACKET && strcmp(main->sign, "(") == 0) strcpy(sign, "~");
      }
      if(strcmp(sign, "+") == 0) {
        if(!main) plusUnary = 1; 
        else if(main->priority == BRACKET && strcmp(main->sign, "(") == 0) plusUnary = 1;
      }
      if(!plusUnary) {
        // printf("123\n");
        main = s21_push(main, NAN, sign, s21_getPriority(sign));}
      i += (int)strlen(sign);
    }
  }

  return s21_reverseStack(main);
}

int s21_getPriority(char *sign) {
  const char *trigFunctionNames[] = {"cos",  "sin",  "tan", "acos", "asin",
                                     "atan", "sqrt", "ln",  "log"};
  int pr = -1;
  for (int i = 0; i < 9; i++) {
    if (strcmp(trigFunctionNames[i], sign) == 0)
      pr = SINCOS;
  }
  if (pr == -1) {
    if (strcmp("+", sign) == 0 || strcmp("-", sign) == 0 || strcmp("~", sign) == 0)
      pr = SUBSUM;
    else if (strcmp("mod", sign) == 0 || strcmp("/", sign) == 0 ||
             strcmp("*", sign) == 0)
      pr = MULDIV;
    else if (strcmp("^", sign) == 0)
      pr = POWER;
  }
  if(pr == -1 && strcmp("x", sign) == 0) pr = NUMBER;
  return pr;
}


s21_stack *getStackOnPolishNotation(s21_stack *main) {
  if (!main)
    return NULL;

  s21_stack *tmp = NULL;
  s21_stack *sign = NULL;

  while (main != NULL) {
    if (main->priority == 0) {
      tmp = s21_push(tmp, main->number, main->sign, main->priority);
    }
    if (main->priority == 1) {
      if (!sign)
        sign = s21_push(sign, main->number, main->sign, main->priority);
      else {
        if (sign->priority < main->priority && sign->priority != 5)
          sign = s21_push(sign, main->number, main->sign, main->priority);
        else {
          while (sign && sign->priority != 5 && sign->priority >= main->priority) {
            tmp = s21_push(tmp, sign->number, sign->sign, sign->priority);
            sign = s21_pop(sign);
          }
          sign = s21_push(sign, main->number, main->sign, main->priority);
        }
      }
    } else if (main->priority == 2) {
      if (!sign)
        sign = s21_push(sign, main->number, main->sign, main->priority);
      else {
        if (sign->priority < main->priority && sign->priority != 5)
          sign = s21_push(sign, main->number, main->sign, main->priority);
        else {
          while (sign && sign->priority != 5 && sign->priority >= main->priority) {
            tmp = s21_push(tmp, sign->number, sign->sign, sign->priority);
            sign = s21_pop(sign);
          }
          sign = s21_push(sign, main->number, main->sign, main->priority);
        }
      }
    } else if (main->priority == 3) {
      if (!sign)
        sign = s21_push(sign, main->number, main->sign, main->priority);
      else {
        if (sign->priority < main->priority && sign->priority != 5)
          sign = s21_push(sign, main->number, main->sign, main->priority);
        else {
          while (sign && sign->priority != 5 && sign->priority >= main->priority) {
            tmp = s21_push(tmp, sign->number, sign->sign, sign->priority);
            sign = s21_pop(sign);
          }
          sign = s21_push(sign, main->number, main->sign, main->priority);
        }
      }
    } else if (main->priority == 4) {
      if (!sign)
        sign = s21_push(sign, main->number, main->sign, main->priority);
      else {
        if (sign->priority < main->priority && sign->priority != 5)
          sign = s21_push(sign, main->number, main->sign, main->priority);
        else {
          while (sign && sign->priority != 5 && sign->priority >= main->priority) {
            tmp = s21_push(tmp, sign->number, sign->sign, sign->priority);
            sign = s21_pop(sign);
          }
          sign = s21_push(sign, main->number, main->sign, main->priority);
        }
      }
    } else if (main->priority == 5) {
      sign = s21_push(sign, main->number, main->sign, main->priority);
      if (strcmp(sign->sign, ")") == 0) {
        if (sign->priority == 5)
          sign = s21_pop(sign);
        while (sign && sign->priority != 5) {
          tmp = s21_push(tmp, sign->number, sign->sign, sign->priority);
          sign = s21_pop(sign);
        }
        if (sign->priority == 5)
          sign = s21_pop(sign);
      }
    }

    main = s21_pop(main);
  }
  while (sign) {
    tmp = s21_push(tmp, sign->number, sign->sign, sign->priority);
    sign = s21_pop(sign);
  }
  // printf("\tPOLISH\n");
  // s21_printStack(tmp);

  s21_clearStack(sign);
  return tmp;
}



void s21_printStrFromStack(s21_stack *st) {
  if (st == NULL) {
    printf("Стек пуст.\n");
    return;
  }

  s21_stack *current = st;
  while (current != NULL) {
    if (st->priority == 0) {
      printf("%f", current->number);
    } else
      printf("%s", current->sign);

    current = current->next;
  }
}

int s21_checkLexem(const char *sign) {
  int lex = -1;
  if(strcmp(sign, "+") == 0)
    lex = PLUS;
  if(strcmp(sign, "-") == 0)
    lex = MINUS;
  if(strcmp(sign, "*") == 0)
    lex = MUL;
  if(strcmp(sign, "/") == 0)
    lex = DIV;
  if(strcmp(sign, "mod") == 0)
    lex = MOD;
  if(strcmp(sign, "^") == 0)
    lex = POW;
  if(strcmp(sign, "sin") == 0)
    lex = SIN;
  if(strcmp(sign, "cos") == 0)
    lex = COS;
  if(strcmp(sign, "tan") == 0)
    lex = TAN;
  if(strcmp(sign, "asin") == 0)
    lex = ASIN;
  if(strcmp(sign, "acos") == 0)
    lex = ACOS;
  if(strcmp(sign, "atan") == 0)
    lex = ATAN;
  if(strcmp(sign, "log") == 0)
    lex = LOG;
  if(strcmp(sign, "ln") == 0)
    lex = LN;
  if(strcmp(sign, "sqrt") == 0)
    lex = SQRT;
  if(strcmp(sign, "~") == 0)
    lex = UNARYMINUS;
  return lex;
}

double s21_operations(double num1, double num2,const int lex) {
  double result = 0;
  switch (lex)
  {
  case PLUS:
    result = num1 + num2;
    break;
  case MINUS:
    result = num1 - num2;
    break;
  case MUL:
    result = num1 * num2;
    break;
  case DIV:
    result = num1 / num2;
    break;
  case MOD:
    result = fmod(num1, num2);
    break;
  case POW:
    result = pow(num1, num2);
    break;
  case SIN:
    result = sin(num1);
    break;
  case COS:
    result = cos(num1);
    break;
  case TAN:
    result = tan(num1);    
    break;
  case ASIN:
    result = asin(num1);
    break;
  case ACOS:
    result = acos(num1);
    break;
  case ATAN:
    result = atan(num1);    
    break;
  case LOG:
    result = log10(num1);
    break;
  case LN:
    result = log(num1);
    break;
  case SQRT:
    result = sqrt(num1);
    break;
  case UNARYMINUS:
    result = -1 * num1;
    break;
  

  default:
    fprintf(stderr, "Не возможно посчитать!\n");
    break;
  }
  return result;
}


double bi_oper(const s21_stack *src, int lex) {
  
  double num2 = src->next->number;
  double num1 = src->next->next->number;
  return s21_operations(num1, num2, lex);
}
double un_oper(const s21_stack *src, int lex) {
  
  double num1 = src->next->number;
  return s21_operations(num1, NAN, lex);
}

void clearElement(s21_stack *st){
  if(st){
    if(st->sign) free(st->sign); 
    if(st->next) st->next = NULL;
    free(st);
  }
}
void setValues(s21_stack *st, double value, char *signs, int pr) {
  st->number = value;
  if(signs){
    if(st->sign)
      free(st->sign);
    st->sign = malloc(strlen(signs) + 1);
    strcpy(st->sign, signs);
  }
  st->priority = pr;
}

double s21_NewCalculator(s21_stack *st) {
  s21_stack *tmp = st;
  s21_stack *stmp = tmp;
  while (tmp) {
    if(tmp->priority != NUMBER) {
      int lex = s21_checkLexem(tmp->sign);
      if(tmp->next && tmp->next->next && tmp->next->next && tmp->next && tmp->next->priority == NUMBER && tmp->next->next->priority == NUMBER && lex < 6) {
        double result = bi_oper(tmp, lex);
        s21_stack *newAdd = tmp->next->next->next;
        clearElement(tmp->next->next);
        clearElement(tmp->next);
        tmp->next = newAdd;
        setValues(tmp, result, "NULL", NUMBER);
        tmp = stmp;
      } 
      if(tmp->next && tmp->next->priority == NUMBER && lex >= 6) {
        double result = un_oper(tmp, lex);
        s21_stack *newAdd = tmp->next->next;
        clearElement(tmp->next);
        tmp->next = newAdd;
        setValues(tmp, result, "NULL", NUMBER);
        tmp = stmp;
      }
    }
    tmp = tmp->next;
    if(!tmp) {tmp = stmp;
    // s21_printStack(stmp);
    }
    if(stmp && !stmp->next) break;
  }
  return tmp->number;
}



// CALCULATION WITH X

int s21_checkX(s21_stack *st) {
  int code = 0;
  s21_stack *tmp = st;
  while (tmp && code == 0) {
    if(strcmp(tmp->sign, "x") == 0) code = 1;
    tmp = tmp->next;
  }
  return code;
}


void s21_replacingXforValue(s21_stack *main,const double value) {
  s21_stack *tmp = main;

  while (tmp)
  {
    if(strcmp(tmp->sign, "x") == 0) {
        tmp->number = value;     
    }
    tmp = tmp->next;
  }
}








