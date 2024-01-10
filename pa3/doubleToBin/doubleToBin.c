#include <stdbool.h>
#include <stdlib.h>
#include <time.h>
#include <stdio.h>
#include <assert.h>
#include <math.h>

#define EXP_SZ 11
#define FRAC_SZ 52

int main(int argc, char *argv[]) {

    // SETUP

    FILE* fp = fopen(argv[1], "r");
    if (!fp) {
        perror("fopen failed");
        return 0;
    }

    // first, read the number
    double value;
    fscanf(fp, "%lf", &value);
    // the reference solution ('the easy way')
    // you are not allowed to print from this casted 'ref_bits' variable below
    // but, it is helpful for validating your solution
    // THE SIGN BIT
    bool sign = value<0.0;
    printf("%d_",sign);
    // THE EXP FIELD
    // find the exponent E such that the fraction will be a canonical fraction:
    // 1.0 <= fraction < 2.0
    double fraction = sign ? -value : value;
    double num = fraction;
    int trial_exp = (1<<(EXP_SZ-1)); // start by assuming largest possible exp (before infinity)
    // do trial division until the proper exponent E is found
    unsigned short bias = (1<<(EXP_SZ-1))-1;
    signed short exp = 0;
    if(fraction>1e-308) {
        frexp(fraction, &trial_exp);
        exp = (trial_exp-1) + bias;
    }
    for ( int exp_index=EXP_SZ-1; 0<=exp_index; exp_index-- ) {
        bool exp_bit = 1&exp>>exp_index;
        printf("%d",exp_bit);
    }
    printf("_");
    // you get partial credit by getting the exp field correct
    // even if you print zeros for the frac field next
    // you should be able to pass test cases 0, 1, 2, 3

    // THE FRAC FIELD
    // prepare the canonical fraction such that:
    // 1.0 <= fraction < 2.0
    /* ... */
    double intp;
    int fraction_bit;
    num = fraction;
    if((fabs(num-2) < 1e-308) ||(fabs(num-1) < 1e-308) ||( num > 1 && num > 2)) {
       num= ldexp ( num, -(trial_exp-1) );
       
    } else{
        if(trial_exp!=0) {
            if(trial_exp==1024){
                num= ldexp ( num, -(-(trial_exp-2)) );
            } else{
                num= ldexp ( num, -(trial_exp-1) );
            }    
        } else{
            num=0;
        }
    }
    num = modf(num, &intp);
    bool frac_array[FRAC_SZ+1]; // one extra LSB bit for rounding
    for ( int frac_index=FRAC_SZ; 0<=frac_index; frac_index-- ) {
        num *= 2;
        fraction_bit = num; 
        frac_array[frac_index] = fraction_bit; // frac set to zero to enable partial credit
        /* ... */
        if(fraction_bit){
            num -= fraction_bit;
        }  
    }

    // rounding
    /* ... */

    for ( int frac_index=FRAC_SZ-1; 0<=frac_index; frac_index-- ) {
        bool frac_bit = frac_array[frac_index+1]; // skipping the extra LSB bit for rounding
        printf("%d", frac_bit);
        // assert (frac_bit == (1&ref_bits>>frac_index)); // validate your result against the reference
    }

}
