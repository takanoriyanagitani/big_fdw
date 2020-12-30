#pragma once

#include "i3n.h"
#include "i4n.h"
#include "code_t.h"

typedef struct year_t {
  DIR*    dir;
  int16_t value;
  i4n     filter;
} year_t;

void year_t_clamp(year_t* y){ y->value = i4_bound(1, y->value, 9999); }

typedef struct month_t {
  DIR*   dir;
  int8_t value;
  i3n    filter;
} month_t;

void month_t_clamp(month_t* m){ m->value = i4_bound(1, m->value, 12); }

typedef struct day_t {
  DIR*   dir;
  int8_t value;
  i3n    filter;
} day_t;

void day_t_clamp(day_t* d){ d->value = i3_bound(1, d->value, 31); }

typedef struct S1State {
  const char* root_dirname;
  DIR*        root;
  char        path[PATH_MAX];
  int8_t      ptype;

  year_t  y;
  month_t m;
  day_t   d;
  code_t  c;

  double unixtime;
} S1State;

S1State* s1state_new(){
  S1State* s = palloc0(sizeof(S1State));
  s->y.filter = i4n_create();
  s->m.filter = i3n_create();
  s->d.filter = i3n_create();
  s->c        = code_t_create();
  s->ptype    = -1;
  return s;
}

bool s1state_ymd_set(const S1State* s){
  return s->y.dir && s->m.dir && s->d.dir;
}
bool s1state_ym_set(const S1State* s){ return s->y.dir && s->m.dir; }
bool s1state_y_set(const  S1State* s){ return !! s->y.dir; }
bool s1state_has_filter(const S1State* s){ return s1state_y_set(s); }

void s1state_clamp(S1State* s){
  year_t_clamp(&s->y);
  month_t_clamp(&s->m);
  day_t_clamp(&s->d);
}

void s1state_sp_ymd(S1State* s){
  snprintf(
    s->path, PATH_MAX, "%s/%04d/%02d/%02d",
    s->root_dirname,
    s->y.filter.value,
    s->m.filter.value,
    s->d.filter.value
  );
}
void s1state_sp_ym(S1State* s){
  snprintf(
    s->path, PATH_MAX, "%s/%04d/%02d",
    s->root_dirname,
    s->y.filter.value,
    s->m.filter.value
  );
}
void s1state_sp_y(S1State* s){
  snprintf(
    s->path, PATH_MAX, "%s/%04d",
    s->root_dirname,
    s->y.filter.value
  );
}
void s1state_sp(S1State* s){
  snprintf(
    s->path, PATH_MAX, "%s",
    s->root_dirname
  );
}

void s1state_setpath(S1State* s){
  const bool y = ! s->y.filter.null;
  const bool m = ! s->m.filter.null;
  const bool d = ! s->d.filter.null;
  s->ptype = 4*(y?1:0) + 2*(m?1:0) + (d?1:0);
  switch(s->ptype){
    case 7:  s1state_sp_ymd(s); break;
    case 6:  s1state_sp_ym(s);  break;
    case 4:  s1state_sp_y(s);   break;
    default: s1state_sp(s);     break;
  }
}
