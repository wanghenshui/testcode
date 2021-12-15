bool isPowerOfFour(int n)
{
    if (1==n)
        return 1;
    
    if ((n<=0)||(n%4)!=0)
        return 0;
    else 
    {
        //return (n/4==1)?1:isPowerOfFour(n/4);
        return n&(n-1)?0:isPowerOfFour(n/4);
    }
}