#include "../PPHP.h"
#include <gtest/gtest.h>
#include <cstring>
#include <stdlib.h>

class PPHPSingleInsertTest : public testing::Test {
    protected:
};

class PPHPVarFieldInsertTest : public testing::Test {
    protected:
};

class PPHPKeyValInsertTest : public testing::Test {
    protected:
};

class PPHPKeyValInsert2Test : public testing::Test {
    protected:
};

class PPHPFieldFinderTest: public testing::Test {
    protected:
};

TEST(PPHPSingleInsertTest, NoField) {
    char unprocessed[] = "Jest to jakis teks bez fielda";
    size_t buffer_size = 200 * sizeof(char);
    char* buffer = (char*)malloc(buffer_size);
    char value[] = "cokolwiek";
    int status = PPHP_first_field_insert(buffer, buffer_size,unprocessed, value);
    EXPECT_EQ(status, -1);
    EXPECT_STREQ(buffer, "Jest to jakis teks bez fielda");
    free(buffer);
}

TEST(PPHPSingleInsertTest, FieldInTheMiddle) {
    char unprocessed[] = "Jest to test z <<x>>fieldem w srodku";
    size_t buffer_size = 200 * sizeof(char);
    char* buffer = (char*)malloc(buffer_size);
    char value[] = "duzym ";
    int status = PPHP_first_field_insert(buffer, buffer_size, unprocessed, value);
    EXPECT_EQ(status, 0);
    EXPECT_STREQ(buffer, "Jest to test z duzym fieldem w srodku");
    free(buffer);
}

TEST(PPHPSingleInsertTest, FieldInTheBegining) {
    char unprocessed[] = "<<x>>Jest to test z fieldem na poczatku";
    size_t buffer_size = 200 * sizeof(char);
    char* buffer = (char*)malloc(buffer_size);
    char value[] = "Joo ";
    int status = PPHP_first_field_insert(buffer, buffer_size, unprocessed, value);
    EXPECT_EQ(status, 0);
    EXPECT_STREQ(buffer, "Joo Jest to test z fieldem na poczatku");
    free(buffer);
}

TEST(PPHPSingleInsertTest, FieldInTheEnd) {
    char unprocessed[] = "Jest to test z fieldem na koncu<<x>>";
    size_t buffer_size = 200 * sizeof(char);
    char* buffer = (char*)malloc(buffer_size);
    char value[] = " Joo";
    int status = PPHP_first_field_insert(buffer, buffer_size, unprocessed, value);
    EXPECT_EQ(status, 0);
    EXPECT_STREQ(buffer, "Jest to test z fieldem na koncu Joo");
    free(buffer);
}

TEST(PPHPSingleInsertTest, SecondField) {
    char unprocessed[] = "Jest to <<x>> test z <<y>>dwoma fieldami";
    size_t buffer_size = 200 * sizeof(char);
    char* buffer = (char*)malloc(buffer_size);
    char value[] = "chyba";
    int status = PPHP_first_field_insert(buffer, buffer_size, unprocessed, value);
    EXPECT_EQ(status, 0);
    EXPECT_STREQ(buffer, "Jest to chyba test z <<y>>dwoma fieldami");
    free(buffer);
}

TEST(PPHPSingleInsertTest, DoubleInsert) {
    char unprocessed[] = "Jest to <<x>> test z dwoma <<y>> fieldami";
    size_t buffer_size = 200 * sizeof(char);
    char* buffer1 = (char*)malloc(buffer_size);
    char* buffer2 = (char*)malloc(buffer_size);
    char value1[] = "chyba";
    char value2[] = "fajnymi";
    int status1 = PPHP_first_field_insert(buffer1, buffer_size, unprocessed, value1); 
    EXPECT_EQ(status1, 0);
    EXPECT_STREQ(buffer1, "Jest to chyba test z dwoma <<y>> fieldami");
    int status2 = PPHP_first_field_insert(buffer2, buffer_size, buffer1, value2);
    EXPECT_EQ(status2, 0);
    EXPECT_STREQ(buffer2, "Jest to chyba test z dwoma fajnymi fieldami");
    free(buffer1);
    free(buffer2);
}

TEST(PPHPVarFieldInsertTest, NoField) {
    char unprocessed[] = "Jest to test bez fielda";
    size_t buffer_size = 200 * sizeof(char);
    char* buffer = (char*)malloc(buffer_size);
    char variable[] = "x";
    char value[] = "chyba";
    int status = PPHP_var_field_insert(buffer, buffer_size, unprocessed, variable, value);
    EXPECT_EQ(status, -1);
    EXPECT_STREQ(buffer, "Jest to test bez fielda");
    free(buffer);
}

TEST(PPHPVarFieldInsertTest, FieldInTheMiddle) {
    char unprocessed[] = "Jest to test z <<x>> fieldem w srodku";
    size_t buffer_size = 200 * sizeof(char);
    char* buffer = (char*)malloc(buffer_size);
    char variable[] = "x";
    char value[] = "fajnym";
    int status = PPHP_var_field_insert(buffer, buffer_size, unprocessed, variable, value);
    EXPECT_EQ(status, 0);
    EXPECT_STREQ(buffer, "Jest to test z fajnym fieldem w srodku");
    free(buffer);
}

TEST(PPHPVarFieldInsertTest, FieldInTheEnd) {
    char unprocessed[] = "Jest to test z fieldem <<x>>";
    size_t buffer_size = 200 * sizeof(char);
    char* buffer = (char*)malloc(buffer_size);
    char variable[] = "x";
    char value[] = "na koncu";
    int status = PPHP_var_field_insert(buffer, buffer_size, unprocessed, variable, value);
    EXPECT_EQ(status, 0);
    EXPECT_STREQ(buffer, "Jest to test z fieldem na koncu");
    free(buffer);
}

TEST(PPHPVarFieldInsertTest, FieldInTheBegining) {
    char unprocessed[] = "<<x>> to test z fieldem na poczatku";
    size_t buffer_size = 200 * sizeof(char);
    char* buffer = (char*)malloc(buffer_size);
    char variable[] = "x";
    char value[] = "Jest";
    int status = PPHP_var_field_insert(buffer, buffer_size, unprocessed, variable, value);
    EXPECT_EQ(status, 0);
    EXPECT_STREQ(buffer, "Jest to test z fieldem na poczatku");
    free(buffer);
}

TEST(PPHPVarFieldInsertTest, RepeatedVar) {
    char unprocessed[] = "<<x>> oraz <<x>>";
    size_t buffer_size = 200 * sizeof(char);
    char* buffer = (char*)malloc(buffer_size);
    char variable[] = "x";
    char value[] = "cos";
    int status = PPHP_var_field_insert(buffer, buffer_size, unprocessed, variable, value);
    EXPECT_EQ(status, 0);
    EXPECT_STREQ(buffer, "cos oraz <<x>>");
    free(buffer);
}

TEST(PPHPVarFieldInsertTest, NoMatchVar) {
    char unprocessed[] = "Jest to test z fieldem <<y>>";
    size_t buffer_size = 200 * sizeof(char);
    char* buffer = (char*)malloc(buffer_size);
    char variable[] = "x";
    char value[] = "na koncu";
    int status = PPHP_var_field_insert(buffer, buffer_size, unprocessed, variable, value);
    EXPECT_EQ(status, -1);
    EXPECT_STREQ(buffer, "Jest to test z fieldem <<y>>");
    free(buffer);
}

TEST(PPHPKeyValInsertTest, NoField) {
    char unprocessed[] = "Nie ma fielda w tym teście";
    size_t buffer_size = 200 * sizeof(char);
    char* buffer = (char*)malloc(buffer_size);
    char keys[2][20] = {"name", "password"};
    char vals[2][30] = {"admin", "idk"};
    int status = PPHP_key_val_insert(buffer, buffer_size, unprocessed, keys, vals, 2);
    EXPECT_EQ(status, 0);
    EXPECT_STREQ(buffer, "Nie ma fielda w tym teście");
    free(buffer);
}

TEST(PPHPKeyValInsertTest, OneField) {
    char unprocessed[] = "Test z <<word>> fieldem";
    size_t buffer_size = 200 * sizeof(char);
    char* buffer = (char*)malloc(buffer_size);
    char keys[2][20] = {"word", "password"};
    char vals[2][30] = {"jednym", "idk"};
    int status = PPHP_key_val_insert(buffer, buffer_size, unprocessed, keys, vals, 2);
    EXPECT_EQ(status, 0);
    EXPECT_STREQ(buffer, "Test z jednym fieldem");
    free(buffer);
}

TEST(PPHPKeyValInsertTest, OneFieldSecondKey) {
    char unprocessed[] = "Test z <<word>> fieldem";
    size_t buffer_size = 200 * sizeof(char);
    char* buffer = (char*)malloc(buffer_size);
    char keys[2][20] = {"password", "word"};
    char vals[2][30] = {"jednym", "jednym"};
    int status = PPHP_key_val_insert(buffer, buffer_size, unprocessed, keys, vals, 2);
    EXPECT_EQ(status, 0);
    EXPECT_STREQ(buffer, "Test z jednym fieldem");
    free(buffer);
}

TEST(PPHPKeyValInsertTest, TwoFields) {
    char unprocessed[] = "Username: <<name>>, password: <<password>>";
    size_t buffer_size = 200 * sizeof(char);
    char* buffer = (char*)malloc(buffer_size);
    char keys[2][20] = {"name", "password"};
    char vals[2][30] = {"admin", "passwd"};
    int status = PPHP_key_val_insert(buffer, buffer_size, unprocessed, keys, vals, 2);
    EXPECT_EQ(status, 0);
    EXPECT_STREQ(buffer, "Username: admin, password: passwd");
    free(buffer);
}

TEST(PPHPKeyValInsertTest, UnknownField) {
    char unprocessed[] = "Username: <<smthng>> ss";
    size_t buffer_size = 200 * sizeof(char);
    char* buffer = (char*)malloc(buffer_size);
    char keys[2][20] = {"name", "password"};
    char vals[2][30] = {"admin", "passwd"};
    int status = PPHP_key_val_insert(buffer, buffer_size, unprocessed, keys, vals, 2);
    EXPECT_EQ(status, -1);
    EXPECT_STREQ(buffer, "Username: <<smthng>> ss");
    free(buffer);
}

TEST(PPHPFieldFinderTest, OneField) {
    char unprocessed[] = "Username: <<smthg>> ss";
    struct matches_struct matches;
    int status = find_matches(unprocessed, &matches);
    EXPECT_EQ(status, 0);
    EXPECT_EQ(unprocessed + 10, matches.outer_start);
    EXPECT_EQ(unprocessed + 12, matches.inner_start);
    EXPECT_EQ(unprocessed + 16, matches.inner_end);
    EXPECT_EQ(unprocessed + 18, matches.outer_end);
}

TEST(PPHPFieldFinderTest, NoField) {
    char unprocessed[] = "Username: ";
    struct matches_struct matches;
    int status = find_matches(unprocessed, &matches);
    EXPECT_EQ(status, -1);
}

TEST(PPHPFieldFinderTest, BrokenField) {
    char unprocessed[] = "Username: <<name>  ";
    struct matches_struct matches;
    int status = find_matches(unprocessed, &matches);
    EXPECT_EQ(status, -2);
}

TEST(PPHPKeyValInsert2Test, NoField) {
    char unprocessed[] = "Nie ma fielda w tym teście";
    size_t buffer_size = 200 * sizeof(char);
    char* buffer = (char*)malloc(buffer_size);
    char keys[2][20] = {"name", "password"};
    char vals[2][30] = {"admin", "idk"};
    int status = PPHP_key_val_insert(buffer, buffer_size, unprocessed, keys, vals, 2);
    EXPECT_EQ(status, 0);
    EXPECT_STREQ(buffer, "Nie ma fielda w tym teście");
    free(buffer);
}

TEST(PPHPKeyValInsert2Test, OneField) {
    char unprocessed[] = "Test z <<word>> fieldem";
    size_t buffer_size = 200 * sizeof(char);
    char* buffer = (char*)malloc(buffer_size);
    char keys[2][20] = {"word", "password"};
    char vals[2][30] = {"jednym", "idk"};
    int status = PPHP_key_val_insert(buffer, buffer_size, unprocessed, keys, vals, 2);
    EXPECT_EQ(status, 0);
    EXPECT_STREQ(buffer, "Test z jednym fieldem");
    free(buffer);
}

TEST(PPHPKeyValInsert2Test, OneFieldSecondKey) {
    char unprocessed[] = "Test z <<word>> fieldem";
    size_t buffer_size = 200 * sizeof(char);
    char* buffer = (char*)malloc(buffer_size);
    char keys[2][20] = {"password", "word"};
    char vals[2][30] = {"jednym", "jednym"};
    int status = PPHP_key_val_insert(buffer, buffer_size, unprocessed, keys, vals, 2);
    EXPECT_EQ(status, 0);
    EXPECT_STREQ(buffer, "Test z jednym fieldem");
    free(buffer);
}

TEST(PPHPKeyValInsert2Test, TwoFields) {
    char unprocessed[] = "Username: <<name>>, password: <<password>>";
    size_t buffer_size = 200 * sizeof(char);
    char* buffer = (char*)malloc(buffer_size);
    char keys[2][20] = {"name", "password"};
    char vals[2][30] = {"admin", "passwd"};
    int status = PPHP_key_val_insert(buffer, buffer_size, unprocessed, keys, vals, 2);
    EXPECT_EQ(status, 0);
    EXPECT_STREQ(buffer, "Username: admin, password: passwd");
    free(buffer);
}

TEST(PPHPKeyValInsert2Test, UnknownField) {
    char unprocessed[] = "Username: <<smthng>> ss";
    size_t buffer_size = 200 * sizeof(char);
    char* buffer = (char*)malloc(buffer_size);
    char keys[2][20] = {"name", "password"};
    char vals[2][30] = {"admin", "passwd"};
    int status = PPHP_key_val_insert(buffer, buffer_size, unprocessed, keys, vals, 2);
    EXPECT_EQ(status, -1);
    EXPECT_STREQ(buffer, "Username: <<smthng>> ss");
    free(buffer);
}