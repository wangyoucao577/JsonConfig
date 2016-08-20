#include "libjson_config/json_config.h"

int main()
{
    int jc_major = 0, jc_minor = 0;
    const char * jc_ver_str = JsonConfig::libjson_config_version(&jc_major, &jc_minor);
    printf("libjson_config major %d minor %d.\n", jc_major, jc_minor);
    printf("%s\n", jc_ver_str);

    //wait before return
    printf("Please press any key to continue...");
    char a;
    scanf_s("%c", &a, (int)sizeof(a));
    return 0;
}