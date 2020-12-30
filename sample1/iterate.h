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
    v[0] = Int16GetDatum(s->y.filter.value);
    v[1] = Int16GetDatum(s->m.filter.value);
    v[2] = Int16GetDatum(s->d.filter.value);
    v[3] = code_topg(&s->c);
    v[4] = Float8GetDatum(*s->prate);
    v[5] = Float8GetDatum(*s->punixtime);
    n[0]=false;
    n[1]=false;
    n[2]=false;
    n[3]=false;
    n[4]=false;
    n[5]=false;
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
