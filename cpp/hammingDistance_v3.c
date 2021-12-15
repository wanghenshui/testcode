int hammingDistance(int x, int y) 
{

    int sum =0;
    int v = x^y;
    while(v)
    {
        v&=(v-1);
        sum++;
    }

    return sum;
}