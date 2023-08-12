
unsigned long long get_factorial(int num){
	if(num>20 || num < 0){
		return 0;
	}
	else if(num <= 1) return 1;
	return num*get_factorial(num-1);
}
