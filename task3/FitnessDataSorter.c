#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>


// Define an appropriate struct
typedef struct {
	char date[11];
	char time[6];
	int steps;
} FitnessData;

// Define any additional variables here
/**
 * @param input the line from the file
 * @param delimeter the comma that splits up the data
 * @param date pointer for where the date should be stored
 * @param time pointer for where the time should be stored
 * @param steps pointer for where steps should be stored
*/

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
    FitnessData data[300];
    int buffer_size = 250;
    char line[buffer_size];
    char filename[buffer_size];
    int counter=0;
    char date[100];
    char time[100];
    char steps[100];
    int i;

    printf("Enter Filename: ");
    fgets(line, buffer_size, stdin);
    sscanf(line, " %s ", filename);
    FILE *input = fopen(filename, "r");
    if (!input)
    {
        printf("Error: invalid file\n");
        return 1;
    }

    while (fgets(line, buffer_size, input))
    {   
        tokeniseRecord(line,",",date,time,steps);
        strcpy(data[counter].date,date);
        strcpy(data[counter].time,time);
        data[counter].steps = atoi(steps);
        counter++;
    }

    for (i=0;i<counter;i++){
        if(strlen(data[i].date) != 10){
            printf("Error: incorrect data\n");
            return 1;
        }
        if (strlen(data[i].time) != 5 ){
            printf("Error: incorrect data\n");
            return 1;
        }
        if (isdigit(data[i].steps) == 1){
            printf("Error: incorrect data\n");
            return 1;
        }
    }
    printf("File opened successfully\n");

    int arr[counter];
    int max = 0;
    int a = 0;

    for (i = 0;i<counter;i++){
        for (int j = i + 1; j<counter;j++){
            if(arr[i]<arr[j]){
                int k = arr[i];
                arr[i] = arr[j];
                arr[j] = k;
            }
        }
    }

    FILE *file = fopen("FitnessData_2023.csv.tsv", "a+");
    if (file == NULL) {
        perror("");
        return 1;
    }
    for (i=0;i<counter;i++){
        fprintf(file, "%s\t%s\t%d", data[arr[i]].date, data[arr[i]].time, data[arr[i]].steps);
        printf("%s\t%s\t%d", data[arr[i]].date, data[arr[i]].time, data[arr[i]].steps);
    }
    fclose(input);
    fclose(file);
    return 0;
}