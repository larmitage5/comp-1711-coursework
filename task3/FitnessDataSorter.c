#include <stdio.h>
#include <stdlib.h>
#include <string.h>


// Define an appropriate struct
typedef struct {
	char date[11];
	char time[6];
	int steps;
} FITNESS_DATA;

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

int main() {
    FitnessData data[100];
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
        fprintf("%s\t%s\t%d", data[arr[i]].date, data[arr[i]].time, data[arr[i]].steps);
    }
    return 0;
}
