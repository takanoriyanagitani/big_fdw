#pragma once

static TupleTableSlot* s1_iterate(ForeignScanState* f){
  TupleTableSlot* s = f->ss.ss_ScanTupleSlot;
  ExecClearTuple(s);
  return s;
}
