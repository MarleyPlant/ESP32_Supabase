### Building The Queries

When building the queries, you can chain the method like in this example.

> Remember in `.select()` method, it is mandatory to put some low amount of `.limit()`, so you can avoid your microcontroller's memory get overflowed

```arduino
String read = db.from("table").select("*").eq("column", "value").order("column", "asc", true).limit(1).doSelect();
```

| Methods                  | Description                                                                             |
| ------------------------ | --------------------------------------------------------------------------------------- |
| `.from(String table);`   | Specify which table you want to query. It will append `?table_name` in Request URL      |
| `.select(String colls);` | Specify that you want to do select query. It will append `&select=colls` in Request URL |
| `.update(String table);` | Specify that you want to do update query. It will append `&update` in Request URL       |


#### Horizontal Filtering (comparison) Operator

| Methods                            | Description                                                                                                |
| ---------------------------------- | ---------------------------------------------------------------------------------------------------------- |
| `.eq(String colls, String value)`  | Equals                                                                                                     |
| `.gt(String colls, String value)`  | Greater than                                                                                               |
| `.gte(String colls, String value)` | Greater than or equal                                                                                      |
| `.lt(String colls, String value)`  | Less than                                                                                                  |
| `.lte(String colls, String value)` | Less than or equal                                                                                         |
| `.neq(String colls, String value)` | Not equal                                                                                                  |
| `.in(String colls, String value)`  | One of a list of values, e.g. `1,2,3` – also supports commas in quoted strings like `"hi,there","yes,you"` |
| `.is(String colls, String value)`  | Checking for exact equality `<null, true, false, unknown>`                                                 |
| `.cs(String colls, String value)`  | Contains e.g. `example, new`                                                                               |
| `.cd(String colls, String value)`  | Contained in e.g. `1, 2, 3`                                                                                |
| `.ov(String colls, String value)`  | Overlap (have points in common), e.g. `2017-01-01, 2017-06-30`                                             |
| `.sl(String colls, String value)`  | Strictly left of, e.g. `1,10`                                                                              |
| `.sr(String colls, String value)`  | Strictly right of                                                                                          |
| `.nxr(String colls, String value)` | Does not extend to the right of, e.g. `1,10`                                                               |
| `.nxl(String colls, String value)` | Does not extend to the left of                                                                             |
| `.adj(String colls, String value)` | Is adjacent to, e.g. `1,10`                                                                                |

#### Ordering, Limiting or Offseting the Result

| Methods                                       | Description                                                                                                                                                                                 |
| --------------------------------------------- | ------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------- |
| `.order(String coll, String by, bool nulls);` | This reorders the response rows. `coll` parameter is column name, `by` parameter is either `asc` or `desc`. The last parameter specifies the position of nulls, `nullsfirst` or `nullslast` |
| `.limit(unsigned int by);`                    | Limit the amount of response rows. THIS IS MANDATORY FOR SELECT METHOD!!!                                                                                                                   |
| `.offset(int by);`                            | Request response rows with offset is with its parameters.                                                                                                                                   |

#### Getting the Query URL (for debugging)

```arduino
db.urlQuery_reset();
```

#### Reset the Query URL

This method calls in mandatory, must be called after one opetation (let's say `doSelect()`, or `doUpdate()`) before doing anything else.

```arduino
db.urlQuery_reset();
```
