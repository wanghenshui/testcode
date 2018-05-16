s ::(Num a) => [a] -> a
--s xs = foldl (\acc x -> acc+x) 0 xs
--s xs = foldl (+) 0 xs
--currying
s = foldl (+) 0
