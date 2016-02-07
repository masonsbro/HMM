#ifndef UNIT_TEST_H
#define UNIT_TEST_H

void set_test_name(char* name);
void assert_int_e(int a, int b);
void assert_int_ne(int a, int b);
void assert_char_e(char a, char b);
void assert_char_ne(char a, char b);
void assert_str_e(char* a, char* b);
void assert_str_ne(char* a, char* b);
void assert_inta_e(int* a, int* b, int len);
void assert_chara_e(char* a, char* b, int len);
void assert_stra_e(char** a, char** b, int len);
void finish_test();

#endif