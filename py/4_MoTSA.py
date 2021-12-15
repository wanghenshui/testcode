class Solution(object):
    def findMedianSortedArrays(self, nums1, nums2):
        """
        :type nums1: List[int]
        :type nums2: List[int]
        :rtype: float
        """

        m = len(nums1);
        n = len(nums2);
        if m > n:
            nums1, nums2, m, n = nums2, nums1, n, m
        imin = 0;
        imax = m;

        while imin <= imax:
            i = (imin + imax) / 2;
            j = (m + n + 1) / 2 - i;
            if i > 0 and nums1[i - 1] > nums2[j]:
                imax = i - 1;                                #二分寻值，用i=i-1也能ac但是慢。
            elif i < m and nums1[i] < nums2[j - 1]:
                imin = i + 1;
            else:
                if (i == 0):                                #分别讨论左值和右值。
                    maxleft = nums2[j - 1];
                elif (j == 0):                              #在nums1=[1] nums2=[1]的情况下需要考虑
                                                            #我一开始认为n>m不用j==0的情况，但是考虑到n与m相等或者相近的情况需要考虑。
                    maxleft = nums1[i - 1];
                else:
                    maxleft = max(nums1[i - 1], nums2[j - 1])
                if (m + n) % 2 == 1:                        #若m+n奇数中位数直接就是中间值，即maxleft;
                    return maxleft;
                if i == m:
                    minright = nums2[j];
                elif j == n:                                   #在nums1=[1] nums2=[1]的情况下需要考虑同左值
                    minright = nums1[i];
                else:
                    minright = min(nums1[i], nums2[j])
                return (maxleft + minright) / 2.0;

