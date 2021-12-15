def twoSum(self, nums, target):
    dict = {}
    for i, num in enumerate(nums):      #enumerate 返回带有索引的对象 index value对。
        if target - num in dict:           """*****字典 in d表示返回key
                                        >>> dic{'father': 'b', 'name': 'a', 'mother': 'c'}
                                        >>> for obj in dic:
                                            print obj

                                        father
                                        name
                                        mothe"""
            return dict[target - num] , i  #返回两个索引返回字典的值
        dict[num] = i                       #将数组的值作为key，索引作为value创建字典dict