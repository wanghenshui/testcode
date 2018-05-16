m :: (a -> b) -> [a] -> [b]
m _ [] = []
m f (x:xs) = f x :map f xs

--fold base
m' ::(a -> b) -> [a] -> [b]
m' f xs = foldr (\x acc -> f x :acc ) [] xs