
#include <time.h>

clock_t start, end;
#define TIC start = clock()
#define TOC end = clock();printf("%f seconds.\n", (double)(end-start)/CLOCKS_PER_SEC)

void disp(stream &s, int l = 0, bool pages = false){
	if(l>s.getLen() || l == 0){
		l = s.getLen();
	}
	int i, j, k;
	k = 0;
	for(i = 0;i<l;i+=16){
		printf("%08X: ", k*16);
		for(j = 0;j<16;j++){
			if(i+j<l){
				printf("%02X ", s[i+j]);
			}
		}
		printf("\n");
		k++;
		if(k%20 == 0 && pages)
			system("pause");
	}
}

void disp(int l){
	printf("%d", l);
}

void disp(int* l, int len){
	for(int i =0 ;i<len;i++){
		printf("%d ", l[i]);
	}
}

void disp(matrix _mat){
	int i,j;
	for(i=0;i<_mat.getRowCount();i++){
		for(j=0;j<_mat.getColumnCount();j++){
			printf("%08X ", (unsigned long)(b32)_mat[i][j]);
		}
		printf("\n");
	}
}

void disp0(matrix _mat){
	int i,j;
	for(i=0;i<_mat.getRowCount();i++){
		for(j=0;j<_mat.getColumnCount();j++){
			if(_mat[i][j] != 0){
				printf("X");
			}else{
				printf("-");
			}
		}
		printf("\n");
	}
}