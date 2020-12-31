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
  SELECT y,m,d,c,v,t FROM t1
  WHERE
    y     =  2020::SMALLINT
    AND m =    12::SMALLINT
    AND d =    31::SMALLINT
    AND c = 'JPY'::TEXT
    --AND c = 'USD'::TEXT
)
SELECT * FROM t0 LIMIT 1
;

DROP FOREIGN TABLE t1;
DROP SERVER        sv1;
DROP EXTENSION     s1_fdw;
