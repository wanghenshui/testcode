template <typename T>
void fill(T* a,int begin,int end,const T& value)
{
	 for(int i=begin;i!=end;++i)
	 {
	 	a[i]= value;
	 }
}