#pragma once

#include "EflCpp/assert.h"
#include "EflCpp/log.h"

#include <string>

namespace EflCpp
{

namespace Details
{

template <typename T>
struct EventLogger
{

    EventLogger(const char* objId, const T& event)
        : _objId(objId)
        , _event(event)
    {
        EFLCPP_ASSERT(objId);
        EFLCPP_LOG_TRACE << _objId << " - Handling " << _event;
    }

    ~EventLogger()
    {
        EFLCPP_LOG_TRACE << _objId << " - Handling " << _event << " done";
    }

    const char* _objId;
    const T& _event;
};

} // namespace Details

template <typename T>
Details::EventLogger<T> logEvent(const char* objId, const T& event)
{
    return Details::EventLogger<T>(objId, event);
}

} // namespace EflCpp
