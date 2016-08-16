/**
@file json_config.h
@brief core header of libjson_config
@author wangyoucao577
@version 0.1.0
@date 2016-08-08
*/

#pragma once

#include <string>
#include "json_config_define.h"
#include "json_config_errors.h"

class JsonConfigContent;

/** core class of JsonConfig.*/
class JSON_CONFIG_API JsonConfig
{
public:
    /**
    @brief Constructor
    @param config_file_path the full path of the config file
    */
    JsonConfig(std::string config_file_path);
    ~JsonConfig();
    
public:
    /**
    @brief insert new type string key-value for this instance. 
       should be called before initialize()
    @param key the key of this item
    @param default_value default value of this item
    @return kOk if success, otherwise failed
    */
    JsonConfigErrors insert_item_string(const std::string& key, std::string default_value);
    
    /**
    @brief insert new type bool key-value for this instance.
        should be called before initialize()
    @param key the key of this item
    @param default_value default value of this item
    @return kOk if success, otherwise failed
    */
    JsonConfigErrors insert_item(const std::string& key, bool default_value);

    /**
    @brief insert new type double key-value for this instance.
        should be called before initialize()
    @param key the key of this item
    @param default_value default value of this item
    @param low the minimum limit, default DBL_MIN
    @param hi the maximum limit, default DBL_MAX
    @return kOk if success, otherwise failed
    */
    JsonConfigErrors insert_item(const std::string& key, double default_value, double low = DBL_MIN, double hi = DBL_MAX);
    
    /**
    @brief insert new type int key-value for this instance.
        should be called before initialize()
    @param key the key of this item
    @param default_value default value of this item
    @param low the minimum limit, default INT_MIN
    @param hi the maximum limit, default INT_MAX
    @return kOk if success, otherwise failed
    */
    JsonConfigErrors insert_item(const std::string& key, int default_value, int low = INT_MIN, int hi = INT_MAX);
    
    /**
    @brief insert new type int64_t key-value for this instance.
        should be called before initialize()
    @param key the key of this item
    @param default_value default value of this item
    @param low the minimum limit, default LLONG_MIN
    @param hi the maximum limit, default LLONG_MAX
    @return kOk if success, otherwise failed
    */
    JsonConfigErrors insert_item_int64(const std::string& key, int64_t default_value, int64_t low = LLONG_MIN, int64_t hi = LLONG_MAX);

    /**
    @brief initialize this instance, read from config file and parse the format and items. load default if failed.
    @return kOk if success, otherwise failed
    */
    JsonConfigErrors initialize();

    /**
    @brief set new value for the indicated key.
    @param key the key of this item
    @param val the new type string value of this item
    @return kOk if success, otherwise failed
    */
    JsonConfigErrors set_value_string(const std::string& key, std::string val);

    /**
    @brief set new value for the indicated key.
    @param key the key of this item
    @param val the new type bool value of this item
    @return kOk if success, otherwise failed
    */
    JsonConfigErrors set_value(const std::string& key, bool val);

    /**
    @brief set new value for the indicated key.
    @param key the key of this item
    @param val the new type double value of this item
    @return kOk if success, otherwise failed
    */
    JsonConfigErrors set_value(const std::string& key, double val);

    /**
    @brief set new value for the indicated key.
    @param key the key of this item
    @param val the new type int value of this item
    @return kOk if success, otherwise failed
    */
    JsonConfigErrors set_value(const std::string& key, int val);

    /**
    @brief set new value for the indicated key.
    @param key the key of this item
    @param val the new type int64_t value of this item
    @return kOk if success, otherwise failed
    */
    JsonConfigErrors set_value_int64(const std::string& key, int64_t val);

    /**
    @brief get value of the indicated key.
    @param key the key of this item
    @param val the output type string value of this item
    @return kOk if success, otherwise failed
    */
    JsonConfigErrors get_value_string(const std::string& key, std::string& val);

    /**
    @brief get value of the indicated key.
    @param key the key of this item
    @param val the output type bool value of this item
    @return kOk if success, otherwise failed
    */
    JsonConfigErrors get_value(const std::string& key, bool& val);

    /**
    @brief get value of the indicated key.
    @param key the key of this item
    @param val the output type double value of this item
    @return kOk if success, otherwise failed
    */
    JsonConfigErrors get_value(const std::string& key, double& val);

    /**
    @brief get value of the indicated key.
    @param key the key of this item
    @param val the output type int value of this item
    @return kOk if success, otherwise failed
    */
    JsonConfigErrors get_value(const std::string& key, int&val);

    /**
    @brief get value of the indicated key.
    @param key the key of this item
    @param val the output type int64_t value of this item
    @return kOk if success, otherwise failed
    */
    JsonConfigErrors get_value_int64(const std::string& key, int64_t& val);

    /**
    @brief get value of the indicated key.
    @param key the key of this item
    @return the type string value of this item.
    */
    std::string value_string(const std::string& key);

    /**
    @brief get value of the indicated key.
    @param key the key of this item
    @return the type bool value of this item.
    */
    bool value_bool(const std::string& key);

    /**
    @brief get value of the indicated key.
    @param key the key of this item
    @return the type double value of this item.
    */
    double value_double(const std::string& key);

    /**
    @brief get value of the indicated key.
    @param key the key of this item
    @return the type int value of this item.
    */
    int value_int(const std::string& key);

    /**
    @brief get value of the indicated key.
    @param key the key of this item
    @return the type int64_t value of this item.
    */
    int64_t value_int64(const std::string& key);

    /**
    @brief dump all key-value pairs as a string, for print and debug.
    @return the styled type-string for all items.
    */
    std::string dump();

    /**
    @brief get how many items in this instance.
    @return items count.
    */
    size_t size();

private:
    JsonConfigContent* config_content_;
};

/**
@brief get version of the libjson_config
@param major output the major numeric version. pass in NULL if you don't care.
@param minor output the minor numeric version. pass in NULL if you don't care.
@return version pointer to the static version string, for caller's printf.
*/
JSON_CONFIG_API const char * libjson_config_version(int* major, int* minor);
