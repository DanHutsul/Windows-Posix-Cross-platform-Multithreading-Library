//
// Created by Dandelonium on 6/10/2021.
//

#ifndef PART1_UNIVERSALFUTURE_H
#define PART1_UNIVERSALFUTURE_H


#include <stdbool.h>
#include <windows.h>
#include <pthread.h>
#include <time.h>

#include <stdexcept>
#include <memory>


template <typename TValue>
class universalFuture {
private:
    std::shared_ptr<TValue*> value_ptr;

    void assert_valid_access()
    {
        if(!has_value())
            throw std::runtime_error("Attempting to access a non-set value from a future");
    }

public:
    universalFuture() : value_ptr(std::make_shared<TValue*>()) {}

    void set(TValue &value) {
        *value_ptr.get() = &value;
    }

    TValue& get() {
        assert_valid_access();
        return **value_ptr;
    }

    TValue* operator->() {
        assert_valid_access();
        return *value_ptr;
    }

    bool has_value() {
        return value_ptr.get() != nullptr;
    }
};

#endif //PART1_UNIVERSALFUTURE_H
