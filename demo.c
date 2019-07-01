#include "sqlite3_eu.h"

#include <stdio.h>

int cb(void * ignored1, int result_count, char ** result, char ** ignored2)
{
  printf("result count: %d\n", result_count);
  printf("first result: %s\n", result[0]);
  return 0;
}

int main() {
  sqlite3 * db;
  sqlite3_open(":memory:", &db);

  sqlite3_eu_init(db, "UPPER_EU", "LOWER_EU");

  printf("* TRY SELECT UPPER_EU with mixed string:\n");

  sqlite3_exec(db, "SELECT UPPER_EU('Alice 😊 é 😊 á 😊 ß 😊 €123')", cb, NULL, NULL);

  printf("* TRY SELECT UPPER_EU with empty string:\n");

  sqlite3_exec(db, "SELECT UPPER_EU('')", cb, NULL, NULL);

  printf("* TRY SELECT LOWER_EU with mixed string:\n");

  sqlite3_exec(db, "SELECT LOWER_EU('DE100 😊 Chris DEF 😊 ẞ 😊 Á 😊 É 😊 €456')", cb, NULL, NULL);

  return 0;
}
