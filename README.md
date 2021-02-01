# personnel.c
This program will store and accept records based upon input. Also proper allocates and frees memory duirng file system


On startup no records will be wthin the database


ENTER RECORD:
  - To enter a record use the notation of "+IDNUM/FIRSTNAME/LASTNAME"
  - IDNUM must be less then 6 digits nd must be at least 1 digit
  - Cannot create record with conflicting IDNUM of a record within the system, if attempted will print friendly error message
REMOVE RECORD:
  - To remove a record use the notation of "-IDNUM"
  - If record exists within the system it will delete record from system and print message detailing which record was deleted
  - IF record does not exist will print friendly error message and reload initial prompt
LIST RECORDS:
  - To list current records, use notation "list"
  - Records will be printed with 0 added on end up to 6 digits
  - Records are stored i ascending order based off of IDNUM
EXIT:
  - To exit program usethe notation "exit"
  - Will exit cleanly and clear memory
INCORRECT INPUT:
  - If input is of incorrect notation, will print friendly error message and readdress initial prompt
