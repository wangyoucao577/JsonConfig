#pragma once

#include <assert.h>
#include "json/json.h"
#include "json_config_define.h"
#include "json_config_errors.h"

#include "pthread.h"

#define JSON_CONFIG_LOG(type, ...) printf(type, ##__VA_ARGS__)
#define JSON_CONFIG_ASSERT(cond) assert(cond)

using namespace std;

enum JsonConfigItemType {
    kItemTypeString = 0,
    kItemTypeInt,
    kItemTypeInt64,
    kItemTypeDouble,
    kItemTypeBool,
};

union Numeric {
    int i;
    int64_t i64;
    double d;
};

struct ValuesSet {
    string s;
    bool b;
    Numeric nv;

    ValuesSet();
    ValuesSet(string val);
    ValuesSet(bool val);
};

struct NumericScope {
    Numeric default;
    Numeric low;
    Numeric hi;

    NumericScope();
    void set_int(int defalut, int low, int hi);
    void set_int64(int64_t default, int64_t low, int64_t hi);
    void set_double(double default, double low, double hi);
};


class JsonConfigContent
{
public:
    JsonConfigContent(string config_file_path);
    ~JsonConfigContent();

public:
    JsonConfigErrors insert_item_string(const string& key, string default_value);
    JsonConfigErrors insert_item_bool(const string& key, bool default_value);
    JsonConfigErrors insert_item_int(const string& key, int default_value, int low, int hi);
    JsonConfigErrors insert_item_int64(const string& key, int64_t default_value, int64_t low, int64_t hi);
    JsonConfigErrors insert_item_double(const string& key, double default_value, double low, double hi);

    JsonConfigErrors initialize_load();

    JsonConfigErrors set_value(const string& key, JsonConfigItemType type, const ValuesSet& val);
    JsonConfigErrors get_value(const string& key, JsonConfigItemType type, ValuesSet& val);

    string dump();
    size_t size();

private:

    bool is_key_exist_unsafe(const string& key);
    size_t key_count_unsafe();
    bool validate_configs_unsafe(Json::Value& config_items);

    Json::Value get_config_items();

    //config file operations
    JsonConfigErrors load(Json::Value& out);
    JsonConfigErrors save(const Json::Value& in);

private:
    static bool clamp_int(int val, int low, int hi);
    static bool clamp_int64(int64_t val, int64_t low, int64_t hi);
    static bool clamp_double(double val, double low, double hi);

private:
    Json::Value config_items_;
    bool initialized_;
    bool initialize_called;
    pthread_mutex_t mutex_;

    //<key, default_value> pair. dynamic initialize at the beginning. 
    map<string, string> key_string_items_;
    map<string, bool> key_bool_items_;
    map<string, NumericScope> key_int_items_;
    map<string, NumericScope> key_int64_items_;
    map<string, NumericScope> key_double_items_;

    string config_file_path_;
    pthread_mutex_t config_file_mutex_;
};

