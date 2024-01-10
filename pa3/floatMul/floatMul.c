#include <stdbool.h>
#include <stdlib.h>
#include <stdio.h>
#include <assert.h>
#include <math.h>

#define EXP_SZ 8
#define FRAC_SZ 23
#define FLOATSIZE 40
void read(bool* s, unsigned int* e, float* f, char* character){
    int count1 = 1;
    float count2 = 1.0;
    *f=1.0;

    if(character[0]=='1'){
        *s = true;
    }
    for(int i=EXP_SZ;i>0;i--){
        if(character[i]=='1'){
            *e=*e+count1;
        }
        count1*=2;
    }
    for(int i=EXP_SZ+1;i<EXP_SZ+FRAC_SZ+1;i++){
        count2/=2.0;
        if(character[i]=='1'){
            *f=*f+count2;
        }
    }
}

int main(int argc, char *argv[]) {
    
    bool fraction_array[FRAC_SZ+1];
    // float value = *(float *) &binary; // you are not allowed to do this.
    // unsigned int binary = *(unsigned int*) &value; // you are not allowed to do this.

    FILE* fp = fopen(argv[1], "r");
    if (!fp) {
        perror("fopen failed");
        return EXIT_FAILURE;
    }

    // SETUP

    // first, read the binary number representation of multiplier
    char multiplier[FLOATSIZE];
    fscanf(fp, "%s", multiplier);
    char multiplicand[FLOATSIZE];
    fscanf(fp, "%s", multiplicand);
    // notice that you are reading two different lines; caution with reading
    bool s1 = false,s2 = false,sign = false;
    unsigned int e1 = 0,e2 = 0,exp = 0;
    float f1 = 0.0,f2 = 0.0,frac = 0.0; 
    // first, read the binary number representation of multiplcand
    read(&s1, &e1, &f1, multiplier);
    read(&s2, &e2, &f2, multiplicand);
    //float product = *(float *) &multiplier * *(float *) &multiplicand; // you are not allowed to print from this.
    //unsigned int ref_bits = *(unsigned int *) &product; // you are not allowed to print from this. But you can use it to validate your solution.

    // SIGN
    if((s1==true&&s2==false)||(s1==false&&s2==true)){
        sign=true;
    }
    printf("%d_",sign);
    //assert (sign == (1&ref_bits>>(EXP_SZ+FRAC_SZ)));

    // EXP
    // get the exp field of the multiplier and multiplicand
    /* ... */
    // add the two exp together
    exp = e1+e2;
    // subtract bias
    unsigned int bias = 127;
    exp-=bias;
    // FRAC
    // get the frac field of the multiplier and multiplicand
    /* ... */
    // assuming that the input numbers are normalized floating point numbers, add back the implied leading 1 in the mantissa
    /* ... */
    // multiply the mantissas
    frac=f1*f2;
    // overflow and normalize
    unsigned int count = 0;
    for(int i=0;i<FRAC_SZ;i++){
        if(frac>=1.0){
            if(frac<2.0){
                break;
            }
            frac/=2.0;
            count+=1;
        } else{
            if(frac<2.0){
                break;
            }
            frac*=2.0;
            count+=1;
        }
    }
    // rounding
    exp+=count;
    count+=bias;
    // move decimal point
    if(exp>255){
        exp=255;
    }
    if(exp<0){
        exp=0;
    }
    // PRINTING
    // print exp
    for ( int bit_index=EXP_SZ-1; 0<=bit_index; bit_index-- ) {
        printf("%d",1&exp>>bit_index);
        //assert (trial_bit == (1&ref_bits>>(bit_index+FRAC_SZ)));
    }
    printf("_");

    // print frac
    for(int i=FRAC_SZ; 0<=i;i--){
        fraction_array[i] = false;
        if(frac>=1.0){
            fraction_array[i] = true;
            frac-=1.0;
        }
        frac*=2.0;
    }
    for (int frac_index=FRAC_SZ-1; 0<=frac_index; frac_index-- ){
        printf("%d",fraction_array[frac_index]);
        //assert (trial_bit == (1&ref_bits>>(bit_index)));
    }

    return(EXIT_SUCCESS);

}