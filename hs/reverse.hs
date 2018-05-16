r :: [a] -> [a]
r [] =[]
r (x:xs) = r xs ++ [x]

r' :: [a] -> [a]
r'=foldl (flip(:)) []