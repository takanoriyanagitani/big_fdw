CREATE EXTENSION     IF NOT EXISTS s1_fdw;
CREATE SERVER        IF NOT EXISTS sv1 FOREIGN DATA WRAPPER s1_fdw;

CREATE FOREIGN TABLE IF NOT EXISTS t1(
  y SMALLINT, -- year;      YYYY
  m SMALLINT, -- month;     MM
  d SMALLINT, -- day;       DD
  c TEXT,     -- currency;  USD,JPY,...
  t FLOAT8    -- unixtime;  1609281603.4757745
) SERVER sv1 OPTIONS(
  rootdir '/path/to/root.d' -- /path/to/root.d/2020/12/30/JPY/rate.dat'
);

--EXPLAIN ANALYZE VERBOSE SELECT * FROM bt WHERE d_type=4;

DROP FOREIGN TABLE t1;
DROP SERVER        sv1;
DROP EXTENSION     s1_fdw;
