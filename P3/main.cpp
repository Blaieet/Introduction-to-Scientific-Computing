/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   main.cpp
 * Author: blair
 *
 * Created on September 26, 2016, 6:24 PM
 */

#include <cstdlib>
#include <stdio.h>
using namespace std;


int main (void){

    int n , m , i , j;
    double **a , *u , *v;
    
    
    // -----------------MATRIU A---------------------------------------
    
    
    printf (" Doneu les dimensions de la matriu A , (n ,m) = \n" );
    scanf ("%d %d" , &n ,&m );
    a = (double **) malloc ( n*sizeof(double *) );
    if ( a == NULL ){
        printf (" No hi ha prou memoria " );
        return 1;
    }
    for (i = 0; i < n; i ++){
        a[i] = (double *) malloc ( m*sizeof(double) );
        if (a[i] == NULL ){
            printf (" No hi ha prou memoria " );
        return 2;
        }
    }
    
    
    printf (" Doneu els (%d x %d) elements de la matriu A \n",n,m);
    for (i = 0; i < n; i ++){
        for (j = 0; j < m; j ++){
            scanf ("%le" , &a[i][j]);
        }
    }
    
    //----------------------MATRIU B ----------------------------------
    int z, y;
    double **o;
    
    printf (" Doneu les dimensions de la matriu B , (m ,n) = \n" );
    scanf ("%d %d" , &z ,&y );
    o = (double **) malloc ( z*sizeof(double *) );
    if (o == NULL ){
        printf (" No hi ha prou memoria " );
        return 3;
    }
    


    for (i = 0; i < n; i ++){
        o[i] = (double *) malloc ( y*sizeof(double) );
        if ( o[i] == NULL ){
            printf (" No hi ha prou memoria " );
        return 4;
        }
    }
    
    
    printf (" Doneu els (%d x %d) elements de la matriu B \n",z,y);
    for (i = 0; i < n; i ++){
        for (j = 0; j < m; j ++){
            scanf ("%le" , &o[i][j]);
        }
    }
    
    //-----------------------VECTOR X-----------------------------
    
    u = (double *) malloc ( m*sizeof(double) );
    v = (double *) malloc ( n*sizeof(double) );
    double *g,*l;
    g = (double *) malloc (m * sizeof(double));
    l = (double *) malloc (m * sizeof(double));
    
    if ( u == NULL || v == NULL ){
        printf (" No hi ha prou memoria" );
        return 3;
    }
    
    printf ("Doneu els %d elements del vector x \n",m);
    for (i = 0; i < m; i ++){
        scanf ("%le" , &u[i]);
    }
    
    
    
    //----Multi B * x------
    
    for (i = 0; i < n; i ++){
        v[i] = 0.;
        for (j = 0; j < m; j++){
            v[i] += a[i][j]* u[j];
        }
    }
    
    printf ("Bx ens dona = \n" );
    for (i = 0; i < m; i ++)
        printf (" %16.7e \n" , v[i]);
    
    //---Multi x * A
    
    for (i = 0; i < n; i ++){
        l[i] = 0.;
        for (j = 0; j < m; j++){
            l[i] += o[i][j]* v[j];
        }
    }
    
    //---Multiples?
    bool mul = false;
    for (int i = 0; i < n; i++){
        
        if ((int)l[i] % (int)u[i] == 0) {
            mul = true;
        }
    } 
    
    //--------------------------VECTOR Y (resultant) ---------------------
    
//    double *q, *w;
//    
//    
//    q = (double *) malloc ( z*sizeof(double) );
//    w = (double *) malloc ( y*sizeof(double) );
//    if ( u == NULL || v == NULL ){
//        printf (" No hi ha prou memoria" );
//        return 4;
//    }
    
//    printf (" Doneu els %d elements del vector x \n",m);
//    for (i = 0; i < m; i ++){
//        scanf ("%le" , &u[i]);
//    }
//    
//    for (i = 0; i < n; i ++){
//        v[i] = 0.;
//        for (j = 0; j < m; j++){
//            v[i] += a[i][j]* u[j];
//        }
//    }
    
    
    
    
    
    
    
    
    
    
    //-------------------------------------------------------
    
    printf ("Matriu A = \n" );
    for (i = 0; i < n; i ++){
        for (j = 0; j < m; j ++){
        printf ("%16.7e" , a[i][j]);
        }
    printf ("\n" );
    }
//    
    printf ("Per la Matriu B = \n" );
    for (i = 0; i < n; i ++){
        for (j = 0; j < m; j ++){
        printf ("%16.7e" , o[i][j]);
        }
    printf ("\n" );
    }

    
    
    
    printf ("i pel vector x = \n" );
    
    for (i = 0; i < m; i ++)
        printf (" %16.7e \n" , u[i]);
    
    printf ("ens dona y = \n" );
    
    for (i = 0; i < n; i ++)
        printf ("%16.7e \n" , l[i]);

    
    
    if (mul) 
        printf("El qual es multiple amb el vector x");
    else 
        printf("El qual no es multiple amb el vector x");
    
    
    
    
    
    for (i = 0; i < n; i ++)
        free (a[i]);
    free (a);
    free (u);
    free (v);
    free(o);
    free(g);
    free(l);
    return 0;
    
   
    
}
