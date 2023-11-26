#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "FitnessDataStruct.h"

// Define the struct for the fitness data
typedef struct {
    char date[11];
    char time[6];
    int steps;
} FitnessData;

// Function to tokenize a record
void tokeniseRecord(char *record, char delimiter, char *date, char *time, int *steps) {
    char *ptr = strtok(record, &delimiter);
    if (ptr != NULL) {
        strcpy(date, ptr);
        ptr = strtok(NULL, &delimiter);
        if (ptr != NULL) {
            strcpy(time, ptr);
            ptr = strtok(NULL, &delimiter);
            if (ptr != NULL) {
                *steps = atoi(ptr);
            }
        }
    }
}


int main() {
    FITNESS_DATA data[100];
    int buffer_size = 250;
    char line[buffer_size];
    char filename[buffer_size];
    int counter=0;
    char date[100];
    char time[100];
    char steps[100];

    while (fgets(line, buffer_size, input))
    {   
        tokeniseRecord(line,",",date,time,steps);
        strcpy(data[counter].date,date);
        strcpy(data[counter].time,time);
        data[counter].steps = atoi(steps);
        counter++;
    }

    printf("Enter Filename:");
    fgets(line, buffer_size, stdin);
    sscanf(line, " %s ", filename);
    FILE *input = fopen(filename, "r");
    if (!input)
    {
        printf("Error: invalid file\n");
        return 1;
    }

    
    int arr[counter];
    int max = 0;
    int a = 0;
    int i;

    for (i = 0;i<counter;i++){
        if (data[i].steps>max){
            max = data[i].steps;
            arr[a] = i;
            a += 1;
        }
    }

    FILE *file = fopen(filename.tsv, "r+");
    if (file == NULL) {
        perror("");
        return 1;
    }
    for (i=0;i<counter;i++){
        fprintf("%s %s %d", data[arr[i]].date, data[arr[i]].time, data[arr[i]].steps);
    }
    return 0;
}
