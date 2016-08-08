/**
@file json_config_errors.h
@brief errors definition of libjson_config
@author wangyoucao577
@version 0.1.0
@date 2016-08-08
*/

#pragma once

enum JsonConfigErrors {
    kOK = 0,

    kErrorOffset = 10001,

    kErrorNotInitialize,
    kErrorNoItem,
    kErrorItemsInitialized,
    kErrorMultipleInitialize,
    kErrorItemExist,
    kErrorItemNotExist,

    kErrorValueOutofRange,
    kErrorValueTypeUnmatch,

    kErrorOpenFileWithWriteFailed,
    kErrorOpenFileWithReadFailed,
    kErrorConfigFileParseFailed,

};

