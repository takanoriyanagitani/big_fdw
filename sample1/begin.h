#pragma once

#include <utils/builtins.h>

#include "c_begin.h"

static void s1_sf_set4(i4n* i, OpExpr* o, Const* c){
  for(; opexpr_is_smli_eq(o);){
    i4n_set_const(i, c);
    break;
  }
}

static void s1_sf_set3(i3n* i, OpExpr* o, Const* c){
  for(; opexpr_is_smli_eq(o);){
    i3n_set_const(i, c);
    break;
  }
}

static void s1_sf_sety(S1State* s, OpExpr* o, Const* c){
  s1_sf_set4(&s->y.filter, o, c);
}
static void s1_sf_setm(S1State* s, OpExpr* o, Const* c){
  s1_sf_set3(&s->m.filter, o, c);
}
static void s1_sf_setd(S1State* s, OpExpr* o, Const* c){
  s1_sf_set3(&s->d.filter, o, c);
}

static void s1_sf_setc(S1State* s, OpExpr* o, Const* c){
  bool is_string = IsA(c, String);
  for(; is_string;){
    const char* code = TextDatumGetCString(c->constvalue);
    strncpy(s->c.filter, code, 4);
    s->c.filter[3] = '\0';
    break;
  }
}

static void s1_sf_vc(
  void* f, const ScanState* s, OpExpr* o, Var* v, Const* c
){
  TupleDesc t = s->ss_currentRelation->rd_att;
  const char* col = NameStr(TupleDescAttr(t, v->varattno-1)->attname);
  S1State* s1 = (S1State*)f;
  for(; NULL != col;){
    switch(col[0]){
      case 'y': s1_sf_sety(s1, o, c); return;
      case 'm': s1_sf_setm(s1, o, c); return;
      case 'd': s1_sf_setd(s1, o, c); return;
      case 'c': s1_sf_setc(s1, o, c); return;
        return;
      default: return;
    }
    break;
  }
}

static void s1_sf_expr(void* f, const ScanState* s, OpExpr* o){
  c_begin_get_vc(
    o->args,
    s,
    o,
    f,
    s1_sf_vc
  );
}

static void s1_set_filter(S1State* f, const ScanState* s){
  List* l = s->ps.plan->qual;
  ListCell* i = NULL;
  foreach(i, l){
    Expr* e = lfirst(i);
    c_begin_get_expr(e, s, f, s1_sf_expr);
  }
  s1state_clamp(f);
  for(; !! f->root_dirname;){
    s1state_setpath(f);
    break;
  }
}

static void s1_begin(ForeignScanState* f, int eflags){
  int  i = eflags & EXEC_FLAG_EXPLAIN_ONLY;
  bool explain_only = !! i;
  for(; ! explain_only;){
    S1State* s = s1state_new();
    f->fdw_state = s;
    S1Option o = {0};
    s1_get_option(RelationGetRelid(f->ss.ss_currentRelation), &o);
    for(; NULL != o.root_dirname;){
      s->root_dirname = o.root_dirname;
      s1_set_filter(s, &f->ss);
      s->root         = AllocateDir(s->root_dirname);
      for(; NULL==s->root;){
        elog(ERROR, "Unable to open dir: %s", s->root_dirname);
        break;
      }
      break;
    }
    break;
  }
}
