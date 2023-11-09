#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "FitnessDataStruct.h"

// Struct moved to header file

// Define any additional variables here
// Global variables for filename and FITNESS_DATA array


// This is your helper function. Do not change it in any way.
// Inputs: character array representing a row; the delimiter character
// Ouputs: date character array; time character array; steps character array
void tokeniseRecord(const char *input, const char *delimiter,
                    char *date, char *time, char *steps) {
    // Create a copy of the input string as strtok modifies the string
    char *inputCopy = strdup(input);
    
    // Tokenize the copied string
    char *token = strtok(inputCopy, delimiter);
    if (token != NULL) {        strcpy(date, token);
    }
    
    token = strtok(NULL, delimiter);
    if (token != NULL) {
        strcpy(time, token);
    }
    
    token = strtok(NULL, delimiter);
    if (token != NULL) {
        strcpy(steps, token);
    }
    
    // Free the duplicated string
    free(inputCopy);

                    }




// Complete the main function
int main() {

    FITNESS_DATA data[100];
    int buffer_size = 250;
    char line[buffer_size];
    int counter=0;

    FILE *input = fopen("FitnessData_2023.csv", "r");

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
    
    printf("Menu Options:\nA: Specify the filename to be imported\nB: Display the total number of records in the file\nC: Find the date and time of the timeslot with the fewest steps\nD: Find the date and time of the timeslot with the largest number of steps\nE: Find the mean step count of all the records in the file\nF: Find the longest continuous period where the step count is above 500 steps\nQ: Quit\n");

    char a,filename;

    printf("Enter character: ");
    scanf("%c", &a);

    if (a == 'A') {
        printf("Input filename: \n");
        scanf("%s", &filename);
    }
    if (a == 'B') {
        printf("Number of records in file: %d\n", counter);
    }
    if (a == 'C') {
        printf("Option C selected\n");
    }
    if (a == 'D') {
        printf("Option D selected\n");
    }
    if (a == 'E') {
        printf("Option E selected\n");
    }
    if (a == 'F') {
        printf("Option F selected\n");
    }
    if (a == 'Q') {
    }
    

    return 0;
}









