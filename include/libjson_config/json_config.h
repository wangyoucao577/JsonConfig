#pragma once

#include <string>
#include "json_config_define.h"
#include "json_config_errors.h"

class JsonConfigContent;
class JSON_CONFIG_API JsonConfig
{
public:
    JsonConfig(std::string config_file_path);
    ~JsonConfig();
    
public:
    JsonConfigErrors insert_item(const std::string& key, std::string default_value);
    JsonConfigErrors insert_item(const std::string& key, bool default_value);
    JsonConfigErrors insert_item(const std::string& key, double default_value, double low = DBL_MIN, double hi = DBL_MAX);
    JsonConfigErrors insert_item(const std::string& key, int default_value, int low = INT_MIN, int hi = INT_MAX);
    JsonConfigErrors insert_item_int64(const std::string& key, int64_t default_value, int64_t low = LLONG_MIN, int64_t hi = LLONG_MAX);

    JsonConfigErrors initialize();

    JsonConfigErrors set_value(const std::string& key, std::string val);
    JsonConfigErrors set_value(const std::string& key, bool val);
    JsonConfigErrors set_value(const std::string& key, double val);
    JsonConfigErrors set_value(const std::string& key, int val);
    JsonConfigErrors set_value_int64(const std::string& key, int64_t val);

    JsonConfigErrors get_value(const std::string& key, std::string& val);
    JsonConfigErrors get_value(const std::string& key, bool& val);
    JsonConfigErrors get_value(const std::string& key, double& val);
    JsonConfigErrors get_value(const std::string& key, int&val);
    JsonConfigErrors get_value_int64(const std::string& key, int64_t& val);

    std::string value_string(const std::string& key);
    bool value_bool(const std::string& key);
    double value_double(const std::string& key);
    int value_int(const std::string& key);
    int64_t value_int64(const std::string& key);

    std::string dump();
    int size();

private:
    JsonConfigContent* config_content_;
};

