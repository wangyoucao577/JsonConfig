
#include "json_config.h"

void json_config_sample()
{
    //��̬��ʼ�����õ�key-default_value��
    JsonConfig *jc = new JsonConfig("json.cfg");
    jc->insert_config_item("str_key_1", (string)"str_1");
    jc->insert_config_item("str_key_2", (string)"str_2");
    jc->insert_config_item("str_key_3", (string)"str_3");
    jc->insert_config_item("bool_key_4", false);
    jc->insert_config_item("bool_key_5", true);
    jc->insert_config_item("int_key_6", 0);
    jc->insert_config_item("int_key_7", -1);
    jc->insert_config_item("int_key_8", 99999);
    jc->insert_config_item("int64_key_9", 11111111111111111111LL);
    jc->insert_config_item("double_key_10", 32423432.32);

    //�������ļ���ȡ
    jc->initialize_load();


}

int main()
{
    json_config_sample();

    return 0;
}