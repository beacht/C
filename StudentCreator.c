#include <stdio.h>
#include <stdlib.h>
#include <string.h>

//Defining the structure
typedef struct student
{
  char Lname[50];
  int assignment;
  int finalExam;
  int total;
  int *quiz;
} students;

students* readData(FILE *in, int *noOfRecords, int *noofquiz)
{
  students *ptr;
  //Read the first line for the number of records and number of quizzes
  fscanf(in, "%d %d", noOfRecords, noofquiz);
  //Allocate memory for the records and students
  ptr = (struct student*)malloc(*noOfRecords * (sizeof(struct student)));
  for(int i = 0; i < *noOfRecords; i++)
  {
    ptr[i].quiz = (int *)malloc(*noofquiz*(sizeof(int)));
    fscanf(in, "%s %d", ptr[i].Lname, &ptr[i].assignment);
    int quizsum = 0;
    //Reading quizzes
    for(int j = 0; j < *noofquiz; j++)
    {
      fscanf(in, "%d", &ptr[i].quiz[j]);
      quizsum += ptr[i].quiz[j];
    }
    //Reading the final exam
    fscanf(in, "%d", &ptr[i].finalExam);
    ptr[i].total = ptr[i].assignment + ptr[i].finalExam + quizsum;
  }
  //Return the dynamically allocated (and now filled) array of the structure
  return ptr;
}

int main()
{
  students *ptr;
  FILE *inFile, *outFile;
  int i, j, noOfRecords, noofquiz;
  inFile = fopen("input.txt", "r");

  if(inFile != NULL)
  {
    printf("Reading data from the input file");
    //Passes the reference of noOfRecords and noofquiz so we know what we have inside the input file
    ptr = readData(inFile, &noOfRecords, &noofquiz);
  }
  else
  {
    printf("PLEASE PROVIDE CORRECT INPUT FILE");
    exit(-1);
  }

  printf("\nReading completed. Showing the summary.");

  printf("\n(Lastname, Total Score)");

  for(i = 0; i < noOfRecords; i++)
  {
    printf("\n(%s, %d)", ptr[i].Lname, ptr[i].total);
  }

  printf("\n\nStudent with the highest score:\n");
  int max_total = 0;
  int max_total_index = 0;

  for(i = 0; i < noOfRecords; i++)
  {
    if(ptr[i].total > max_total)
    {
      max_total = ptr[i].total;
      max_total_index = i;
    }
  }

  outFile = fopen("output.txt", "w");

  fprintf(outFile, "(%s, %d)", ptr[max_total_index].Lname, ptr[max_total_index].total);
  printf("(%s, %d)", ptr[max_total_index].Lname, ptr[max_total_index].total);
  printf("\noutput generated");

  //Free allocated memory for every student's quizzes
  for(i = 0; i < noOfRecords; i++)
  {
    free(ptr[i].quiz);
  }
  
  //Free allocated memory for all records
  free(ptr);
  fclose(inFile);
  fclose(outFile);

  return 0;
}