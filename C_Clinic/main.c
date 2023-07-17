/******************************************************************/
/****************  Author  : HAMDY NADY        ********************/
/****************  Date    : 1/1/2023         ********************/
/****************  Version : 1.0               ********************/
/******************************************************************/
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_PATIENTS         100    //max number of patient
#define MAX_SLOTS            5      //max number of slots available per day
#define MAX_NAME_LENGTH      50     //the max length of patient name

/*the patient details : name, age, Gender, ID*/
struct Patient
{
    char Name[MAX_NAME_LENGTH];
    int Age;
    char Gender;
    int ID;
};

/*the details needed for reserve a slot*/
struct Reservation
{
    int slot;
    int patientID;
};


void AdmenMode(void);
void UserMode(void);
void AddNewPatientRecord(void);
void EditPatientRecord(void);
void ReserveSlotWithTheDoctor(void);
void CancelReservation(void);
void ViewPatientRecord(void);
void ViewTodayReservations(void);

/* Global Variables */
struct Patient patients[MAX_PATIENTS];
int patient_count = 0;
struct Reservation reservations[MAX_SLOTS];
int reserveSlots = 0;

int main()
{
    int mode;
    printf("Welcome to the Clinic Management System!\n");
    printf("Please Choose Mode : \n");
    printf("1- Admen Mode\n");
    printf("2- User Mode\n");
    printf("3- Exit Program.\n");
    printf("Enter Your Choice : ");
    scanf("%d",&mode);
    if(mode == 1)
    {
        AdmenMode();
    }
    else if(mode == 2)
    {
        UserMode();
    }
    else if(mode == 3)
    {
        exit(0);
    }
    else
    {
        printf("InValid Choice, Exiting...\n");
    }
    return 0;
}


void AdmenMode()
{
    int PassAttempt = 0;
    int password;
    int choice;
    while(PassAttempt < 3)
    {
        printf("Enter PassWord : ");
        scanf("%d",&password);
        if(password == 1234)
        {
            printf("Login Successfully!\n");
            while(1)
            {
                printf("\nAdmen Mode\n");
                printf("1. Add new patient record.\n");
                printf("2. Edit patient record.\n");
                printf("3. Reserve a slot with the doctor.\n");
                printf("4. Cancel reservation.\n");
                printf("5. Switch to user Mode\n");
                printf("Enter YOur Choice : ");
                scanf("%d",&choice);
                switch(choice)
                {
                case 1:
                    AddNewPatientRecord();
                    break;
                case 2:
                    EditPatientRecord();
                    break;
                case 3:
                    ReserveSlotWithTheDoctor();
                    break;
                case 4:
                    CancelReservation();
                    break;
                case 5:
                    /*return=> used to exit the adminMode() function and
                        return control to the main() function*/
                    printf("Switching to User Mode...\n");
                    return main();
                default:
                    printf("Invalid Choice.\n");
                    break;
                }
            }
        }
        else
        {
            PassAttempt++;
            printf("Wrong Choice, Please Try Again.\n");
        }
    }
    printf("Too many Incorrect password attempt,Exiting....");
    /*exit() is c std lib function,it takes status as a parameter.
     *Status indicates how the program terminated => 0 :Program terminated successfully*/
    exit(0);
}

void UserMode()
{
    int choice;
    while(1)
    {
        printf("\nUser Mode\n");
        printf("1. View patient record.\n");
        printf("2. View today's reservations.\n");
        printf("3. Switch to Admen Mode.\n");
        printf("Enter Your Choice:");
        scanf("%d",&choice);
        switch(choice)
        {
        case 1:
            ViewPatientRecord();
            break;
        case 2:
            ViewTodayReservations();
            break;
        case 3:
            printf("Switching to Admen Mode....\n");
            return main();
        default:
            printf("Invalid choice.\n");
            break;
        }
    }
}

void AddNewPatientRecord()
{
    struct Patient patient;
    int i;
    printf("\nAdd New Patient Record!\n");

    printf("Enter Patient Name : ");
    scanf(" %[^\n]s", patient.Name);

    printf("Enter Patient Age: ");
    scanf("%d",&patient.Age);

    printf("Enter Patient Gender(M/F): ");
    scanf(" %c",&patient.Gender);

    printf("Enter Patient ID : ");
    scanf("%d",&patient.ID);

    /*Check if Id already exists*/
    for(i =0; i<patient_count; i++)
    {
        if(patients[i].ID == patient.ID)
        {
            printf("Error, ID is already exists");
            break;
        }
    }
    patients[patient_count++] = patient;
    printf("Patient Record Added Successfully.\n");
}

void EditPatientRecord()
{
    int id,count;
    printf("\nEdit Patient Record\n");

    printf("Enter Patient ID: ");
    scanf("%d",&id);

    for(count=0; count<patient_count; count++)
    {
        if(patients[count].ID == id)
        {
            printf("Enter updated name : ");
            scanf(" %[^\n]s", patients[count].Name);

            printf("Enter updated age: ");
            scanf("%d",&patients[count].Age);

            printf("Enter updated Gender(M/F): ");
            scanf(" %c",&patients[count].Gender);

            printf("Patient Record Updated Successfully.\n");
            return;
        }
    }
    printf("Error: Patient with ID %d is not found.\n",id);
}

void ReserveSlotWithTheDoctor()
{
    int id, slot, i;
    printf("\nReserve a Slot With The Doctor.\n");
    printf("The available slots: \n");
    printf("1. 2pm    to 2:30pm\n");
    printf("2. 2:30pm to 3pm   \n");
    printf("3. 3pm    to 3:30pm\n");
    printf("4. 4pm    to 4:30pm\n");
    printf("5. 4:30pm to 5pm   \n");

    printf("Enter patient ID: ");
    scanf("%d", &id);

    printf("Enter desired slot:");
    scanf("%d",&slot);

    for(i=0; i<reserveSlots; i++)
    {
        if(reservations[i].patientID == id)
        {
            printf("Error: this slot already reserved.\n");
            return;
        }
    }
    reservations[reserveSlots].slot = slot;
    reservations[reserveSlots].patientID = id;
    reserveSlots++;
    printf("Slot Reserved Successfully.\n");
}

void CancelReservation()
{
    int id,i,j;
    printf("\nCancel Reservation.\n");

    printf("Enter patient ID: ");
    scanf("%d",&id);

    for(i=0;i<reserveSlots;i++){
        if(reservations[i].patientID == id){
            for(j=i;j<reserveSlots-1;j++){
                reservations[j]=reservations[j+1];
            }
            reserveSlots--;
            printf("Reservation Canceled Successfully.\n");
            return;
        }
    }
    printf("Error: Reservation not found for patient with ID %d",id);
}

void ViewPatientRecord(){
 int id,i;
    printf("\nView Patient Record\n");

    printf("Enter Patient ID:");
    scanf("%d",&id);

    for(i=0;i<patient_count;i++){
        if(patients[i].ID == id){
            printf("\nThe Patient Record\n");
            printf("Patient name: %s\n",patients[i].Name);
            printf("Patient Age: %d\n",patients[i].Age);
            printf("Patient Gender: %c\n",patients[i].Gender);
            return;
        }
    }
    printf("Error:Patient with ID &d not found.\n",id);
}

void ViewTodayReservations()
{
    int i;
    printf("\nView Today's Reservations\n");

    if(reserveSlots == 0){
        printf("No Reservations for today\n");
    }else{
        for(i=0;i<reserveSlots;i++){
            printf("Slot: %d\n,Patient: %d\n",reservations[i].slot,reservations[i].patientID);
        }
    }

}
