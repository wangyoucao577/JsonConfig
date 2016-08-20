
#include "test_case_boundary.h"

const static char * kNull = NULL;

const static string kNullStr = "";
const static string kVeryLongStr = \
"long_string_0123456789_abcdefghijklmnopqrstuvwxyz_ABCDEFGHIJKLMNOPQRSTUVWXYZ";
const static string kNormalStr[] = \
{"normal_string_1", "normal_string_2", "normal_string_3", "normal_string_4", "normal_string_5"};

void string_interface_key_boundary_test()
{
    JsonConfig* jc = NULL;

    jc = new JsonConfig("key_boundary_string.test");
    jc->insert_item_string(kNullStr, kNormalStr[0]);
    jc->insert_item_string(kVeryLongStr, kNormalStr[1]);
    jc->initialize();

    string val_0 = jc->value_string(kNullStr);
    JSON_CONFIG_TEST_ASSERT(val_0 == kNormalStr[0]);
    string val_1 = jc->value_string(kVeryLongStr);
    JSON_CONFIG_TEST_ASSERT(val_1 == kNormalStr[1]);

    jc->set_value_string(kNullStr, kNormalStr[2]);
    jc->set_value_string(kVeryLongStr, kNormalStr[3]);

    string val_2, val_3;
    JsonConfigErrors err = jc->get_value_string(kNullStr, val_2);
    JSON_CONFIG_TEST_ASSERT(err == kOK);
    JSON_CONFIG_TEST_ASSERT(val_2 == kNormalStr[2]);

    err = jc->get_value_string(kVeryLongStr, val_3);
    JSON_CONFIG_TEST_ASSERT(err == kOK);
    JSON_CONFIG_TEST_ASSERT(val_3 == kNormalStr[3]);

    delete jc;
    jc = NULL;


}


void boundary_test_suite()
{
    string_interface_key_boundary_test();
}