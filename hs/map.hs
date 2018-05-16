m :: (a -> b) -> [a] -> [b]
m _ [] = []
m f (x:xs) = f x :map f xs