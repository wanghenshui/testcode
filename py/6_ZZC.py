class Solution(object):
    def convert(self, s, numRows):
        """
        :type s: str
        :type numRows: int
        :rtype: str
        """                                 # 整体思路是分成numRows个字符串，每个字符串在结尾添加元素。
        L = [''] * numRows;
        index = 0;
        step = 1;

        if numRows == 1 or numRows >= len(s):
            return s;

        for c in s:
            L[index] += c;

            if index == numRows - 1:
                step = -1;                  #在逆向-1过程中应设置index=0时改变方向。
            elif index == 0:
                step = 1;
            index += step;

        return ''.join(L);