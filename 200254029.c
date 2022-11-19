/*Name: Caner Koyuncu, Number:200254029, Ders: COM 201_HW_1*/

#include <stdlib.h>
#include <stdio.h>
#include <stdbool.h>
#include <string.h>

typedef struct{
    char firstLetter;
    struct Record* firstRecordPtr;
}HospitalList;

typedef struct {
    char name[50];
    char surname[50];
    int personId;
    char polyclinic[50];
    struct Record* nextRecord;
}Record;

void starter(HospitalList *);
void menu(HospitalList*);

int AddRecord(HospitalList* );
void SearchRecords();
void SortWithName(HospitalList*);
void SortWithSurname(HospitalList*);
void SortWithPolyclinic(HospitalList*);
int SearchfirstLetter(HospitalList* ,char);
Record* GetAllForSorting(HospitalList*);

void Del(HospitalList*);
void PrintRecord(Record*);

HospitalList hl[26];

int main() {

    starter(hl);
    menu(hl);

}


void menu(HospitalList *hl){
    int selected;
    bool flag=false;
    char select[20]= "";
    char s;

    do{

    selected=0;
    printf("1-) Add New Record\n");
    printf("2-) Search Record (with name, surname, and polyclinic name)\n");
    printf("3-) Delete Record (with name, surname, and polyclinic name)\n");
    printf("4-) Sort Records By Name\n");
    printf("5-) Sort Records By Surname\n");
    printf("6-) Sort Records By Polyclinic Name\n");
    printf("7-) Exit\n");
    printf("Please select: ");
    flag = true;
    fgets(select, sizeof select, stdin);
    selected = atoi(select);


    switch(selected){
        case 1:
            AddRecord(hl);
            continue;
        case 2:
            SearchRecords();
            continue;
        case 3:
            Del(hl);
            continue;
	    case 4:
	        SortWithName(hl);
            continue;
	    case 5:
	        SortWithSurname(hl);
            continue;
	    case 6:
            SortWithPolyclinic(hl);
            continue;
	    case 7:

	    	printf("Are you sure you want to log out? ('Y'es or 'No')");
            scanf("%c", &s);
            if(strcmp(s,"y") == 0){
                flag = false;
            }
            continue;
        default:
            printf("Please enter a number between 1 and 7.\n");
            continue;
		}
	}while(flag);

}

//tamamlandi
void starter(HospitalList *hospitallist){
    int i=0;
    char c;
    for(c=(char)('a');c<=(char)('z');c++,i++){
            hospitallist[i].firstLetter=c;
            hospitallist[i].firstRecordPtr=NULL;
    }
}


int AddRecord(HospitalList* hl){
	char nameTemp[50];
    char surnameTemp[50];
    char polyclinicNameTemp[50];
    char polyclinicTemp[3];
	int personIDTemp = 0;

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
    printf("Please select a polyclinic:");
    scanf(" %c", &polyclinicTemp);
    int polyclinic = NULL;
    polyclinic = atoi(polyclinicTemp);

    switch (polyclinic){
        case 1:
            strcpy(polyclinicNameTemp , "Orthodontics");
            goto bit;
        case 2:
            strcpy(polyclinicNameTemp , "Endoscopy");
            goto bit;
        case 3:
            strcpy(polyclinicNameTemp , "Implant");
            goto bit;
        case 4:
            strcpy(polyclinicNameTemp , "Cardiology");
            goto bit;
        default:
            printf("Please select a polyclinic number between 1 and 4.");

    }
    Record *recordTemp;
    bit:

    recordTemp = malloc(sizeof(Record));
	strcpy(recordTemp->name, nameTemp);
	strcpy(recordTemp->surname, surnameTemp);
	strcpy(recordTemp->polyclinic, polyclinicNameTemp);
	recordTemp->personId = personIDTemp;
    recordTemp->nextRecord= NULL;

	int nameNumber = SearchfirstLetter(hl,recordTemp->name[0]);

    Record * ptr = NULL;
    ptr = hl[nameNumber].firstRecordPtr;
	bool flag = true;
	do{
		if(hl[nameNumber].firstRecordPtr==NULL){
            hl[nameNumber].firstRecordPtr = recordTemp;
			flag = false;
		}else{
            while(ptr->nextRecord != NULL){
                ptr = ptr->nextRecord;
            }
            ptr->nextRecord = recordTemp;
            flag = false;
		}
	}while(flag);
    return 1;
}

//tamamlandi
int SearchfirstLetter(HospitalList *hl, char cTemp){

	char nameTemp= cTemp;
	char charTemp;
	int i=0;
    char c;
    for(charTemp=('a');charTemp<=('z');charTemp++,i++){
        if(nameTemp == charTemp){
            break;
        }
    }
	return i;
}

void SearchPolyclinic(HospitalList* hospitalList, char value[50]){
    int iterator = 0;
    Record* record= NULL;
    bool flag = true;

    for(iterator= 0; iterator<=26 && flag ; iterator++){
        record= hl[iterator].firstRecordPtr;
        while(record != NULL){
            if(strcmp(record->polyclinic, value)){
                PrintRecord(record);
                flag = false;
                break;
            }else if(record->nextRecord != NULL){
                record = record->nextRecord;
            }
        }
    }
    if(flag){
        printf("Cannot found this value.\n");
    }
}

void SearchName(HospitalList* hospitalList, char value[50]){
    int k = SearchfirstLetter(hl, value[0]);
    Record* record = hl[k].firstRecordPtr;
    bool flag = false;
    while(record != NULL){
        if(strcmp(record->name, value) == 0){
            PrintRecord(record);
            flag = true;
            record = record->nextRecord;
        }else if(record->nextRecord != NULL){
            record = record->nextRecord;
        }else{
            break;
        }
    }
    if(!flag){
        printf("Cannot found this value.\n");
    }
}

void SearchSurname(HospitalList* hospitalList, char value[50]){
    int iterator = 0;
    Record* record= NULL;
    bool flag = true;

    for(iterator= 0; iterator<=26 && flag ; iterator++){
        record= hl[iterator].firstRecordPtr;
        while(record != NULL){
            if(strcmp(record->surname, value)){
                PrintRecord(record);
                flag = false;
                break;
            }else if(record->nextRecord != NULL){
                record = record->nextRecord;
            }
        }
    }
    if(flag){
        printf("Cannot found this value.\n");
    }

}

void SearchRecords(){
    char value[50];
	int selected = 0;

    printf("1-) Search with name.\n");
    printf("2-) Search with surname.\n");
    printf("3-) Search with polyclinic name.\n");
    printf("4-) Quit.\n");
    printf("Please select: ");
    scanf(" %d", &selected);

    switch(selected){
		case 1:
            printf("Enter a name for search: ");
            scanf(" %s", value);
			//SearchWithName(hl, value);
            SearchName(hl, value);
            break;
        case 2:
            printf("Enter a surname for search: ");
            scanf(" %s", value);
            SearchSurname(hl, value);
            break;
        case 3:
            printf("Enter a polyclinic for search: ");
            scanf(" %s", value);
            SearchPolyclinic(hl, value);
            break;
        default:
            printf("Incorrect value input, please enter an integer of your choice from the menu.\n");
            printf("Press enter a integer: ");
            break;
    }
}

void Del(HospitalList* hospitalList){
    Record* records[50];
    Record* afterRecords[50];
    Record* recordTemp;
    Record* afterRecordTemp = NULL;
    int i;
    int k = 0;
    bool flag = false;
    char value[50];
    printf("Please enter a name, surname or polyclinic Name for delete a recordTemp: ");
    scanf(" %s", &value);

    for(i= 0; i<26; i++){
        recordTemp = (Record *) hl[i].firstRecordPtr;
        afterRecordTemp = NULL;
        while(recordTemp != NULL){
            if(strcmp(recordTemp->name, value) == 0 || strcmp(recordTemp->surname, value) == 0 || strcmp(recordTemp->polyclinic, value) == 0){
                records[k] = recordTemp;
                afterRecords[k] = afterRecordTemp;
                afterRecordTemp = recordTemp;
                flag = true;
                k += 1;
            }
            recordTemp = (Record *) recordTemp->nextRecord;
        }
    }
    if(!flag){
        printf("Cannot found this value.\n");
    }else{
        int i = 0;
        while(i<k){
            printf("#####################--%d--######################\n",i+1);
            PrintRecord(records[i]);
            i+=1;
        }
    }
    printf("Please select one record for delete. (Press '0' for quit.): ");
    scanf(" %d", &i);
    if(i != 0){
            afterRecords[i-1]->nextRecord = records[i-1]->nextRecord;
            free(records[i-1]);
    }

}

void PrintRecord(Record* record){
    printf("Name: %s\n", record->name);
    printf("Surname: %s\n", record->surname);
    printf("PersonID: %d\n", record->personId);
    printf("Polyclinic: %s\n", record->polyclinic);
    printf("############################################\n");
}

Record* GetAllForSorting(HospitalList* hl){
    Record* head = NULL;
    Record* recordTemp ;
    Record* temp = NULL;
    Record* current = recordTemp;
    int i;

    for(i= 0; i<=26; i++){
        recordTemp= hl[i].firstRecordPtr;
        if(recordTemp!=NULL){
            Record *temp = malloc(sizeof(Record));
            strcpy(temp->name, recordTemp->name);
            strcpy(temp->surname, recordTemp->surname);
            strcpy(temp->polyclinic, recordTemp->polyclinic);
            temp->personId = recordTemp->personId;
            temp->nextRecord = NULL;

        if(head == NULL){
            head = recordTemp;
            current = head;
        }else {
            while (recordTemp != NULL) {

                Record *temp1 = malloc(sizeof(Record));
                strcpy(temp1->name, recordTemp->name);
                strcpy(temp1->surname, recordTemp->surname);
                strcpy(temp1->polyclinic, recordTemp->polyclinic);
                temp1->personId = recordTemp->personId;
                temp1->nextRecord = NULL;
                if (recordTemp->nextRecord != NULL) {
                    current->nextRecord = temp1;
                    recordTemp = recordTemp->nextRecord;
                    current = current->nextRecord;
                }else{
                    current->nextRecord = temp1;
                    current = current->nextRecord;
                    break;
                }
            }
        }
        }
    }
    return head;
}

void SortWithName(HospitalList* hospitalList){
    Record* list = GetAllForSorting(hospitalList);
    Record* sortedList = NULL;
    Record* sortedListHead;
    Record* current = list;
    Record* after = NULL;
    Record* tmp = NULL;
    bool flag = true;

    while(list != NULL){

        if(sortedList != NULL){

            while(strcmp(list->name, sortedList->name)>0){
                if(flag){
                    flag = false;
                }else{
                    after = sortedList;
                    sortedList = sortedList->nextRecord;
                }
                if(sortedList == NULL){
                    break;
                }

            }

        }

        Record *recordTemp = malloc(sizeof(Record));
        strcpy(recordTemp->name, list->name);
        strcpy(recordTemp->surname, list->surname);
        strcpy(recordTemp->polyclinic, list->polyclinic);
        recordTemp->personId = list->personId;
        recordTemp->nextRecord= NULL;
        if(sortedList == NULL){
            if(after != NULL) {
                after->nextRecord = recordTemp;
            }else{
                sortedList=recordTemp;
                sortedListHead = recordTemp;
            }

        }else{
            if (sortedList == sortedListHead) {
                if(flag){
                    recordTemp->nextRecord = sortedListHead;
                    sortedListHead = recordTemp;
                }else{
                    recordTemp->nextRecord = sortedList->nextRecord;
                    sortedList->nextRecord = recordTemp;
                }
            }else{
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
    while (current != NULL){
        PrintRecord(current);
        current = current->nextRecord;
    }
}

void SortWithSurname(HospitalList* hospitalList){
    Record* list = GetAllForSorting(hospitalList);
    Record* sortedList = NULL;
    Record* sortedListHead;
    Record* current = list;
    Record* after = NULL;
    Record* tmp = NULL;
    bool flag = true;

    while(list != NULL){

        if(sortedList != NULL){

            while(strcmp(list->surname, sortedList->surname)>0){
                if(flag){
                    flag = false;
                }else{
                    after = sortedList;
                    sortedList = sortedList->nextRecord;
                }
                if(sortedList==NULL){
                    break;
                }
            }
        }

        Record *recordTemp = malloc(sizeof(Record));
        strcpy(recordTemp->name, list->name);
        strcpy(recordTemp->surname, list->surname);
        strcpy(recordTemp->polyclinic, list->polyclinic);
        recordTemp->personId = list->personId;
        recordTemp->nextRecord= NULL;
        if(sortedList == NULL){
            if(after != NULL) {
                after->nextRecord = recordTemp;
            }else{
                sortedList=recordTemp;
                sortedListHead = recordTemp;
            }
        }else{
            if (sortedList == sortedListHead) {
                if(flag){
                    recordTemp->nextRecord = sortedListHead;
                    sortedListHead = recordTemp;
                }else{
                    recordTemp->nextRecord = sortedList->nextRecord;
                    sortedList->nextRecord = recordTemp;
                }
            }else{
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
    while (current != NULL){
        PrintRecord(current);
        current = current->nextRecord;
    }
}

void SortWithPolyclinic(HospitalList* hospitalList){
    Record* list = GetAllForSorting(hospitalList);
    Record* sortedList = NULL;
    Record* sortedListHead;
    Record* current = list;
    Record* after = NULL;
    Record* tmp = NULL;
    bool flag = true;

    while(list != NULL){

        if(sortedList != NULL){
            while(strcmp(list->polyclinic, sortedList->polyclinic)>0){
                if(flag){
                    flag = false;
                }else{
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
        recordTemp->nextRecord= NULL;
        if(sortedList == NULL){
            if(after != NULL) {
                after->nextRecord = recordTemp;
            }else{
                sortedList=recordTemp;
                sortedListHead = recordTemp;
            }
        }else{
            if (sortedList == sortedListHead) {
                if(flag){
                    recordTemp->nextRecord = sortedListHead;
                    sortedListHead = recordTemp;
                }else{
                    recordTemp->nextRecord = sortedList->nextRecord;
                    sortedList->nextRecord = recordTemp;
                }
            }else{
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
    char polyclinic[50] ="";
    while (current != NULL){
        if(strcmp(polyclinic,current->polyclinic) != 0){
            printf("############PolyClinic: %s ###########\n", current->polyclinic);
            *polyclinic = (char*)current->polyclinic;
        }
        PrintRecord(current);
        current = current->nextRecord;
    }
}
