/*Càlcul del polinomi característic*/

/*Fòrmula que fem servir per calcular el polinomi característic:
detA = sumatori(i=1,..., n) ( (-1)^(i+1) * a[i][1]*detA[i][1] )
*/

#include<stdio.h>
#include<stdlib.h>
#include<math.h>

typedef struct{
	int n, max;
	int *coef;
}polinomi;

polinomi det(polinomi **, int, int);
void prodPolEsc(polinomi, int, polinomi*);
void prodPol(polinomi, polinomi, polinomi*);
void sumaPol(polinomi, polinomi, polinomi*);
void alliberarPol(polinomi*);
polinomi inicialitzarPol(int);

/*Funció main*/
int main(void){
	int i, j, n, valor;
	polinomi carac, **a, *prim;
	FILE *entrada;
	char nom[30];
	
	printf("Nom del fitxer?\n");
	scanf(" %s", nom);
	entrada = fopen(nom, "r");
	if(entrada == NULL){
		printf("Error al obrir el fitxer\n");
		exit(2);
	}
	fscanf(entrada, "%d", &n);
	if(n<0){
		printf("El grau del polinomi no pot ser negatiu\n");
		exit(3);
	}
	prim = (polinomi*)malloc((n*n)*sizeof(polinomi));
	for(i=0; i<n*n; i++)
		prim[i] = inicialitzarPol(n);
	a = (polinomi**)malloc(n*sizeof(polinomi*));
	if(a == NULL){
		printf("No memory\n");
		exit(1);
	}
	/*DUBTE: QUÈ FA AQUÍ?*/
	a[0] = prim;
	for(i=1; i<n; i++)
		a[i] = a[i-1]+n;
 	while(fscanf(entrada, "%d%d%d", &i, &j, &valor)!=EOF)
		a[i][j].coef[0]=valor;
	fclose(entrada);
	
	/*Tenim una matriu A i ara volem (A-xI)*/
	for(i=0; i<n; i++){
		a[i][i].coef[1]=-1;
		a[i][i].n = 1;
	}
	/*Polinomi característic*/
	carac = det(a, n, n); /*n dim, n max*/

	printf("El polinomi característic que tenim és:\n\n");
	for(i=0; i<=n; i++){
		printf("%+d x^%d\n", carac.coef[i], i); 
	}
	alliberarPol(&carac);
	free(prim);
	for(i=0; i<n; i++)
		free(a[i]);
	free(a);
	return 0;
	/*escriure polinomi "%+dx^%d", coef[i], i
	alliberar memoria
	return 0*/
}


/*Funció: inicialitzar el polinomi amb el grau màxim m*/
polinomi inicialitzarPol(int m){
	polinomi poli;
	poli.max = m;
	poli.coef = (int*)calloc((m+1), sizeof(int));
	if(poli.coef == NULL){
		printf("No memory\n");
		exit(1);
	}
	poli.n = 0;
	poli.coef[0]=0;
	return poli;
}

/*Funció alliberar polinomi*/
void alliberarPol(polinomi *apPol){
	apPol->n=-1;
	apPol->max=-1;
	free(apPol->coef);
	apPol->coef=NULL;
	return;
}

/*Funció suma de polinomis*/
void sumaPol(polinomi p1, polinomi p2, polinomi *res){ /*res = resultat*/
	polinomi *ap1, *ap2;
	int i;
	/*Mirem quin té el grau més gran. No podrem assignar a un punter de polinomi un polinomi*/
	if(p1.n<=p2.n){
		ap1 = &p1;
		ap2 = &p2;
	}else{
		ap1 = &p2;
		ap2 = &p1;
	}
	for(i=0; i<=ap1->n; i++)
		res->coef[i] = ap1->coef[i] + ap2->coef[i];
	for(i=ap1->n+1; i<=ap2->n; i++) /*ap1->n+1 = (ap1->n)+1*/
		res->coef[i] = ap2->coef[i];
	/*Comprovació dels zeros*/
	for(i=ap2->n; i>=0 && res->coef[i]==0; i--); /*Instrucció buida, tot està dins del for*/
	res->n = i;
	return;
}

/*Funció producte de dos polinomis*/
void prodPol(polinomi p1, polinomi p2, polinomi *r){
	int i,j;
	/*Cas curiós on algun dels dos polinomis és zero*/
	if((p1.n==0 && p1.coef[0]==0) || (p2.n==0 && p1.coef[0]==0)){
		r->n=0;
		r->coef[0]=0;
		return;
	}
	r->n = p1.n + p2.n;
	if(r->n > r->max){
		puts("Error en el producte. Grau massa gran\n"); /*Aquí fa servir puts equivalentment a printf*/
		exit(1);
	}
	/*Cas general. No el vam fer a classe*/
	/*Li posaré al polinomi resultat tots els coeficients iguals a zero per començar*/
	for(i=0; i<=r->n; i++)
		r->coef[i] = 0;
	
	for(i=0; i<=p1.n; i++){
		for(j=0; j<=p2.n; j++)
			r->coef[i+j] += p1.coef[i]* p2.coef[j];
	}
	return;
}

/*Funció producte polinomi per escalar. No feta a classe*/
void prodPolEsc(polinomi p1, int num, polinomi *res){
	int i;
	for(i=0; i<= p1.n; i++)
		res->coef[i] = num*p1.coef[i];
	return;
}

/*Funció determinant. Crec que suposem n>1*/
polinomi det(polinomi **a, int n, int gr){ /*gr = grau màx*/
	polinomi deter, calcul, terme, **nova, aux;
	int i, j, sing;
	deter = inicialitzarPol(gr);
	calcul = inicialitzarPol(gr);
	terme = inicialitzarPol(gr);
	aux = inicialitzarPol(gr);
	
	/*Cas simple*/
	if(n==2){
		prodPol(a[0][0], a[1][1], &terme);
		prodPol(a[1][0], a[0][1], &calcul);
		prodPolEsc(calcul, -1, &aux);
		sumaPol(terme, aux, &deter);
		alliberarPol(&calcul);
		alliberarPol(&terme);
		alliberarPol(&aux);
		return deter;
	}
	/*Cas reclusiu*/
	nova  = (polinomi**)malloc((n-1)*sizeof(polinomi*)); /*Només apuntarà a punters que ja tenim guardats*/
	if(nova == NULL){
		printf("No memory\n");
		exit(1);
	}
	sing = 1;
	for(i=0; i<n; i++){
		for(j=0; j<i; j++)
			nova[j] = a[j]+1;
		for(j=i+1; j<n; j++)
			nova[j-1] = a[j]+1;
		terme = det(nova, n-1, gr);
		prodPol(terme, a[i][0], &calcul);
		prodPolEsc(calcul, sing, &aux);
		sumaPol(deter, aux, &deter);
		sing = -sing;
	}
	alliberarPol(&calcul);
	alliberarPol(&aux);
	alliberarPol(&terme);
	free(nova);
	return deter;
}
