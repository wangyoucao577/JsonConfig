#pragma once

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

struct JsonConfigItemValue {
    string s;
    int i;
    int64_t i64;
    double d;
    bool b;

    JsonConfigItemValue();
};

class JsonConfigContent
{
public:
    JsonConfigContent(string config_file_path);
    ~JsonConfigContent();

public:
    bool insert_config_item(const string& key, string default_value);
    bool insert_config_item(const string& key, bool default_value);
    bool insert_config_item(const string& key, int default_value);
    bool insert_config_item(const string& key, int64_t default_value);
    bool insert_config_item(const string& key, double default_value);

    bool initialize_load();

    JsonConfigErrors set_value(const string& key, JsonConfigItemType type, const JsonConfigItemValue& val);
    JsonConfigErrors get_value(const string& key, JsonConfigItemType type, JsonConfigItemValue val);

    void get_last_error(JsonConfigErrors& error_code, string& msg);

private:
    void set_last_error_unsafe(const JsonConfigErrors& error_code);
    void set_last_error(const JsonConfigErrors& error_code);

    bool correct_configs(Json::Value& config_items);
    JsonConfigErrors save();

private:
    Json::Value config_items_;
    bool initialized_;
    JsonConfigErrors last_error_code_;
    pthread_mutex_t mutex_;

    //<key, default_value> pair. dynamic initialize at the beginning. 
    map<string, string> key_string_items_;
    map<string, bool> key_bool_items_;
    map<string, int> key_int_items_;
    map<string, int64_t> key_int64_items_;
    map<string, double> key_double_items_;

    string config_file_path_;
    pthread_mutex_t config_file_mutex_;

};

