<h1><b>ESP32_Supabase</b></h1>
<p>An Arduino Platform Library for connecting ESP32 to Supabase via REST API, including user authentication.</p>

<br />



## Instance Methods
| Method                                           | Description                                                                                                                          |
| ------------------------------------------------ | ------------------------------------------------------------------------------------------------------------------------------------ |
| `begin(String url_a, String key_a);`             | `url_a`  is a Supabase URL and `key_a` is supabase anon key. Returns `void`                                                          |
| `login_email(String email_a, String password_a)` | Returns http response code `int`                                                                                                     |
| `login_phone(String phone_a, String password_a)` | Returns http response code `int`                                                                                                     |
| `insert(String table, String json, bool upsert)` | Returns http response code `int`. If you want to do upsert, set thirt parameter to `true`                                            |
| `upload(String bucket, String filename, String mime_type, Stream *stream, uint32_t size)` | `bucket` is the name of the Supabase Storage bucket without any `/`. `filename` is the name to upload the file with, should have extension but no `/`. Takes a `Stream*` pointer as an argument, this can be Arduino SD `File*` or SPIFFS `File*` types. Returns http response code `int`. `mime_type` is for eg. `image/jpg`. `size` is the total size in bytes of the file to upload. Returns http response code `int`. |
| `upload(String bucket, String filename, String mime_type, uint8_t *buffer, uint32_t size)` | Same function as the previous one but takes a `uint8_t*` buffer instead of a `Stream*`. Can be used for files stored in RAM. |
| `.doSelect()`                                    | Called at the end of select query chain, see [Examples](#examples). Returns http response payload (your data) from Supabase `String` |
| `.doUpdate(String json)`                         | Called at the end of update query chain, see [Examples](#examples). Returns http response code from Supabase `int`                   |


 
 <br />

## Connecting To The Database

 
 <br />

### Reealtime Listener
```arduino
db.realtime.addEntry("Devices", "*", queries, numqueries, DevicesTableHandler);
```

#### Queries
```arduino
SUPABASEQuery queries[1] = {
    { "field", "eq", "value }
};

realtime.setupListener("Table", "*", queries, 1);
realtime.setupHandler([&](JsonDocument doc) {
    handlerFunction(doc);
});
```

#### Loop

```arduino
db.realtime.loop();
```


 
 <br />


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

 
 <br />


 
 <br />


## 🧑‍💼 **Contributors**

| **Name** | **Email**      |**Commits**     | **Social**           |
| -------- | -------------- | -------------- | -------------------- |
| **Jeremy Watt** | jermwatt@gmail.com | [![Commits](https:&#x2F;&#x2F;img.shields.io&#x2F;badge&#x2F;Commits-9-blue?style&#x3D;for-the-badge&amp;logo&#x3D;git)](..&#x2F;commits&#x2F;master?author&#x3D;) | [![gravatar](https:&#x2F;&#x2F;img.shields.io&#x2F;badge&#x2F;gravatar-1E8CBE?style&#x3D;for-the-badge&amp;logo&#x3D;gravatar&amp;logoColor&#x3D;white)](https:&#x2F;&#x2F;gravatar.com&#x2F;jermwatt)  |
| **haykodarb** | work@hayk.ar | [![Commits](https:&#x2F;&#x2F;img.shields.io&#x2F;badge&#x2F;Commits-7-blue?style&#x3D;for-the-badge&amp;logo&#x3D;git)](..&#x2F;commits&#x2F;master?author&#x3D;) |  |
| **Jhagas Hana Winaya** | jhagashana@mailbox.org,jhagas.205001@mhs.its.ac.id,5001201017@student.its.ac.id,jhagas.205001@mhs.its.ac.id | [![Commits](https:&#x2F;&#x2F;img.shields.io&#x2F;badge&#x2F;Commits-18-blue?style&#x3D;for-the-badge&amp;logo&#x3D;git)](..&#x2F;commits&#x2F;master?author&#x3D;) |  |
| **atulraj85** | 121156542+atulraj85@users.noreply.github.com | [![Commits](https:&#x2F;&#x2F;img.shields.io&#x2F;badge&#x2F;Commits-3-blue?style&#x3D;for-the-badge&amp;logo&#x3D;git)](..&#x2F;commits&#x2F;master?author&#x3D;) |  |
| **Marley Plant** | marley@marleyplant.com | [![Commits](https:&#x2F;&#x2F;img.shields.io&#x2F;badge&#x2F;Commits-2-blue?style&#x3D;for-the-badge&amp;logo&#x3D;git)](..&#x2F;commits&#x2F;master?author&#x3D;marleyplant) | [![github](https:&#x2F;&#x2F;img.shields.io&#x2F;badge&#x2F;github-181717?style&#x3D;for-the-badge&amp;logo&#x3D;github&amp;logoColor&#x3D;white)](https:&#x2F;&#x2F;github.com&#x2F;MarleyPlant) [![gravatar](https:&#x2F;&#x2F;img.shields.io&#x2F;badge&#x2F;gravatar-1E8CBE?style&#x3D;for-the-badge&amp;logo&#x3D;gravatar&amp;logoColor&#x3D;white)](https:&#x2F;&#x2F;gravatar.com&#x2F;marleyjosephplant) [![gitlab](https:&#x2F;&#x2F;img.shields.io&#x2F;badge&#x2F;gitlab-FC6D26?style&#x3D;for-the-badge&amp;logo&#x3D;gitlab&amp;logoColor&#x3D;white)](https:&#x2F;&#x2F;gitlab.com&#x2F;MarleyPlant)  |
| **Steyn** | steyn.guelen@me.com | [![Commits](https:&#x2F;&#x2F;img.shields.io&#x2F;badge&#x2F;Commits-2-blue?style&#x3D;for-the-badge&amp;logo&#x3D;git)](..&#x2F;commits&#x2F;master?author&#x3D;) |  |
| **achmadnr21** | achmad.riskynanda01@gmail.com | [![Commits](https:&#x2F;&#x2F;img.shields.io&#x2F;badge&#x2F;Commits-2-blue?style&#x3D;for-the-badge&amp;logo&#x3D;git)](..&#x2F;commits&#x2F;master?author&#x3D;) |  |
| **Achmad Nashruddin Riskynanda** | 91010605+achmadnr21@users.noreply.github.com | [![Commits](https:&#x2F;&#x2F;img.shields.io&#x2F;badge&#x2F;Commits-1-blue?style&#x3D;for-the-badge&amp;logo&#x3D;git)](..&#x2F;commits&#x2F;master?author&#x3D;) |  |
| **Nicholas Humfrey** | njh@aelius.com | [![Commits](https:&#x2F;&#x2F;img.shields.io&#x2F;badge&#x2F;Commits-1-blue?style&#x3D;for-the-badge&amp;logo&#x3D;git)](..&#x2F;commits&#x2F;master?author&#x3D;) | [![gravatar](https:&#x2F;&#x2F;img.shields.io&#x2F;badge&#x2F;gravatar-1E8CBE?style&#x3D;for-the-badge&amp;logo&#x3D;gravatar&amp;logoColor&#x3D;white)](https:&#x2F;&#x2F;gravatar.com&#x2F;nhumfrey)  |


 
 <br />


## 💻 **TECHNOLOGIES**
[![Arduino](https:&#x2F;&#x2F;img.shields.io&#x2F;badge&#x2F;Arduino-00878F?style&#x3D;for-the-badge&amp;logo&#x3D;Arduino&amp;logoColor&#x3D;white)]()
[![JSON](https:&#x2F;&#x2F;img.shields.io&#x2F;badge&#x2F;JSON-000000?style&#x3D;for-the-badge&amp;logo&#x3D;JSON&amp;logoColor&#x3D;white)]()


 
 <br />

