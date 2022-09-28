#include <stdio.h>
#include <math.h>
double getEMI(double, double, double);
void getPrompt();
int main(int argc, char* argv[]){
    double p, t, r;
    p=t=r=0;

    getPrompt(p, r, t);
    return 0;
}
double getEMI(double principal, double roi, double time){
    double temp=pow(1+roi/1200,time*12);
    return (principal*roi/1200*temp)/(temp-1);
}
void getPrompt(double p, double r, double t){
    puts("*********EMI CALCULATOR********");
    printf("Principal: ");
    scanf("%lf", &p);

    printf("ROI: ");
    scanf("%lf", &r);

    printf("Time: ");
    scanf("%lf", &t);

    printf("EMI: %.2lf", getEMI(p, r, t));
    putchar('\n');
    printf("Enter y to quit.");
    scanf("%lf", &p);
}