


/* 
 * File:   Triangular.c
 * Author: Blai Ras Jimenez
 *
 * Created on 3 / d’octubre / 2016, 09:33
 */

/*Imports necesaris*/
#include <stdio.h>
#include <math.h>
#include <stdlib.h>

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
        x[n-1-i] = (y[n-1-i]-aux) /u[n-1-i][n-1-i]; /*Comenso desde el final i mel quedo*/
    }
    
    /* He intentat seguir les indicacions a clase de fer 
     * dos fors, un de "i" fins "n" i un altre que comensa desde
     * abaix, pero no m'he n'he sortit, aixi que he implementat el meu propi
    */
    
    /*
    for (i = n-1; i >= 0; i--) {
        x[i] = y[i];
        for (j = i+1; j<n; j++) {
            x[i]  -= u[i][j] * x[j];
            if (abs(u[i][i]<tol)) {
                return 0;
            } else {
                x[i] /= u[i][i];
            }
        } 
    }*/
}

/*Funcio que calcula el producte d'una matriu per un vector*/
double* prodMatVec (int n, double **u, double *x, double *Ux) {
    
    int i,j;
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
double* restaVec(int n, double *Ux, double *y, double *Uxy) {
    
    int i;
    for (i = 0; i < n; i++) { /*Per cada posicio...*/
        Uxy[i] = Ux[i]-y[i]; /*Les resto*/
    }
    return Uxy;
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

/*Funcio main. Conté l'execucio del programa*/
int main(int argc, char** argv) {
    
    /*------------Matriu U-------------------*/
    int n;
    double** u;
    FILE *fin,*fout;
    
    fout = fopen("uxy.res","w");
    fin = fopen("uxy.dad","r");
    fscanf(fin, "%d",&n);
    
    if (n < 1) {
        return 1;
    }
    
    fprintf(fout,"Matriu U\n");
    
    u = matrix_alloc(n);
    matrix_read(n,u,fin);
    matrix_write(n,u,fout);

    /*------------Vector y------------------*/
    
    double *y; /*vector y*/
    double *x; /*vector resultant*/

    double tol;
    tol = 0.001; /*Per exemple*/
    
    y = vector_alloc(n);
    x = vector_alloc(n);  
    vector_read(n,y,fin);
    
    fprintf(fout,"Vector y\n");
    vector_write(n,y,fout);
    
    resoltrisup(n,u,y,x,tol);
            
    fprintf(fout,"Vector x\n");
    vector_write(n,x,fout);
    
    /*y = Ax*/
    double* Ux;
    Ux = vector_alloc(n);
    Ux = prodMatVec(n,u,x,Ux);
    fprintf(fout,"ProdMatVec\n");
    vector_write(n,Ux,fout);
    
    /*Ax-b*/
    double *Uxy;
    Uxy = vector_alloc(n);
    Uxy =restaVec(n,Ux,y,Uxy);
    fprintf(fout,"Ax-b\n");
    vector_write(n,Uxy,fout);
    
    /*|Ax-b|*/
    double modul;
    modul = norma2(n,Uxy);
    
    fprintf(fout,"Modul de  ||Ax-b|| com a indicador de la solucio x:\n");
    fprintf(fout,"%25.16le\t" ,modul);

    return 0;
}
