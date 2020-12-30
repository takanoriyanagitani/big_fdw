#pragma once

typedef struct i3n {
  int8_t value;
  bool   null;
} i3n;

i3n i3n_create(){
  i3n i = {.value=0, .null=true};
  return i;
}

void i3n_set(i3n* i, int8_t v){
  i->value = v;
  i->null = false;
}

int8_t i3_max(int8_t x, int8_t y){ return x < y ? y : x; }
int8_t i3_min(int8_t x, int8_t y){ return x > y ? y : x; }

int8_t i3_bound(int8_t lbi, int8_t x, int8_t ubi){
  return i3_max(
    lbi,
    i3_min(ubi, x)
  );
}

void i3n_set_const(i3n* i, Const* c){
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
