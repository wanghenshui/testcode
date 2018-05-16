e ::(Eq a) => a ->[a] -> Bool
e a [] = False
e a (x:xs)
 | a == x = True
 | otherwise = a `e` xs

--fold base
e'::(Eq a) => a ->[a] -> Bool 
e' y ys = foldr (\x acc -> if x == y then True else acc) False ys