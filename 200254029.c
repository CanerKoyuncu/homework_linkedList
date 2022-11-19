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
void SortInsert(HospitalList* );
void SortRecordsBySurname(char);
void SortRecordsByPolyclinicName(char );
int SearchfirstLetter(HospitalList* ,char);
Record* GetAllForSorting(HospitalList*);
void SortName(HospitalList*);
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
	        SortInsert(hl);
            //GetAllForSorting(hl);
            continue;
	    case 5:
	        printf("5-");
            continue;
	    case 6:
	        printf("6");
            continue;
	    case 7:
	    	printf("false");
            flag = false;
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

//TODO: Hatalı giriş uyarıları yapılacak.
int AddRecord(HospitalList* hl){
	char nameTemp[50];
    char surnameTemp[50];
    char polyclinicNameTemp[50];
	int personIDTemp = 0;

	printf("Name: ");
    scanf(" %s", &nameTemp);
    printf("Surname:");
    scanf(" %s", &surnameTemp);
    printf("Person ID: ");
    scanf(" %d", &personIDTemp);
    printf("Polyclinic: ");
    scanf(" %s", &polyclinicNameTemp);

	Record *recordTemp = malloc(sizeof(Record));
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
                if (recordTemp->nextRecord != NULL) {
                    current->nextRecord = temp;
                    recordTemp = recordTemp->nextRecord;
                    current = current->nextRecord;
                }else{
                    current->nextRecord = temp;
                    current = current->nextRecord;
                    break;
                }
            }
        }
        }
    }
    return head;
}

int GetLength(HospitalList* hl){

    int i;
    int counter = 0;
    Record* current = NULL;

    for(i= 0; i<26; i++){
        current = hl[i].firstRecordPtr;
        if(current != NULL){
            do{
                counter += 1;
                current = current->nextRecord;
            }while(current != NULL);
        }
    }
    return counter;
}
//bubble

void SortName(HospitalList* hospitalList){

    int length = GetLength(hospitalList);
    bool flag;

    Record* head= NULL;
    Record* current = hl[0].firstRecordPtr;
    Record* next = current->nextRecord;
    Record* afterTemp = NULL;
    Record* tmp = NULL;

    for(int i =0; i < length; i++){
        flag = true;
        for (int j = length; j>1; j--) {
            if(strcmp(current, next)>0){
                if(afterTemp != NULL){
                    flag = false;
                    tmp = current->nextRecord;
                    current->nextRecord = next->nextRecord;
                    next->nextRecord = afterTemp->nextRecord;
                    afterTemp->nextRecord = tmp;
                }else if(afterTemp == NULL){
                    flag = false;
                    tmp = current->nextRecord;
                    current->nextRecord = next->nextRecord;
                    next->nextRecord = afterTemp->nextRecord;
                    head = tmp;
                }
            }
        }
    }

}

//insertion sort
void SortInsert(HospitalList* hospitalList){
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
            sortedList = recordTemp;
            sortedListHead = recordTemp;
        }else{
            if (sortedList == sortedListHead) {
                if(flag){
                    recordTemp->nextRecord = sortedListHead;
                    sortedListHead = recordTemp;
                }else{
                    sortedList = sortedList->nextRecord;
                    recordTemp->nextRecord = sortedList->nextRecord;
                    sortedList->nextRecord = recordTemp;

                }
            }else
            {
                if (sortedList != NULL) {
                    if (sortedList->nextRecord != NULL) {
                        tmp = sortedList->nextRecord;
                        sortedList->nextRecord = recordTemp;
                        recordTemp->nextRecord = tmp;
                    } else {
                        sortedList->nextRecord = recordTemp;
                    }
                }
            }

        }
        current = sortedListHead;
        while (current != NULL){
            printf("%s\n", current->name);
            current = current->nextRecord;
        }

        flag = true;
        sortedList = sortedListHead;
        list = list->nextRecord;
    }



}

//deprecated functions
void SearchWithName(HospitalList* hospitalList, char value[50]){
    int k = SearchfirstLetter(hospitalList, value[0]);
    Record* record = (Record*)hospitalList[k].firstRecordPtr;

    bool flag = true;
    while(flag){
        if(strcmp(record->name , value) == 0){
            printf("Name: %s\n", record->name);
            printf("Surname: %s\n", record->surname);
            printf("PersonID: %d\n", record->personId);
            printf("Polyclinic: %s\n", record->polyclinic);
            flag =false;
            break;
        }else{
            if(record->nextRecord != NULL){
                record = (Record*)record->nextRecord;
            }else if(record->nextRecord == NULL){
                printf("There is no record with this name.");
                flag = false;
            }
        }
    }

}

void SearchWithSurname(HospitalList* hospitalList, char value[50]){
    int i = 0;
    bool flag = true;
    bool flag2 = true;
    while(flag) {
        Record* record = (Record*)hl[i].firstRecordPtr;

        for (i = 0; i <= 26; i++) {

            record = hl[i].firstRecordPtr;
            flag2 = true;
            while(flag2){
                if (record != NULL) {
                    if (strcmp(record->surname, value) == 0) {
                        printf("Name: %s\n", record->name);
                        printf("Surname: %s\n", record->surname);
                        printf("PersonID: %d\n", record->personId);
                        printf("Polyclinic: %s\n", record->polyclinic);
                        flag = false;
                        flag2 = false;
                        break;
                    }else if (record->nextRecord != NULL) {
                        record = record->nextRecord;
                    }
                }else{

                }
            }
            if(i==26){
                flag = false;
                printf("Cannot found this surname.");
                break;
            }
        }
    }

}

void SearchWithPolyclinic(HospitalList* hospitalList, char value[50]){
    int i = 0;
    bool flag = true;
    while(flag) {
        for (i = 0; i <= 26; i++) {
            Record* record = (Record*)hl[i].firstRecordPtr;

            if (strcmp(record->polyclinic, value) == 0) {
                printf("Name: %s\n", record->name);
                printf("Surname: %s\n", record->surname);
                printf("PersonID: %d\n", record->personId);
                printf("Polyclinic: %s\n", record->polyclinic);
                flag = false;
                break;
            } else {
                if (record->nextRecord != NULL) {
                    record = record->nextRecord;
                } else if (i == 26 && record->nextRecord == NULL) {
                    printf("There is no record with this name.");
                    flag = false;
                }
            }
        }
    }
}

void Delete(HospitalList* hospitalList){
    Record* records[50];
    Record* afterRecords[50];
    Record* recordTemp;
    Record* afterRecordTemp = NULL;
    bool flag1 = false;
    bool flag2 = true;
    char value[50];
    printf("Please enter a name, surname or polyclinic Name for delete a record: ");
    scanf(" %s", value);

    int i = 0;
    int n =0;
    for(i= 0; i <= 26; i++){
        recordTemp = hospitalList[i].firstRecordPtr;
        if(recordTemp != NULL) {
            while (flag2){
                if ((strcmp(recordTemp->name, value) == 0) || (strcmp(recordTemp->surname, value) == 0) ||
                    (strcmp(recordTemp->polyclinic, value) == 0)) {
                    records[n] = recordTemp->nextRecord;
                    afterRecords[n] = afterRecordTemp;
                    n += 1;
                    flag1 = true;
                }
                afterRecordTemp= recordTemp;
                recordTemp = recordTemp->nextRecord;
            }
        }
        afterRecordTemp = NULL;
    }

    if(!flag1){
        printf("Cannot found this value.\n");
    }else{
        int k = 0;
        while(k<n){
            PrintRecord(records[k]);
            k+=1;
        }
    }

}