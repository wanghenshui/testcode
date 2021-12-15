int hammingDistance(int x, int y) {
	if((x^y)==0) return 0;
	return (x^y)%2 + hammingDistance(x/2,y/2);
}