#pragma once

#include <optimizer/optimizer.h>

#include "c_estimate.h"

static double s1_estimate_ntuple_a(const RelOptInfo* r, const void* v){
  const double density = c_estimate_density(r->tuples, r->pages);
  const double npage   = 1.0;
  return c_estimate_ntuple_by_density(density, npage);
}
static double s1_estimate_ntuple_d(const RelOptInfo* r, const void* v){
  return 86400.0 * 10.0; // 10 trades / second
}

static double s1_estimate_ntuple(PlannerInfo* p, RelOptInfo* r, Oid o){
  return c_estimate_ntuple(
    r,
    NULL,
    s1_estimate_ntuple_a,
    s1_estimate_ntuple_d
  );
}

static double s1_estimate_rowcnt(PlannerInfo* p, RelOptInfo* r, Oid o){
  double t = s1_estimate_ntuple(p, r, o);
  double s = c_estimate_selectivity(p, r);
  return clamp_row_est(t * s);
}

static void s1_rel(PlannerInfo* p, RelOptInfo* r, Oid o){
  r->rows = s1_estimate_rowcnt(p, r, o);
}
