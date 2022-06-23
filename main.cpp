#include <iostream>
#include <math.h>
#include <time.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include "GA.h"

float y(float param[], float x){
    return  (param[0] + param[1]*x + param[2]*x*x + param[3]*x*x*x);
}

int main() {
//    GeneticAlgorithm ga;
    printf("TEST");
    int n_chromosomes=100, n_genes=4, n_samples=100, n_iter=10000;
    float mutation_rate, selection_precentage, ground_truth[]={-0.1, 0.3, -0.7, 0.1};

    int gd,gm,survivors;
    float tmp, Chromosome[4], Population[100][4], Loss[100];

    survivors = n_chromosomes*selection_precentage/100;
    srand(time(NULL));

    for(int i=0; i<n_chromosomes; i++){
        for(int j=0; j<n_genes; j++){
            Population[i][j] = 2*rand()/RAND_MAX -1;
        }
    }

    sleep(2000);

    for(int i=0; i<=n_iter; i++){
        for(int j=0; j<n_chromosomes; j++){
            for(int k=0; k<n_genes; k++){
                Chromosome[k] = Population[j][k];
            }

            Loss[j]=0;
            for(int k=0; k<n_samples; k++){
                tmp = 2.0*rand()/RAND_MAX;
                Loss[j] += pow(y(ground_truth, tmp) - y(Chromosome, tmp), 2);
            }
            Loss[j] /= n_samples;
            Loss[j] = sqrt(Loss[j]);
        }
        for(int j=0; j<n_chromosomes; j++){
            for(int k=0; k<n_chromosomes; k++){
                if(Loss[j] < Loss[k]){
                    Loss[j] = Loss[k];
                    Loss[k] = tmp;
                }

                for(int l=0; l<n_genes; l++){
                    tmp = Population[j][l];
                    Population[j][l]= Population[k][l];
                    Population[k][l]= tmp;
                }
            }
        }

        for(int j=survivors; j<n_chromosomes; j++){
            for(int k=0; k<n_genes; k++){
                mutation_rate = 10/(100.0+i);
                Population[j][k] = Population[rand()%survivors][k] + 2.0*mutation_rate*rand()/RAND_MAX - mutation_rate;
            }
        }
    }

    //Print the solution
    for(int i=0; i<n_genes; i++) printf("%f", Population[0][i]);

    getchar();

    std::cout << "Hello, World!" << std::endl;
    return 0;
}
