#include <stdbool.h>
#include <stdlib.h>
#include <stdio.h>
#include <math.h>

#define EXP_SZ 8
#define FRAC_SZ 23

int main(int argc, char *argv[]) {
    int acummulative = 7;
    int E = 0;
    float M = 0;
    
    FILE* fp = fopen(argv[1], "r");
    if (!fp) {
        perror("fopen failed");
        return EXIT_FAILURE;
    }

    // SETUP

    // first, read the binary number representation of float point number
    int buff[EXP_SZ+FRAC_SZ+1];
    for (int i = EXP_SZ+FRAC_SZ; 0<=i; i--) { // read MSB first as that is what comes first in the file
        /* ... */
        buff[(31-i)] = (bool)(fgetc(fp)-'0');
    }
    // float number = *(float *)&binary; // you are not allowed to do this.

    /* ... */

    // E
    /* ... */
    for (int i=1; i<9; i++) {
       E += ldexp ( buff[i], acummulative );
       acummulative--;   
    }
    // M
    /* ... */
    acummulative = 1;
    for (int i=9; i<32; i++) { // read MSB first as that is what comes first in the file
       M += ldexp ( buff[i], -acummulative );
       acummulative++;
    }
    // https://www.tutorialspoint.com/c_standard_library/c_function_ldexp.htm
    double number = ldexp ( M+1, E-127 );
    number = buff[0] ? -number : number;
    printf("%e\n", number);

    return EXIT_SUCCESS;

}
