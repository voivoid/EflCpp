#pragma once

#define DISABLE_COPY_SEMANTICS(klass) \
    klass(const klass&) = delete;     \
    klass& operator=(const klass&) = delete;

#define DISABLE_MOVE_SEMANTICS(klass) \
    klass(klass&&) = delete;          \
    klass& operator=(klass&&) = delete;

#define DISABLE_COPY_MOVE_SEMANTICS(klass) \
    DISABLE_COPY_SEMANTICS(klass)          \
    DISABLE_MOVE_SEMANTICS(klass)
