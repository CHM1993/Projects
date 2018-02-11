#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

char *file_get_contents(char *filename, char *fmode) {
    FILE *f = fopen(filename, fmode);
    fseek(f, 0L, SEEK_END);
    long fsize = ftell(f);
    rewind(f);
    char *file_contents = malloc(fsize+1);
    fread(file_contents, fsize, 1, f);
    fclose(f);
    file_contents[fsize] = 0;
    return file_contents;
}


char *str_copy(char *string, int start, int length) {
    char *s = malloc(length);
    strncpy(s, string+start, length);
    s[length+1] = '\0';    
    return s;
}

void count_factors(int *array, int number) {
    int i;
    for (i=2; i<number; i++)
        if (number % i == 0)
            array[i]++;
}

int main() {
    clock_t start, end;
    double cpu_time_used;
    start = clock();
    char *file_contents = file_get_contents("cipher.txt", "rt");
    char *test_string, *compare_string, match, is_in_array;
    unsigned seq_min = 3, seq_max = 4;
    unsigned long i, j, k, f, number, str_index = 0; 
    unsigned long iterations = 0;
    unsigned *factors_index = {0};
    unsigned text_length = strlen(file_contents);
    unsigned long *factors_value = calloc(text_length, sizeof(unsigned long));
    unsigned arr_str_count = text_length+1, arr_str_length = seq_max+1;
    char strings[arr_str_count][arr_str_length];
    unsigned count_strings = 1;

    test_string = str_copy(file_contents, 0, seq_min);
    strcpy(strings[0], test_string);
    free(test_string);

    for (i=seq_min; i<=seq_max; i++) {
        count_strings = 1;
        for (j=0; j<text_length-i*2;) {
            match = 0;
            is_in_array = 0;
            test_string = str_copy(file_contents, j, i);

            for (f=0; f<arr_str_count; f++) {
                if(strcmp(strings[i], test_string) == 0) {
                    is_in_array = 1;
                    iterations++;
                    break;
                }
            }
            //skipping couple hundreds of iterations in case we already processed current N-gram
            if (!is_in_array) {
                strcpy(strings[count_strings], test_string);
                count_strings++;
                str_index = j;
                for (k=j+i; k<text_length-i-1;) {
                    compare_string = str_copy(file_contents, k, i);
                    if (strcmp(test_string, compare_string) == 0) {
                        number = (k-str_index); //distance between current and old N-gram
                        for (f=2; f<number; f++)
                            if (number % f == 0) {
                                factors_value[f]++;
                                iterations++;
                            }
                        str_index = k;
                        match = 1;
                        k += i;
                    } else {
                        k++;
                    }
                    free(compare_string);
                    iterations++;
                }
            }
            match == 1 ? j+=i : j++;
            free(test_string);
        }

    }

    for (i=0; i<100; i++) {
        if (factors_value[i] > 1)
            printf("%: %d \n", i, factors_value[i]);
    }

    printf("%llu iterations\n", iterations);

    free(file_contents);
    free(factors_value);

    end = clock();
    cpu_time_used = ((double) (end-start)) / CLOCKS_PER_SEC;
    printf("Process finished: %4.3f secs.\n", cpu_time_used);
    getch();
    return 0;
}