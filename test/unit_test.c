#include <stdlib.h>
#include <stdio.h>
#include <string.h>

#include "unit_test.h"

static char* TEST_NAME;
static int ASSERTS_FAILED;
static int ASSERTS_RUN;

void set_test_name(char* name) {
    TEST_NAME = name;
}

void assert_null(void* ptr) {
    ASSERTS_RUN++;
    if (ptr != NULL) {
        ASSERTS_FAILED++;
        printf("%s %d: assert_null\n", TEST_NAME, ASSERTS_RUN);
        printf("\tExpected:  NULL\n");
        printf("\tActual:    %p\n", ptr);
    }
}

void assert_int_e(int a, int b) {
    ASSERTS_RUN++;
    if (a != b) {
        ASSERTS_FAILED++;
        printf("%s %d: assert_int_e\n", TEST_NAME, ASSERTS_RUN);
        printf("\tExpected:  %d\n", a);
        printf("\tActual:    %d\n", b);
    }
}

void assert_int_ne(int a, int b) {
    ASSERTS_RUN++;
    if (a == b) {
        ASSERTS_FAILED++;
        printf("%s %d: assert_int_ne\n", TEST_NAME, ASSERTS_RUN);
        printf("\tExpected: !%d\n", a);
        printf("\tActual:    %d\n", b);
    }
}

void assert_char_e(char a, char b) {
    ASSERTS_RUN++;
    if (a != b) {
        ASSERTS_FAILED++;
        printf("%s %d: assert_char_e\n", TEST_NAME, ASSERTS_RUN);
        printf("\tExpected:  %c\n", a);
        printf("\tActual:    %c\n", b);
    }
}

void assert_char_ne(char a, char b) {
    ASSERTS_RUN++;
    if (a == b) {
        ASSERTS_FAILED++;
        printf("%s %d: assert_char_ne\n", TEST_NAME, ASSERTS_RUN);
        printf("\tExpected: !%c\n", a);
        printf("\tActual:    %c\n", b);
    }
}

void assert_str_e(char* a, char* b) {
    ASSERTS_RUN++;
    if (strcmp(a, b) != 0) {
        ASSERTS_FAILED++;
        printf("%s %d: assert_str_e\n", TEST_NAME, ASSERTS_RUN);
        printf("\tExpected:  %s\n", a);
        printf("\tActual:    %s\n", b);
    }
}

void assert_str_ne(char* a, char* b) {
    ASSERTS_RUN++;
    if (strcmp(a, b) == 0) {
        ASSERTS_FAILED++;
        printf("%s %d: assert_str_ne\n", TEST_NAME, ASSERTS_RUN);
        printf("\tExpected: !%s\n", a);
        printf("\tActual:    %s\n", b);
    }
}

void assert_inta_e(int* a, int* b, int len) {
    ASSERTS_RUN++;
    for (int i = 0; i < len; i++) {
        if (a[i] != b[i]) {
            ASSERTS_FAILED++;
            printf("%s %d: assert_inta_e\n", TEST_NAME, ASSERTS_RUN);
            printf("\tExpected:  {%d", a[0]);
            for (int j = 1; j < len; j++) {
                printf(", %d", a[j]);
            }
            printf("}\n");
            printf("\tActual:    {%d", b[0]);
            for (int j = 1; j < len; j++) {
                printf(", %d", b[j]);
            }
            printf("}\n");
            return;
        }
    }
}

void assert_chara_e(char* a, char* b, int len) {
    ASSERTS_RUN++;
    for (int i = 0; i < len; i++) {
        if (a[i] != b[i]) {
            ASSERTS_FAILED++;
            printf("%s %d: assert_chara_e\n", TEST_NAME, ASSERTS_RUN);
            printf("\tExpected:  {%c", a[0]);
            for (int j = 1; j < len; j++) {
                printf(", %c", a[j]);
            }
            printf("}\n");
            printf("\tActual:    {%c", b[0]);
            for (int j = 1; j < len; j++) {
                printf(", %c", b[j]);
            }
            printf("}\n");
            return;
        }
    }
}

void assert_stra_e(char** a, char** b, int len) {
    ASSERTS_RUN++;
    for (int i = 0; i < len; i++) {
        if (strcmp(a[i], b[i]) != 0) {
            ASSERTS_FAILED++;
            printf("%s %d: assert_stra_e\n", TEST_NAME, ASSERTS_RUN);
            printf("\tExpected:  {\"%s\"", a[0]);
            for (int j = 1; j < len; j++) {
                printf(", \"%s\"", a[j]);
            }
            printf("}\n");
            printf("\tActual:    {\"%s\"", b[0]);
            for (int j = 1; j < len; j++) {
                printf(", \"%s\"", b[j]);
            }
            printf("}\n");
            return;
        }
    }
}

void finish_test() {
    if (ASSERTS_FAILED == 0) {
        printf("%s passed\n", TEST_NAME);
    } else {
        printf("%s FAILED %d assertions\n", TEST_NAME, ASSERTS_FAILED);
    }
}