r :: Int -> a->[a]
r n x
 | n<=0 =[]
 | otherwise = x:r (n-1) x