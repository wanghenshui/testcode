int getSum(int a, int b) {
        if (b)
            return getSum(a ^ b, (a & b) << 1);
        else
            return a;
}

int add(int a, int b) { int c = a & b, r = a ^ b; return c == 0 ? r : add(r, c << 1); }