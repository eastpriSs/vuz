
size_t _strlen(const char * s)
// Длина строки
{
    size_t i = 0, len = 0;
    while (s[i++] != '\0')
    {
        ++len;
    }
    return len;
}

void _strcpy( char * copyin, const char * copyfrom )
// Копирование символов одной строки в другую
{
    size_t i = 0;
    while ((copyin[i] = copyfrom[i]) != '\0')
    {
        ++i;
    }
}

char toLower(char ch)
// Перевод заглавных букв в строковые
{
    if ( ch <= 'Z' && ch >= 'A') return ch + 32;
    return ch;
}

int _stricmp( const char * l, const char * r )
// Сравнивание строк вне зависимости от регистра отдельного символа
{
    size_t i = 0;
    char chl = l[i];
    char chr = r[i];
    while ( chl != '\0' && chr != '\0'){
        chl = toLower(l[i]);
        chr = toLower(r[i]);
        if (chl > chr) return 1;
        else if (chl < chr) return -1;
        ++i;
    }
    return 0;
}

// STRTOK
char * splex = NULL; // начало лексемы
char * psep = NULL; // указатель на разделитель
char old_sep = '\0'; // разделитель, который стоял раньше
char * _strtok(char * s, char * sep)
// Разбивание строки на токены
{
    if (splex == NULL && psep == NULL)
    { // Первый запуск
        splex = s + _strspn(s, sep);
        psep = _strpbrk(splex, sep);
    }
    // Если кончились разделители
    else if (psep == NULL) {
        splex = NULL;
        return NULL;
    }
    // Запрос лексемы из той же строки
    else if (s == NULL) 
    {
        splex = psep + 1;
        splex += _strspn(splex, sep);
        *psep = old_sep;
        psep = _strpbrk(splex, sep);
    }

    if (psep != NULL)
    {
        old_sep = *psep;
        *psep = '\0';
    }

    if ( *splex != '\0' ) return splex;
    return (splex = NULL);
}


void _gets(char * buffer)
// Ввод строки
{
    char ich = '\0';
    size_t i = 0;
    while(ich != '\n'){
        scanf("%c", &ich);
        buffer[i++] = ich;
    }
    buffer[i - 1] = '\0';
}

void _prints(char * buffer)
// Вывод строки
{
    while(*buffer != '\0')
        printf("%c", *buffer++);  
}

char * _strpbrk(char * str1, char * str2)
// Первое вхождение символов строки str2 в строку str1
{  
    for (size_t i = 0; str1[i] != '\0'; ++i)
    {
        for (size_t j = 0; str2[j] != '\0'; ++j)
        {
            if (str1[i] == str2[j]) return str1 + i;
        }
    }
    return NULL;
}

int _strspn(char * str1, char * sep)
// расстояние до символа строки str1, который не относится к строке sep
{
    char isSep;
    size_t i;
    for (i = 0; str1[i] != '\0'; ++i )
    {
        isSep = 0;
        for (size_t j = 0; sep[j] != '\0'; ++j )
        {
            if (str1[i] == sep[j]) isSep = 1;
        }
        if (!isSep) return i;
    }
    return i;
}