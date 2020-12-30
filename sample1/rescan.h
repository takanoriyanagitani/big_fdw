#pragma once

static void s1_rescan(ForeignScanState* f){
  for(S1State* s = f->fdw_state; NULL != s->root;){
    rewinddir(s->root);
    break;
  }
}
