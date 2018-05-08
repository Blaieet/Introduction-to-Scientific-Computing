
/* 
 * File:   gauss.c
 * Author: Ras Jimenez Blai
 * DNI: 46980893N
 * Created on November 1, 2016, 12:28 AM
 */


/*Imports necesaris*/
#include <stdio.h>
#include <stdlib.h>
#include <math.h>

/*Funcio que guarda memoria per la creacio de la matriu A*/
double** matrix_alloc(int n) {
    int i;
    double **u;
    
    u = (double **) malloc (n*sizeof(double*));
    for (i = 0; i < n; i ++){
        u[i] = (double *) malloc (n*sizeof(double));
        if (u[i] == NULL ){
            printf ("No hi ha prou memoria");
        }
    }
    return u;
}

/*Reserva d'espai per una matriu ampliada, es a dir, amb una columna mes*/
double** matrixAmpliada_alloc(int n) {
    
    int i;
    double** ampliada;
    ampliada = (double **) malloc ((n+1)*sizeof(double*));
    for (i = 0; i < n; i ++){
        ampliada[i] = (double *) malloc (n*sizeof(double));
        if (ampliada[i] == NULL ){
            printf ("No hi ha prou memoria");
        
        }
    }
    return ampliada;
}

/*Funcio que llegeix els valors d'un fitxer i els assigna a una matriu*/
void matrix_read(int n,double** u, FILE* fin) {
    
    int i,j;
    
    for (i = 0; i < n; i++) {
        for (j = 0; j < n; j++) {
            fscanf(fin,"%lf",u[i]+j); /*Lf == double* Adreça*/
        }
    }
    
    
}

/*Funcio que imprimeix una matriu en un fitxer*/
void matrix_write(int n, double**u, FILE* fout) {
    
    int i;
    int j;
    for (i = 0; i < n; i++) {
        for (j = 0; j < n; j++){
            fprintf(fout,"%25.16le\t",u[i][j]); /*posicio*/
        }
        fprintf(fout,"\n");
    }
    fprintf(fout,"\n");
    
    
}


/*Funcio que reserva espai per un vector*/
double* vector_alloc(int n) {
   
    double* y;
    
    y = (double *) malloc (n*sizeof(double));
    if (y == NULL ){
        printf ("No hi ha prou memoria" );
        return 0;
    }
    return y;
}

/*Funcio que llegeix els valors d'un fitxer per un vector*/
void vector_read(int n, double* y, FILE* fin) {
    int i;

    for (i = 0; i < n; i ++){
        fscanf (fin,"%lf", y+i); /*&y[i]*/
    }
}

/*Funcio que imprimeix un vector en un fitxer*/
void vector_write(int n, double *y, FILE* fout) {
    
    int i;
    
    for (i = 0; i < n; i++) {
        
        fprintf (fout,"%25.16le\t" ,y[i]);
    }
    fprintf(fout,"\n");
}

/*Funcio que calcula Ux=y amb una tolerancia*/
int resoltrisup (int n, double **u, double *y, double *x, double tol) {
    
    int i,j;
    double aux;
    x[n-1] = y[n-1]/u[n-1][n-1]; /* Primera assignacio, es una matriu
                                  * triangular.*/
    
    for (i = 1; i < n; i++){ /* i=1 perque ja hem fet la ultima fila*/
        aux = 0.0;
        for (j = 0; j <=i; j++){  
            aux = aux + x[n-1-j]*u[n-1-i][n-1-j]; /*Sumatori, multiplico la fila * columna i ho sumo*/
        }
        x[n-1-i] = (y[n-1-i]-aux)/u[n-1-i][n-1-i]; /*Comenso desde el final i mel quedo*/
    }
}

/*Funcio que calcula el producte d'una matriu per un vector*/
double* prodMatVec (int n, double **u, double *x) {
    
    int i,j;
    double* Ux;
    Ux = vector_alloc(n);
    double aux;
    
    for (i = 0; i <n; i++) { /*Per cada fila...*/
        aux = 0.0;
        for (j = 0; j<n; j++){ 
            aux = aux + u[i][j]*x[j]; /*Es calcula la suma de la fila per la posicio del vector*/
        }
        Ux[i] = aux; /*Vaig asignant*/
    }
    return Ux;
}

/*Funcio que calcula la resta de dos vectors*/
double* restaVec(int n, double *Ux, double *y) {
    
    double* Axb;
    Axb = vector_alloc(n);
    
    int i;
    
    for (i = 0; i < n; i++) { /*Per cada posicio...*/
        Axb[i] = Ux[i]-y[i]; /*Les resto*/
    }
    return Axb;
}

/*Funcio que em calcula el modul d'un vector*/
double norma2(int n, double *z) {
    
    int i;
    double modul;
    modul = 0;
    
    for (i=0; i < n; i++) { /*Per cada posicio...*/
        modul = modul + pow(z[i],2); /*Elevo al cuadrat les seves components i les sumo*/
    }
    modul = sqrt(modul); /*Ara faig l'arrel cuadrada i retorno*/
    return modul;
}

/*Funcio que copia la matriu A a una altra matriu (Copia)*/
double** copiaMatriu(int n,double** A,double** copia) {
    
    int i,j;
    
    for (i = 0; i<n; i++) {
        for (j =0; j<n; j++){
            copia[i][j]=A[i][j]; /*Per cada fila i columna la copio a fila i columna de laltre matriu*/
        }
    }
    return copia;
}

/*Funcio que et separa un vector b d'una matriu ampliada A*/
double* separaVector(int n, double** A,double* b) {
    
    int i;

    for (i = 0; i < n; i++) {
        b[i] = A[i][n]; /*Copia nomes la columna numero n (la ultima)*/
    }
    return b;
}

/*Funció que donada una matriu ampliada, treu l'ampliacio i es queda únicament amb la matriu*/
double** separaMatriu(int n,double** ASup, double** ampliada) {
    
    int i,j;

    
    for (i = 0; i<n; i++) {
        for (j = 0; j<n; j++) {
            ASup[i][j] = ampliada[i][j]; /*Copia nomes fins l'ultima columna*/
        }
    }
    return ASup;
}

/*Funcio que fa el procediment de gauss - jordan a una matriu i troba les solucions del sistema amb resoltrisup*/
int gauss(int n, double **A, double *v, double tol,double* x) {
    
    int i,j,k;
    double multiplicador;
    int index;
    
    for (i = 0; i < n; i++) {
        for (j = i+1; j<n; j++) {
            multiplicador = A[j][i]/A[i][i]; /*Calcula el multiplicador de les posicions corresponents*/
            for (index = 0; index <= n; index++) {
                A[j][index] = A[j][index]-(multiplicador*A[i][index]); /*Es multiplica tota la fila pel multiplicador i se li resta la fila de dalt*/
            }
            /*Es mira que compleixi que > tolerancia*/
            for (k=0; k<n; k++){
                if (fabs(A[k][k]) <= tol){
                    return 1; /*Si no, es retorna error*/
                }
            }
        }
    }
    
    /*Vector v despres d'haver fet gauss*/
    double* bGauss;
    bGauss = vector_alloc(n);
    bGauss = separaVector(n,A,bGauss);
    
    /*Matriu triangular superior*/
    double** ASup;
    ASup = matrix_alloc(n);
    ASup = separaMatriu(n,ASup,A);
    
    resoltrisup(n,ASup,bGauss,x,tol);
    
    return 0;
}


int main(int argc, char** argv) {
    
    int n; /*dimensio*/
    double tol;
    tol = 0.001; /*Per exemple*/
    FILE *fin,*fout;

    fout = fopen("Uxy2.res","w"); /*Fitxer d'impressio de dades*/
    fin = fopen("Uxy2.dad","r"); /*Fitxer de lectura de dades*/
    fscanf(fin, "%d",&n); /*Lectura de la dimensio*/
    
    if (n < 1) {
        return 1;
    }
    
    
    /*Matriu A*/ 
    double** A;
    fprintf(fout,"Matriu A\n");

    A = matrix_alloc(n);
    matrix_read(n,A,fin);
    matrix_write(n,A,fout);
    
    /*Vector b*/
    
    double* b;
    
    fprintf(fout,"Vector b\n");
    b = vector_alloc(n);
    vector_read(n,b,fin);
    vector_write(n,b,fout);
    
    
    
    /*Matriu ampliada*/
    /*Copia de A, pero necesita una reserva de memoria especial*/
    double** ampliada;
    ampliada = matrixAmpliada_alloc(n);
    ampliada = copiaMatriu(n,A,ampliada);
    

    
    /*Li adjuntu la ampliacio (b)*/
    int i;
    for (i = 0; i<n; i++){
        ampliada[i][n]=b[i];
    }
   
    /*Vector solucio*/
    double* x;
    x = vector_alloc(n);
    
    /*GAUS*/
    gauss(n,ampliada,b,tol,x);

    
    
    fprintf(fout,"Vector x\n");
    vector_write(n,x,fout);

    
    /*y = Ax*/
    double* y;
    y = prodMatVec(n,A,x);
    
    fprintf(fout,"ProdMatVec\n");
    vector_write(n,y,fout);
    
    /*Ax-b*/
    y =restaVec(n,y,b);
    fprintf(fout,"Ax-b\n");
    vector_write(n,y,fout);
    
    /*|Ax-b|*/
    double modul;
    modul = norma2(n,y);
    
    fprintf(fout,"Modul de  ||Ax-b|| com a indicador de la solucio x:\n");
    fprintf(fout,"%25.16le\t" ,modul);

    return (0);
}

