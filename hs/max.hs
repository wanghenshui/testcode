m :: (Ord a) => a->a->a
m a b
 | a < b= b
 | otherwise = a