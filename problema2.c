#include <stdio.h>
#include <stdlib.h>
#include <time.h>
int n;

int reflexiva(int matriz[n][n]){
	for(int i = 0; i<n; i++){
		if(matriz[i][i] != 1){
			return 0;
		}
	}
	return 1;
}

int simetrica(int matriz[n][n]){
	for(int i=0; i<n; i++){
		for(int j=0; j<n; j++){
			if(i!=j){
				if(matriz[i][j]!=matriz[j][i]){
					return 0;
				}
			}
		}
	}
	return 1;
}

int funcional(int matriz[n][n]){
	for(int i=0; i<n; i++){
		for(int j=0, k=0; j<n; j++){
			if(matriz[i][j]==1){
				k++;
			}
			if(k>1){
				return 0;
			}
		}
	}
	return 1;
}

int injetora(int matriz[n][n]){
	for(int i=0; i<n; i++){
		for(int j=0, k=0; j<n; j++){
			if(matriz[j][i]==1){
				k++;
			}
			if(k>1){
				return 0;
			}
		}
	}
	return 1;
}

int total(int matriz[n][n]){
	for(int i=0; i<n; i++){
		int k=n;
		for(int j=0; j<n; j++){
			if(matriz[i][j]==1){
				k--;
			}
		}
		if(k==n){
			return 0;
		}
	}
	return 1;
}

int sobrejetora(int matriz[n][n]){
	for(int i=0; i<n; i++){
		int k=n;
		for(int j=0; j<n; j++){
			if(matriz[j][i]==1){
				k--;
			}
		}
		if(k==n){
			return 0;
		}
	}
	return 1;
}

int main(){
	printf("Matriz: ");
	scanf("%d",&n);
	srand(time(NULL));
	
	int matriz[n][n];
	int vetor[6], p=0;
	
	for(int i = 0; i<n; i++){
		for(int j = 0; j<n; j++){
			matriz[i][j] = rand()%2;
			printf("%d ",matriz[i][j]);
		}
		printf("\n");
	}
	
	vetor[p]=reflexiva(matriz);
	p++;
	vetor[p]=simetrica(matriz);
	p++;
	vetor[p]=funcional(matriz);
	p++;
	vetor[p]=injetora(matriz);
	p++;
	vetor[p]=total(matriz);
	p++;
	vetor[p]=sobrejetora(matriz);
	
	printf("\n");
	for(int i=0; i<6; i++){
		printf("%d ", vetor[i]);
	}
	
	return 0;
}
