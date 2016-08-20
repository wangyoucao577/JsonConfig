#pragma once

#include <stdio.h>
#include <assert.h>
#include <string>

using namespace std;

#define JSON_CONFIG_TEST_LOG(type, ...) printf(type, ##__VA_ARGS__)
#define JSON_CONFIG_TEST_ASSERT(cond) assert(cond)

string generate_rand_str(int len);