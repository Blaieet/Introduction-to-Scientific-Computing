#include< stdio .h >
int main (void){
    int n , i;
    float *x , *y , prod;

    printf (" Doneu la dimensio dels vectors,n =\n");
    scanf ("%d", &n );
    x = (float *) malloc ( n*sizeof(float) );
    y = (float *) malloc ( n*sizeof(float) );
    if ( x == NULL || y == NULL ){
        printf (" No hi ha prou mem`oria " );
        return 1;
    }
    printf ("Doneu els %d elements del vector x\n",n );
    for (i = 0; i < n; i ++){
        scanf ("%f" , &x[i ]);
    }
    printf ("Doneu els %d elements del vector y\n",n );
    for (i=0; i < n; i++){
        scanf ("%f" , &y[i ]);
    }
    prod = 0. f;
    for (i = 0; i < n; i ++){
        prod += x[i ]* y[i ];
    }
    printf ("El producte escalar val : %16.7 e \n",prod);
    free (x);
    free (y);
    return 0;
}
