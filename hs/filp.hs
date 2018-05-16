f :: (a->b->c) ->(b->a->c)
f q = w 
 where w x y = q x y
