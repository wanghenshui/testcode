int hammingDistance(int x, int y) 
{

     int sum =0;
     for (int i=0; i!=x+y; i++)
     {
         if((x&(1<<i))^(y&(1<<i)))
         {
            sum+=1;
         }
     }
     
     return sum;
}

//wrong 93 12