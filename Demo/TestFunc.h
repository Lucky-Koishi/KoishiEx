
#include <time.h>

clock_t start, end;
#define TIC start = clock()
#define TOC end = clock();printf("%f seconds.\n", (double)(end-start)/CLOCKS_PER_SEC)

void disp(stream &s, int l = 0){
	if(l>s.len || l == 0){
		l = s.len;
	}
	int i;
	for(i = 0;i<l;i++){
		printf("%d ", s[i]);
	}
}
void dispx(stream &s, int l = 0){
	if(l>s.len || l == 0){
		l = s.len;
	}
	int i;
	for(i = 0;i<l;i++){
		printf("%02X ", s[i]);
	}
}
void disps(stream &s, int l = 0){
	if(l>s.len || l == 0){
		l = s.len;
	}
	int i;
	for(i = 0;i<l;i++){
		printf("%c", s[i]);
	}
}

void disp(queue &s, int l = 0){
	if(l>s.size() || l == 0){
		l = s.size();;
	}
	int i;
	for(i = 0;i<l;i++){
		printf("%d ", s[i]);
	}
}

void disp(int l){
	printf("%d", l);
}

void dispb(word s){
	word mask = 1;
	for(int i = 0;i<16;i++){
		if(s & mask){
			printf("1");
		}else{
			printf("0");
		}
		mask <<= 1;
	}
}


void disp(int* l, int len){
	for(int i =0 ;i<len;i++){
		printf("%d ", l[i]);
	}
}


str num2str(unsigned int n){
	if(n == 0){
		return "0";
	}
	str s = "";
	while(n){
		char d = '0' + n % 10;
		s = d + s;
		n /= 10;
	}
	return s;
}

