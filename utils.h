#ifndef GEB_UTILS
#define GEB_UTILS

void exit_with_msg(int exit_code, const char* msg) {
    perror(msg);
    exit(exit_code);
}

// 0 false, 1 true -> true removes the character
void filter(char* str_out, int (*compare_function)(int)) {
    char* str_in = str_out;
    while (*str_in != '\0') {
        while (compare_function(*str_in) && *str_in != '\0')
            str_in += 1;

        *str_out = *str_in;
        str_out += 1;
        str_in += 1;
    }
    // assign new null terminator
    *str_out = *str_in;
}

FILE* fopen_expect(const char* filename, const char* mode) {
    FILE* fp = fopen(filename, mode);
    if (fp == NULL) {
        char buff[512];
        sprintf(buff, "could not find './%s' file", filename);
        exit_with_msg(1, buff);
    }
    return fp;
}

int count_lines(FILE* fp) {
    if (fp == NULL)
        return 0;

    int ch = 0;
    int lines = 1;

    // TODO: would a getline() approach be faster?
    while ((ch = fgetc(fp)) != EOF) {
        if (ch == '\n')
            lines += 1;
    }
    return lines;
}

int compare_char(const void* ptr1, const void* ptr2) {
    char ch_a = *(char*) ptr1;
    char ch_b = *(char*) ptr2;

    // largest first
    if (ch_a > ch_b) {
        return -1;
    } else if (ch_a < ch_b) {
        return 1;
    } else {
        return 0;
    }
}

int compare_int_desc(const void* ptr1, const void* ptr2) {
    int a = *(int*) ptr1;
    int b = *(int*) ptr2;

    // largest first
    if (a > b) {
        return -1;
    } else if (a < b) {
        return 1;
    } else {
        return 0;
    }
}

#endif