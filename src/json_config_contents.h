#pragma once

#include "json/json.h"
using namespace std;

struct JsonConfigContents
{
    Json::Value config_items;

    //<key, default_value> pair. dynamic initialize at the beginning. 
    map<string, string> key_string_items;
    map<string, bool> key_bool_items;
    map<string, int> key_int_items;
    map<string, int64_t> key_int64_items;
    map<string, double> key_double_items;

    bool correct_configs(Json::Value& config_items);
    void clear();
};

