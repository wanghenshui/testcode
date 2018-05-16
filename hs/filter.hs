f :: (a -> Bool ) -> [a] ->[a]
f _ [] =[]
f p (x:xs) 
 | p x = x:f p xs
 | otherwise = f p xs

-- 刚才下面这个实现和上面的| 对齐导致一直没编过。。。。
f' :: (a -> Bool ) -> [a] ->[a]
f' p = foldr (\x acc -> if (p x) then x:acc else acc ) []