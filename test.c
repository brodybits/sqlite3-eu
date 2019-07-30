#include "sqlite3_eu.h"

#include <assert.h>

#include <stdio.h>

#include <string.h>

#define TESTTRACE(...) printf(__VA_ARGS__)

#define TESTLOG(text) printf("* %s\n", text)

int assert_result_matches(void * expected_vp, int result_count, char ** result, char ** ignored2)
{
  const char * expected = (const char *) expected_vp;

  assert(result_count == 1);
  TESTTRACE("check string result: %s\n", result[0]);
  assert(!strcmp(result[0], expected));
  TESTTRACE("- OK\n\n");
  return 0;
}

int assert_result_is_null(void * ignored, int result_count, char ** result, char ** ignored2)
{
  assert(result_count == 1);
  assert(result[0] == NULL);
  TESTTRACE("- OK\n\n");
  return 0;
}

int main() {
  sqlite3 * db;
  sqlite3_open(":memory:", &db);

  sqlite3_eu_init(db, "UPPER_EU", "LOWER_EU");

  TESTLOG("TRY SELECT UPPER_EU with mixed string");

  sqlite3_exec(db, "SELECT UPPER_EU('Alice 😊 é 😊 á 😊 ß 😊 €123')",
    assert_result_matches, "ALICE 😊 É 😊 Á 😊 ẞ 😊 €123", NULL);

  TESTLOG("TRY SELECT UPPER_EU with empty string");

  sqlite3_exec(db, "SELECT UPPER_EU('')", assert_result_is_null, NULL, NULL);

  TESTLOG("TRY SELECT LOWER_EU with mixed string");

  sqlite3_exec(db, "SELECT LOWER_EU('DE100 😊 Chris DEF 😊 ẞ 😊 Á 😊 É 😊 €456')",
    assert_result_matches, "de100 😊 chris def 😊 ß 😊 á 😊 é 😊 €456", NULL);

  return 0;
}
