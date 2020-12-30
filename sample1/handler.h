#pragma once

#include <postgres.h>

#include <foreign/fdwapi.h>

#include "state.h"

#include "relsize.h"
#include "path.h"
#include "plan.h"
#include "explain.h"
#include "begin.h"
#include "iterate.h"
#include "rescan.h"
#include "end.h"

Datum s1_fdw_handler(PG_FUNCTION_ARGS){
  FdwRoutine* r = makeNode(FdwRoutine);

  r->GetForeignRelSize  = s1_rel;
  r->GetForeignPaths    = s1_path;
  r->GetForeignPlan     = s1_plan;
  r->ExplainForeignScan = s1_explain;
  r->BeginForeignScan   = s1_begin;
  r->IterateForeignScan = s1_iterate;
  r->ReScanForeignScan  = s1_rescan;
  r->EndForeignScan     = s1_end;

  PG_RETURN_POINTER(r);
}
