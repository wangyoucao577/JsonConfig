
#include "json_config.h"
#include "json_config_content.h"

JsonConfig::JsonConfig(string config_file_path) :
config_content_(new JsonConfigContent(config_file_path))
{

}
JsonConfig::~JsonConfig()
{

}

JsonConfigErrors JsonConfig::insert_item_string(const string& key, string default_value)
{
    return config_content_->insert_item_string(key, default_value);
}
JsonConfigErrors JsonConfig::insert_item(const string& key, bool default_value)
{
    return config_content_->insert_item_bool(key, default_value);
}
JsonConfigErrors JsonConfig::insert_item(const string& key, int default_value, int low, int hi)
{
    return config_content_->insert_item_int(key, default_value, low, hi);
}
JsonConfigErrors JsonConfig::insert_item_int64(const string& key, int64_t default_value, int64_t low, int64_t hi)
{
    return config_content_->insert_item_int64(key, default_value, low, hi);
}
JsonConfigErrors JsonConfig::insert_item(const string& key, double default_value, double low, double hi)
{
    return config_content_->insert_item_double(key, default_value, low, hi);
}

JsonConfigErrors JsonConfig::initialize()
{
    return config_content_->initialize_load();
}

JsonConfigErrors JsonConfig::set_value_string(const string& key, string val)
{
    ValuesSet item_val(val);
    return config_content_->set_value(key, kItemTypeString, item_val);
}
JsonConfigErrors JsonConfig::set_value(const string& key, bool val)
{
    ValuesSet item_val(val);
    return config_content_->set_value(key, kItemTypeBool, item_val);
}
JsonConfigErrors JsonConfig::set_value(const string& key, int val)
{
    ValuesSet item_val;
    item_val.nv.i = val;
    return config_content_->set_value(key, kItemTypeInt, item_val);
}
JsonConfigErrors JsonConfig::set_value_int64(const string& key, int64_t val)
{
    ValuesSet item_val;
    item_val.nv.i64 = val;
    return config_content_->set_value(key, kItemTypeInt64, item_val);
}
JsonConfigErrors JsonConfig::set_value(const string& key, double val)
{
    ValuesSet item_val;
    item_val.nv.d = val;
    return config_content_->set_value(key, kItemTypeDouble, item_val);
}

JsonConfigErrors JsonConfig::get_value_string(const string& key, string& val)
{
    ValuesSet item_val;
    JsonConfigErrors err = config_content_->get_value(key, kItemTypeString, item_val);
    if (err == kOK) {
        val = item_val.s;
        return kOK;
    }
    return err;
}
JsonConfigErrors JsonConfig::get_value(const string& key, bool& val)
{
    ValuesSet item_val;
    JsonConfigErrors err = config_content_->get_value(key, kItemTypeBool, item_val);
    if (err == kOK) {
        val = item_val.b;
        return kOK;
    }
    return err;
}
JsonConfigErrors JsonConfig::get_value(const string& key, int&val)
{
    ValuesSet item_val;
    JsonConfigErrors err = config_content_->get_value(key, kItemTypeInt, item_val);
    if (err == kOK) {
        val = item_val.nv.i;
        return kOK;
    }
    return err;

}
JsonConfigErrors JsonConfig::get_value_int64(const string& key, int64_t& val)
{
    ValuesSet item_val;
    JsonConfigErrors err = config_content_->get_value(key, kItemTypeInt64, item_val);
    if (err == kOK) {
        val = item_val.nv.i64;
        return kOK;
    }
    return err;

}
JsonConfigErrors JsonConfig::get_value(const string& key, double& val)
{
    ValuesSet item_val;
    JsonConfigErrors err = config_content_->get_value(key, kItemTypeDouble, item_val);
    if (err == kOK) {
        val = item_val.nv.d;
        return kOK;
    }
    return err;
}

string JsonConfig::value_string(const string& key)
{
    string out_value;
    JsonConfigErrors err = get_value_string(key, out_value);
    if (err != kOK) {
        JSON_CONFIG_ASSERT(0);
        return "";
    }
    return out_value;
}
bool JsonConfig::value_bool(const string& key)
{
    bool out_value;
    JsonConfigErrors err = get_value(key, out_value);
    if (err != kOK) {
        JSON_CONFIG_ASSERT(0);
        return false;
    }
    return out_value;
}
double JsonConfig::value_double(const string& key)
{
    double out_value;
    JsonConfigErrors err = get_value(key, out_value);
    if (err != kOK) {
        JSON_CONFIG_ASSERT(0);
        return 0.0;
    }
    return out_value;
}
int JsonConfig::value_int(const string& key)
{
    int out_value;
    JsonConfigErrors err = get_value(key, out_value);
    if (err != kOK) {
        JSON_CONFIG_ASSERT(0);
        return 0;
    }
    return out_value;
}
int64_t JsonConfig::value_int64(const string& key)
{
    int64_t out_value;
    JsonConfigErrors err = get_value_int64(key, out_value);
    if (err != kOK) {
        JSON_CONFIG_ASSERT(0);
        return 0LL;
    }
    return out_value;
}

string JsonConfig::dump()
{
    return config_content_->dump();
}

int JsonConfig::size()
{
    return config_content_->size();
}