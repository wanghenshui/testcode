#ifndef __SELECTOR__
#define __SELECTOR__

template<bool PARAMETER> selector{};

typedef selector<true> true_type;
typedef selector<false> false_type;

#endif
