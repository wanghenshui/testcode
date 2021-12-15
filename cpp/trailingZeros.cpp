#include <gtest/gtest.h>
#include "trailingZeros.h"


TEST(trailingZeros_case, trailingZeros__)
{
	trailing_zeros::Solution s;
	EXPECT_EQ(s.trailingZeros(1),0);
	EXPECT_EQ(s.trailingZeros(11), 2);
};
