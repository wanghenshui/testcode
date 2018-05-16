--?
z :: (a->b->c) ->[a] ->[b] ->[c]
z _ [] _ = []
z _ _ [] = []
z f (x:xs) (y:ys) =f x y :z f xs ys
--f for compose