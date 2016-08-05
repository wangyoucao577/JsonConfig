
#include <fstream>
#include <assert.h>
#include "json_config_content.h"

#define JSON_CONFIG_LOG(type, ...) printf(type, ##__VA_ARGS__)
#define JSON_CONFIG_ASSERT(cond) assert(cond)



#include "json_config.h"


JsonConfigItemValue::JsonConfigItemValue() :
i(0),
i64(0LL),
d(0.0),
b(false)
{

}

JsonConfigContent::JsonConfigContent(string config_file_path) :
    config_file_path_(config_file_path),
    initialized_(false),
    last_error_code_(kOK)
{
    pthread_mutex_init(&mutex_, NULL);
    pthread_mutex_init(&config_file_mutex_, NULL);
}


JsonConfigContent::~JsonConfigContent()
{
    pthread_mutex_destroy(&mutex_);
    pthread_mutex_destroy(&config_file_mutex_);
}

bool JsonConfigContent::insert_config_item(const string& key, string default_value)
{
    pthread_mutex_lock(&mutex_);
    if (initialized_) {
        set_last_error_unsafe(kErrorItemsInitialized);
        pthread_mutex_unlock(&mutex_);
        return false;
    }

    pair<map<string, string>::iterator, bool> ret = key_string_items_.insert(map<string, string>::value_type(key, default_value));
    if (!ret.second) {
        set_last_error_unsafe(kErrorItemExist);
        pthread_mutex_unlock(&mutex_);
        return false;
    }
    pthread_mutex_unlock(&mutex_);
    return true;
}
bool JsonConfigContent::insert_config_item(const string& key, bool default_value)
{
    pthread_mutex_lock(&mutex_);
    if (initialized_) {
        set_last_error_unsafe(kErrorItemsInitialized);
        pthread_mutex_unlock(&mutex_);
        return false;
    }

    pair<map<string, bool>::iterator, bool> ret = key_bool_items_.insert(map<string, bool>::value_type(key, default_value));
    if (!ret.second) {
        set_last_error_unsafe(kErrorItemExist);
        pthread_mutex_unlock(&mutex_);
        return false;
    }
    pthread_mutex_unlock(&mutex_);
    return true;
}
bool JsonConfigContent::insert_config_item(const string& key, int default_value)
{
    pthread_mutex_lock(&mutex_);
    if (initialized_) {
        set_last_error_unsafe(kErrorItemsInitialized);
        pthread_mutex_unlock(&mutex_);
        return false;
    }

    pair<map<string, int>::iterator, bool> ret = key_int_items_.insert(map<string, int>::value_type(key, default_value));
    if (!ret.second) {
        set_last_error_unsafe(kErrorItemExist);
        pthread_mutex_unlock(&mutex_);
        return false;
    }
    pthread_mutex_unlock(&mutex_);
    return true;
}
bool JsonConfigContent::insert_config_item(const string& key, int64_t default_value)
{
    pthread_mutex_lock(&mutex_);
    if (initialized_) {
        set_last_error_unsafe(kErrorItemsInitialized);
        pthread_mutex_unlock(&mutex_);
        return false;
    }

    pair<map<string, int64_t>::iterator, bool> ret = key_int64_items_.insert(map<string, int64_t>::value_type(key, default_value));
    if (!ret.second) {
        set_last_error_unsafe(kErrorItemExist);
        pthread_mutex_unlock(&mutex_);
        return false;
    }
    pthread_mutex_unlock(&mutex_);
    return true;
}
bool JsonConfigContent::insert_config_item(const string& key, double default_value)
{
    pthread_mutex_lock(&mutex_);
    if (initialized_) {
        set_last_error_unsafe(kErrorItemsInitialized);
        pthread_mutex_unlock(&mutex_);
        return false;
    }

    pair<map<string, double>::iterator, bool> ret = key_double_items_.insert(map<string, double>::value_type(key, default_value));
    if (!ret.second) {
        set_last_error_unsafe(kErrorItemExist);
        pthread_mutex_unlock(&mutex_);
        return false;
    }
    pthread_mutex_unlock(&mutex_);
    return true;
}

bool JsonConfigContent::correct_configs(Json::Value& config_items)
{
    bool anything_changed = false;

    for (map<string, string>::iterator it = key_string_items_.begin(); it != key_string_items_.end(); ++it) {
        if (config_items[it->first].empty() || !config_items[it->first].isString()) {
            config_items[it->first] = it->second;
            anything_changed = true;
        }
    }

    for (map<string, bool>::iterator it = key_bool_items_.begin(); it != key_bool_items_.end(); ++it) {
        if (config_items[it->first].empty() || !config_items[it->first].isBool()) {
            config_items[it->first] = it->second;
            anything_changed = true;
        }
    }

    for (map<string, int>::iterator it = key_int_items_.begin(); it != key_int_items_.end(); ++it) {
        if (config_items[it->first].empty() || !config_items[it->first].isInt()) {
            config_items[it->first] = it->second;
            anything_changed = true;
        }
    }

    for (map<string, int64_t>::iterator it = key_int64_items_.begin(); it != key_int64_items_.end(); ++it) {
        if (config_items[it->first].empty() || !config_items[it->first].isInt64()) {
            config_items[it->first] = it->second;
            anything_changed = true;
        }
    }

    for (map <string, double> ::iterator it = key_double_items_.begin(); it != key_double_items_.end(); ++it) {
        if (config_items[it->first].empty() || !config_items[it->first].isDouble()) {
            config_items[it->first] = it->second;
            anything_changed = true;
        }
    }

    return anything_changed;
}

bool JsonConfigContent::get_value(const string& key, string& val)
{
    pthread_mutex_lock(&mutex_);
    if (!initialized_) {
        set_last_error_unsafe(kErrorNotInitialize);
        pthread_mutex_unlock(&mutex_);
        return false;
    }

    val = config_items_[key].asString();
    pthread_mutex_unlock(&mutex_);
    return true;

}
bool JsonConfigContent::get_value(const string& key, bool& val)
{
    pthread_mutex_lock(&mutex_);
    if (!initialized_) {
        set_last_error_unsafe(kErrorNotInitialize);
        pthread_mutex_unlock(&mutex_);
        return false;
    }

    val = config_items_[key].asBool();
    pthread_mutex_unlock(&mutex_);
    return true;

}
bool JsonConfigContent::get_value(const string& key, int&val)
{
    pthread_mutex_lock(&mutex_);
    if (!initialized_) {
        set_last_error_unsafe(kErrorNotInitialize);
        pthread_mutex_unlock(&mutex_);
        return false;
    }

    val = config_items_[key].asInt();
    pthread_mutex_unlock(&mutex_);
    return true;

}
bool JsonConfigContent::get_value(const string& key, int64_t& val)
{
    pthread_mutex_lock(&mutex_);
    if (!initialized_) {
        set_last_error_unsafe(kErrorNotInitialize);
        pthread_mutex_unlock(&mutex_);
        return false;
    }

    val = config_items_[key].asInt64();
    pthread_mutex_unlock(&mutex_);
    return true;

}


bool JsonConfigContent::get_value(const string& key, double& val)
{
    pthread_mutex_lock(&mutex_);
    if (!initialized_) {
        set_last_error_unsafe(kErrorNotInitialize);
        pthread_mutex_unlock(&mutex_);
        return false;
    }

    val = config_items_[key].asDouble();
    pthread_mutex_unlock(&mutex_);
    return true;
}
bool JsonConfigContent::set_value(const string& key, JsonConfigItemType type, const JsonConfigItemValue& val)
{
    pthread_mutex_lock(&mutex_);
    if (!initialized_) {
        set_last_error_unsafe(kErrorNotInitialize);
        pthread_mutex_unlock(&mutex_);
        return false;
    }

    if (config_items_[key].empty()) {
        set_last_error_unsafe(kErrorItemNotExist);
        pthread_mutex_unlock(&mutex_);
        return false;
    }

    switch (type)
    {
    case kItemTypeString:
        if (0 == config_items_[key].asString().compare(val.s)) {
            pthread_mutex_unlock(&mutex_);
            return true;
        }
        config_items_[key] = val.s;
        break;
    case kItemTypeInt:
        if (config_items_[key].asInt() == val.i) {
            pthread_mutex_unlock(&mutex_);
            return true;
        }
        config_items_[key] = val.i;
        break;
    case kItemTypeInt64:
        if (config_items_[key].asInt64() == val.i64) {
            pthread_mutex_unlock(&mutex_);
            return true;
        }
        config_items_[key] = val.i64;
        break;
    case kItemTypeDouble:
        if (config_items_[key].asDouble() == val.d) {
            pthread_mutex_unlock(&mutex_);
            return true;
        }
        config_items_[key] = val.d;
        break;
    case kItemTypeBool:
        if (config_items_[key].asBool() == val.b) {
            pthread_mutex_unlock(&mutex_);
            return true;
        }
        config_items_[key] = val.b;
        break;
    default:
        JSON_CONFIG_ASSERT(0);
        break;
    }
    pthread_mutex_unlock(&mutex_);

    return save();
}

bool JsonConfigContent::initialize_load()
{
    pthread_mutex_lock(&mutex_);
    if (initialized_) { //only allow to invoke once.
        set_last_error_unsafe(kErrorMultipleInitialize);
        pthread_mutex_unlock(&mutex_);
        return false;
    }
    initialized_ = true;
    pthread_mutex_unlock(&mutex_);


    bool need_save_to_file = false;
    Json::Value new_config_items;

    // read all from file
    pthread_mutex_lock(&config_file_mutex_);
    ifstream ifs(config_file_path_.c_str(), ios::binary);
    if (!ifs) {
        JSON_CONFIG_LOG("%s config file %s in open failed, we'll create a new one.\n", __FUNCTION__, config_file_path_.c_str());

        correct_configs(new_config_items);
        need_save_to_file = true;
    }
    else {
        //read content from file
        string config_str;
        ifs.seekg(0, std::ios::end);
        config_str.reserve(ifs.tellg());
        ifs.seekg(0, std::ios::beg);
        config_str.assign((std::istreambuf_iterator<char>(ifs)),
            std::istreambuf_iterator<char>());
        ifs.close();

        // parse from file and check whether valid 
        Json::Reader config_reader;
        if (!config_reader.parse(config_str, new_config_items)) {
            JSON_CONFIG_LOG("%s config parse failed, restore to default.\n", __FUNCTION__);

            correct_configs(new_config_items);
            need_save_to_file = true;
        }
        else if (correct_configs(new_config_items)) {
            need_save_to_file = true;
        }
    }
    pthread_mutex_unlock(&config_file_mutex_);

    pthread_mutex_lock(&mutex_);
    config_items_ = new_config_items;
    pthread_mutex_unlock(&mutex_);

    if (need_save_to_file) {
        return save();
    }

    return true;
}

bool JsonConfigContent::save()
{
    pthread_mutex_lock(&mutex_);
    Json::Value copy_config_items = config_items_;
    pthread_mutex_unlock(&mutex_);

    pthread_mutex_lock(&config_file_mutex_);
    ofstream ofs(config_file_path_.c_str(), ios::binary | ios::trunc);
    if (!ofs)
    {
        JSON_CONFIG_LOG("%s config file %s out open failed.\n", __FUNCTION__, config_file_path_.c_str());
        pthread_mutex_unlock(&config_file_mutex_);
        set_last_error(kErrorOpenFileWithWriteFailed);
        return false;
    }
    else {
        Json::StyledStreamWriter stream_writer;
        stream_writer.write(ofs, copy_config_items);
        ofs.close();

        JSON_CONFIG_LOG("%s config file %s saved.\n", __FUNCTION__, config_file_path_.c_str());
    }
    pthread_mutex_unlock(&config_file_mutex_);
    return true;
}

void JsonConfigContent::set_last_error_unsafe(const JsonConfigErrors& error_code)
{
    last_error_code_ = error_code;
}

void JsonConfigContent::set_last_error(const JsonConfigErrors& error_code)
{
    pthread_mutex_lock(&mutex_);
    last_error_code_ = error_code;
    pthread_mutex_unlock(&mutex_);
}

void JsonConfigContent::get_last_error(JsonConfigErrors& error_code, string& msg)
{
    pthread_mutex_lock(&mutex_);
    error_code = last_error_code_;
    pthread_mutex_unlock(&mutex_);
}
