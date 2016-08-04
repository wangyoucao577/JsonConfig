
#include <fstream>
#include "json_config.h"
#include "json_config_contents.h"

#define JSON_CONFIG_LOG(type, ...) printf(type, ##__VA_ARGS__)
#define JSON_CONFIG_ASSERT(cond) assert(cond)

JsonConfig::JsonConfig(string config_file_path):
config_file_path_(config_file_path), 
initialized_(false),
last_error_code_(kOK)
{
    config_contents_ = new JsonConfigContents();

    pthread_mutex_init(&mutex_, NULL);
    pthread_mutex_init(&config_file_mutex_, NULL);
}


JsonConfig::~JsonConfig()
{
    delete config_contents_;
    config_contents_ = NULL;

    pthread_mutex_destroy(&mutex_);
    pthread_mutex_destroy(&config_file_mutex_);
}

bool JsonConfig::insert_config_item(const string& key, string default_value)
{
    pthread_mutex_lock(&mutex_);
    if (initialized_) {
        set_last_error_unsafe(kErrorItemsInitialized);
        pthread_mutex_unlock(&mutex_);
        return false;
    }

    pair<map<string, string>::iterator, bool> ret = config_contents_->key_string_items.insert(map<string, string>::value_type(key, default_value));
    if (!ret.second) {
        set_last_error_unsafe(kErrorItemExist);
        pthread_mutex_unlock(&mutex_);
        return false;
    }
    pthread_mutex_unlock(&mutex_);
    return true;
}
bool JsonConfig::insert_config_item(const string& key, bool default_value)
{
    pthread_mutex_lock(&mutex_);
    if (initialized_) {
        set_last_error_unsafe(kErrorItemsInitialized);
        pthread_mutex_unlock(&mutex_);
        return false;
    }

    pair<map<string, bool>::iterator, bool> ret = config_contents_->key_bool_items.insert(map<string, bool>::value_type(key, default_value));
    if (!ret.second) {
        set_last_error_unsafe(kErrorItemExist);
        pthread_mutex_unlock(&mutex_);
        return false;
    }
    pthread_mutex_unlock(&mutex_);
    return true;
}
bool JsonConfig::insert_config_item(const string& key, int default_value)
{
    pthread_mutex_lock(&mutex_);
    if (initialized_) {
        set_last_error_unsafe(kErrorItemsInitialized);
        pthread_mutex_unlock(&mutex_);
        return false;
    }

    pair<map<string, int>::iterator, bool> ret = config_contents_->key_int_items.insert(map<string, int>::value_type(key, default_value));
    if (!ret.second) {
        set_last_error_unsafe(kErrorItemExist);
        pthread_mutex_unlock(&mutex_);
        return false;
    }
    pthread_mutex_unlock(&mutex_);
    return true;
}
bool JsonConfig::insert_config_item(const string& key, int64_t default_value)
{
    pthread_mutex_lock(&mutex_);
    if (initialized_) {
        set_last_error_unsafe(kErrorItemsInitialized);
        pthread_mutex_unlock(&mutex_);
        return false;
    }

    pair<map<string, int64_t>::iterator, bool> ret = config_contents_->key_int64_items.insert(map<string, int64_t>::value_type(key, default_value));
    if (!ret.second) {
        set_last_error_unsafe(kErrorItemExist);
        pthread_mutex_unlock(&mutex_);
        return false;
    }
    pthread_mutex_unlock(&mutex_);
    return true;
}
bool JsonConfig::insert_config_item(const string& key, double default_value)
{
    pthread_mutex_lock(&mutex_);
    if (initialized_) {
        set_last_error_unsafe(kErrorItemsInitialized);
        pthread_mutex_unlock(&mutex_);
        return false;
    }

    pair<map<string, double>::iterator, bool> ret = config_contents_->key_double_items.insert(map<string, double>::value_type(key, default_value));
    if (!ret.second) {
        set_last_error_unsafe(kErrorItemExist);
        pthread_mutex_unlock(&mutex_);
        return false;
    }
    pthread_mutex_unlock(&mutex_);
    return true;
}

bool JsonConfig::get_value(const string& key, string& val)
{
    pthread_mutex_lock(&mutex_);
    if (!initialized_) {
        set_last_error_unsafe(kErrorNotInitialize);
        pthread_mutex_unlock(&mutex_);
        return false;
    }

    val = (config_contents_->config_items)[key].asString();
    pthread_mutex_unlock(&mutex_);
    return true;

}
bool JsonConfig::get_value(const string& key, bool& val)
{
    pthread_mutex_lock(&mutex_);
    if (!initialized_) {
        set_last_error_unsafe(kErrorNotInitialize);
        pthread_mutex_unlock(&mutex_);
        return false;
    }

    val = (config_contents_->config_items)[key].asBool();
    pthread_mutex_unlock(&mutex_);
    return true;

}
bool JsonConfig::get_value(const string& key, int&val)
{
    pthread_mutex_lock(&mutex_);
    if (!initialized_) {
        set_last_error_unsafe(kErrorNotInitialize);
        pthread_mutex_unlock(&mutex_);
        return false;
    }

    val = (config_contents_->config_items)[key].asInt();
    pthread_mutex_unlock(&mutex_);
    return true;

}
bool JsonConfig::get_value(const string& key, int64_t& val)
{
    pthread_mutex_lock(&mutex_);
    if (!initialized_) {
        set_last_error_unsafe(kErrorNotInitialize);
        pthread_mutex_unlock(&mutex_);
        return false;
    }

    val = (config_contents_->config_items)[key].asInt64();
    pthread_mutex_unlock(&mutex_);
    return true;

}
bool JsonConfig::get_value(const string& key, double& val)
{
    pthread_mutex_lock(&mutex_);
    if (!initialized_) {
        set_last_error_unsafe(kErrorNotInitialize);
        pthread_mutex_unlock(&mutex_);
        return false;
    }

    val = (config_contents_->config_items)[key].asDouble();
    pthread_mutex_unlock(&mutex_);
    return true;
}

bool JsonConfig::set_value(const string& key, string val)
{
    pthread_mutex_lock(&mutex_);
    if (!initialized_) {
        set_last_error_unsafe(kErrorNotInitialize);
        pthread_mutex_unlock(&mutex_);
        return false;
    }

    if (0 == (config_contents_->config_items)[key].asString().compare(val)) {
        pthread_mutex_unlock(&mutex_);
        return true;
    }
    (config_contents_->config_items)[key] = val;
    pthread_mutex_unlock(&mutex_);

    return save();
}
bool JsonConfig::set_value(const string& key, bool val)
{
    pthread_mutex_lock(&mutex_);
    if (!initialized_) {
        set_last_error_unsafe(kErrorNotInitialize);
        pthread_mutex_unlock(&mutex_);
        return false;
    }

    if ((config_contents_->config_items)[key].asBool() == val) {
        pthread_mutex_unlock(&mutex_);
        return true;
    }
    (config_contents_->config_items)[key] = val;
    pthread_mutex_unlock(&mutex_);

    return save();

}
bool JsonConfig::set_value(const string& key, int val)
{
    pthread_mutex_lock(&mutex_);
    if (!initialized_) {
        set_last_error_unsafe(kErrorNotInitialize);
        pthread_mutex_unlock(&mutex_);
        return false;
    }

    if ((config_contents_->config_items)[key].asInt() == val) {
        pthread_mutex_unlock(&mutex_);
        return true;
    }
    (config_contents_->config_items)[key] = val;
    pthread_mutex_unlock(&mutex_);

    return save();

}
bool JsonConfig::set_value(const string& key, int64_t val)
{
    pthread_mutex_lock(&mutex_);
    if (!initialized_) {
        set_last_error_unsafe(kErrorNotInitialize);
        pthread_mutex_unlock(&mutex_);
        return false;
    }

    if ((config_contents_->config_items)[key].asInt64() == val) {
        pthread_mutex_unlock(&mutex_);
        return true;
    }
    (config_contents_->config_items)[key] = val;
    pthread_mutex_unlock(&mutex_);

    return save();

}
bool JsonConfig::set_value(const string& key, double val)
{
    pthread_mutex_lock(&mutex_);
    if (!initialized_) {
        set_last_error_unsafe(kErrorNotInitialize);
        pthread_mutex_unlock(&mutex_);
        return false;
    }

    if ((config_contents_->config_items)[key].asDouble() == val) {
        pthread_mutex_unlock(&mutex_);
        return true;
    }
    (config_contents_->config_items)[key] = val;
    pthread_mutex_unlock(&mutex_);

    return save();

}


bool JsonConfig::initialize_load()
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

        //correct_configs(new_config_items);
        config_contents_->correct_configs(new_config_items);
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

            config_contents_->correct_configs(new_config_items);
            need_save_to_file = true;
        }
        else if (config_contents_->correct_configs(new_config_items)) {
            need_save_to_file = true;
        }
    }
    pthread_mutex_unlock(&config_file_mutex_);

    pthread_mutex_lock(&mutex_);
    (config_contents_->config_items) = new_config_items;
    pthread_mutex_unlock(&mutex_);

    if (need_save_to_file) {
        return save();
    }

    return true;
}

bool JsonConfig::save()
{
    pthread_mutex_lock(&mutex_);
    Json::Value copy_config_items = (config_contents_->config_items);
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

void JsonConfig::set_last_error_unsafe(const JsonConfigErrors& error_code)
{
    last_error_code_ = error_code;
}

void JsonConfig::set_last_error(const JsonConfigErrors& error_code)
{
    pthread_mutex_lock(&mutex_);
    last_error_code_ = error_code;
    pthread_mutex_unlock(&mutex_);
}

void JsonConfig::get_last_error(JsonConfigErrors& error_code, string& msg)
{
    pthread_mutex_lock(&mutex_);
    error_code = last_error_code_;
    pthread_mutex_unlock(&mutex_);
}