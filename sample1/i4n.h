#pragma once

typedef struct i4n {
  int16_t value;
  bool    null;
} i4n;

i4n i4n_create(){
  i4n i = {.value=0, .null=true};
  return i;
}

void i4n_set(i4n* i, int16_t v){
  i->value = v;
  i->null = false;
}

int16_t i4_max(int16_t x, int16_t y){ return x < y ? y : x; }
int16_t i4_min(int16_t x, int16_t y){ return x > y ? y : x; }

int16_t i4_bound(int16_t lbi, int16_t x, int16_t ubi){
  return i4_max(
    lbi,
    i4_min(ubi, x)
  );
}

void i4n_set_const(i4n* i, Const* c){
  i->null = true;
  for(; NULL != c;){
    for(; ! c->constisnull;){
      i->value = DatumGetInt16(c->constvalue);
      i->null  = false;
      break;
    }
    break;
  }
}
