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
    char filename[buffer_size];
    int counter=0;
    char choice;
    char date[100];
    char time[100];
    char steps[100];
    int min;
    int max = 0;
    int i = 0;
    int a;
    int b;
    int mean;
    int sum=0;

    while(1)
    {
        printf("Menu Options:\nA: Specify the filename to be imported\nB: Display the total number of records in the file\nC: Find the date and time of the timeslot with the fewest steps\nD: Find the date and time of the timeslot with the largest number of steps\nE: Find the mean step count of all the records in the file\nF: Find the longest continuous period where the step count is above 500 steps\nQ: Quit\n");

        choice = getchar();
        while(getchar() != '\n');

        switch(choice)
        {
            case 'A':
            case 'a':
                printf("Input filename:\n");
                fgets(line, buffer_size, stdin);
                sscanf(line, " %s ", filename);
                FILE *input = fopen(filename, "r");
                if (!input)
                {
                    printf("Error: File could not be opened\n");
                    return 1;
                }
                printf("File successfully loaded\n");
                break;

            case 'B':
            case 'b':
                while (fgets(line, buffer_size, input))
                {   
                    tokeniseRecord(line,",",date,time,steps);
                    strcpy(data[counter].date,date);
                    strcpy(data[counter].time,time);
                    data[counter].steps = atoi(steps);
                    counter++;
                }
                printf("Number of records in file: %d\n", counter);
                break;

            case 'C':
            case 'c':
                min = data[1].steps;
                for(i = 0; i<counter; i++)
                {
                    if (data[i].steps<min)
                    {
                        min = data[i].steps;
                        a = i;
                    }
                }
                printf("Fewest steps: %s, %s\n", data[a].date, data[a].time);
                break;

            case 'D':
            case 'd':
                for(i = 0; i<counter; i++)
                {
                    if (data[i].steps>max)
                    {
                        max = data[i].steps;
                        b = i;
                    }
                }
                printf("Largest steps: %s, %s\n", data[b].date, data[b].time);
                break;
            case 'E':
            case 'e':
                for(i = 0; i<counter; i++)
                {
                    sum = sum + data[i].steps;
                }
                mean = sum/counter;
                printf("Mean step count: %d\n", mean);
                break;

            case 'F':
            case 'f':

            case 'Q':
            case 'q':
                return 0;
                break;

            default:
                printf("Invalid choice\n");
                break;

        }
    }
    return 0;
}









