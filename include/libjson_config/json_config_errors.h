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

