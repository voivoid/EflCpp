#include "EflCpp/platform/elm_file_selector.h"

#include "EflCpp/assert.h"
#include "EflCpp/log.h"
#include "EflCpp/safe_callback.h"

#include <boost/algorithm/string/case_conv.hpp>
#include <boost/algorithm/string/join.hpp>
#include <boost/algorithm/string/predicate.hpp>
#include <boost/filesystem/path.hpp>

#include "EflCpp/elementary_inc.h"

namespace EflCpp
{

namespace
{
static Eina_Bool fileFilterCallback(const char* const path, const Eina_Bool isDir, void* const data)
{
    EFLCPP_ASSERT(path);
    EFLCPP_ASSERT(data);

    if (isDir)
    {
        return EINA_TRUE;
    }

    const auto& exts = *reinterpret_cast<decltype(FileSelector::ExtFilter::extensions)*>(data);

    const auto lowerCasePath = boost::algorithm::to_lower_copy(std::string(path));
    for (const auto& ext : exts)
    {
        if (boost::algorithm::ends_with(lowerCasePath, ext))
        {
            return EINA_TRUE;
        }
    }

    return EINA_FALSE;
}
}

ElmFileSelector::ElmFileSelector(ElmObj& parent, const char* const objId)
    : Layout(objId, &parent, &elm_fileselector_add)
{
    EFLCPP_LOG_OBJECT_METHOD;
}

ElmFileSelector::~ElmFileSelector()
{
    EFLCPP_LOG_OBJECT_METHOD;
}

void ElmFileSelector::setRootPath(const boost::filesystem::path& path)
{
    elm_fileselector_path_set(getHandle(), path.string().c_str());
}

boost::filesystem::path ElmFileSelector::getSelectedPath() const
{
    auto* selectedFile = elm_fileselector_selected_get(getHandle());
    if (!selectedFile)
    {
        return {};
    }

    return selectedFile;
}

void ElmFileSelector::setMultiselection(const bool enable)
{
    elm_fileselector_multi_select_set(getHandle(), enable);
}

bool ElmFileSelector::getMultiselection() const
{
    return elm_fileselector_multi_select_get(getHandle());
}

void ElmFileSelector::setFolderOnly(const bool enable)
{
    elm_fileselector_folder_only_set(getHandle(), enable);
}

bool ElmFileSelector::getFolderOnly() const
{
    return elm_fileselector_folder_only_get(getHandle());
}

void ElmFileSelector::setFilter(const FileSelector::MimeFilter& filter)
{
    elm_need_efreet();
    clearFilter();

    const auto& filterStr = boost::algorithm::join(filter.mimes, ";");
    elm_fileselector_mime_types_filter_append(getHandle(), filterStr.c_str(), filter.name.c_str());
}

void ElmFileSelector::setFilter(const FileSelector::ExtFilter& filter)
{
    clearFilter();

    _extsToFilter = std::vector<std::string>{};
    _extsToFilter->reserve(filter.extensions.size());
    std::transform(filter.extensions.cbegin(), filter.extensions.cend(), std::back_inserter(*_extsToFilter), [](const std::string& ext) { return boost::algorithm::to_lower_copy(ext); });

    elm_fileselector_custom_filter_append(getHandle(), EFLCPP_WRAP_INTO_SAFE_CALLBACK(fileFilterCallback), (void*)&(*_extsToFilter), filter.name.c_str());
}

void ElmFileSelector::clearFilter()
{
    elm_fileselector_filters_clear(getHandle());
    _extsToFilter.reset();
}

void ElmFileSelector::setShowHiddenFiles(const bool enable)
{
    elm_fileselector_hidden_visible_set(getHandle(), enable);
}

bool ElmFileSelector::getShowHiddenFiles() const
{
    return elm_fileselector_hidden_visible_get(getHandle());
}

} // namespace EflCpp
