///bin/true;COMPILER_OPTIONS="-g -Wall -Wextra --std=c99 -O1 -fsanitize=address,undefined";THIS_FILE="$(cd "$(dirname "$0")"; pwd -P)/$(basename "$0")";OUT_FILE="/tmp/build-cache/$THIS_FILE";mkdir -p "$(dirname "$OUT_FILE")";test "$THIS_FILE" -ot "$OUT_FILE" || $(which clang || which gcc) $COMPILER_OPTIONS -xc "$THIS_FILE" -o "$OUT_FILE" || exit;exec "$OUT_FILE" "$@"
#include <stdio.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#define MAX 2000                                          //Number of records in the input file
#define INPUTFILE "itcont.txt"      //Input file location
#define OUTPUTFILE "top_cost_drug.txt"                           //Output file location

typedef struct rec{             //input STRUCT - Heterogenous Data Type
	int id;                     //id
	char last_name[20];         //prescriber_last_name
	char first_name[20];        //prescriber_first_name
	char drug_name[30];         //drug_name
	float drug_cost;            //drug_cost
}r;

typedef struct output{          //output STRUCT - Heterogenous Data Type
	char drug_name[30];         //drug_name
	int num_prescriber;         //Number of unique prescribers
	float total_cost;           //total drug cost
}op;

int main() {
	FILE *fp; 	struct rec record[MAX]; r t; op output[MAX];
	char line[200],header_buffer[1000], *item,*temp;  int count = 0; 
	
	fp = fopen(INPUTFILE, "r");                    //Reading from the Input file
	if (fp == NULL) {
		fprintf(stderr, "Error reading file\n");   //Handling Error for empty file
		return 1;
	}
	if (fp != NULL){
		    fgets(header_buffer, 1000, fp);               //Handling the headers in the file
			while (fgets(line, 200, fp) != NULL){         //Handling the data   
				item = strtok(line, ",");   	 record[count].id = atoi(item);
				item = strtok(NULL, ",");        strcpy(record[count].last_name, item);
				item = strtok(NULL, ",");        strcpy(record[count].first_name, item);
				item = strtok(NULL, ",");        strcpy(record[count].drug_name, item);
				item = strtok(NULL, " \n\t");  	 record[count].drug_cost = atof(item);
				count++;
			
		}
	}
	
	for (int i = 0; i < count; i++){                // printing the records in the original order as read from file
		printf(" %d,%s,%s,%s,%f\n", record[i].id, record[i].last_name, record[i].first_name, record[i].drug_name, record[i].drug_cost);
	}

	/*sorting in descending alphabetical order of drug name*/
	for (int i = 0; i < count; i++){
		for (int j = i + 1; j < count; j++){
			if (strcmp(record[i].drug_name, record[j].drug_name)<0){
				t = record[i];
				record[i] = record[j];
				record[j] = t;
			}
		}
	}
	temp = "ABC";
	printf("After sorting \n");         // printing the records after sorting in descending alphabetical order of drug name
	for (int i = 0; i < count; i++){
		int num_count = 1;
		int total_cost = record[i].drug_cost;
		for (int j = i + 1; j < count; j++){
			while (strcmp(record[i].drug_name, record[j].drug_name) == 0 && (strcmp(record[i].last_name, record[j].last_name) != 0 || strcmp(record[i].first_name, record[j].first_name) != 0)){
	         	num_count++; 
				total_cost = total_cost + record[j].drug_cost;
				break;
			}
		}
		
		if (strcmp(temp, record[i].drug_name)!=0){
			strcpy(output[i].drug_name, record[i].drug_name);
			output[i].num_prescriber = num_count;
			temp = record[i].drug_name;
			output[i].total_cost = total_cost;
		}
		else{
			strcpy(output[i].drug_name, record[i].drug_name);
			output[i].num_prescriber = 0;
			output[i].total_cost = 0;
		}
		
	}
		for (int i = 0; i < count; i++){ 
			if (output[i].num_prescriber >0)
				printf("%s, %d, %f \n", output[i].drug_name, output[i].num_prescriber, output[i].total_cost);
		}
	fclose(fp);

	FILE *fp1 = fopen(OUTPUTFILE,"w");                   //Opening the file in write mode 
	fprintf(fp1,"drug_name, num_prescriber, total_cost\n");
	for (int i = 0; i < count; i++){                     //Writing the output to a file
		if (output[i].num_prescriber>0)
		fprintf(fp1,"%s, %d, %f\n", output[i].drug_name, output[i].num_prescriber, output[i].total_cost);
	}
	fclose(fp1);
	return 0;
}
