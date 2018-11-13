//
// Created by оля on 30.10.18.
//

#include <ctype.h>

size_t take_out_symbol_and_tolower(my_str_t* str){
    int num_symbol = 0;
    int last_alpha = 0;
    for(int i = 0; i < str->size_m;  i++){
        if(!isalpha(*(str->data+i))){
            num_symbol += 1;
        }
        else{
            *(str->data + last_alpha) = (char) tolower(*(str->data + last_alpha+ num_symbol));
            last_alpha += 1;
        }
    }
    str->size_m -= num_symbol;
    return 0;
}

int my_str_write_file(my_str_t* str, FILE* file){
    *(str->data + str->size_m) = '\0';
    fputs(str->data, file);
    return 0;
}

int change_file(FILE* from, FILE*to) {
    my_str_t str;
    my_str_create(&str, 32);
    while(!my_str_read_file_until_blankspace(&str, from)){
        take_out_symbol_and_tolower(&str);
        str_add(&str, ' ');
        my_str_write_file(&str, to);
    }
    fclose(from);
    fclose(to);
    return 0;
}