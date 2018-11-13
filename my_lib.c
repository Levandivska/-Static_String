#include "my_lib.h"
#include <stdlib.h>
#include "ctype.h"

int str_add(my_str_t* str, char c){
    if (str->size_m < str->capacity_m){
        *(str->data+str->size_m) = c;
        str->size_m += 1;
    }
    return 0;
}

size_t clenght(const char* c_str){
    const char* adress = c_str;
    char c = *c_str;
    size_t lenght = 1;
    while (c != '\0'){
        lenght++;
        adress++;
        c = *(adress);
    }
    return lenght-1;
}

void print_str(my_str_t* str){
    for(size_t i = 0; i < str->size_m; i++){
        printf("%c", *(str->data+i));
    }
}

int my_str_cmp(my_str_t* str, const char* from) {
    if (!str || !str->data)
        return -1;
    size_t size_1 = str->size_m;
    size_t size_2 = clenght(from);
    if (size_1 > size_2)
        return 1;
    if (size_2 > size_1)
        return -1;
    for (int i = 0; i < clenght(from); i++)
        if (str->data[i] > from[i])
            return 1;
        else if (str->data[i] < from[i])
            return -1;
    return 0;
}

int my_str_create(my_str_t* str, size_t buf_size){
    if(!str)
        return -1;
    char* buffer = malloc(buf_size+1);
    if (buffer==NULL)
        return -1;
    str->size_m = 0;
    str->capacity_m = buf_size;
    str->data = buffer;
    return 0;
}


//! Створити стрічку із буфером вказаного розміру із переданої С-стрічки.
//! Якщо розмір -- 0, виділяє блок, рівний розміру С-стрічки, якщо
//! менший за її розмір -- вважати помилкою.
//! Пам'ять виділяється динамічно.
//! 0 -- якщо все ОК, -1 -- недостатній розмір буфера, -2 -- не вдалося виділити пам'ять
int my_str_from_cstr(my_str_t* str, const char* cstr, size_t buf_size){
    size_t cstr_size = clenght(cstr);
    if (buf_size < cstr_size){
        return -1;
    }
    str->data = malloc(buf_size+1);
    if (!str->data){
        return -2;
    }

    str->capacity_m = buf_size+1;
    str->size_m = cstr_size;

    for(size_t i = 0; i < cstr_size; i++)
        *(str->data + i) = *(cstr + i);

    return 0;
}

void my_str_free(my_str_t* str){
    free(str->data);
}

size_t my_str_size(const my_str_t* str){
    if(!str || !str->data)
        return (size_t)-1u;
    return str->size_m;
}

size_t my_str_capacity(const my_str_t* str){
    if(!str || !str->data)
        return  (size_t)-1u;
    return str->capacity_m;
}

int my_str_empty(const my_str_t* str){
    if(!str || !str->data)
        return  -1;
    return str->size_m == 0;
}

int my_str_getc(const my_str_t* str, size_t index){
    if(!str || !str->data)
        return  -1;
    if (str->size_m <= index)
        return -1;
    return *(str->data+index);
}

int my_str_putc(my_str_t* str, size_t index, char c){
    if(!str || !str->data)
        return  -1;
    if (str->size_m <= index)
        return -1;
    *(str -> data+index) = c;
    return 0;
}

int my_str_pushback(my_str_t* str, char c){
    if(!str || !str->data)
        return  -1;
    *(str->data + str->size_m) = c;
    str->size_m++;
    return 0;
}

int my_str_popback(my_str_t* str){
    if(!str || !str->data)
        return  -1;
    if (str->size_m == 0)
        return -1;
    char symbol = *(str->data + str->size_m-1);
    str->size_m--;
    return symbol;
}

//! Копіює стрічку. Якщо reserve == true,
//! то із тим же розміром буферу, що й вихідна,
//! інакше -- із буфером мінімального достатнього розміру.
//! Старий вміст стрічки перед тим звільняє, за потреби.
int my_str_copy(const my_str_t* from,  my_str_t* to, int reserve) {
    if (from->size_m > to->capacity_m)
        return -1;
    if (!reserve)
        to->capacity_m = from->size_m;
    for (int i = 0; i < from->size_m; i++)
        to->data[i] = from->data[i];
    to->size_m = from->size_m;
    return 0;
}

void my_str_clear(my_str_t* str){
    str->size_m = 0;
}

int my_str_insert_c(my_str_t* str, char c, size_t pos){
    if(!str || !str->data)
        return  -1;
    if (pos >= str->size_m)
        return -1;
    char take_out = NULL;
    char take_in = *(str->data+pos);
    for (size_t i = pos + 1; i <= str->size_m; i++){
        take_out = *(str->data+i);
        *(str->data+i) = take_in;
        take_in = take_out;
    }
    *(str->data+pos) = c;
    if (take_out)
        *(str->data+str->size_m+1) = take_out;
    str->size_m++;
    return 0;
}

int my_str_insert(my_str_t* str, const my_str_t* from, size_t pos){
    if(!str || !str->data)
        return  -1;
    if(!from|| !from->data)
        return  -1;
    if (pos >= str->size_m)
        return -1;
    my_str_t copy_str;
    my_str_create(&copy_str, str->size_m - pos + 1);
    my_str_substr(str, &copy_str, pos, str->size_m);
    str->size_m = pos;
    my_str_append(str, from);
    my_str_append(str, &copy_str);
    return 0;
}

int my_str_insert_cstr(my_str_t* str, const char* from, size_t pos){
    if(!str || !str->data)
        return  -1;
    if(!from)
        return  -1;
    if (pos >= str->size_m)
        return -1;
    my_str_t copy_str;
    my_str_create(&copy_str, str->size_m - pos + 1);
    my_str_substr(str, &copy_str, pos, str->size_m);
    str->size_m = pos;
    my_str_append_cstr(str, from);
    my_str_append(str, &copy_str);
    return 0;
}

int my_str_append(my_str_t* str, const my_str_t* from){
    if(!str || !str->data)
        return  -1;
    if(!from || !from->data)
        return  -1;
    for (size_t i = 0; i < from->size_m; i++)
        *(str->data + str->size_m + i) = *(from->data+i);
    str->size_m += from->size_m;
    return 0;
}

int my_str_substr(const my_str_t* str, my_str_t* to, size_t beg, size_t end){
    if(!str || !str->data)
        return  -1;
    if(!to || !to->data)
        return  -1;
    if (beg > end)
        return -1;
    if (beg >= str->size_m)
        return -1;
    for (size_t i = beg; i < end; i++){
        if (i > str->size_m - 1){
            end = i;
            break;
        }
        *(to->data + i - beg) = *(str -> data+ i);
    }
    to->size_m = end - beg;
    return 0;
}

int my_str_append_cstr(my_str_t* str, const char* from){
    if(!str || !str->data)
        return  -1;
    if (!from)
        return -1;
    size_t c_size_m = clenght(from);
    const char* adress = from;
    char c = *from;
    size_t i = 0;
    while (c != '\0'){
        *(str->data+str->size_m+i) = c;
        adress++;
        i++;
        c = *(adress);
    }
    str->size_m += c_size_m;
    return 0;
}

int my_str_substr_cstr(const my_str_t* str, char* to, size_t beg, size_t end){
    if (beg > end)
        return -1;
    if(!str || !str->data)
        return  -1;
    if (!to)
        return -1;
    if (beg >= str->size_m)
        return -1;
    for (size_t i = beg; i < end; i++){
        if (i >= str->size_m){
            end = i;
            break;
        }
        *(to + i - beg) = *(str->data+ i);
    }
    *(to + end - beg) = '\0';
    return 0;
}

const char* my_str_get_cstr(my_str_t* str){
    *(str->data + str->size_m) = '\0';
    return str->data;
}

size_t my_str_find(const my_str_t* str, const my_str_t* tofind, size_t from){
    if(!str || !str->data)
        return (size_t)-1u;
    if(!tofind || !tofind->data)
        return (size_t)-1u;
    if (from >= str->size_m)
        return (size_t)-1u;
    for(size_t i = from; i < str->size_m; ++i){
        if(str->data[i] != tofind->data[0])
            continue;
        size_t l = i, r = 0;
        while(l < str->size_m && r < tofind->size_m && str->data[l] == tofind->data[r]){
            ++l;
            ++r;
        }
        if(r == tofind->size_m)
            return i;
    }
    return (size_t)-1u;
}

size_t my_str_find_c(const my_str_t* str, char tofind, size_t from){
    if(!str || !str->data)
        return (size_t)-1u;
    if (!tofind)
        return (size_t)-1u;
    if (from >= str->size_m)
        return (size_t)-1u;
    for( size_t i = from; i < str->size_m; i++){
        if ( *(str->data + i) == tofind)
            return i;
    }
    return (size_t)-1u;
}

size_t my_str_find_if(const my_str_t* str, int (*predicat)(char)){
    if(!str || !str->data)
        return (size_t)-1u;
    for (size_t i = 0; i < str->size_m; i++){
        if ((*predicat)(*(str->data+i)))
            return i;
    }
    return (size_t)-1u;
}

int my_str_read_file(my_str_t* str, FILE* file){
    if(!str || !str->data)
        return -1;
    fgets(str->data, (int) str->capacity_m, file);
    if (str->data == NULL){
        return -1;
    }
    str->size_m = clenght(str->data);
    return 0;
}

int my_str_read_file_until_blankspace(my_str_t* str, FILE* file){
    if(!str || !str->data)
        return -1;
    char format[32];
    snprintf(format, sizeof(format), "%%%ds", str->capacity_m);
    int res = fscanf(file, format, str->data);
    if (res == -1)
        return -1;
    str->size_m = clenght(str->data);
    return 0;
}

int my_str_read(my_str_t* str) {
    if (!str || !str->data)
        return -1;
    fgets(str->data, (int) str->capacity_m + 1, stdin);
    str->size_m = clenght(str->data);
    return 0;
}

int test_func_for_str_find_if(char tofind) {
    my_str_t to_string;
    int cr = my_str_create(&to_string,32);
    int add = my_str_from_cstr(&to_string,"emma", 4);
    for (int s = 0; s < to_string.size_m; s++) {
        if (*(to_string.data + s) == tofind)
            return 1;
    }
    return 0;
}

