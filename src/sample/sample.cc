
#include "libjson_config/json_config.h"
#include "sample.h"

using namespace std;

void json_config_sample()
{
    int jc_major = 0, jc_minor = 0;
    const char * jc_ver_str = libjson_config_version(&jc_major, &jc_minor);
    printf("libjson_config major %d minor %d.\n", jc_major, jc_minor);
    printf("%s\n", jc_ver_str);

    JsonConfig *jc = new JsonConfig("sample.cfg");

    jc->insert_item_string(SAMPLE_CONFIG_STRING_KEY_NAME, SAMPLE_CONFIG_STRING_VALUE_NAME);
    jc->insert_item_string(SAMPLE_CONFIG_STRING_KEY_BIO, SAMPLE_CONFIG_STRING_VALUE_BIO);
    jc->insert_item(SAMPLE_CONFIG_BOOL_KEY_SEX, SAMPLE_CONFIG_BOOL_VALUE_SEX);
    jc->insert_item(SAMPLE_CONFIG_INT_KEY_AGE, SAMPLE_CONFIG_INT_VALUE_AGE_DEFAULT, SAMPLE_CONFIG_INT_VALUE_AGE_LOW, SAMPLE_CONFIG_INT_VALUE_AGE_HI);
    jc->insert_item(SAMPLE_CONFIG_DOUBLE_KEY_HEIGHT, SAMPLE_CONFIG_DOUBLE_VALUE_HEIGHT_DEFAULT, SAMPLE_CONFIG_DOUBLE_VALUE_HEIGHT_LOW, SAMPLE_CONFIG_DOUBLE_VALUE_HEIGHT_HI);
    jc->insert_item_int64(SAMPLE_CONFIG_INT64_KEY_THE_BOOK_BYTES, SAMPLE_CONFIG_INT64_VALUE_THE_BOOK_BYTES);

    jc->initialize();

    printf("sample:%d items\n%s\n\n", (int)jc->size(), jc->dump().c_str());

    jc->set_value_string(SAMPLE_CONFIG_STRING_KEY_NAME, "Lucy");
    jc->set_value_string(SAMPLE_CONFIG_STRING_KEY_BIO, "sale");
    jc->set_value(SAMPLE_CONFIG_BOOL_KEY_SEX, false);
    jc->set_value(SAMPLE_CONFIG_INT_KEY_AGE, 25);
    jc->set_value(SAMPLE_CONFIG_DOUBLE_KEY_HEIGHT, 1.65f);
    jc->set_value_int64(SAMPLE_CONFIG_INT64_KEY_THE_BOOK_BYTES, 20000000000LL);

    printf("sample(after changed):%d items\n%s\n\n", (int)jc->size(), jc->dump().c_str());

    printf("sample peek one by one:\n");
    printf("%s->%s\n", SAMPLE_CONFIG_STRING_KEY_NAME, jc->value_string(SAMPLE_CONFIG_STRING_KEY_NAME).c_str());
    printf("%s->%s\n", SAMPLE_CONFIG_STRING_KEY_BIO, jc->value_string(SAMPLE_CONFIG_STRING_KEY_BIO).c_str());
    printf("%s->%s\n", SAMPLE_CONFIG_BOOL_KEY_SEX, jc->value_bool(SAMPLE_CONFIG_BOOL_KEY_SEX) ? "true" : "false");
    printf("%s->%d\n", SAMPLE_CONFIG_INT_KEY_AGE, jc->value_int(SAMPLE_CONFIG_INT_KEY_AGE));
    printf("%s->%f\n", SAMPLE_CONFIG_DOUBLE_KEY_HEIGHT, jc->value_double(SAMPLE_CONFIG_DOUBLE_KEY_HEIGHT));
    printf("%s->%lld\n", SAMPLE_CONFIG_INT64_KEY_THE_BOOK_BYTES, jc->value_int64(SAMPLE_CONFIG_INT64_KEY_THE_BOOK_BYTES));


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