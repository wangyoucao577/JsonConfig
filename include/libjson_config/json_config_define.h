/**
@file json_config_define.h
@brief definitions of libjson_config
@author wangyoucao577
@version 0.1.0
@date 2016-08-08
*/

#pragma once

typedef long long int64_t;


#if defined(_MSC_VER)   //on Windows
#if defined(JSON_CONFIG_DLL_BUILD)
#define JSON_CONFIG_API __declspec(dllexport)
#else
#define JSON_CONFIG_API __declspec(dllimport)
#endif
#elif defined(__linux__)
//TODO: 
#endif
#if !defined(JSON_CONFIG_API)
#define JSON_CONFIG_API
#endif

