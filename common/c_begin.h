#pragma once

void c_begin_get_expr(
  Expr* e,
  const ScanState* s,
  void* param,
  void cb(void*,const ScanState*,OpExpr*)
){
  for(Node* n=(Node*)e; n && IsA(n, OpExpr);){
    cb(param, s, (OpExpr*)n);
    break;
  }
}

void c_begin_get_vc(
  List* l,
  const ScanState* s,
  OpExpr* o,
  void* param,
  void cb(void*,const ScanState*,OpExpr* o,Var*,Const*)
){
  for(; 2 == list_length(l);){
    for(Node* left=list_nth(l,0); IsA(left,Var);){
      for(Node* right=list_nth(l,1); IsA(right,Const);){
        cb(param, s, o, (Var*)left, (Const*)right);
        break;
      }
      break;
    }
    break;
  }
}

bool opexpr_is_text_eq(const OpExpr* o){ return 67 == o->opfuncid; }
bool opexpr_is_smli_eq(const OpExpr* o){ return 63 == o->opfuncid; }

int16_t i4c_alt(const Const* c, int16_t alt){
  for(; NULL != c;){
    for(; ! c->constisnull;){
      return DatumGetInt16(c->constvalue);
    }
    return alt;
  }
  return alt;
}
