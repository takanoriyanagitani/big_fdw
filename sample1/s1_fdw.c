#include <postgres.h>
#include <funcapi.h>

PG_MODULE_MAGIC;

PG_FUNCTION_INFO_V1(s1_fdw_handler);
PG_FUNCTION_INFO_V1(s1_fdw_validator);

#include "handler.h"
#include "validator.h"
