#include <iostream>

bool func(int);

int main(){
	int x = 32;
	std::cout << func(x) << std::endl; 

	return 0;
}

bool func(int x){
/*	if (x == 1){
		return(true);
	}
	if (x%2 == 1){
		return(false);
	}
*/
	if (x%2 == 1) {
		return (x == 1) ? true : false;
	}

	return func(x/2);
}
