#pragma once

static void s1_end(ForeignScanState* f){
  for(S1State* s=f->fdw_state; NULL != s;){
    FreeDir(s->root);
    FreeDir(s->y.dir);
    FreeDir(s->m.dir);
    FreeDir(s->d.dir);
    break;
  }
}
