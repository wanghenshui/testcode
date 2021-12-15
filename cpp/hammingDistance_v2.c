int hammingDistance(int x, int y) 
{
//((（x>>i）& 1))^((y>>i)&1))
     int sum =0;
     for (int i=0; i!=9; i++)
     {
         if(((x>>i)&1)^((y>>i)&1))
         {
            printf("((x>>i)&1)=[%d],((y>>i)&1)=[%d],i=[%d]\n",((x>>i)&1),((y>>i)&1),i);
            sum+=1;
         }
     }

     return sum;
}
//限于精度。大数不可行。