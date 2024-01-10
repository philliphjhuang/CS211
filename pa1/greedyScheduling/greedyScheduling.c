#include <stdlib.h>
#include <stdio.h>
#include <stdbool.h>

// Selection sort based approach to sorting jobs

int main(int argc, char* argv[]) {

    unsigned char optimalJob;  
    unsigned int optimalStart;
    unsigned int optimalEnd; 

    unsigned int previousEnd;
    // First peek at how many jobs and timeslots there are
    FILE* fp = fopen(argv[1], "r");
    if (!fp) {
        perror("fopen failed");
        exit(EXIT_FAILURE);
    }
    

    char buf[256];

    // Read the number of jobs to be scheduled
    if (!fscanf(fp, "%s\n", buf)) {
        perror("reading the number of jobs failed");
        exit(EXIT_FAILURE);
    }
    int jobcount = atoi(buf);

    // Next read the maximum number of timeslots
    if (!fscanf(fp, "%s\n", buf)) {
        perror("reading the number of timeslots failed");
        exit(EXIT_FAILURE);
    }
    int timeslots = atoi(buf);

    // We've read the number of timeslots so close the file and start over
    fclose(fp);

    for (unsigned int slot = 0; slot<timeslots; slot++) {

        FILE* fp = fopen(argv[1], "r");
        if (!fp) {
            perror("fopen failed");
            exit(EXIT_FAILURE);
        }

        char buf[256];

        // First read the number of jobs to be scheduled
        if (!fscanf(fp, "%s\n", buf)) {
            perror("reading the number of jobs failed");
            exit(EXIT_FAILURE);
        }

        // Next read the maximum number of timeslots
        if (!fscanf(fp, "%s\n", buf)) {
            perror("reading the number of timeslots failed");
            exit(EXIT_FAILURE);
        }

        // Now read the rest of the file
        for ( int line=0; line<jobcount; line++ ) {
            if (!fgets(buf, 256, fp)) {
                perror("reading a line for a job failed");
                exit(EXIT_FAILURE);
            }

            char job;
            unsigned int start;
            unsigned int end;            
            if (!sscanf(buf, "%c %d %d", &job, &start, &end)) {
                perror("parsing a line for a job failed");
                exit(EXIT_FAILURE);
            } 

            //printf("Job:%c, Start:%d, End:%d\n", job, start, end);
            if(optimalJob==0){
                optimalJob = job;
                optimalStart = start;
                optimalEnd = end;
                break;
            }

            //check if they have same ends
            if((job!=optimalJob)&&(end==optimalEnd)&&(start>previousEnd)){
                if(start==optimalStart){
                    if(job>optimalJob){
                        optimalJob = job;
                        optimalStart = start;
                        optimalEnd = end;
                        if(line==jobcount-1){
                            break;
                        }
                    }
                } else if(start<optimalStart){                    
                    optimalJob = job;
                    optimalStart = start;
                    optimalEnd = end;
                    if(line==jobcount-1){
                        break;
                    }
                }
            }
            
            //check if there is a smaller start than the optimalStart without overlapping
            if((start>previousEnd)&&(start!=optimalStart)&&(job!=optimalJob)){
                //printf("OptimalJob: %c, OptimalStart: %d, Job: %c, Start: %d\n", optimalJob, optimalStart, job, start);
                if((end<optimalEnd)&&(start!=previousEnd)){
                    //printf("OptimalJob: %c, OptimalStart: %d, Job: %c, Start: %d\n", optimalJob, optimalStart, job, start);    
                    optimalJob = job;
                    optimalStart = start;
                    optimalEnd = end;
                    //printf("OptimalJob: %c, OptimalStart: %d, Job: %c, Start: %d\n", optimalJob, optimalStart, job, start);
                    if(line==jobcount-1){
                        break;
                    }
                } else if((start>previousEnd)&&(previousEnd==optimalEnd)){
                    //printf("OptimalJob: %c, OptimalStart: %d, Job: %c, Start: %d\n", optimalJob, optimalStart, job, start);
                    optimalJob = job;
                    optimalStart = start;
                    optimalEnd = end;
                    if(line==jobcount-1){
                        break;
                    }
                }
            } 
            //check if they have same Starts
            if((start==optimalStart)&&(start>previousEnd)&&(job!=optimalJob)){
                if(end<optimalEnd){
                    optimalJob = job;
                    optimalStart = start;
                    optimalEnd = end;
                    if(line==jobcount-1){
                        break;
                    }
                }
            }
                        

            /*
            if ( (end==slot) && (start!= 0) && (previousStart!=0)) {
                if(previousEnd<start){
                   optimalJob = job;
                } else if(end<previousStart){
                    optimalJob = previousJob;
                }
                if(end==previousEnd){
                    if(start==previousStart){
                        if((int)job > (int)previousJob){
                            optimalJob = job;
                        } else{
                            optimalJob = previousJob;
                        }
                    } else if((start<previousStart)&&(start>previousEnd)){
                        optimalJob = job;
                    } else if((previousStart<start)&&(previousStart>end)){
                        optimalJob = previousJob;
                    }
                }                
            }  
            previousJob = job;
            previousStart = start;
            previousEnd = end; 
            */     
           
        }
        if(optimalEnd!=previousEnd){
            printf("%c\n", optimalJob);
            previousEnd = optimalEnd;
        }
        fclose(fp);
    }
    exit(EXIT_SUCCESS);
}
