/*

controlBase.c
Реализация работы с базой данных

*/

#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#define MAX_FILENAME 255
#define MAX_FILEMODE 10
#define MAX_LINE_SIZE 500

#define CORRECT_RETURN 0
#define FAILURE_RETURN 1

#define UNDEFINED_STRING "!UNDF\0"

struct DataBase
{
    char _fName [MAX_FILENAME];
    char _fMode [MAX_FILEMODE];
    FILE *_ptrFile;
    char _isDef;
};

void closedb(struct DataBase * db);

void initDefault(struct DataBase * db)
{
    db->_ptrFile      = NULL;
    db->_isDef        = 0;
    strcpy(db->_fName, UNDEFINED_STRING);
    strcpy(db->_fMode, UNDEFINED_STRING);
}

void initDbWithFile(struct DataBase * db, const char * fileName, 
                    char mode [])
{
    if (db->_isDef) fclose(db->_ptrFile);
    strcpy(db->_fName, fileName);
    strcpy(db->_fMode, mode);
    db->_isDef = 1;
}

void changeFMode(struct DataBase * db, char mode [])
{
    if (db->_isDef) fclose(db->_ptrFile);
    else return;
    strcpy(db->_fMode, mode);
}

void changeFName(struct DataBase * db, char name [])
{
    if (db->_isDef) fclose(db->_ptrFile);
    else return;
    strcpy(db->_fName, name);
}


void dbcpy(struct DataBase * dbt, struct DataBase * dbf)
{
    dbt->_ptrFile = fopen(dbf->_fName, dbf->_fMode);
    strcpy(dbt->_fMode, dbf->_fMode);
    strcpy(dbt->_fName, dbf->_fName);
    dbt->_isDef = dbf->_isDef;
}

void dbconnect(struct DataBase * db)
{
    db->_ptrFile = fopen(db->_fName, db->_fMode);
}

void _nextLine(struct DataBase * db)
{
    fputc('\n', db->_ptrFile);
}

void writeLine(struct DataBase * db, char * data)
{
    fputs(data, db->_ptrFile);
    fputc('\n', db->_ptrFile);
}

char * getLine(struct DataBase * db)
{
    static char line [MAX_LINE_SIZE];
    if (fgets(line, MAX_LINE_SIZE, db->_ptrFile)) return line;
    return NULL;
}

void resetPtr(struct DataBase * db)
{
    fseek(db->_ptrFile, 0, SEEK_SET);
}

void closedb(struct DataBase * db)
{
    resetPtr(db);
    fclose(db->_ptrFile);
}
// DATABASE



#define MAX_SIZE_GNAME 255
#define MAX_BASEPOOL 10
#define FILE_LINE_SEPORATOR_S ";"

#define MAX_CHANGES 100
char createdFiles [MAX_CHANGES][MAX_FILENAME];
char *lastcratedFile = *createdFiles;
int amfiles = 0;

typedef struct DataBase DataBase;

struct DataBase curr_base; 
struct DataBase temp_base; 

struct Record 
{
    int number;

    struct GameStat
    {
        char name [MAX_SIZE_GNAME];
        int memoryD;
        int ageR;
        int graphic;
        int plrL;
        int arate;

    } gmst;

} recordToFile, recordFromFile; 

struct Call 
{
    enum nameCoincedence {ABSOLUTE, INTER};
    int nc;
    char name[MAX_SIZE_GNAME];
    
    enum borders {MORE, LESS};
    int bmem;
    int mem;

    int ageR;
    int graphic;
    int plrL;

    int barate;
    int arate;
};

char isFileExistInCDir(char * f)
{
    if (fopen(f, "r") == NULL) return 0;
    return 1;
}

void appendFileName(char * fn)
{
    for (int i = 0; i < amfiles; ++i)
        if (strcmp(createdFiles[i], fn) == 0) return;
    
    lastcratedFile = createdFiles[amfiles++];
    strcpy(lastcratedFile, fn);
}

void openReadonlyConnect(struct DataBase * base)
{
    appendFileName(base->_fName);
    initDbWithFile(base, base->_fName, "r");
    dbconnect(base);
}

void openOutputAndReadConnect(struct DataBase * base)
{
    appendFileName(base->_fName);
    initDbWithFile(base, base->_fName, "a+");
    dbconnect(base);
}

void openWriteConnect(struct DataBase * base)
{
    appendFileName(base->_fName);
    initDbWithFile(base, base->_fName, "w");
    dbconnect(base);
}

void closeConnect(struct DataBase * b)
{
    closedb(b);
}

void pushRecord(struct DataBase * b)
{
    char line [MAX_LINE_SIZE] = {0};
    char strNumber [30]; // макс. число разрядов

    snprintf(strNumber, 30, "%d", recordToFile.number);
    strcat(line, strNumber);
    strcat(line, FILE_LINE_SEPORATOR_S);
    
    strcat(line, recordToFile.gmst.name);
    strcat(line, FILE_LINE_SEPORATOR_S);

    snprintf(strNumber, 30, "%d", recordToFile.gmst.memoryD);
    strcat(line, strNumber);
    strcat(line, FILE_LINE_SEPORATOR_S);
    
    snprintf(strNumber, 30, "%d", recordToFile.gmst.ageR);
    strcat(line, strNumber);
    strcat(line, FILE_LINE_SEPORATOR_S);

    snprintf(strNumber, 30, "%d", recordToFile.gmst.graphic);
    strcat(line, strNumber);
    strcat(line, FILE_LINE_SEPORATOR_S);
    
    snprintf(strNumber, 30, "%d", recordToFile.gmst.plrL);
    strcat(line, strNumber);
    strcat(line, FILE_LINE_SEPORATOR_S);
    
    snprintf(strNumber, 30, "%d", recordToFile.gmst.arate);
    strcat(line, strNumber);
    strcat(line, FILE_LINE_SEPORATOR_S);

    writeLine(b, line);

}

int nextRecord(struct DataBase * b)
{
    char * line = getLine(b);
    if (line == NULL) return NULL;

    recordFromFile.number = atoi(strtok(line, FILE_LINE_SEPORATOR_S));
    strcpy(recordFromFile.gmst.name, strtok(NULL, FILE_LINE_SEPORATOR_S));
    recordFromFile.gmst.memoryD = atoi(strtok(NULL, FILE_LINE_SEPORATOR_S));
    recordFromFile.gmst.ageR    = atoi(strtok(NULL, FILE_LINE_SEPORATOR_S));
    recordFromFile.gmst.graphic = atoi(strtok(NULL, FILE_LINE_SEPORATOR_S));
    recordFromFile.gmst.plrL    = atoi(strtok(NULL, FILE_LINE_SEPORATOR_S));
    recordFromFile.gmst.arate   = atoi(strtok(NULL, FILE_LINE_SEPORATOR_S));

    return 1;
}

void outRecord(const struct Record *rec)
{
    printf(" %10d ", rec->number);
    printf(" \t%20.10s ", rec->gmst.name);
    printf(" %10d ", rec->gmst.memoryD);
    printf(" %10d+ ", rec->gmst.ageR);
    printf(" \t%10d ", rec->gmst.graphic);
    printf(" \t%10d ", rec->gmst.plrL);
    printf(" \t%10d ", rec->gmst.arate);

}

void openBufferDb(char * name)
{
    strcpy(temp_base._fName, name);
    openOutputAndReadConnect(&temp_base);
}

void openBufferDbW(char * name)
{
    strcpy(temp_base._fName, name);
    openWriteConnect(&temp_base);
}

void closeBufferDb()
{
    closeConnect(&temp_base);
}

void deleteRecordByNumber(int nn)
{
    static char nameFile[MAX_FILENAME];
    
    sprintf(nameFile, "after_remove_%d", nn);
    if (isFileExistInCDir(nameFile)) strcat(nameFile, "_");

    openBufferDb(nameFile);

    while (nextRecord(&curr_base)) {
        if (recordFromFile.number != nn) {
            recordToFile = recordFromFile; 
            pushRecord(&temp_base);
        }
    }
    
    closeConnect(&curr_base);
    dbcpy(&curr_base, &temp_base);
    closeBufferDb();
    resetPtr(&curr_base);
}

struct Record * findRecordByNumber (int nn)
{
    static struct Record foundRecord;

    while (nextRecord(&curr_base))
    {
        if (recordFromFile.number == nn) {
            foundRecord = recordFromFile;
            resetPtr(&curr_base); 
            return &foundRecord;
        }
    }
    resetPtr(&curr_base);
    return NULL;
}

