#pragma once

typedef struct s21_stack {
    double number;
    char *sign;
    int priority;

    struct s21_stack *next;
} s21_stack;