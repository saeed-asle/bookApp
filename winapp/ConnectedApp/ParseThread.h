#pragma once
#ifndef PARSETHREAD_H
#define PARSETHREAD_H

#include "CommonObject.h"
#include "nlohmann/json.hpp"
#include <iostream>

class ParseThread {
public:
    void operator()(CommonObjects& common);
};

#endif // PARSETHREAD_H
