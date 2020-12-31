CREATE EXTENSION     IF NOT EXISTS s1_fdw;
CREATE SERVER        IF NOT EXISTS sv1 FOREIGN DATA WRAPPER s1_fdw;

CREATE FOREIGN TABLE IF NOT EXISTS t1(
  y SMALLINT, -- year;      YYYY
  m SMALLINT, -- month;     MM
  d SMALLINT, -- day;       DD
  c TEXT,     -- currency;  USD,JPY,...
  v FLOAT8,   -- rate;      103.19 yen/usd
  t FLOAT8    -- unixtime;  1609281603.4757745
) SERVER sv1 OPTIONS(
  rootdir '/path/to/root.d' -- /path/to/root.d/2020/12/30/JPY/rate.dat'
);

WITH t0 AS (
  WITH c0 AS (
    SELECT
      2020::SMALLINT AS cy,
      12::SMALLINT   AS cm,
      31::SMALLINT   AS cd,
      'JPY'::TEXT    AS cc
  )
  SELECT y,m,d,c,v,t FROM t1, c0
  WHERE
    y     = c0.cy
    AND m = c0.cm
    AND d = c0.cd
    AND c = c0.cc
)
SELECT * FROM t0 LIMIT 1
;

DROP FOREIGN TABLE t1;
DROP SERVER        sv1;
DROP EXTENSION     s1_fdw;
