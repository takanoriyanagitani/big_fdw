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

SELECT COUNT(*) FROM t1
WHERE
  y     = 2020::SMALLINT
  AND m =   12::SMALLINT
  AND d =   31::SMALLINT
;

DROP FOREIGN TABLE t1;
DROP SERVER        sv1;
DROP EXTENSION     s1_fdw;
