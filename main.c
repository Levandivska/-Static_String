#include "my_lib.h"
#include <string.h>
#include "program2.c"

int main() {
    my_str_t my_str;
    my_str_t *source = &my_str;

    printf("\n\nTesting my_str_read, please input something: \n");
    my_str_t read_to;
    int test_cr = my_str_create(&read_to,32);
    int test_read2 = my_str_read(&read_to);
    if (test_read2 == -1)
        printf("\nWrong argument");
    else {
        printf("The string read is ");
        print_str(&read_to);
    }

    printf("\nTesting my_str_create:");
    int test_create = my_str_create(source, 32);
    if (test_create == -1)
        printf("\nBuffer NULL, failed to allocate memory in my_str_create");
    else
        printf("\nCreated an instance of type my_str_t with capacity 32");

    printf("\n\nTesting my_str_capacity:");
    size_t test_capacity = my_str_capacity(source);
    if (test_capacity != source->capacity_m)
        printf("\nWrong result in my_str_capacity");
    else
        printf("\nCapacity of our string is %zu", source->capacity_m);

    printf("\n\nTesting my_str_from_cstr:");
    int test_cstr = my_str_from_cstr(source, "women", 32);
    if (test_cstr == -1) {
        printf("\nBuffer size < cstr size");
    } else if (test_cstr == -2) {
        printf("\nBuffer NULL, failed to allocate memory in my_str_from_cstr");
    } else {
        printf("\nWrote a c-string to our string: ");
        print_str(source);
    }

    printf("\n\nTesting my_str_empty:");
    int test_empty = my_str_empty(source);
    if (test_empty == 0){
        if (source->size_m == 0) {
            printf("\nWrong result in my_str_empty");
        } else {
            printf("\nOur string is not empty");
        }
    } else if (test_empty == 1) {
        if (source->size_m != 0) {
            printf("\nWrong result in my_str_empty");
        } else {
            printf("\nOur string is empty.");
        }
    }


    printf("\n\nTesting my_str_getc:");
    int test_getc_1 = my_str_getc(source, 1);
    if (test_getc_1 != source->data[1])
        printf("\nWrong symbol in my_str_getc");
    else
        printf("\nThe symbol at index 1 is '%c'",test_getc_1);


    printf("\n\nTesting my_str_putc:");
    int test_putc1 = my_str_putc(source, 3, 'a');
    if (test_putc1 == -1)
        printf("\nIndex too big");
    else {
        printf("\nThe string after putting 'a' at index 3 is '");
        print_str(source);
        printf("'");
    }

    printf("\n\nTesting my_str_pushback:");
    int test_pushback = my_str_pushback(source, 's');
    if (test_pushback == -1)
        printf("\nInvalid arguments or buffer ended");
    else {
        printf("\nAfter pushing 's' the string is '");
        print_str(source);
        printf("'");
    }



    printf("\n\nTesting my_str_popback:");
    char last = source->data[source->size_m - 1];
    int test_popback = my_str_popback(source);
    if (test_popback == -1) {
        printf("\nBuffer ended or invalid arguments");
    } else if (last != test_popback) {
        printf("\nWrong symbol");
    } else {
        printf("\nSymbol '%c' was popped and the string now is '", test_popback);
        print_str(source);
        printf("'");
    }


    printf("\n\nTesting my_str_size:");
    size_t test_size = my_str_size(source);
    if (test_size != source->size_m)
        printf("\nWrong size in my_str_size");
    else
        printf("\nThe size of the string is %zu",test_size);


    printf("\n\nTesting my_str_copy:");
    my_str_t to_str;
    my_str_t from_str;
    my_str_create(&to_str, 32);
    my_str_create(&from_str, 32);
    my_str_from_cstr(&from_str,"miss", 5);
    int test_copy1 = my_str_copy(&from_str,&to_str,1);
    if (test_copy1 == -1)
        printf("\nSizes different");
    for (int i = 0; i < from_str.size_m; i++)
        if (from_str.data[i] != to_str.data[i])
            printf("\nWrong result");
    printf("\nCopied ");
    print_str(&from_str);
    printf(" to some string_2 - ");
    print_str(&to_str);



    printf("\n\nTesting my_str_insert_c:");
    my_str_t my_str_ins;
    my_str_create(&my_str_ins,32);
    my_str_from_cstr(&my_str_ins,"dmsel",10);
    int test_insert_c = my_str_insert_c(&my_str_ins, 'a', 1);
    printf("\n");
    print_str(&my_str_ins);
    if (test_insert_c == -1)
        printf("\nCapacity of str is too small or invalid arguments");
    else {
        printf("\nInserted 'a' into '");
        print_str(&my_str_ins);
        printf("'");
    }

    printf("\n\nTesting my_str_clear:");
    my_str_clear(&to_str);
    if ((&to_str)->size_m != 0)
        printf("\nDid not work");
    else
        printf("\nString was cleared");


    printf("\n\nTesting my_str_insert_cstr:");
    my_str_t str_ins;
    my_str_create(&str_ins,32);
    my_str_from_cstr(&str_ins,"ladybird",9);
    int test = my_str_insert_cstr(&str_ins, "miss",4);
    if (test == -1)
        printf("\nInvalid arguments or position of insertion > length of the string");
    printf("\nInserted 'miss' at index 4 into 'ladybird' : ");
    print_str(&str_ins);

    printf("\n\nTesting my_str_insert:");
    my_str_t str_in;
    my_str_t str_to;
    my_str_create(&str_to,32);
    my_str_create(&str_in,32);
    my_str_from_cstr(&str_in,"birdman",8);
    my_str_from_cstr(&str_to, "boy",4);
    int test_11 = my_str_insert(&str_in, &str_to,4);
    if (test == -1)
        printf("\nInvalid arguments or position of insertion > length of the string");
    printf("\nInserted my_str '");
    print_str(&str_to);
    printf("' at index 4 into 'birdman' : ");
    print_str(&str_in);

    printf("\n\nTesting my_str_append:");
    my_str_t to_string;
    my_str_create(&to_string, 32);
    my_str_from_cstr(&to_string, "lady", 10);
    int test_append = my_str_append(&to_string,source);
    if (test_append == -1)
        printf("\nCapacity of str is too small or invalid arguments");
    size_t len_from_str = source->size_m;
    for (int i = 0; i < len_from_str; i++)
        if (to_string.data[i+to_string.size_m - len_from_str] != source->data[i])
            printf("\nWrong result");
    printf("\nAppended 'woman' to 'lady' : ");
    print_str(&to_string);

    printf("\n\nTesting my_str_append_cstr:");
    my_str_t old_my_str;
    my_str_create(&old_my_str, 32);
    my_str_copy(source,&old_my_str,1);
    char cstr_to_append[13] = "mademoiselle";
    int test_append_cstr = my_str_append_cstr(source, cstr_to_append);
    if (test_append_cstr == -1)
        printf("\nCapacity of str is too small or invalid arguments");
    for (int i = 0; i < old_my_str.size_m; i++)
        if (source->data[i] != old_my_str.data[i])
            printf("\nWrong result of my_str_append_cstr");
    for (int i = 0; i < strlen(cstr_to_append); i++)
        if (source->data[i + old_my_str.size_m] != cstr_to_append[i])
            printf("\nWrong result of my_str_append_cstr");
    printf("\nAppended '%s' to 'woman' : ",cstr_to_append);
    print_str(source);


    printf("\n\nTesting my_str_substr");
    my_str_t str1_sub;
    my_str_t str2_sub;
    my_str_create(&str1_sub, 32);
    my_str_create(&str2_sub, 32);
    my_str_from_cstr(&str1_sub,"superman", 8);
    size_t begg = 0;
    size_t endd = 5;
    int test_subb = my_str_substr(&str1_sub, &str2_sub, begg, endd);
    if (test_subb == -1)
        printf("\nInvalid arguments");
    else {
        printf("\nThe substring of '");
        print_str(&str1_sub);
        printf("' from index 0 to 4 was written to string: ");
        print_str(&str2_sub);
    }

    printf("\n\nTesting my_str_substr_cstr:");
    my_str_t str_1_sub;
    char str_2_sub[] = "";
    my_str_create(&str_1_sub,32);
    my_str_from_cstr(&str_1_sub,"wonderwoman", 12);
    size_t beg = 3;
    size_t end = 9;
    int test_sub = my_str_substr_cstr(&str_1_sub, str_2_sub, beg, end);
    if (test_sub == -1)
        printf("\nInvalid arguments");
    else {
        printf("\nThe substring of '");
        print_str(&str_1_sub);
        printf("' from index 3 to 9 was written to string: %s", str_2_sub);
    }

    printf("\n\nTesting my_str_get_cstr");
    my_str_t my_str_;
    my_str_create(&my_str_,32);
    my_str_from_cstr(&my_str_,"girl",4);
    const char* test_getcstr = my_str_get_cstr(&my_str_);
    printf("\nReturned a c-string : %s", test_getcstr);

    printf("\n\nTesting my_str_find:(using the string: '");
    print_str(source);
    my_str_t str_to_find;
    my_str_create(&str_to_find, 32);
    my_str_from_cstr(&str_to_find,"sel",4);
    size_t test_find = my_str_find(source,&str_to_find,0);
    if (test_find == -1)
        printf("')\nSubstring not found or starting point > string size or invalid arguments");
    else if (test_find != 12)
        printf("')\nWrong index of substring");
    printf("')\nSubstring 'sel' was found starting at index %zu",test_find);

    printf("\n\nTesting my_str_find_c:");
    size_t test_find_c = my_str_find_c(source, 'w', 0);
    if (test_find_c == -1)
        printf("\nChar not found or starting point > string size or invalid arguments");
    if (test_find_c != 0)
        printf("\nWrong index of character");
    printf("\nChar 'w' was found at index %zu",test_find_c);

    printf("\n\nTesting my_str_find_if \nwith a function that looks for "
                   "a symbol in string that appears in word 'emma' :");
    size_t test_find_if = my_str_find_if(source, test_func_for_str_find_if);
    if (test_find_if == -1)
        printf("\nNo symbol in the string to return True for the given function");
    if (test_find_if != 2)
        printf("\nWrong symbol index");
    printf("\nThe first symbol in string '");
    print_str(source);
    printf("' to appear in string 'emma' is at index %zu\n",test_find_if);

    printf("\n\nTesting my_str_read_file:\n'");
    char* my_f = "../file1.txt";
    FILE* file1 = fopen(my_f, "r");
    if (file1 == NULL) {
        printf("file not found");
        return 0;
    }
    my_str_t read_file;
    int test_read_str = my_str_create(&read_file,60);
    int test_read = my_str_read_file(&read_file, file1);
    if (test_read == -1)
        printf("\nCouldn't read_file");
    print_str(&read_file);
    printf("' was read from file as a string of capacity 60.");
    fclose(file1);

    printf("\n\nTesting my_str_cmp:\n");
    char string_2[] = "mothers";
    my_str_from_cstr(source, "mother", 7);
    int test_cmp = my_str_cmp(source, string_2);
    int test_using_strcmp = strcmp(source->data, string_2);
    if (test_cmp == 1) {
        if (test_using_strcmp <= 0)
            printf("Wrong results: ");
        printf("%s > %s\n", source->data, string_2);
    } else if (test_cmp == -1) {
        if (test_using_strcmp >= 0)
            printf("\nWrong results: ");
        printf("%s < %s", source->data, string_2);
    } else if (test_cmp == 0) {
        if (test_using_strcmp != 0)
            printf("\nWrong results: ");
        printf("%s == %s", source->data, string_2);
    }

    printf("\n\nTesting my_str_free");
    my_str_free(source);
    printf("\nString freed");

    printf("\nTesting program2");
    char* prog_f1 = "../my_str_f.txt";
    FILE* f1 = fopen(prog_f1, "r");
    char* prog_f2 = "../new_str.txt";
    FILE* f2 = fopen(prog_f2, "w");
    change_file(f1, f2);
    printf("\nString from file %s was written to file %s without punctuation marks and extra spaces", prog_f1, prog_f2);
}