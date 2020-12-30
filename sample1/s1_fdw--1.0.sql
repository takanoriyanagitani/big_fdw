\echo Use "CREATE EXTENSION s1_fdw" to load this file. \quit

CREATE FUNCTION s1_fdw_handler()
RETURNS fdw_handler
AS 'MODULE_PATHNAME'
LANGUAGE C STRICT;

CREATE FUNCTION s1_fdw_validator(text[], oid)
RETURNS void
AS 'MODULE_PATHNAME'
LANGUAGE C STRICT;

CREATE FOREIGN DATA WRAPPER s1_fdw
HANDLER s1_fdw_handler
VALIDATOR s1_fdw_validator;
