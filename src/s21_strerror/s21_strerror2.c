char *s21_strerror(int errnum) {
  static char result[50] = {'\0'};
  if ((errnum >= 0) && (errnum <= ERR_SIZE)) {
    s21_strncpy(result, ERRORS[errnum], 50);
  } else {
    sprintf(result, STR_ERROR "%d", errnum);
  }
  return result;
}