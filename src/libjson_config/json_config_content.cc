
#include <fstream>
#include <assert.h>
#include "json_config_content.h"
#include "json_config.h"


JsonConfigItemValue::JsonConfigItemValue() :
b(false)
{
    memset(&nv, 0, sizeof(nv));
}

JsonConfigContent::JsonConfigContent(string config_file_path) :
    config_file_path_(config_file_path),
    initialized_(false)
{
    pthread_mutex_init(&mutex_, NULL);
    pthread_mutex_init(&config_file_mutex_, NULL);
}


JsonConfigContent::~JsonConfigContent()
{
    pthread_mutex_destroy(&mutex_);
    pthread_mutex_destroy(&config_file_mutex_);
}

JsonConfigErrors JsonConfigContent::insert_item_string(const string& key, string default_value)
{
    pthread_mutex_lock(&mutex_);
    if (initialized_) {
        pthread_mutex_unlock(&mutex_);
        return kErrorItemsInitialized;
    }

    pair<map<string, string>::iterator, bool> ret = key_string_items_.insert(map<string, string>::value_type(key, default_value));
    if (!ret.second) {
        pthread_mutex_unlock(&mutex_);
        return kErrorItemExist;
    }
    pthread_mutex_unlock(&mutex_);
    return kOK;
}
JsonConfigErrors JsonConfigContent::insert_item_bool(const string& key, bool default_value)
{
    pthread_mutex_lock(&mutex_);
    if (initialized_) {
        pthread_mutex_unlock(&mutex_);
        return kErrorItemsInitialized;
    }

    pair<map<string, bool>::iterator, bool> ret = key_bool_items_.insert(map<string, bool>::value_type(key, default_value));
    if (!ret.second) {
        pthread_mutex_unlock(&mutex_);
        return kErrorItemExist;
    }
    pthread_mutex_unlock(&mutex_);
    return kOK;
}
JsonConfigErrors JsonConfigContent::insert_item_int(const string& key, int default_value, int low, int hi)
{
    pthread_mutex_lock(&mutex_);
    if (initialized_) {
        pthread_mutex_unlock(&mutex_);
        return kErrorItemsInitialized;
    }

    pair<map<string, int>::iterator, bool> ret = key_int_items_.insert(map<string, int>::value_type(key, default_value));
    if (!ret.second) {
        pthread_mutex_unlock(&mutex_);
        return kErrorItemExist;
    }
    pthread_mutex_unlock(&mutex_);
    return kOK;
}
JsonConfigErrors JsonConfigContent::insert_item_int64(const string& key, int64_t default_value, int64_t low, int64_t hi)
{
    pthread_mutex_lock(&mutex_);
    if (initialized_) {
        pthread_mutex_unlock(&mutex_);
        return kErrorItemsInitialized;
    }

    pair<map<string, int64_t>::iterator, bool> ret = key_int64_items_.insert(map<string, int64_t>::value_type(key, default_value));
    if (!ret.second) {
        pthread_mutex_unlock(&mutex_);
        return kErrorItemExist;
    }
    pthread_mutex_unlock(&mutex_);
    return kOK;
}
JsonConfigErrors JsonConfigContent::insert_item_double(const string& key, double default_value, double low, double hi)
{
    pthread_mutex_lock(&mutex_);
    if (initialized_) {
        pthread_mutex_unlock(&mutex_);
        return kErrorItemsInitialized;
    }

    pair<map<string, double>::iterator, bool> ret = key_double_items_.insert(map<string, double>::value_type(key, default_value));
    if (!ret.second) {
        pthread_mutex_unlock(&mutex_);
        return kErrorItemExist;
    }
    pthread_mutex_unlock(&mutex_);
    return kOK;
}

bool JsonConfigContent::validate_configs(Json::Value& config_items)
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

Json::Value JsonConfigContent::copy_config_items()
{
    pthread_mutex_lock(&mutex_);
    Json::Value val = config_items_;
    pthread_mutex_unlock(&mutex_);
    return val;
}

JsonConfigErrors JsonConfigContent::get_value(const string& key, JsonConfigItemType type, JsonConfigItemValue val)
{
    pthread_mutex_lock(&mutex_);
    if (!initialized_) {
        pthread_mutex_unlock(&mutex_);
        return kErrorNotInitialize;
    }

    if (config_items_[key].empty()) {
        pthread_mutex_unlock(&mutex_);
        return kErrorItemNotExist;
    }

    switch (type)
    {
    case kItemTypeString:
        if (!config_items_[key].isString()) {
            pthread_mutex_unlock(&mutex_);
            return kErrorItemNotExist;
        }
        val.s = config_items_[key].asString();
        break;
    case kItemTypeInt:
        if (!config_items_[key].isInt()) {
            pthread_mutex_unlock(&mutex_);
            return kErrorItemNotExist;
        }
        val.nv.i = config_items_[key].asInt();
        break;
    case kItemTypeInt64:
        if (!config_items_[key].isInt64()) {
            pthread_mutex_unlock(&mutex_);
            return kErrorItemNotExist;
        }
        val.nv.i64 = config_items_[key].asInt64();
        break;
    case kItemTypeDouble:
        if (!config_items_[key].isDouble()) {
            pthread_mutex_unlock(&mutex_);
            return kErrorItemNotExist;
        }
        val.nv.d = config_items_[key].asDouble();
        break;
    case kItemTypeBool:
        if (!config_items_[key].isBool()) {
            pthread_mutex_unlock(&mutex_);
            return kErrorItemNotExist;
        }
        val.b = config_items_[key].asBool();
        break;
    default:
        JSON_CONFIG_ASSERT(0);
        break;
    }

    pthread_mutex_unlock(&mutex_);
    return kOK;
}

JsonConfigErrors JsonConfigContent::set_value(const string& key, JsonConfigItemType type, const JsonConfigItemValue& val)
{
    pthread_mutex_lock(&mutex_);
    if (!initialized_) {
        pthread_mutex_unlock(&mutex_);
        return kErrorNotInitialize;
    }

    if (config_items_[key].empty()) {
        pthread_mutex_unlock(&mutex_);
        return kErrorItemNotExist;
    }

    switch (type)
    {
    case kItemTypeString:
        if (0 == config_items_[key].asString().compare(val.s)) {
            pthread_mutex_unlock(&mutex_);
            return kOK;
        }
        config_items_[key] = val.s;
        break;
    case kItemTypeInt:
        if (config_items_[key].asInt() == val.nv.i) {
            pthread_mutex_unlock(&mutex_);
            return kOK;
        }
        config_items_[key] = val.nv.i;
        break;
    case kItemTypeInt64:
        if (config_items_[key].asInt64() == val.nv.i64) {
            pthread_mutex_unlock(&mutex_);
            return kOK;
        }
        config_items_[key] = val.nv.i64;
        break;
    case kItemTypeDouble:
        if (config_items_[key].asDouble() == val.nv.d) {
            pthread_mutex_unlock(&mutex_);
            return kOK;
        }
        config_items_[key] = val.nv.d;
        break;
    case kItemTypeBool:
        if (config_items_[key].asBool() == val.b) {
            pthread_mutex_unlock(&mutex_);
            return kOK;
        }
        config_items_[key] = val.b;
        break;
    default:
        JSON_CONFIG_ASSERT(0);
        break;
    }
    pthread_mutex_unlock(&mutex_);

    return save(copy_config_items());
}

JsonConfigErrors JsonConfigContent::initialize_load()
{
    pthread_mutex_lock(&mutex_);
    if (initialized_) { //only allow to invoke once.
        pthread_mutex_unlock(&mutex_);
        return kErrorMultipleInitialize;
    }
    initialized_ = true;
    pthread_mutex_unlock(&mutex_);

    bool require_save = false;

    Json::Value load_config_items;
    JsonConfigErrors err = load(load_config_items);
    if (err != kOK){
        //load error, require save to file
        require_save = true;
    }
    if (validate_configs(load_config_items)) {
        //anything changed, require save to file
        require_save = true;
    }

    //initialize config items
    pthread_mutex_lock(&mutex_);
    config_items_ = load_config_items;
    pthread_mutex_unlock(&mutex_);

    err = kOK;
    if (require_save) {
        err = save(load_config_items);
    }

    return err;
}

JsonConfigErrors JsonConfigContent::save(const Json::Value& in)
{
    pthread_mutex_lock(&config_file_mutex_);
    ofstream ofs(config_file_path_.c_str(), ios::binary | ios::trunc);
    if (!ofs)
    {
        pthread_mutex_unlock(&config_file_mutex_);
        return kErrorOpenFileWithWriteFailed;
    }
    else {
        Json::StyledStreamWriter stream_writer;
        stream_writer.write(ofs, in);
        ofs.close();
    }
    pthread_mutex_unlock(&config_file_mutex_);
    return kOK;
}

JsonConfigErrors JsonConfigContent::load(Json::Value& out)
{
    // read all from file
    pthread_mutex_lock(&config_file_mutex_);
    ifstream ifs(config_file_path_.c_str(), ios::binary);
    if (!ifs) {
        pthread_mutex_unlock(&config_file_mutex_);
        return kErrorOpenFileWithReadFailed;
    }

    //read content from file
    string config_str;
    ifs.seekg(0, std::ios::end);
    config_str.reserve(ifs.tellg());
    ifs.seekg(0, std::ios::beg);
    config_str.assign((std::istreambuf_iterator<char>(ifs)),
        std::istreambuf_iterator<char>());
    ifs.close();
    pthread_mutex_unlock(&config_file_mutex_);

    Json::Reader config_reader;
    if (!config_reader.parse(config_str, out)) {
        return kErrorJsonParseFailed;
    }

    return kOK;
}
