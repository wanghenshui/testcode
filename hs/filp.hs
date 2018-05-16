f :: (a-> b-> c) -> b-> a-> c
f g x y = g y x
--f g = w where w x y = g y x