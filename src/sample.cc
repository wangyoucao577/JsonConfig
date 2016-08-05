
#include "libjson_config/json_config.h"

void json_config_sample()
{
    //动态初始化配置的key-default_value对
    JsonConfig *jc = new JsonConfig("json.cfg");
    jc->insert_item("str_key_1", (string)"str_1");
    jc->insert_item("str_key_2", (string)"str_2");
    jc->insert_item("str_key_3", (string)"str_3");
    jc->insert_item("bool_key_4", false);
    jc->insert_item("bool_key_5", true);
    jc->insert_item("int_key_6", 0, 0, 1);
    jc->insert_item("int_key_7", -1, -10, 22);
    jc->insert_item("int_key_8", 99999, 0, 93);
    jc->insert_item_int64("int64_key_9", 11111111111111111111LL, 0LL, 11LL);
    jc->insert_item("double_key_10", 32423432.32);

    //从配置文件读取
    jc->initialize_load();

    jc->set_value("str_key_1", (string)"str_1_changed");
    bool ret = jc->set_value("str", "fail_test");

    JsonConfigErrors err = kOK;
    string err_msg;
    jc->get_last_error(err, err_msg);
}

int main()
{
    json_config_sample();

    //wait before return
    printf("Please press any key to continue...");
    char a;
    scanf_s("%c", &a, (int)sizeof(a));
    return 0;
}