typedef struct code_t {
  char value[4];  // USD, JPY, ...
  char filter[4];
} code_t;

code_t code_t_create(){
  code_t c = {0};
  return c;
}

Datum code_topg(const code_t* c){
  const int sz = VARHDRSZ + 3;
  bytea*    b  = palloc0(sz);
  memcpy(VARDATA(b), c->filter, 3);
  SET_VARSIZE(b, sz);
  return PointerGetDatum(b);
}
