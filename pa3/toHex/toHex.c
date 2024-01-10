#include <stdlib.h>
#include <stdio.h>

int main(int argc, char *argv[]) {


    // char decToHex[16] = {'1', '2', '3', '4', '5', '6', '7', '8', '9', 'A', 'B', 'C', 'D', 'E', 'F', '\0'};
    FILE* fp = fopen(argv[1], "r");
    if (!fp) {
        perror("fopen failed");
        return 0;
    }

    // first, read the number
    signed int input;
    fscanf(fp, "%d", &input);

    // print bits; you will see this kind of for loop often in this assignment
    signed char num[4] = {'0','0','0','0'};
    int isNegative = 0;
    if(input<0){
        num[0] = 'F';
        num[1] = 'F';
        num[2] = 'F';
        num[3] = 'F';
        isNegative = 1;
        input = input*-1;
    }
    signed int remainder = 0;
    int digit = 3;
    
    while(input!=0){        
        if(isNegative==0){
            remainder = input%16;
            switch(remainder){
                case 0:
                    num[digit] = '0';
                    break;
                case 1:
                    num[digit] = '1';
                    break;
                case 2:
                    num[digit] = '2';
                    break;
                case 3:
                    num[digit] = '3';
                    break;
                case 4:
                    num[digit] = '4';
                    break;
                case 5:
                    num[digit] = '5';
                    break;
                case 6:
                    num[digit] = '6';
                    break;
                case 7:
                    num[digit] = '7';
                    break;
                case 8:
                    num[digit] = '8';
                    break;
                case 9:
                    num[digit] = '9';
                    break;
                case 10:
                    num[digit] = 'A';
                    break;
                case 11:
                    num[digit] = 'B';
                    break;
                case 12:
                    num[digit] = 'C';
                    break;
                case 13:
                    num[digit] = 'D';
                    break;
                case 14:
                    num[digit] = 'E';
                    break;
                case 15:
                    num[digit] = 'F';
                    break;
                default:
                    break;
            }
        } else if(isNegative==1){
            remainder = input%16;
            if(remainder==0){
                num[digit] = '0';
            }
            if(digit!=3){
                remainder++;
            }
            switch(remainder){
                case 1:
                    num[digit] = 'F';
                    break;
                case 2:
                    num[digit] = 'E';
                    break;
                case 3:
                    num[digit] = 'D';
                    break;
                case 4:
                    num[digit] = 'C';
                    break;
                case 5:
                    num[digit] = 'B';
                    break;
                case 6:
                    num[digit] = 'A';
                    break;
                case 7:
                    num[digit] = '9';
                    break;
                case 8:
                    num[digit] = '8';
                    break;
                case 9:
                    num[digit] = '7';
                    break;
                case 10:
                    num[digit] = '6';
                    break;
                case 11:
                    num[digit] = '5';
                    break;
                case 12:
                    num[digit] = '4';
                    break;
                case 13:
                    num[digit] = '3';
                    break;
                case 14:
                    num[digit] = '2';
                    break;
                case 15:
                    num[digit] = '1';
                    break;
                default:
                    break;
            }
        }
        input/=16;
        digit--;
    }
    
    /*
    for ( int bit=sizeof(signed int)*8-1; 0<=bit; bit-- ) {
        size_t bit_val = ((1<<1)-1) & input>>bit*1; // shift and mask
        char character = bit_val ? '1' : '0';
        printf("%c",character);
    }
    printf("\n");
    */
    printf("%c%c%c%c", num[0], num[1], num[2], num[3]);
    return EXIT_SUCCESS;

}
