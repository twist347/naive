#pragma once

#include <iostream>

struct Log {
    Log() {
        std::cout << "Log()\n";
    }

    ~Log() {
        std::cout << "~Log()\n";
    }

    Log(const Log &) {
        std::cout << "Log(const Log &)\n";
    }

    Log &operator=(const Log &) {
        std::cout << "Log& operator=(const Log &)\n";
        return *this;
    }

    Log(Log &&) noexcept {
        std::cout << "Log(Log &&)\n";
    }

    Log &operator=(Log &&) noexcept {
        std::cout << "Log& operator=(Log &&)\n";
        return *this;
    }
};