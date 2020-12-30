#pragma once

static TupleTableSlot* s1i_ymdc(
  ForeignScanState* f,
  TupleTableSlot*   slot,
  S1State*          s
){
  TupleDesc t = slot->tts_tupleDescriptor;
  switch(t->natts){
    case 6:  break;
    default: return slot;
  }
  for(; NULL != s->file;){
    switch(fread(s->buf, 1, 16, s->file)){
      case 16: break;
      default: return slot;
    }
    Datum* v = slot->tts_values;
    bool*  n = slot->tts_isnull;
    v[0] = Int16GetDatum(2020);
    v[1] = Int16GetDatum(12);
    v[2] = Int16GetDatum(31);
    v[3] = PointerGetDatum(s->c.filter);
    n[0]=false;
    n[1]=false;
    n[2]=false;
    n[3]=false;
    n[4]=true;
    n[5]=true;
    ExecStoreVirtualTuple(slot);
    break;
  }
  return slot;
}

static TupleTableSlot* s1_iterate(ForeignScanState* f){
  TupleTableSlot* s = f->ss.ss_ScanTupleSlot;
  ExecClearTuple(s);
  S1State* state = (S1State*)f->fdw_state;
  switch(state->ptype){
    case 15: return s1i_ymdc(f, s, state);
    default: break;
  }
  return s;
}
