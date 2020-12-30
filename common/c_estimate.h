#pragma once

#include <optimizer/optimizer.h>

#include "c_f8.h"

double c_estimate_selectivity(PlannerInfo* p, RelOptInfo* r){
  return clauselist_selectivity(
    p,
    r->baserestrictinfo,
    0,
    JOIN_INNER,
    NULL
  );
}

double c_estimate_density(double ntuple, double npage){
  double t = f8_max(0.0, ntuple);
  double p = f8_max(1.0, npage);
  return t / p;
}

double c_estimate_ntuple_by_density(double density, double npage){
  const double d = f8_max(0.0, density);
  const double p = f8_max(0.0, npage);
  return clamp_row_est(d * p);
}

double c_estimate_ntuple(
  const RelOptInfo*  r,
  const void*        param,
  double cb_analyze(const RelOptInfo*,const void*),
  double cb_default(const RelOptInfo*,const void*)
){
  bool is_analyzed = 0 < r->pages;
  switch(is_analyzed){
    case true: return cb_analyze(r, param);
    default:   return cb_default(r, param);
  }
}
