#include <stdbool.h>
#include <stdlib.h>
#include <stdio.h>

int main(int argc, char *argv[]) {

    FILE* fp = fopen(argv[1], "r");
    if (!fp) {
        perror("fopen failed");
        return EXIT_FAILURE;
    }

    // SETUP

    // first, read the minuend (number to be subtracted from)
    bool minuend[8]; // suggested that you store bits as array of bools; minuend[0] is the LSB
    for (int i=7; 0<=i; i--) { // read MSB first as that is what comes first in the file
        /* ... */
        /*
        int* temp;
        fscanf(fp, "%d", temp);
        if(temp==1){
            minuend[i] = true;
        } else{
            minuend[i] = false;
        }
        */
        minuend[i] = (bool)(fgetc(fp)-'0');
    }

    // notice that you are reading two different lines; caution with reading
    /* ... */
    fgetc(fp);
    // second, read the subtrahend (number to subtract)
    bool subtrahend[8]; // suggested that you store bits as array of bools; subtrahend[0] is the LSB
    for (int i=7; 0<=i; i--) { // read MSB first as that is what comes first in the file
        /* ... */
        /*
        int* temp;
        fscanf(fp, "%d", temp);
        if(temp==1){
            subtrahend[i] = true;
        } else{
            subtrahend[i] = false;
        }
        */
        subtrahend[i] = (bool)(fgetc(fp)-'0');
    }

    // WE WILL DO SUBTRACTION BY NEGATING THE SUBTRAHEND AND ADD THAT TO THE MINUEND

    // Negate the subtrahend
    // flip all bits
    /* ... */
    for(int i = 0; i < sizeof(subtrahend); i++){
        // subtrahend[i] = NULL;
        subtrahend[i] = !subtrahend[i];
    }
    // add one
    bool carry = true; // to implement the 'add one' logic, we do binary addition logic with carry set to true at the beginning
    bool difference[8];
    int result = 0;
    for (int i=0; i<8; i++) { // iterate from LSB to MSB
        /* ... */
        result = minuend[i] + subtrahend[i] + carry;
        if(result == 0){
            difference[i] = false;
            carry = false;
        }
        else if(result == 1) {
            difference[i] = true;
            carry = false;
        } else if(result == 2) {
            difference[i] = false;
            carry = true;
        } else{
            difference[i] = true;
            carry = true;
        }
    }

    // Add the minuend and the negated subtrahend
    /* ... */
    /*
    for(int i = 0; i < sizeof(minuend); i++){}
        minuend[i] += subtrahend[i];
    }
    */
    // print the difference bit string
    for (int i=7; 0<=i; i--)
        printf("%d",difference[i]);

    return EXIT_SUCCESS;

}
