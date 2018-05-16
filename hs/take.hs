t :: (Num i, Ord i) => i -> [a] ->[a]
t n _
 | n<=0 = []
t _ [] = []
t n (x:xs) =  x: t (n-1) xs