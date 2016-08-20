#include "libjson_config/json_config.h"
#include "test_case_boundary.h"

int main()
{
    printf("libjson_config test start.\n");
    int jc_major = 0, jc_minor = 0;
    const char * jc_ver_str = JsonConfig::libjson_config_version(&jc_major, &jc_minor);
    printf("libjson_config version major %d minor %d.\n", jc_major, jc_minor);
    printf("%s\n\n", jc_ver_str);

    boundary_test_suite();


    //wait before return
    printf("All test cases passed!\n\n Please press any key to continue...");
    char a;
    scanf_s("%c", &a, (int)sizeof(a));
    return 0;
}