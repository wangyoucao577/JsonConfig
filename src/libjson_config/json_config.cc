
#include "json_config.h"
#include "json_config_content.h"

JsonConfig::JsonConfig(string config_file_path) :
config_content_(new JsonConfigContent(config_file_path))
{

}
JsonConfig::~JsonConfig()
{

}

bool JsonConfig::insert_item(const string& key, string default_value)
{
    return config_content_->insert_config_item(key, default_value);
}
bool JsonConfig::insert_item(const string& key, bool default_value)
{
    return config_content_->insert_config_item(key, default_value);

}
bool JsonConfig::insert_item(const string& key, int default_value, int low, int hi)
{
    return config_content_->insert_config_item(key, default_value);
}
bool JsonConfig::insert_item_int64(const string& key, int64_t default_value, int64_t low, int64_t hi)
{
    return config_content_->insert_config_item(key, default_value);
}
bool JsonConfig::insert_item(const string& key, double default_value)
{
    return config_content_->insert_config_item(key, default_value);
}

bool JsonConfig::initialize_load()
{
    return config_content_->initialize_load();
}

bool JsonConfig::set_value(const string& key, string val)
{
    return config_content_->set_value(key, val);
}
bool JsonConfig::set_value(const string& key, bool val)
{
    return config_content_->set_value(key, val);

}
bool JsonConfig::set_value(const string& key, int val)
{
    return config_content_->set_value(key, val);

}
bool JsonConfig::set_value_int64(const string& key, int64_t val)
{
    return config_content_->set_value(key, val);

}
bool JsonConfig::set_value(const string& key, double val)
{
    return config_content_->set_value(key, val);

}

bool JsonConfig::get_value(const string& key, string& val)
{
    return config_content_->set_value(key, val);

}
bool JsonConfig::get_value(const string& key, bool& val)
{
    return config_content_->get_value(key, val);

}
bool JsonConfig::get_value(const string& key, int&val)
{
    return config_content_->get_value(key, val);

}
bool JsonConfig::get_value_int64(const string& key, int64_t& val)
{
    return config_content_->get_value(key, val);

}
bool JsonConfig::get_value(const string& key, double& val)
{
    return config_content_->get_value(key, val);

}

void JsonConfig::get_last_error(JsonConfigErrors& error_code, string& msg)
{
    return config_content_->get_last_error(error_code, msg);

}
