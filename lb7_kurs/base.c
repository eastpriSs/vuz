/*

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
{ // инвариант
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
