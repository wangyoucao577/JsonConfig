
#include <fstream>
#include "json_config_content.h"
#include "json_config.h"


ValuesSet::ValuesSet() :
b(false)
{
    memset(&nv, 0, sizeof(nv));
}
ValuesSet::ValuesSet(string val) : 
s(val),
b(false)
{
    memset(&nv, 0, sizeof(nv));
}
ValuesSet::ValuesSet(bool val) :
b(val)
{
    memset(&nv, 0, sizeof(nv));
}

NumericScope::NumericScope()
{
    memset(&default, 0, sizeof(default));
    memset(&low, 0, sizeof(low));
    memset(&hi, 0, sizeof(hi));
}
void NumericScope::set_int(int def, int low, int hi)
{
    this->default.i = def;
    this->low.i = low;
    this->hi.i = hi;
}
void NumericScope::set_int64(int64_t def, int64_t low, int64_t hi)
{
    this->default.i64 = def;
    this->low.i64 = low;
    this->hi.i64 = hi;
}
void NumericScope::set_double(double def, double low, double hi)
{
    this->default.d = def;
    this->low.d = low;
    this->hi.d = hi;

}


JsonConfigContent::JsonConfigContent(string config_file_path) :
    config_file_path_(config_file_path),
    initialized_(false),
    initialize_called(false)
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
    if (initialized_ || initialize_called) {
        pthread_mutex_unlock(&mutex_);
        JSON_CONFIG_ASSERT(0);
        return kErrorItemsInitialized;
    }

    if (is_key_exist_unsafe(key)) {
        pthread_mutex_unlock(&mutex_);
        JSON_CONFIG_ASSERT(0);
        return kErrorItemExist;
    }

    key_string_items_.insert(map<string, string>::value_type(key, default_value));
    pthread_mutex_unlock(&mutex_);
    return kOK;
}
JsonConfigErrors JsonConfigContent::insert_item_bool(const string& key, bool default_value)
{
    pthread_mutex_lock(&mutex_);
    if (initialized_ || initialize_called) {
        pthread_mutex_unlock(&mutex_);
        JSON_CONFIG_ASSERT(0);
        return kErrorItemsInitialized;
    }

    if (is_key_exist_unsafe(key)) {
        pthread_mutex_unlock(&mutex_);
        JSON_CONFIG_ASSERT(0);
        return kErrorItemExist;
    }

    key_bool_items_.insert(map<string, bool>::value_type(key, default_value));
    pthread_mutex_unlock(&mutex_);
    return kOK;
}
JsonConfigErrors JsonConfigContent::insert_item_int(const string& key, int default_value, int low, int hi)
{
    JSON_CONFIG_ASSERT(clamp_int(default_value, low, hi));

    pthread_mutex_lock(&mutex_);
    if (initialized_ || initialize_called) {
        pthread_mutex_unlock(&mutex_);
        JSON_CONFIG_ASSERT(0);
        return kErrorItemsInitialized;
    }

    if (is_key_exist_unsafe(key)) {
        pthread_mutex_unlock(&mutex_);
        JSON_CONFIG_ASSERT(0);
        return kErrorItemExist;
    }

    NumericScope val;
    val.set_int(default_value, low, hi);
    key_int_items_.insert(map<string, NumericScope>::value_type(key, val));
    pthread_mutex_unlock(&mutex_);
    return kOK;
}
JsonConfigErrors JsonConfigContent::insert_item_int64(const string& key, int64_t default_value, int64_t low, int64_t hi)
{
    JSON_CONFIG_ASSERT(clamp_int64(default_value, low, hi));

    pthread_mutex_lock(&mutex_);
    if (initialized_ || initialize_called) {
        pthread_mutex_unlock(&mutex_);
        JSON_CONFIG_ASSERT(0);
        return kErrorItemsInitialized;
    }

    if (is_key_exist_unsafe(key)) {
        pthread_mutex_unlock(&mutex_);
        JSON_CONFIG_ASSERT(0);
        return kErrorItemExist;
    }

    NumericScope val;
    val.set_int64(default_value, low, hi);
    key_int64_items_.insert(map<string, NumericScope>::value_type(key, val));
    pthread_mutex_unlock(&mutex_);
    return kOK;
}
JsonConfigErrors JsonConfigContent::insert_item_double(const string& key, double default_value, double low, double hi)
{
    JSON_CONFIG_ASSERT(clamp_double(default_value, low, hi));

    pthread_mutex_lock(&mutex_);
    if (initialized_ || initialize_called) {
        pthread_mutex_unlock(&mutex_);
        JSON_CONFIG_ASSERT(0);
        return kErrorItemsInitialized;
    }

    if (is_key_exist_unsafe(key)) {
        pthread_mutex_unlock(&mutex_);
        JSON_CONFIG_ASSERT(0);
        return kErrorItemExist;
    }

    NumericScope val;
    val.set_double(default_value, low, hi);
    key_double_items_.insert(map<string, NumericScope>::value_type(key, val));
    pthread_mutex_unlock(&mutex_);
    return kOK;
}

bool JsonConfigContent::validate_configs_unsafe(Json::Value& config_items)
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

    for (map<string, NumericScope>::iterator it = key_int_items_.begin(); it != key_int_items_.end(); ++it) {
        if (    config_items[it->first].empty()
            || !config_items[it->first].isInt()
            || !clamp_int(config_items[it->first].asInt(), it->second.low.i, it->second.hi.i)){
            config_items[it->first] = it->second.default.i;
            anything_changed = true;
        }
    }

    for (map<string, NumericScope>::iterator it = key_int64_items_.begin(); it != key_int64_items_.end(); ++it) {
        if (    config_items[it->first].empty() 
            || !config_items[it->first].isInt64()
            || !clamp_int64(config_items[it->first].asInt64(), it->second.low.i64, it->second.hi.i64)) {
            config_items[it->first] = it->second.default.i64;
            anything_changed = true;
        }
    }

    for (map <string, NumericScope> ::iterator it = key_double_items_.begin(); it != key_double_items_.end(); ++it) {
        if (    config_items[it->first].empty() 
            || !config_items[it->first].isDouble()
            || !clamp_double(config_items[it->first].asDouble(), it->second.low.d, it->second.hi.d)) {
            config_items[it->first] = it->second.default.d;
            anything_changed = true;
        }
    }
    return anything_changed;
}

Json::Value JsonConfigContent::get_config_items()
{
    pthread_mutex_lock(&mutex_);
    Json::Value val = config_items_;
    pthread_mutex_unlock(&mutex_);
    return val;
}


JsonConfigErrors JsonConfigContent::get_value(const string& key, JsonConfigItemType type, ValuesSet val)
{
    pthread_mutex_lock(&mutex_);
    if (!initialized_) {
        pthread_mutex_unlock(&mutex_);
        return kErrorNotInitialize;
    }

    if (config_items_[key].empty()) {
        pthread_mutex_unlock(&mutex_);
        JSON_CONFIG_ASSERT(0);
        return kErrorItemNotExist;
    }

    switch (type)
    {
    case kItemTypeString:
        if (!config_items_[key].isString()) {
            pthread_mutex_unlock(&mutex_);
            JSON_CONFIG_ASSERT(0);
            return kErrorValueTypeUnmatch;
        }
        val.s = config_items_[key].asString();
        break;
    case kItemTypeInt:
        if (!config_items_[key].isInt()) {
            pthread_mutex_unlock(&mutex_);
            JSON_CONFIG_ASSERT(0);
            return kErrorValueTypeUnmatch;
        }
        val.nv.i = config_items_[key].asInt();
        break;
    case kItemTypeInt64:
        if (!config_items_[key].isInt64()) {
            pthread_mutex_unlock(&mutex_);
            JSON_CONFIG_ASSERT(0);
            return kErrorValueTypeUnmatch;
        }
        val.nv.i64 = config_items_[key].asInt64();
        break;
    case kItemTypeDouble:
        if (!config_items_[key].isDouble()) {
            pthread_mutex_unlock(&mutex_);
            JSON_CONFIG_ASSERT(0);
            return kErrorValueTypeUnmatch;
        }
        val.nv.d = config_items_[key].asDouble();
        break;
    case kItemTypeBool:
        if (!config_items_[key].isBool()) {
            pthread_mutex_unlock(&mutex_);
            JSON_CONFIG_ASSERT(0);
            return kErrorValueTypeUnmatch;
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

JsonConfigErrors JsonConfigContent::set_value(const string& key, JsonConfigItemType type, const ValuesSet& val)
{
    pthread_mutex_lock(&mutex_);
    if (!initialized_) {
        pthread_mutex_unlock(&mutex_);
        return kErrorNotInitialize;
    }

    if (config_items_[key].empty()) {
        pthread_mutex_unlock(&mutex_);
        JSON_CONFIG_ASSERT(0);
        return kErrorItemNotExist;
    }

    switch (type)
    {
    case kItemTypeString:
        if (!config_items_[key].isString()) {
            pthread_mutex_unlock(&mutex_);
            JSON_CONFIG_ASSERT(0);
            return kErrorValueTypeUnmatch;
        }
        if (0 == config_items_[key].asString().compare(val.s)) {
            pthread_mutex_unlock(&mutex_);
            return kOK;
        }
        config_items_[key] = val.s;
        break;
    case kItemTypeInt:
        if (!config_items_[key].isInt()) {
            pthread_mutex_unlock(&mutex_);
            JSON_CONFIG_ASSERT(0);
            return kErrorValueTypeUnmatch;
        }
        if (config_items_[key].asInt() == val.nv.i) {
            pthread_mutex_unlock(&mutex_);
            return kOK;
        }
        if (!clamp_int(val.nv.i, key_int_items_[key].low.i, key_int_items_[key].hi.i)) {
            pthread_mutex_unlock(&mutex_);
            return kErrorValueOutofRange;
        }
        config_items_[key] = val.nv.i;
        break;
    case kItemTypeInt64:
        if (!config_items_[key].isInt64()) {
            pthread_mutex_unlock(&mutex_);
            JSON_CONFIG_ASSERT(0);
            return kErrorValueTypeUnmatch;
        }
        if (config_items_[key].asInt64() == val.nv.i64) {
            pthread_mutex_unlock(&mutex_);
            return kOK;
        }
        if (!clamp_int64(val.nv.i64, key_int64_items_[key].low.i64, key_int64_items_[key].hi.i64)) {
            pthread_mutex_unlock(&mutex_);
            return kErrorValueOutofRange;
        }
        config_items_[key] = val.nv.i64;
        break;
    case kItemTypeDouble:
        if (!config_items_[key].isDouble()) {
            pthread_mutex_unlock(&mutex_);
            JSON_CONFIG_ASSERT(0);
            return kErrorValueTypeUnmatch;
        }
        if (config_items_[key].asDouble() == val.nv.d) {
            pthread_mutex_unlock(&mutex_);
            return kOK;
        }
        if (!clamp_double(val.nv.d, key_double_items_[key].low.d, key_double_items_[key].hi.d)) {
            pthread_mutex_unlock(&mutex_);
            return kErrorValueOutofRange;
        }
        config_items_[key] = val.nv.d;
        break;
    case kItemTypeBool:
        if (!config_items_[key].isBool()) {
            pthread_mutex_unlock(&mutex_);
            JSON_CONFIG_ASSERT(0);
            return kErrorValueTypeUnmatch;
        }
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

    return save(get_config_items());
}

JsonConfigErrors JsonConfigContent::initialize_load()
{
    pthread_mutex_lock(&mutex_);
    if (initialized_ || initialize_called) { //only allow to invoke once.
        pthread_mutex_unlock(&mutex_);
        JSON_CONFIG_ASSERT(0);
        return kErrorMultipleInitialize;
    }
    if (key_count_unsafe() <= 0) {
        pthread_mutex_unlock(&mutex_);
        JSON_CONFIG_ASSERT(0);
        return kErrorNoItem;
    }
    initialize_called = true;
    pthread_mutex_unlock(&mutex_);

    bool require_save = false;

    Json::Value load_config_items;
    JsonConfigErrors err = load(load_config_items);
    if (err != kOK){
        //load error, require save to file
        require_save = true;
    }

    pthread_mutex_lock(&mutex_);
    if (validate_configs_unsafe(load_config_items)) {
        //anything changed, require save to file
        require_save = true;
    }

    //initialize config items
    config_items_ = load_config_items;
    initialized_ = true;
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
        return kErrorConfigFileParseFailed;
    }

    return kOK;
}

bool JsonConfigContent::clamp_int(int val, int low, int hi)
{
    if (val >= low && val <= hi) {
        return true;
    }
    return false;
}
bool JsonConfigContent::clamp_int64(int64_t val, int64_t low, int64_t hi)
{
    if (val >= low && val <= hi) {
        return true;
    }
    return false;
}
bool JsonConfigContent::clamp_double(double val, double low, double hi)
{
    if (val >= low && val <= hi) {
        return true;
    }
    return false;
}

bool JsonConfigContent::is_key_exist_unsafe(const string& key)
{
    if (   key_string_items_.find(key) == key_string_items_.end()
        && key_bool_items_.find(key) == key_bool_items_.end()
        && key_int_items_.find(key) == key_int_items_.end()
        && key_int64_items_.find(key) == key_int64_items_.end()
        && key_double_items_.find(key) == key_double_items_.end()) {
        return false;
    }
    return true;
}

string JsonConfigContent::dump()
{
    pthread_mutex_lock(&mutex_);
    if (!initialized_) {
        pthread_mutex_unlock(&mutex_);
        JSON_CONFIG_ASSERT(0);
        return "";
    }
    pthread_mutex_unlock(&mutex_);

    return get_config_items().toStyledString();
}

int JsonConfigContent::size()
{
    pthread_mutex_lock(&mutex_);
    if (!initialized_) {
        pthread_mutex_unlock(&mutex_);
        JSON_CONFIG_ASSERT(0);
        return 0;
    }
    int key_count = key_count_unsafe();
    pthread_mutex_unlock(&mutex_);

    return key_count;
}

int JsonConfigContent::key_count_unsafe()
{
    int key_count = (key_string_items_.size() + key_int_items_.size()
        + key_int64_items_.size() + key_double_items_.size()
        + key_bool_items_.size());
    return key_count;
}