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
    int j;
    char nums[] = "0123456789-";
    const char ch = '-';
    const char cha = ':';

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
        if (strlen(data[i].time) != 5 ){
            printf("Error: incorrect data\n");
            return 1;
        }
    }
    for (i=0;i<counter;i++){
        if (strcspn(data[i].date,"-") != 4 ){
            printf("Error: incorrect data\n");
            return 1;
        }
    }
    for (i=0;i<counter;i++){
        for (j=0;j<counter;j++){
            if (!isdigit(data[i].date[j]) && strchr(data[i].date, '-')==NULL){
                printf("Error: incorrect data\n");
                return 1;
            }
        }
    }
    for (i=0;i<counter;i++){
        for (j=0;j<counter;j++){
            if (!isdigit(data[i].time[j]) && strchr(data[i].time, ':')==NULL){
                printf("Error: incorrect data\n");
                return 1;
            }
        }
    }
    for (i=0;i<counter;i++){
        if (data[i].date[4] != '-'){
            return 1;
        }
        if (data[i].date[7] != '-'){
            return 1;
        }
        if ((data[i].date[0] - '0')>2){
            return 1;
        }
        if ((data[i].date[5] - '0')>1){
            return 1;
        }
        if ((data[i].date[8] - '0')>3){
            return 1;
        }
    }
    for (i=0;i<counter;i++){
        if (data[i].time[2] != ':'){
            return 1;
        }
        if ((data[i].date[0] - '0') > 2){
            return 1;
        }
        if ((data[i].date[3] - '0') > 5){
            return 1;
        }
    }
    for (i=0;i<counter;i++){
        if (strcspn(data[i].time,":") != 2 ){
            printf("Error: incorrect data\n");
            return 1;
        }
    }
    for (i=0;i<counter;i++){
        if (isdigit(data[i].steps) == 1){
            printf("Error: incorrect data\n");
            return 1;
        }
    }
    for (i=0;i<counter;i++){
        if (strlen(data[i].date )!= 10){
            printf("Error: incorrect data\n");
            return 1;
        }
    }
    printf("File opened successfully\n");

    int arr[100];
    int max = 0;
    int a;
    int b = 0;

    for (a = 3000;a>=0;a--){
        for (i=0;i<counter;i++){
            if (data[i].steps==a){
            arr[b] = i;
            b += 1;
        }
        }
    }

    FILE *file = fopen(strcat(filename, ".tsv"), "w");
    if (file == NULL) {
        perror("");
        return 1;
    }
    for (i=0;i<counter;i++){
        fprintf(file, "%s\t%s\t%d\n", data[arr[i]].date, data[arr[i]].time, data[arr[i]].steps);
    }
    fclose(input);
    fclose(file);
    return 0;
}