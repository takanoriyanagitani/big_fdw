#pragma once

#include <postgres.h>

#include <foreign/fdwapi.h>
#include <access/reloptions.h>
#include <commands/defrem.h>
#include <catalog/pg_foreign_table.h>

Datum s1_fdw_validator(PG_FUNCTION_ARGS){
  PG_RETURN_VOID();
}
