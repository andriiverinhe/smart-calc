#pragma once

#include "../smart_calc.h" // Включение общего заголовка

// Объявления функций и структур, связанных с модулем calculator

#include "string.h"
#include <ctype.h>
#include <math.h>
#include <stdio.h>
#include <stdlib.h>

typedef enum {
  NUMBER = 0,
  SUBSUM = 1,
  MULDIV = 2,
  SINCOS = 4,
  POWER = 3,
  BRACKET = 5,
} CodePriority;

typedef enum {
  PLUS = 0,
  MINUS = 1,

  MUL = 2,
  DIV = 3,
  MOD = 4,

  POW = 5,

  SIN = 6,
  COS = 7,
  TAN = 8,

  ASIN = 9,
  ACOS = 10,
  ATAN = 11,

  LOG = 12,
  LN = 13,

  SQRT = 14,

  UNARYMINUS = 15,
} lexema;

double s21_NewCalculator(s21_stack *st);

double s21_calc(char *input);
// HELPERS
void s21_getNumber(const char *input, char *num);
void s21_getSign(const char *input, char *sign);
s21_stack *s21_getStackFromStr(const char *input, s21_stack *main);
int s21_getPriority(char *sign);
s21_stack *getStackOnPolishNotation(s21_stack *main);
void s21_printStrFromStack(s21_stack *st);
//PARESER
int s21_validator(char *str);


//CALCULATOR WITH X
int s21_checkX(s21_stack *st);
void s21_replacingXforValue(s21_stack *main,const double value);