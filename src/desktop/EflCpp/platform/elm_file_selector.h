#pragma once

#include "EflCpp/file_selector.h"
#include "EflCpp/layout.h"

#include <boost/optional.hpp>

namespace boost
{
namespace filesystem
{
class path;
}
}

namespace EflCpp
{
class ElmFileSelector : public Layout
{
public:
    EFLCPP_DECL_EFL_WIDGET(ElmFileSelector)
    ~ElmFileSelector();

    void setRootPath(const boost::filesystem::path& path);

    boost::filesystem::path getSelectedPath() const;

    void setMultiselection(bool enable);
    bool getMultiselection() const;

    void setFolderOnly(bool enable);
    bool getFolderOnly() const;

    void setShowHiddenFiles(bool enable);
    bool getShowHiddenFiles() const;

    void clearFilter();
    void setFilter(const FileSelector::MimeFilter& mimeFilter);
    void setFilter(const FileSelector::ExtFilter& extFilter);

    static constexpr const char* EventDone = "done";
    static constexpr const char* EventItemClicked = "selected";
    static constexpr const char* EventItemSelected = "activated";
    static constexpr const char* EventInvalidFile = "selected,invalid";
    static constexpr const char* EventDirChanged = "directory,open";

protected:
    ElmFileSelector(ElmObj& parent, const char* objId = FileSelectorDefaultId);

private:
    static constexpr const char* FileSelectorDefaultId = "FILE_SELECTOR";

    boost::optional<std::vector<std::string>> _extsToFilter;
};

} // namespace EflCpp
