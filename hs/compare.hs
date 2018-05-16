c :: (Ord a) => a->a->Ordering
a `c` b
 | a == b = EQ
 | a >= b = GT
 | otherwise = LT