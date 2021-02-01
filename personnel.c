#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <math.h>
struct Record {
  char *Fname, *Gname;
  int ID;
  struct Record *next;
};

struct Record *head = NULL;

//prototypes
void makeRecord(char *Fname, char *Gname, int ID);
void addRecord(char *input);
void checkInput();
void listRecords();
void exitCleanly();
int IDisNumber(char *ID);
void removeRecord(char *input);
int recordExists(int ID);
int main(void) {
  printf("Welcome to the Record Keeper! Please enter your instruction\n");
  checkInput();
  return 0;
}
void checkInput() {
  while(0==0){
    //check input from user
    int MAX_LIMIT = 100;
    char input[MAX_LIMIT];
    fgets(input,MAX_LIMIT,stdin);
    //if user wants to add record
    if(input[0] == '+') {
      char *token  = strtok(input,"+");
      addRecord(token);
      
    }
    // user wants to delete record
    else if(input[0] == '-') {
      char *token = strtok(input,"-");
      removeRecord(token);
    }
    //if user wants to exit program
    else if(strcmp(input,"exit\n") == 0){
      exitCleanly();
    }
    //User wants to list records
    else if(strcmp(input,"list\n") == 0) {
      listRecords();
    }
    //if user command is unknown
    else{
      printf("Im sorry. I do not recognize that command\n");
    }
  }
}
void makeRecord(char *Fname, char *Gname, int ID) {
  struct Record *newRecord = (struct Record*)malloc(sizeof(struct Record));
  newRecord->Fname = Fname;
  newRecord->Gname = Gname;
  newRecord->ID = ID;
  struct Record *current = head;
  struct Record *previous = NULL;
  if(current == NULL) {
    head = newRecord;
    head->next = NULL;
  }
  else if(newRecord->ID < current->ID) {
    newRecord->next = current;
    head = newRecord;
  }
  else{
    previous = current;
    current = current->next;
    int added = 0;
    while(current != NULL) {
      if(newRecord->ID < current->ID) {
	previous->next = newRecord;
	newRecord->next = current;
	added = 1;
	break;
      }
      previous = current;
      current = current->next;
    }
    printf("%d\n",added);
    if(added != 1) {
      previous->next = newRecord;
    }
  }
  printf("Thank you. %s %s (%d) has been added.\n", newRecord->Fname, newRecord->Gname, newRecord->ID);
}
//pulls input and splits as well as checking for valid input ID
 void addRecord(char *input) {
   //parses input and adds record or throws error
   char *token = strtok(input,"/");//get ID from input
   if(IDisNumber(token) == 0) {
     printf("please enter a valid ID\n");
     checkInput();
   }
   if((floor(log10(abs(atoi(token)))) +1) > 6) {
     printf("Please enter valid ID\n");
     checkInput();
   } 
   int ID = atoi(token);// save ID to ID
   if(recordExists(ID) == 1) {
     printf("Record with ID: %d already exists, please use different ID", ID);
     checkInput();
   }
   char *Fname = strtok(NULL,"/");
   char *Gname = strtok(NULL,"\n");
   makeRecord(Fname, Gname, ID);
   checkInput();
 }
int IDisNumber(char *ID) {
  int i = 0;
  while(ID[i] != '\0'){
    if(isdigit(ID[i])== 0){
      return(0);
    }
    i++;
  }
  return 1;
}
//returns 1 if record exists in system, 0 if not
int recordExists(int ID){
  struct Record *currentRecord = head;
  while(currentRecord != NULL) {
    if(currentRecord->ID == ID) {
      return 1;
    }
    currentRecord = currentRecord->next;
  }
  return 0;
  
   }
//list Records list all current records
 void listRecords(){
   printf("Here are the current records:\n");
   struct Record *currentRecord = head;
   while(currentRecord!= NULL) {
     printf("%s %s (", currentRecord->Fname, currentRecord->Gname);
     int i = 6;
     int IDLen = (floor(log10(abs(currentRecord->ID))) + 1);
     while(IDLen < i) {
       printf("0");
       i--;
     }
     printf("%d)\n",currentRecord->ID);
     currentRecord = currentRecord->next;
   }
   checkInput();
 }
//removes record from the list and frees memory
void removeRecord(char *input) {
  struct Record *current = head;
  struct Record *previous = NULL;
  char *token = strtok(input,"/");
  int ID = atoi(token);
  if(recordExists(ID) != 1) {
    printf("No record with ID: %d exists\n", ID);
    checkInput();
  }
  if(current == NULL) {
    checkInput();
  }
  else{
    while(current->ID != ID) {
      previous = current;
      current = current->next;
    }
    printf("Thank you. %s %s has been deleted.\n", current->Fname, current->Gname);
    if(current == head) {
      head = head->next;
      free(current);
    }
    else{
      previous->next = current->next;
      free(current);
    }
  }
}
//exits program
void exitCleanly(){
 printf("Goodbye!");
  exit(0);
}
