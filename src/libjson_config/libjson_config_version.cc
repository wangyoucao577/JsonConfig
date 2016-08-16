
#include "libjson_config_version.h"
#include "libjson_config/json_config.h"

const static char* kLibJsonConfigVersionString = LIBJSON_CONFIG_VERSION_STRING_EX;

const char * libjson_config_version(int* major, int* minor)
{
    if (major) {
        *major = LIBJSON_CONFIG_VERSION_MAJOR;
    }
    if (minor) {
        *minor = LIBJSON_CONFIG_VERSION_MINOR;
    }
    return kLibJsonConfigVersionString;
}
