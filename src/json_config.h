#pragma once

#include "pthread.h"

using namespace std;

typedef long long int64_t;

#if defined(_MSC_VER)   //on Windows
#if defined(JSON_CONFIG_DLL_BUILD)
#define JSON_CONFIG_API __declspec(dllexport)
#else
#define JSON_CONFIG_API __declspec(dllimport)
#endif
#elif defined(__linux__)
//TODO: 
#endif
#if !defined(JSON_CONFIG_API)
#define JSON_CONFIG_API
#endif

enum JsonConfigErrors {
    kOK = 0,
    
    kErrorOffset = 10001,

    kErrorNotInitialize,
    kErrorItemsInitialized,
    kErrorMultipleInitialize,
    kErrorItemExist,
    kErrorItemNotExist,

    kErrorOpenFileWithWriteFailed,

};

struct JsonConfigContents;

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
    void set_last_error_unsafe(const JsonConfigErrors& error_code);
    void set_last_error(const JsonConfigErrors& error_code);

    bool save();

private:
    JsonConfigContents* config_contents_;
    bool initialized_;
    JsonConfigErrors last_error_code_;
    pthread_mutex_t mutex_;

    string config_file_path_;
    pthread_mutex_t config_file_mutex_;
};

