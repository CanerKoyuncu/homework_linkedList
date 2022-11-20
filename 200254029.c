/*Name: Caner Koyuncu, Number:200254029, Ders: COM 201_HW_1*/

#include <stdlib.h>
#include <stdio.h>
#include <stdbool.h>
#include <string.h>

typedef struct {
    char firstLetter;
    struct Record *firstRecordPtr;
} HospitalList;

typedef struct {
    char name[50];
    char surname[50];
    int personId;
    char polyclinic[50];
    struct Record *nextRecord;
} Record;

void starter(HospitalList *);

void menu(HospitalList *);

int AddRecordToList(HospitalList *hospitalList);

void SearchRecordsFromList(HospitalList *);

void SortWithNameAllList(HospitalList *hospitalList);

void SortWithSurnameAllList(HospitalList *);

void SortWithPolyclinicAllList(HospitalList *);

int SearchfirstLetter(char);

Record *GetAllForSorting(HospitalList *);

void DeleteRecordFromList(HospitalList *hospitalList);

void PrintRecord(Record *);

int main() {
    HospitalList hospitalList[26];
    starter(hospitalList);
    menu(hospitalList);
}

void menu(HospitalList *h1) {
    int selected = 0;
    bool flag = true;
    do {
        printf("#####################-Hospital-Management-System-###################\n");
        printf("##  1-) Add New Record                                            ##\n");
        printf("##  2-) Search Record (with name, surname, and polyclinic name)   ##\n");
        printf("##  3-) Delete Record (with name, surname, and polyclinic name)   ##\n");
        printf("##  4-) Sort Records By Name                                      ##\n");
        printf("##  5-) Sort Records By Surname                                   ##\n");
        printf("##  6-) Sort Records By Polyclinic Name                           ##\n");
        printf("##  7-) Exit                                                      ##\n");
        printf("####################################################################\n");
        printf("Please select: ");
        scanf(" %d", &selected);
        printf("\n");
        switch (selected) {
            case 1:
                AddRecordToList(h1);
                break;
            case 2:
                SearchRecordsFromList(h1);
                break;
            case 3:
                DeleteRecordFromList(h1);
                break;
            case 4:
                SortWithNameAllList(h1);
                break;
            case 5:
                SortWithSurnameAllList(h1);
                break;
            case 6:
                SortWithPolyclinicAllList(h1);
                break;
            case 7:
                flag = false;
                break;
            default:
                printf("sdf");
                break;
        }
    } while (flag);
}

void mdenu(HospitalList *hospitalList) {

    bool flag = false;
    char select[20] = "";
    char s;

    do {
        int selected;
        printf("#####################-Hospital-Management-System-###################\n");
        printf("##  1-) Add New Record                                            ##\n");
        printf("##  2-) Search Record (with name, surname, and polyclinic name)   ##\n");
        printf("##  3-) Delete Record (with name, surname, and polyclinic name)   ##\n");
        printf("##  4-) Sort Records By Name                                      ##\n");
        printf("##  5-) Sort Records By Surname                                   ##\n");
        printf("##  6-) Sort Records By Polyclinic Name                           ##\n");
        printf("##  7-) Exit                                                      ##\n");
        printf("####################################################################\n");
        printf("Please select: ");
        flag = true;
        fgets(select, sizeof select, stdin);
        selected = atoi(select);

        switch (selected) {
            case 1:
                AddRecordToList(hospitalList);
                break;
            case 2:
                SearchRecordsFromList(hospitalList);
                break;
            case 3:
                DeleteRecordFromList(hospitalList);
                break;
            case 4:
                SortWithNameAllList(hospitalList);
                break;
            case 5:
                SortWithSurnameAllList(hospitalList);
                break;
            case 6:
                SortWithPolyclinicAllList(hospitalList);
                break;
            case 7:
                printf("Are you sure you want to log out? ('Y'es or 'No')");
                scanf("%c", &s);
                if (strcmp(&s, "y") == 0) {
                    flag = false;
                }
                break;
            default:
                printf("\nPlease enter a number between 1 and 7.\n");
                break;
        }
    } while (flag);

}

//tamamlandi
void starter(HospitalList *hospitallist) {
    int i = 0;
    char c;
    for (c = (char) ('a'); c <= (char) ('z'); c++, i++) {
        hospitallist[i].firstLetter = c;
        hospitallist[i].firstRecordPtr = NULL;
    }
}

int AddRecordToList(HospitalList *hospitalList) {
    char nameTemp[50];
    char surnameTemp[50];
    char polyclinicNameTemp[50];
    char polyclinicTemp[10];
    int personIDTemp = 0;
    bool flag1 = true;
    Record *recordTemp;

    printf("Name: ");
    scanf(" %s", &nameTemp);
    printf("Surname:");
    scanf(" %s", &surnameTemp);
    printf("Person ID: ");
    scanf(" %d", &personIDTemp);
    printf("#####-Polyclinics-#####}\n");
    printf("1)Orthodontics\n");
    printf("2)Endoscopy\n");
    printf("3)Implant\n");
    printf("4)Cardiology\n");
    while (flag1) {
        printf("Please select a polyclinic:");
        scanf(" %s", &polyclinicTemp);
        int polyclinic;
        polyclinic = atoi(polyclinicTemp);
        switch (polyclinic) {
            case 1:
                strcpy(polyclinicNameTemp, "Orthodontics");
                flag1 = false;
                goto bit;
            case 2:
                strcpy(polyclinicNameTemp, "Endoscopy");
                flag1 = false;
                goto bit;
            case 3:
                strcpy(polyclinicNameTemp, "Implant");
                flag1 = false;
                goto bit;
            case 4:
                strcpy(polyclinicNameTemp, "Cardiology");
                flag1 = false;
                goto bit;
            default:
                strcpy(polyclinicTemp, "");
                printf("Please select a polyclinic number between 1 and 4.\n");

        }
    }

    bit:

    printf("############Record Complited############\n\n");
    recordTemp = malloc(sizeof(Record));
    strcpy(recordTemp->name, nameTemp);
    strcpy(recordTemp->surname, surnameTemp);
    strcpy(recordTemp->polyclinic, polyclinicNameTemp);
    recordTemp->personId = personIDTemp;
    recordTemp->nextRecord = NULL;

    int nameNumber = SearchfirstLetter(recordTemp->name[0]);

    Record *ptr = NULL;
    ptr = (Record *) hospitalList[nameNumber].firstRecordPtr;
    bool flag = true;
    do {
        if (hospitalList[nameNumber].firstRecordPtr == NULL) {
            hospitalList[nameNumber].firstRecordPtr = (struct Record *) recordTemp;
            flag = false;
        } else {
            while (ptr->nextRecord != NULL) {
                ptr = (Record *) ptr->nextRecord;
            }
            ptr->nextRecord = (struct Record *) recordTemp;
            flag = false;
        }
    } while (flag);
    return 1;
}

//tamamlandi
int SearchfirstLetter(char cTemp) {

    char nameTemp = cTemp;
    char charTemp;
    int i = 0;
    for (charTemp = ('a'); charTemp <= ('z'); charTemp++, i++) {
        if (nameTemp == charTemp) {
            break;
        }
    }
    return i;
}

void SearchPolyclinicAllList(HospitalList *hospitalList) {

    int iterator;
    char value[50];
    Record *record = NULL;
    bool flag = true;
    bool flag1 = true;
    char polyclinicTemp[10];

    printf("#####-Polyclinics-#####\n");
    printf("1)Orthodontics\n");
    printf("2)Endoscopy\n");
    printf("3)Implant\n");
    printf("4)Cardiology\n");

    while (flag1) {
        printf("Please select a polyclinic:");
        scanf(" %s", &polyclinicTemp);
        int polyclinic;
        polyclinic = atoi(polyclinicTemp);
        switch (polyclinic) {
            case 1:
                strcpy(value, "Orthodontics");
                flag1 = false;
                goto bit;
            case 2:
                strcpy(value, "Endoscopy");
                flag1 = false;
                goto bit;
            case 3:
                strcpy(value, "Implant");
                flag1 = false;
                goto bit;
            case 4:
                strcpy(value, "Cardiology");
                flag1 = false;
                goto bit;
            default:
                strcpy(polyclinicTemp, "");
                printf("Please select a polyclinic number between 1 and 4.\n");

        }
    }

    bit:
    printf("\n\n#######################################\n");
    printf("##########FOUNDED RECORDS##############\n");
    for (iterator = 0; iterator <= 26 && flag; iterator++) {
        record = (Record *) hospitalList[iterator].firstRecordPtr;
        while (record != NULL) {
            if (strcmp(record->polyclinic, value) != 0) {
                PrintRecord(record);
                flag = false;
                break;
            } else if (record->nextRecord != NULL) {
                record = record->nextRecord;

            } else {
                flag = false;
                break;
            }
        }
    }
    if (flag) {
        printf("Cannot found this value.\n");
    }
}

void SearchName(HospitalList *hospitalList, char value[50]) {
    printf("\n###############FOUNDED RECORDS################\n");
    int k = SearchfirstLetter(value[0]);
    Record *record = hospitalList[k].firstRecordPtr;
    bool flag = false;

    while (record != NULL) {
        if (strcmp(record->name, value) == 0) {
            PrintRecord(record);
            flag = true;
            record = record->nextRecord;
        } else if (record->nextRecord != NULL) {
            record = record->nextRecord;
        } else {
            break;
        }
    }
    if (!flag) {
        printf("\nCannot found this value.\n\n");
    }
}

void SearchSurname(HospitalList *hospitalList, char value[50]) {
    int iterator = 0;
    Record *record = NULL;
    bool flag = true;

    printf("##########FOUNDED RECORDS#############\n");

    for (iterator = 0; iterator <= 26 && flag; iterator++) {
        record = hospitalList[iterator].firstRecordPtr;
        while (record != NULL) {
            if (strcmp(record->surname, value) == 0) {
                PrintRecord(record);
                flag = false;
                break;
            } else if (record->nextRecord != NULL) {
                record = record->nextRecord;
            }
        }
    }
    if (flag) {
        printf("Cannot found this value.\n");
    }

}

void SearchRecordsFromList(HospitalList *hospitalList) {
    char value[50];
    char selectedTemp[10];
    int selected = 0;
    bool flag = true;

    while (flag) {
        printf("1-) Search with name.\n");
        printf("2-) Search with surname.\n");
        printf("3-) Search with polyclinic name.\n");
        printf("4-) Search in all data.\n");
        printf("5-) Quit.\n");
        printf("Please select: ");
        scanf(" %s", &selectedTemp);
        selected = atoi(selectedTemp);


        switch (selected) {
            case 1:
                printf("Enter a name for search: ");
                scanf(" %s", value);
                SearchName(hospitalList, value);
                flag = false;
                break;
            case 2:
                printf("Enter a surname for search: ");
                scanf(" %s", value);
                SearchSurname(hospitalList, value);
                flag = false;
                break;
            case 3:
                printf("Enter a string for search: ");
                scanf(" %s", value);
                SearchName(hospitalList, value);
                SearchSurname(hospitalList, value);
                flag = false;
                flag = false;
                break;
            case 4:
                printf("Incorrect value input, please enter an integer of your choice from the menu.\n");
                break;
            default:
                printf("Please enter a number between 1 and 4.");
                printf("\n#########################################################################\n");
                break;
        }
    }
}

void DeleteRecordFromList(HospitalList *hospitalList) {
    Record *records[50];
    Record *afterRecords[50];
    Record *recordTemp;
    Record *afterRecordTemp = NULL;
    int i;
    int k = 0;
    bool flag = false;
    char value[50];
    printf("Please enter a name, surname or polyclinic Name for delete a recordTemp: ");
    scanf(" %s", &value);

    for (i = 0; i < 26; i++) {
        recordTemp = (Record *) hospitalList[i].firstRecordPtr;
        afterRecordTemp = NULL;
        while (recordTemp != NULL) {
            if (strcmp(recordTemp->name, value) == 0 || strcmp(recordTemp->surname, value) == 0 ||
                strcmp(recordTemp->polyclinic, value) == 0) {
                records[k] = recordTemp;
                afterRecords[k] = afterRecordTemp;
                afterRecordTemp = recordTemp;
                flag = true;
                k += 1;
            }
            recordTemp = (Record *) recordTemp->nextRecord;
        }
    }
    if (!flag) {
        printf("Cannot found this value.\n");
    } else {
        int i = 0;
        while (i < k) {
            printf("#####################--%d--######################\n", i + 1);
            PrintRecord(records[i]);
            i += 1;
        }
    }
    printf("Please select one record for delete. (Press '0' for quit.): ");
    scanf(" %d", &i);
    if (i != 0) {
        if (afterRecords[i - 1] != NULL) {
            afterRecords[i - 1]->nextRecord = records[i - 1]->nextRecord;
        }
        free(records[i - 1]);
    }
}

void PrintRecord(Record *record) {
    printf("Name: %s\n", record->name);
    printf("Surname: %s\n", record->surname);
    printf("PersonID: %d\n", record->personId);
    printf("Polyclinic: %s\n", record->polyclinic);
    printf("##############################################\n\n");
}

Record *GetAllForSorting(HospitalList *hospitalList) {
    Record *head = NULL;
    Record *recordTemp;
    Record *current;

    int i;

    for (i = 0; i < 26; i++) {
        recordTemp = hospitalList[i].firstRecordPtr;
        while (recordTemp != NULL) {
            Record *temp;
            temp = malloc(sizeof(Record));
            strcpy(temp->name, recordTemp->name);
            strcpy(temp->surname, recordTemp->surname);
            strcpy(temp->polyclinic, recordTemp->polyclinic);
            temp->personId = recordTemp->personId;
            temp->nextRecord = NULL;
            recordTemp = recordTemp->nextRecord;
            if (head == NULL) {
                head = temp;
                current = head;
            } else {
                current->nextRecord = temp;
                current = current->nextRecord;
            }
        }
    }
    return head;
}

void SortWithNameAllList(HospitalList *hospitalList) {
    Record *list = GetAllForSorting(hospitalList);
    Record *sortedList = NULL;
    Record *sortedListHead;
    Record *current = list;
    Record *after = NULL;
    Record *tmp = NULL;
    bool flag = true;

    while (list != NULL) {

        if (sortedList != NULL) {

            while (strcmp(list->name, sortedList->name) > 0) {
                if (flag) {
                    flag = false;
                } else {
                    after = sortedList;
                    sortedList = sortedList->nextRecord;
                }
                if (sortedList == NULL) {
                    break;
                }
            }
        }

        Record *recordTemp = malloc(sizeof(Record));
        strcpy(recordTemp->name, list->name);
        strcpy(recordTemp->surname, list->surname);
        strcpy(recordTemp->polyclinic, list->polyclinic);
        recordTemp->personId = list->personId;
        recordTemp->nextRecord = NULL;
        if (sortedList == NULL) {
            if (after != NULL) {
                after->nextRecord = recordTemp;
            } else {
                sortedList = recordTemp;
                sortedListHead = recordTemp;
            }
        } else {
            if (sortedList == sortedListHead) {
                if (flag) {
                    recordTemp->nextRecord = sortedListHead;
                    sortedListHead = recordTemp;
                } else {
                    recordTemp->nextRecord = sortedList->nextRecord;
                    sortedList->nextRecord = recordTemp;
                }
            } else {
                tmp = after->nextRecord;
                after->nextRecord = recordTemp;
                recordTemp->nextRecord = tmp;
            }

        }
        flag = true;
        sortedList = sortedListHead;
        list = list->nextRecord;
    }
    current = sortedListHead;
    while (current != NULL) {
        PrintRecord(current);
        current = current->nextRecord;
    }
}

void SortWithSurnameAllList(HospitalList *hospitalList) {
    Record *list = GetAllForSorting(hospitalList);
    Record *sortedList = NULL;
    Record *sortedListHead;
    Record *current = list;
    Record *after = NULL;
    Record *tmp = NULL;
    bool flag = true;

    while (list != NULL) {

        if (sortedList != NULL) {

            while (strcmp(list->surname, sortedList->surname) > 0) {
                if (flag) {
                    flag = false;
                } else {
                    after = sortedList;
                    sortedList = sortedList->nextRecord;
                }
                if (sortedList == NULL) {
                    break;
                }
            }
        }

        Record *recordTemp = malloc(sizeof(Record));
        strcpy(recordTemp->name, list->name);
        strcpy(recordTemp->surname, list->surname);
        strcpy(recordTemp->polyclinic, list->polyclinic);
        recordTemp->personId = list->personId;
        recordTemp->nextRecord = NULL;
        if (sortedList == NULL) {
            if (after != NULL) {
                after->nextRecord = recordTemp;
            } else {
                sortedList = recordTemp;
                sortedListHead = recordTemp;
            }
        } else {
            if (sortedList == sortedListHead) {
                if (flag) {
                    recordTemp->nextRecord = sortedListHead;
                    sortedListHead = recordTemp;
                } else {
                    recordTemp->nextRecord = sortedList->nextRecord;
                    sortedList->nextRecord = recordTemp;
                }
            } else {
                tmp = after->nextRecord;
                after->nextRecord = recordTemp;
                recordTemp->nextRecord = tmp;

            }

        }
        flag = true;
        sortedList = sortedListHead;
        list = list->nextRecord;
    }
    current = sortedListHead;
    while (current != NULL) {
        PrintRecord(current);
        current = current->nextRecord;
    }
}

void SortWithPolyclinicAllList(HospitalList *hospitalList) {
    Record *list = GetAllForSorting(hospitalList);
    Record *sortedList = NULL;
    Record *sortedListHead;
    Record *current = list;
    Record *after = NULL;
    Record *tmp = NULL;
    bool flag = true;

    while (list != NULL) {

        if (sortedList != NULL) {
            while (strcmp(list->polyclinic, sortedList->polyclinic) > 0) {
                if (flag) {
                    flag = false;
                } else {
                    after = sortedList;
                    sortedList = sortedList->nextRecord;
                }
            }
        }

        Record *recordTemp = malloc(sizeof(Record));
        strcpy(recordTemp->name, list->name);
        strcpy(recordTemp->surname, list->surname);
        strcpy(recordTemp->polyclinic, list->polyclinic);
        recordTemp->personId = list->personId;
        recordTemp->nextRecord = NULL;
        if (sortedList == NULL) {
            if (after != NULL) {
                after->nextRecord = recordTemp;
            } else {
                sortedList = recordTemp;
                sortedListHead = recordTemp;
            }
        } else {
            if (sortedList == sortedListHead) {
                if (flag) {
                    recordTemp->nextRecord = sortedListHead;
                    sortedListHead = recordTemp;
                } else {
                    recordTemp->nextRecord = sortedList->nextRecord;
                    sortedList->nextRecord = recordTemp;
                }
            } else {
                tmp = after->nextRecord;
                after->nextRecord = recordTemp;
                recordTemp->nextRecord = tmp;

            }

        }
        flag = true;
        sortedList = sortedListHead;
        list = list->nextRecord;
    }
    current = sortedListHead;
    char polyclinic[50] = "";
    while (current != NULL) {
        if (strcmp(polyclinic, current->polyclinic) != 0) {
            printf("############PolyClinic: %s ###########\n", current->polyclinic);
            *polyclinic = current->polyclinic;
        }
        PrintRecord(current);
        current = (Record *) current->nextRecord;
    }
    *polyclinic = "";
}
