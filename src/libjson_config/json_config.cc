
#include "json_config.h"
#include "json_config_content.h"

JsonConfig::JsonConfig(string config_file_path) :
config_content_(new JsonConfigContent(config_file_path))
{

}
JsonConfig::~JsonConfig()
{

}

JsonConfigErrors JsonConfig::insert_item(const string& key, string default_value)
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

JsonConfigErrors JsonConfig::initialize_load()
{
    return config_content_->initialize_load();
}

JsonConfigErrors JsonConfig::set_value(const string& key, string val)
{
    ValuesSet item_val;
    item_val.s = val;
    return config_content_->set_value(key, kItemTypeString, item_val);
}
JsonConfigErrors JsonConfig::set_value(const string& key, bool val)
{
    ValuesSet item_val;
    item_val.b = val;
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

JsonConfigErrors JsonConfig::get_value(const string& key, string& val)
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

