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
    bool insert_config_item(const string& key, string default_value);
    bool insert_config_item(const string& key, bool default_value);
    bool insert_config_item(const string& key, int default_value);
    bool insert_config_item(const string& key, int64_t default_value);
    bool insert_config_item(const string& key, double default_value);

    bool initialize_load();

    bool set_value(const string& key, string val);
    bool set_value(const string& key, bool val);
    bool set_value(const string& key, int val);
    bool set_value(const string& key, int64_t val);
    bool set_value(const string& key, double val);

    bool get_value(const string& key, string& val);
    bool get_value(const string& key, bool& val);
    bool get_value(const string& key, int&val);
    bool get_value(const string& key, int64_t& val);
    bool get_value(const string& key, double& val);

    void get_last_error(JsonConfigErrors& error_code, string& msg);

private:
    JsonConfigContent* config_content_;
};

