/*
 * Copyright (c) New Cloud Technologies, Ltd., 2013-2016
 *
 * You can not use the contents of the file in any way without
 * New Cloud Technologies, Ltd. written permission.
 *
 * To obtain such a permit, you should contact New Cloud Technologies, Ltd.
 * at http://ncloudtech.com/contact.html
 *
 */
#pragma once

#include "EflCpp/file_selector.h"
#include "EflCpp/window.h"
#include "elm_file_selector.h"

#include <string>

namespace EflCpp
{

namespace FileSelector
{

void launchImpl(bool multiselection, const boost::filesystem::path& root, MultipleFileHandler handler, const Filter& filter, bool dirsOnly);

} // namespace FileSelector
} // namespace EflCpp
