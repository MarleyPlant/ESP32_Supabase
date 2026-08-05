<h1><b>ESP32 Supabase</b></h1>
<p>An Arduino Platform Library for connecting ESP32 to Supabase via REST API, including user authentication. For now, it only supports the architectures espressif32 in PlatformIO targets.</p>

<br />

[![GitHub Last Commit](https://img.shields.io/github/last-commit/MarleyPlant/ESP32_Supabase?style=flat)](https://github.com/MarleyPlant/ESP32_Supabase) [![GitHub Commit Activity](https://img.shields.io/github/commit-activity/m/MarleyPlant/ESP32_Supabase?style=flat)](https://github.com/MarleyPlant/ESP32_Supabase) [![GitHub Repo stars](https://img.shields.io/github/stars/MarleyPlant/ESP32_Supabase?style=flat)](https://github.com/MarleyPlant/ESP32_Supabase/stargazers) [![GitHub forks](https://img.shields.io/github/forks/MarleyPlant/ESP32_Supabase?style=flat)](https://github.com/MarleyPlant/ESP32_Supabase/network) [![GitHub Issues](https://img.shields.io/github/issues/MarleyPlant/ESP32_Supabase?style=flat)](https://github.com/MarleyPlant/ESP32_Supabase/issues) [![GitHub License](https://img.shields.io/github/license/MarleyPlant/ESP32_Supabase?style=flat)](https://github.com/MarleyPlant/ESP32_Supabase/blob/master/LICENSE) [![GitHub repo size](https://img.shields.io/github/repo-size/MarleyPlant/ESP32_Supabase?style=flat)](https://github.com/MarleyPlant/ESP32_Supabase) [![GitHub top language](https://img.shields.io/github/languages/top/MarleyPlant/ESP32_Supabase?style=flat)](https://github.com/MarleyPlant/ESP32_Supabase)  
 
 <br /> 







## 👨‍💻 Development

### 🔌 Installing Dependencies
```bash
pio pkg install
```

### 🟢 Running The Project
```bash
pio run
```



 
 <br />


This library is built for microcontrollers, so it is appropriate to not include as much user management features, filters or modifier as in [Official Javascript Library](https://supabase.com/docs/reference/javascript/introduction).

For further information :
- [Supabase Documentation](https://supabase.com/docs)
- [PostgREST API Documentation](https://postgrest.org/en/stable/api.html)


 
 <br />

## Using This Library

This library is available at Arduino's Library Manager, as well as PlatformIO Library Manager
- [Arduino Library Manager Guide](http://arduino.cc/en/guide/libraries)

## Examples

See all examples in `examples` folder


 
 <br />

## Available Method

### Directly Makes Connection to Database

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

## To-do (sorted by priority)

- [x] Make Select API (GET Request), full with row limits (one by default)
- [x] Make filtering query builder method in Select and update
- [x] Make order/sort query builder method to in Select
- [x] Implement Update with PATCH HTTPS Request
- [x] Port to ESP8266
- [x] Implement calling RPC function with HTTPS Request
- [ ] Implement several methods to implement [Supabase Realtime](https://supabase.com/docs/guides/realtime)

Better documentation is always a welcoming change 😄️😄️


 
 <br />


 
 <br />




## 💻 Technologies

[![Arduino](https:&#x2F;&#x2F;img.shields.io&#x2F;badge&#x2F;Arduino-00878F?style&#x3D;for-the-badge&amp;logo&#x3D;Arduino&amp;logoColor&#x3D;white)]()
[![Espressif](https:&#x2F;&#x2F;img.shields.io&#x2F;badge&#x2F;Espressif-E7352C?style&#x3D;for-the-badge&amp;logo&#x3D;Espressif&amp;logoColor&#x3D;white)]()
[![PlatformIO](https:&#x2F;&#x2F;img.shields.io&#x2F;badge&#x2F;PlatformIO-F5822A?style&#x3D;for-the-badge&amp;logo&#x3D;PlatformIO&amp;logoColor&#x3D;white)]()
[![Supabase](https:&#x2F;&#x2F;img.shields.io&#x2F;badge&#x2F;Supabase-3FCF8E?style&#x3D;for-the-badge&amp;logo&#x3D;Supabase&amp;logoColor&#x3D;white)]()
[![C++](https:&#x2F;&#x2F;img.shields.io&#x2F;badge&#x2F;C++-00599C?style&#x3D;for-the-badge&amp;logo&#x3D;C++&amp;logoColor&#x3D;white)]()
[![JSON](https:&#x2F;&#x2F;img.shields.io&#x2F;badge&#x2F;JSON-000000?style&#x3D;for-the-badge&amp;logo&#x3D;JSON&amp;logoColor&#x3D;white)]()
[![PostgreSQL](https:&#x2F;&#x2F;img.shields.io&#x2F;badge&#x2F;PostgreSQL-4169E1?style&#x3D;for-the-badge&amp;logo&#x3D;PostgreSQL&amp;logoColor&#x3D;white)]()
[![GitHub](https:&#x2F;&#x2F;img.shields.io&#x2F;badge&#x2F;GitHub-181717?style&#x3D;for-the-badge&amp;logo&#x3D;GitHub&amp;logoColor&#x3D;white)]()



 
 <br />


## 📎 **LICENSE**
> A short and simple permissive license with conditions only requiring preservation of copyright and license notices. Licensed works, modifications, and larger works may be distributed under different terms and without source code.


This Repository Is Licensed Under [MIT License](/LICENSE)


 
 <br />


## 🗃️ Related Projects
- [Supabase](https:&#x2F;&#x2F;supabase.com)
- [PostgREST](https:&#x2F;&#x2F;postgrest.org)
- [ArduinoJson](https:&#x2F;&#x2F;arduinojson.org)
- [PlatformIO](https:&#x2F;&#x2F;platformio.org)

 
 <br />

