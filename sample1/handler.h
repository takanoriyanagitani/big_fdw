#pragma once

#include <postgres.h>

#include <foreign/fdwapi.h>

Datum s1_fdw_handler(PG_FUNCTION_ARGS){
  FdwRoutine* r = makeNode(FdwRoutine);
  PG_RETURN_POINTER(r);
}
