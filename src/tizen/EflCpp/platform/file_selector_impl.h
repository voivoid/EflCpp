#pragma once

#include "EflCpp/file_selector.h"

#include <memory>
#include <string>

namespace EflCpp
{
namespace FileSelector
{
// class AppControl;
// class FileSelectorImpl
//{
// public:
//    FileSelectorImpl(bool multiselection, const boost::filesystem::path& root, FileSelector::MultipleFileHandler handler, const FileSelector::Filter& filter, bool dirsOnly);
//    ~FileSelectorImpl();
//    void launch();

// private:
//    FileSelector::MultipleFileHandler _handler;
//    // std::unique_ptr<AppControl> _appControl;
//};

void launchImpl(bool multiselection, const boost::filesystem::path& root, MultipleFileHandler handler, const Filter& filter, bool dirsOnly);

} // namespace FileSelector
} // namespace EflCpp
