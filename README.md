# sqlite3-eu

Add EU string function to sqlite3: UPPER_EU

**LICENSE:** MIT

## External dependencies

- SQLite3

## Sample usage

```c

int cb(void * ignored1, int result_count, char ** result, char ** ignored2)
{
  printf("result count: %d\n", result_count);
  printf("first result: %s\n", result[0]);
  return 0;
}

int main() {
  sqlite3 * db;
  sqlite3_open(":memory:", &db);

  sqlite3_eu_init(db);

  sqlite3_exec(db, "SELECT UPPER_EU('Alice abc é á ß €123')", cb, NULL, NULL);

  return 0;
}
```
