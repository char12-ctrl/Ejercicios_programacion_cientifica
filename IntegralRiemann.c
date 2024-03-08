/*   Calcularem l'area d'una funcio continua en el interval [a,b] 

    S'utilitzara el Metode del Trapezi      					  */
/* Fixada una tolerancia ∂, calcularem l'area Q tal que | Q - ∫f(x)dx| < ∂   */
#include <stdio.h>
#include <stdlib.h>
#include <math.h>
double f1(double);
double f2(double);
double trapezi(double (*)(double),double,double);
double adapTrapezi(double (*)(double),double,double,double,double);

int main(void){
	double a,b,tol,trap,adapt; /* ∂ es la tolerancia*7
	/* LLegim a,b,tol*/
	printf("a: ");
	scanf("%lf",&a);
	printf("b: ");
	scanf("%lf",&b);
	printf("tol: ");
	scanf("%lf",&tol); 
	/* Fem els calculs per f1 */
	/* Calculem trapezi inicial */
	trap=trapezi(f1,a,b);
	adapt=adapTrapezi(f1,a,b,tol,trap);
	/* Imprimim resultats*/
	printf("L'area de f1 en el interval [%lf,%lf] es %20.12lf\n",a,b,adapt);
	/* Fem els calculs per f2 */
	/* Calculem trapezi inicial */
	trap=trapezi(f2,a,b);
	adapt=adapTrapezi(f2,a,b,tol,trap);
	/* Imprimim resultats*/
	printf("\nL'area de f2 en el interval [%lf,%lf] es %20.12lf\n",a,b,adapt);
	return 0;
}
/* Area que calcula el trapezi de f en el interval [a,b] */
double trapezi(double (*f)(double),double a,double b){
	return (f(a)+f(b))*(b-a)/2;
}

double adapTrapezi(double (*f)(double),double a,double b,double tol,double anterior){
	double esq,dret,actual,c,adapt;
	/* C es el punt mig de a i b */
	c=(a+b)/2;
	esq=trapezi(f,a,c);
	dret=trapezi(f,c,b);
	actual=esq+dret;
	if(fabs(actual-anterior)<=3*tol){
		actual+= (actual-anterior)/3;
		return actual;
	}
	/* Funcio recursiva */
	adapt=adapTrapezi(f,a,c,tol/2.,esq) + adapTrapezi(f,c,b,tol/2.,dret);
	return adapt;
}


/* Funcio f1(x) */
double f1(double x){
	return x*x; /* Per exemple x^2 */
}

/* Funcio f2(x) */
double f2(double x){
	return x*x*x; /* x^3 */
}
