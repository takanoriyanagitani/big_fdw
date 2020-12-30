#pragma once

#include <optimizer/paths.h>
#include <optimizer/pathnode.h>

#include "c_path.h"

static void s1_path(PlannerInfo* p, RelOptInfo* r, Oid o){
  BlockNumber npage  = 1;
  double      ntuple = 86400.0 * 10.0; // max ntuple / day

  Cost start   = c_start_cost(r);
  Cost storage = c_storage_cost(seq_page_cost, npage);
  Cost cpu     = c_cpu_total_cost(
    c_cpu_cost(cpu_tuple_cost, r),
    ntuple
  );

  Cost total = c_total_cost(
    start,
    cpu,
    storage
  );
  add_path(r, (Path*)create_foreignscan_path(
    p,
    r,
    NULL, // default path
    r->rows,
    start,
    total,
    NIL,  // no pathkeys
    NULL, // no outer rel
    NULL, // no extra plan
    NIL   // no private data
  ));
}
