#include "spec_percent.h"

// Обрабатывает спецификатор %, добавляющий в str символ %
void specPercent(char* str, int* shiftStr, Spec* specs) {
  if (specs->accuracy || specs->dot || specs->lenght || specs->minus ||
      specs->plus || specs->space || specs->width) {
    perror("conversion lacks type at end of format");
  } else {
    *str = '%';
    *shiftStr += 1;
  }
}