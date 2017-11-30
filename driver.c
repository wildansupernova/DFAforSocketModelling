#include <stdio.h>
#include <string.h>
typedef char ElType[255];

#define BrsMin 1
#define BrsMax 100
#define KolMin 1
#define KolMax 100

typedef struct { 
	char Memc [255]; /* banyaknya/ukuran kolom yg terdefinisi */
} tabel[90][90];
typedef struct { 
	char Mem[30][30][255];
    int NBrsEff; /* banyaknya/ukuran baris yg terdefinisi */
	int NKolEff; /* banyaknya/ukuran kolom yg terdefinisi */
} MATRIKS;
/* *** Selektor *** */
#define NBrsEff(M) (M).NBrsEff
#define NKolEff(M) (M).NKolEff
#define Elmt(M,i,j) (M).Mem[(i)][(j)]

int caridibaris(ElType x, MATRIKS m, int baris){
	int i=0,hasil=0;
	
	for(i=1;i<=NKolEff(m);i++){
		if(strcmp(x,m.Mem[baris][i])==0){
			hasil = i;
			break;
		}
	}
	return hasil ;
}
int caridikolom(ElType x, MATRIKS m, int kolom){
	int i=0,hasil=0;
	for(i=1;i<=NBrsEff(m);i++){
		if(strcmp(x,m.Mem[i][kolom])==0){
			hasil=i;
			break;
		}
	}
	return hasil ;
}


int main(){
	MATRIKS tab;
	//Pembacaan File
	printf("");
	FILE *fp;
    ElType buff;
	char namafile[255];
	printf("Nama File nya : ");
	scanf("%s",namafile);
	fp = fopen(namafile, "r");
	if (fp == NULL){
		printf("File kosong atau tidak ada \n");
		fclose(fp); //exit
		return 0 ;
	}
    fscanf(fp, "%s", buff);
	if (buff[0]!='#'){
		printf("File tidak sesuai format\n");
		return 0; //exit
	}
	fscanf(fp, "%s", buff);
	int i = 0;
	//Pembacaan State
	printf("+++Pembacaan State loading..........+++\n");
	while(buff[0]!='#'){
		i++;
		printf("+++Pembacaan state  %s....+++\n",buff);
		strcpy(tab.Mem[i][0],buff);
		fscanf(fp, "%s", buff);
	}
	
	NBrsEff(tab) = i;

	//Pembacaan Simbol
	printf("+++Pembacaan simbol loading..........+++\n");
	i = 0;
	fscanf(fp, "%s", buff);
	while(buff[0]!='#'){
		i++;
		printf("+++Pembacaan simbol  %s....+++\n",buff);
		strcpy(tab.Mem[0][i],buff);
		fscanf(fp, "%s", buff);
	}
	
	NKolEff(tab) = i;
	//////////////////
	
	
	//Pembacaan State Awal
	printf("+++Pembacaan State Awal..........+++\n");
	ElType statenow;
	fscanf(fp, "%s", buff);
	strcpy(statenow,buff);
	printf("1 : %s\n", statenow );
	///////////
	
	
	//Pembacaan State Akhir
	printf("+++Pembacaan state akhir..........+++\n");
	fscanf(fp, "%s", buff);
	fscanf(fp, "%s", buff);
	MATRIKS endstate;
	
	i=0;
	while(buff[0]!='#'){
		i++;
		strcpy(endstate.Mem[1][i],buff);
		fscanf(fp, "%s", buff);
	}
	NBrsEff(endstate) = 1;
	NKolEff(endstate) = i;

	///////////////
	
	
	////Pembacaan Transition Function
	printf("+++Pembacaan fungsi Transisi(statesekarang,simbol)=nextstep  ..........+++\n");
	ElType baris,kolom, hasil;
	fscanf(fp, "%s %s %s", baris,kolom,hasil);
	while(baris[0]!='#'){
		i++;
		printf("+++Transisi(%s,%s)=%s  ..........+++\n",baris,kolom,hasil);
		strcpy(tab.Mem[caridikolom(baris,tab,0)][caridibaris(kolom,tab,0)],hasil);
		fscanf(fp, "%s %s %s", baris,kolom,hasil);
	}
	int j=0;
	i=0;
	/*for(i=1;i<=NBrsEff(tab);i++){
		for(j=1;j<=NKolEff(tab);j++){
			printf("%s\n", tab.Mem[i][j]);
		}
	}*/
	////////////////
	MATRIKS masukan;
	int n;
	printf("Masukan Jumlah Input : ");
	scanf("%d",&n);
	
	for(i=1;i<=n;i++){
		scanf("%s",masukan.Mem[1][i]);
	}
	printf("Path yang terbentuk : \n");
	for(i=1;i<=n;i++){
		printf("q%s > ",statenow);
		int indbar,indkol;
		indbar = caridikolom(statenow,tab,0);
		indkol = caridibaris(masukan.Mem[1][i],tab,0);
		strcpy(statenow,tab.Mem[indbar][indkol]);
	}
	printf("q%s\n",statenow);
	
	if (caridibaris(statenow,endstate,1)!=0){
		printf("Hasil : Accepted\n");
	} else{
		printf("Hasil : Rejected\n");
	}
	fclose(fp);
}