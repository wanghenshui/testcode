f :: (a -> Bool ) -> [a] ->[a]
f _ [] =[]
f p (x:xs) 
 | p x = x:f p xs
 | otherwise = f p xs