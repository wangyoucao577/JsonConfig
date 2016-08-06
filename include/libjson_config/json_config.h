#pragma once

#include <string>
#include "json_config_define.h"
#include "json_config_errors.h"

using namespace std;

class JsonConfigContent;
class JSON_CONFIG_API JsonConfig
{
public:
    JsonConfig(string config_file_path);
    ~JsonConfig();
    
public:
    JsonConfigErrors insert_item(const string& key, string default_value);
    JsonConfigErrors insert_item(const string& key, bool default_value);
    JsonConfigErrors insert_item(const string& key, double default_value, double low, double hi);
    JsonConfigErrors insert_item(const string& key, int default_value, int low, int hi);
    JsonConfigErrors insert_item_int64(const string& key, int64_t default_value, int64_t low, int64_t hi);


    bool initialize_load();

    JsonConfigErrors set_value(const string& key, string val);
    JsonConfigErrors set_value(const string& key, bool val);
    JsonConfigErrors set_value(const string& key, double val);
    JsonConfigErrors set_value(const string& key, int val);
    JsonConfigErrors set_value_int64(const string& key, int64_t val);

    JsonConfigErrors get_value(const string& key, string& val);
    JsonConfigErrors get_value(const string& key, bool& val);
    JsonConfigErrors get_value(const string& key, double& val);
    JsonConfigErrors get_value(const string& key, int&val);
    JsonConfigErrors get_value_int64(const string& key, int64_t& val);

    void get_last_error(JsonConfigErrors& error_code, string& msg);

private:
    JsonConfigContent* config_content_;
};

