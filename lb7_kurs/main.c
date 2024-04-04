/*
    main.c
    Основной модуль, драйвер

*/

#include <stdio.h>
#include <conio.h>
#include <locale.h>
#include "controlBase.c"
#include "inputFuncs.c"


#define DEFAULT_INIT_STRING "__DFINIT\0"
#define DEFAULT_INIT_INT -1

#define RESET   "\033[0m"
#define RED     "\033[1;31m"
#define YELLOW  "\033[1;33m"

int globalNumberOfRecord = 0;

#ifdef _WIN32
void clearConsole()
{ system("cls"); }
#endif
#ifdef linux
void clearConsole()
{ system("clear") }
#endif

// FILE BAR INTERFACE
int focusfile = DEFAULT_INIT_INT;
void outFileBar()
{
    int ptrid = 0;
    char *begin = createdFiles[ptrid];
    char *end   = lastcratedFile;
    while (begin != end)
        if (focusfile != ptrid)
            printf("%s %c ", (begin = createdFiles[ptrid++]) , 29 );
        else 
            printf("%s%s%s %c ", YELLOW, (begin = createdFiles[ptrid++]), RESET, 29 );

    if (focusfile == DEFAULT_INIT_INT)
        printf("%spress 8 and 9 for move between files%s", YELLOW, RESET);
    else
        printf("press 8 and 9 for move between files");
    
    printf("\n\nActive file now =  %s ", curr_base._fName);

}
///


// zone ADD REMOVE
void event_add()
{
    openOutputAndReadConnect(&curr_base);
    printf("\n\nAdd record.\n");
    recordToFile.number = globalNumberOfRecord++;
    fillRecord(&recordToFile);
    pushRecord(&curr_base);
    closeConnect(&curr_base);
}

void event_remove()
{
    
    openReadonlyConnect(&curr_base);
    int num;
    
    // файл пуст
    if (nextRecord(&curr_base) == NULL)
    {
        printf("\nHmm.. file is empty.\n");
        closeConnect(&curr_base);
        return;
    }
    resetPtr(&curr_base);
    
    printf("\nEnter the number of record > ");
    waitInt(&num);
    if (findRecordByNumber(num) == NULL)
    {
        printf("Oops.. record with this number do not exist.");
        waitButtom();
        return;
    }

    printf("\nAre you sure? Enter 'y' for accept..\n");
    if (getchar() == 'y') 
        deleteRecordByNumber(num);
    closeConnect(&curr_base);
}
///

void event_outTable()
{
    openReadonlyConnect(&curr_base);
    printf("\n  Number\t\t Name(0) \t Memory(1) \t Age(2) \t Graphic(3) \t Players(4) \t Rating(5)\n");
    printf("___________________________________________________________________________________________________________________\n\n");
    while (nextRecord(&curr_base))
    {
        outRecord(&recordFromFile);
        putchar('\n');
    }
    closeConnect(&curr_base);
}

void event_addRemove()
{
    int inputcmd;
    
    do
    {
        clearConsole();
        event_outTable();

        printf("\n\n1) Add / 2) Remove / 3) Exit > ");

        waitInt(&inputcmd);

        if (inputcmd == 1) event_add();
        if (inputcmd == 2) event_remove();
        if (inputcmd == 3) return;

        printf("\n\nYou can press ESC, for exit the block.");
    } while (_getch() != 27);
    
}
//

void event_edit()
{
    struct Record *save_rec;
    int num;
    int field;
    
    
    openOutputAndReadConnect(&curr_base);
    if (nextRecord(&curr_base) == NULL) {
        printf("\nHmm.. file is empty.\n");
        closeConnect(&curr_base);
        waitButtom();
        return;
    }

    do
    {
        clearConsole();
        event_outTable();
        openOutputAndReadConnect(&curr_base);

        printf("\n\nEnter the number of record or \"-1\" for exit: ");
        waitInt(&num);
        if (num == -1) return;

        printf("\n\nEnter ID of field: ");
        waitInt(&field);
        
        // Подготавливаем новую запись на основе старой
        save_rec = findRecordByNumber(num);
        if (save_rec == NULL) {
            printf("Oops.. record with this number do not exist.");
            waitButtom();
            return;
        }
        fillField(save_rec, field);
        
        printf("\nAfter the changes, you will get this record:\n\n");
        outRecord(save_rec);
        
        printf("\n\nEnter '1' for accept, '0' for decline\n> ");
        if (getchar() == '1')
            deleteRecordByNumber(num);
        else { closeConnect(&curr_base); continue; }

        recordToFile = *save_rec;
        pushRecord(&curr_base);
        closeConnect(&curr_base);

    } while ((printf("\n\nYou can press ESC, for exit the block.")), _getch() != 27);
}


void inputFieldsForCall(struct Call *cl)
{
    char fields[8];

    printf("\n\nCall block.\n\n- For exit enter 'exit' or '-1'. \n");
    printf("\nintrested field> ");
    gets_s(fields, 7);

    if (stricmp("exit", fields) == 0 || stricmp("-1", fields) == 0) return;
    
    int inputField = 0; 
    for (int i = 0; fields[i] != '\0'; ++i)
    {
        inputField = fields[i] - '0';
        if (inputField <= 5 && inputField >= 0) printf("\n\033[0;36mEntering data for the call. Field < %d >%s\n", inputField, RESET);
        switch (inputField)
        {
        case NAME: inputNameForCall(cl);
            break;
        case MEM: inputMemForCall(cl);
            break;
        case AGER: inputAgerateForCall(cl);
            break;
        case GRAPHIC: inputGraphic(&cl->graphic);
            break;
        case PLAYERS: inputPlayerAm(&cl->plrL);
            break;
        case AVERATE: inputAverForCall(cl);
            break;
        default: printf("\n\nWarning. %sIncorrect%s input was ignored : %s%c%s\n", RED, RESET, RED, fields[i], RESET);
        }
    }
}

void call_init_default(struct Call *cl)
{
    strcpy(cl->name, DEFAULT_INIT_STRING);
    cl->mem     = DEFAULT_INIT_INT;
    cl->ageR    = DEFAULT_INIT_INT;
    cl->graphic = DEFAULT_INIT_INT;
    cl->plrL    = DEFAULT_INIT_INT;
    cl->arate   = DEFAULT_INIT_INT;
}

void event_call()
{
    struct Call cl; 
    call_init_default(&cl);
    clearStdin();
    inputFieldsForCall(&cl);

    const struct Record *rec;
    char isNeedRec;

    openReadonlyConnect(&curr_base);

    printf("\n \033[44;1m -*- Games for you:%s\n", RESET);
    while (nextRecord(&curr_base))
    {
        isNeedRec = 1;
        rec = &recordFromFile;

        if (strcmp(cl.name, DEFAULT_INIT_STRING) != 0)
            if (cl.nc == cl.ABSOLUTE)
                isNeedRec = (stricmp(cl.name, rec->gmst.name) == 0);
            else 
                isNeedRec = (strstr(rec->gmst.name, cl.name) != NULL);

        if (cl.mem != DEFAULT_INIT_INT && isNeedRec) 
            if (cl.bmem == cl.LESS) isNeedRec = (rec->gmst.memoryD < cl.mem);
            else isNeedRec = (rec->gmst.memoryD > cl.mem);

        if (cl.ageR != DEFAULT_INIT_INT && isNeedRec)
            isNeedRec = (cl.ageR >= rec->gmst.ageR);
        
        if (cl.graphic != DEFAULT_INIT_INT && isNeedRec)
            isNeedRec = (cl.graphic == rec->gmst.graphic);

        if (cl.plrL != DEFAULT_INIT_INT && isNeedRec)
            isNeedRec = (cl.plrL == rec->gmst.plrL);

        if (cl.arate != DEFAULT_INIT_INT && isNeedRec)
            if (cl.barate == cl.MORE) isNeedRec = (cl.arate < rec->gmst.arate);
            else isNeedRec = (cl.arate >= rec->gmst.arate);
    
        if (isNeedRec){
            outRecord(rec);
            printf("\n");

        }

    }
    waitButtom();
    closeConnect(&curr_base);
    
}

void event_exit()
{
    exit(EXIT_SUCCESS);
}

void event_invalidcmd(){}

int init_focusfile(int val)
{
    static int init = (focusfile = val);
    return 0;
}

void event_swapfile_left()
{
    static int init = init_focusfile(amfiles);
    if (focusfile != 0) focusfile -= 1;
}

void event_swapfile_right()
{
    static int init = init_focusfile(0);
    if (focusfile < amfiles - 1) focusfile += 1;
}

void event_run_focus_file()
{
    if (amfiles > 0 && focusfile != -1)
        strcpy(curr_base._fName, createdFiles[focusfile]);
}


void event_save()
{
    if (stricmp(createdFiles[0], curr_base._fName) == 0) return;

    openReadonlyConnect(&curr_base);
    openBufferDbW(createdFiles[0]); 
    
    while (nextRecord(&curr_base)) 
    {
        recordToFile = recordFromFile;
        pushRecord(&temp_base);
    }
    closeBufferDb();
    closeConnect(&curr_base);
}

void mainLoop()
{
    
    clearConsole();
    printf("\n");
    outFileBar();
    printf("\n\n");
    event_outTable();

    printf("\nSelect the block you need.");
    printf("\n1) Add / Remove");
    printf("\n2) Edit");
    printf("\n3) Call");
    printf("\n4) Exit");
    printf("\nR) Run focused file");
    printf("\nS) Save changes");
    printf("\nThe button is expected to be pressed to go to the block...");
    
    
    switch (_getch())
    {
    case 49: event_addRemove(); // '1'
        break;
    case 50: event_edit();
        break;
    case 51: event_call();
        break;
    case 52: event_exit();
        break;
    case 56: event_swapfile_left(); // '8'
        break;
    case 57: event_swapfile_right(); // '9'
        break;
    case 114: event_run_focus_file(); // 'R'
        break;
    case 115: event_save(); // 'S'
        break;
    default:
        event_invalidcmd();
        break;
    }
    
}


void intro()
{
    printf("\n\n\t\t\tWelcome!");
    printf("\n\t\t\tDeveloper -> https://github.com/eastpriSs");
    _getch();
}


void setGlobalNumberByFile()
{
    openReadonlyConnect(&curr_base);
    while (nextRecord(&curr_base))
    {
        if (globalNumberOfRecord < recordFromFile.number)
            globalNumberOfRecord = recordFromFile.number;
    }
    ++globalNumberOfRecord;
    closeConnect(&curr_base);
}

int main(){
    setlocale(LC_ALL, "rus");
    intro();
    clearConsole();
    enterFileName(curr_base._fName); // ???
    clearStdin();
    setGlobalNumberByFile();
    
    while (1) mainLoop();
}
