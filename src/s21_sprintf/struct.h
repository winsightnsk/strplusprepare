#ifndef SPEC_H
#define SPEC_H

typedef struct {
  int minus;     // к левому краю
  int plus;      // явно указать знак
  int space;     // доп символ под знак или пробел
  int wight;     // ширина
  int accuracy;  // точность
  int lenght;    // длина
  int flag_to_size;  // если число отрицательное или есть + или space
  int dot;  // наличие точки, значит точности
} Spec;

#endif