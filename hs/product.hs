p :: (Num a) => [a] -> a
p = foldl (*) 1