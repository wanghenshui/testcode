bool isPowerOfThree(int n)
{
    if(n==1)
        return 1;
        
    if ((n==0)||n%3!=0)
        return 0;
    else 
    {
        return n/3==1?1:isPowerOfThree(n/3);
    }
   
}