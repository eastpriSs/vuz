#include "base.c"

#define MAX_BASEPOOL 10

struct DataBase curr_base; 

void openOutputConnect(char * name)
{
    initDefault(&curr_base);
    initDbWithFile(&curr_base, name, "w");
    dbconnect(&curr_base);
}

void makeRecord()
{
    writeLine(&curr_base, "$$$");
}

void writeToRecord()
{

}

int main()
{
}