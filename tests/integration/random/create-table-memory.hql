use "/";
drop table if exists RandomTest;
create table RandomTest (
  Field,
  T1,
  T2,
  T3,
  T4,
  T5,
  T6,
  T7,
  ACCESS GROUP default (Field) IN_MEMORY,
  ACCESS GROUP AT1 (T1) IN_MEMORY,
  ACCESS GROUP AT2 (T2) IN_MEMORY,
  ACCESS GROUP AT3 (T3) IN_MEMORY,
  ACCESS GROUP AT4 (T4) IN_MEMORY,
  ACCESS GROUP AT5 (T5) IN_MEMORY,
  ACCESS GROUP AT6 (T6) IN_MEMORY,
  ACCESS GROUP AT7 (T7) IN_MEMORY
) COMPRESSOR="none";
