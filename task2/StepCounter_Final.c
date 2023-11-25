
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
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
    int min = 1000000;
    int max = 0;
    int i = 0;
    int a;
    int b;
    float meanf;
    int sum=0;
    int arr[100];
    int c = 1;
    int maxc;
    int length = 0;
    int start;
    int end;
    float mean;
    int meanint;

    while(1)
    {
        printf("Menu Options:\nA: Specify the filename to be imported\nB: Display the total number of records in the file\nC: Find the date and time of the timeslot with the fewest steps\nD: Find the date and time of the timeslot with the largest number of steps\nE: Find the mean step count of all the records in the file\nF: Find the longest continuous period where the step count is above 500 steps\nQ: Quit\n");
        printf("Enter choice: ");
        choice = getchar();
        while(getchar() != '\n');
        switch(choice)
        {
            case 'A':
                printf("Input filename: ");
                fgets(line, buffer_size, stdin);
                sscanf(line, " %s ", filename);
                FILE *input = fopen(filename, "r");
                if (!input)
                {
                    printf("Error: Could not find or open the file.\n");
                    return 1;
                }
                printf("File successfully loaded.\n");
                break;

            case 'B':
                while (fgets(line, buffer_size, input))
                {   
                    tokeniseRecord(line,",",date,time,steps);
                    strcpy(data[counter].date,date);
                    strcpy(data[counter].time,time);
                    data[counter].steps = atoi(steps);
                    counter++;
                }
                printf("Total records: %d\n", counter);
                break;

            case 'C':
                while (fgets(line, buffer_size, input))
                {   
                    tokeniseRecord(line,",",date,time,steps);
                    strcpy(data[counter].date,date);
                    strcpy(data[counter].time,time);
                    data[counter].steps = atoi(steps);
                    counter++;
                }
                a = 0;
                for(i = 0; i<counter; i++)
                {
                    if (data[i].steps<min)
                    {
                        min = data[i].steps;
                        a = i;
                    }
                }
                printf("Fewest steps: %s %s\n", data[a].date, data[a].time);
                break;

            case 'D':
                while (fgets(line, buffer_size, input))
                {   
                    tokeniseRecord(line,",",date,time,steps);
                    strcpy(data[counter].date,date);
                    strcpy(data[counter].time,time);
                    data[counter].steps = atoi(steps);
                    counter++;
                }
                for(i = 0; i<counter; i++)
                {
                    if (data[i].steps>max)
                    {
                        max = data[i].steps;
                        b = i;
                    }
                }
                printf("Largest steps: %s %s\n", data[b].date, data[b].time);
                break;

            case 'E':
                while (fgets(line, buffer_size, input))
                {   
                    tokeniseRecord(line,",",date,time,steps);
                    strcpy(data[counter].date,date);
                    strcpy(data[counter].time,time);
                    data[counter].steps = atoi(steps);
                    counter++;
                }
                for(i = 0; i<counter; i++)
                {
                    sum = sum + data[i].steps;
                }
                float counterf = counter;
                mean = (sum/counterf);
                meanint = (int)(mean+0.5);
                printf("Mean step count:%d\n", meanint);
                break;

            case 'F':
                while (fgets(line, buffer_size, input))
                {   
                    tokeniseRecord(line,",",date,time,steps);
                    strcpy(data[counter].date,date);
                    strcpy(data[counter].time,time);
                    data[counter].steps = atoi(steps);
                    counter++;
                }
                // create array with line numbers above 500
                for(i=0;i<counter;i++){
                    if(data[i].steps>500){
                        arr[length] = i;
                        length += 1;  
                    }
                }
                for(i=1;i<counter;i++){
                    if (arr[i-1] == (arr[i]-1)){
                        c += 1;
                    }
                    else{
                        c = 1;
                    }
                    // finds length of longest consecutive sequence
                    if (c>maxc){
                        maxc=c;
                    }
                }
                maxc = maxc-1;
                for(i=1;i<counter;i++){
                    // check that they are consecutive and difference is correct
                    if(arr[i+maxc] == arr[i]+maxc){
                        start = arr[i];
                        end = arr[i+maxc];
                    }
                }
                printf("Longest period start: %s %s\n", data[start].date, data[start].time);
                printf("Longest period end: %s %s\n", data[end].date, data[end].time);
                break;

            case 'Q':
                return 0;
                break;

            default:
                printf("Invalid choice. Try again.\n");
                break;

        }
    }
    return 0;
}
