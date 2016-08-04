#include "json_config_contents.h"



void JsonConfigContents::clear()
{
    config_items.clear();

    key_string_items.clear();
    key_bool_items.clear();
    key_int_items.clear();
    key_int64_items.clear();
    key_double_items.clear();
}

bool JsonConfigContents::correct_configs(Json::Value& items)
{
    bool anything_changed = false;

    for (map<string, string>::iterator it = key_string_items.begin(); it != key_string_items.end(); ++it) {
        if (items[it->first].empty() || !items[it->first].isString()) {
            items[it->first] = it->second;
            anything_changed = true;
        }
    }

    for (map<string, bool>::iterator it = key_bool_items.begin(); it != key_bool_items.end(); ++it) {
        if (items[it->first].empty() || !items[it->first].isBool()) {
            items[it->first] = it->second;
            anything_changed = true;
        }
    }

    for (map<string, int>::iterator it = key_int_items.begin(); it != key_int_items.end(); ++it) {
        if (items[it->first].empty() || !items[it->first].isInt()) {
            items[it->first] = it->second;
            anything_changed = true;
        }
    }

    for (map<string, int64_t>::iterator it = key_int64_items.begin(); it != key_int64_items.end(); ++it) {
        if (items[it->first].empty() || !items[it->first].isInt64()) {
            items[it->first] = it->second;
            anything_changed = true;
        }
    }

    for (map <string, double> ::iterator it = key_double_items.begin(); it != key_double_items.end(); ++it) {
        if (items[it->first].empty() || !items[it->first].isDouble()) {
            items[it->first] = it->second;
            anything_changed = true;
        }
    }

    return anything_changed;
}