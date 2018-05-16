m ::(Ord a) => [a] -> a
m [] = error"fuck empty"
m [x] = x
m (x:xs) = max x $ m xs

m' ::(Ord a) => [a] -> a
m' = foldl1 max