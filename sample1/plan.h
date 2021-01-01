#pragma once

#include <optimizer/planmain.h>
#include <optimizer/restrictinfo.h>

static ForeignScan* s1_plan(
  PlannerInfo* p,
  RelOptInfo*  r,
  Oid          o,
  ForeignPath* path,
  List*        l,
  List*        s,
  Plan*        plan
){
  s = extract_actual_clauses(s, false);
  Query* q  = p->parse;
  List*  sc = NULL == q ? NIL : q->sortClause;
  ListCell* i = NULL;
  foreach(i, sc){ elog(NOTICE, "sort found."); }
  return make_foreignscan(
    l,
    s,
    r->relid,
    NIL, // no expressions to evaluate
    path->fdw_private,
    NIL,
    NIL,
    plan
  );
}
