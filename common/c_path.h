#pragma once

double c_cpu_cost(double tuple_cost, const RelOptInfo* r){
  return tuple_cost + r->baserestrictcost.per_tuple;
}

double c_storage_cost(double seq_page, double npage){
  return seq_page * npage;
}

double c_cpu_total_cost(double cpu_cost, double ntuple){
  return cpu_cost * ntuple;
}

double c_start_cost(const RelOptInfo* r){
  return r->baserestrictcost.startup;
}

double c_total_cost(double start, double cpu, double storage){
  return start + cpu + storage;
}
