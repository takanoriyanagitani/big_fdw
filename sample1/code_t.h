typedef struct code_t {
  char value[4];  // USD, JPY, ...
  char filter[4];
} code_t;

code_t code_t_create(){
  code_t c = {0};
  return c;
}
