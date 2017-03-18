#include "EflCpp/file_selector.h"

#include "EflCpp/assert.h"
#include "EflCpp/platform/file_selector_impl.h"

#include <boost/filesystem/path.hpp>

namespace EflCpp
{
namespace
{
FileSelector::MultipleFileHandler adaptToMultipleFileHandler(FileSelector::SingleFileHandler handler)
{
    return [h = std::move(handler)](const FileSelector::PathsOpt& selectedFiles)
    {
        if (selectedFiles)
        {
            EFLCPP_ASSERT(selectedFiles->size() <= 1);
            h((*selectedFiles)[0]);
        }
        else
        {
            h({});
        }
    };
}
}

namespace FileSelector
{

void launch(const boost::filesystem::path& root, SingleFileHandler handler, const Filter& filter, bool dirsOnly)
{
    launchImpl(false, root, adaptToMultipleFileHandler(std::move(handler)), filter, dirsOnly);
}

void launch(const boost::filesystem::path& root, MultipleFileHandler handler, const Filter& filter, bool dirsOnly)
{
    launchImpl(true, root, std::move(handler), filter, dirsOnly);
}

} // namespace FileSelector
} // namespace EflCpp
