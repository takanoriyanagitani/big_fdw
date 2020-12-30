#pragma once

#include <sys/types.h>
#include <sys/stat.h>

#include <commands/explain.h>
#include <utils/rel.h>

#include "option.h"

static void s1_explain(ForeignScanState* f, ExplainState* e){
  S1Option o = {0};
  s1_get_option(RelationGetRelid(f->ss.ss_currentRelation), &o);

  for(; !! o.root_dirname;){
    ExplainPropertyText("Foreign root dir", o.root_dirname, e);
    for(; !! e->costs;){
      struct stat s = {0};
      for(; 0==stat(o.root_dirname, &s);){
        ExplainPropertyInteger("Foreign root size", "b", s.st_size, e);
        break;
      }
      break;
    }
    break;
  }
}
