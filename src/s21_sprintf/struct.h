typedef struct {
  int minus;  // к левому краю
  int plus;   // явно указать знак
  int space;  // доп символ под знак или пробел
  // int hash;
  // int zero;
  int wight;     // ширина
  int accuracy;  // точность
  int lenght;    // длина
  // int number_system;
  int flag_to_size;  // если чсило отрицательное или есть + или space
  int dot;  // наличие точки, значит точности
  // int upper_case;
  // int g;
  // int e;
} Spec;