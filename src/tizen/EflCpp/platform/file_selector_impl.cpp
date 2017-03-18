#include "EflCpp/platform/file_selector_impl.h"

#include "EflCpp/assert.h"
#include "EflCpp/log.h"
#include "EflCpp/platform/app_control.h"

#include <boost/algorithm/string/join.hpp>
#include <boost/filesystem/path.hpp>
#include <boost/functional/overloaded_function.hpp>

#include <app_control.h>

namespace
{
//#ifndef CO_TIZEN_EMULATOR
// const char* FileManagerAppId = "com.samsung.myfile.fileselector";
//#else2
// const char* FileManagerAppId = "ug-myfile-efl"; // emulator's filemanager has a different app id
//#endif

const char* FileManagerPathOption = "path";
const char* FileManagerExtensionsFilterOption = "file_type";
const char* FileManagerSelectModeOption = "select_type";
const char* FileManagerSelectModeDirsOnly = "SAVE";
const char* FileManagerSelectModeSingle = "single";
const char* FileManagerSelectModeMultiple = "multiple";

} // namespace anonymous

namespace EflCpp
{
namespace FileSelector
{

void launchImpl(bool multiselection, const boost::filesystem::path& root, MultipleFileHandler handler, const Filter& filter, bool dirsOnly)
{
    auto* ctrl = new AppControl(
        [h = std::move(handler)](const boost::optional<AppControl>& ctrl) {
            PathsOpt resPaths;

            if (ctrl)
            {
                const auto& result = ctrl->getExtraData(APP_CONTROL_DATA_SELECTED);
                resPaths = std::vector<boost::filesystem::path>(result.cbegin(), result.cend());
            }

            h(std::move(resPaths));
        },
        true);
    ctrl->setOperation(AppControl::Operation::Pick);

    if (dirsOnly)
    {
        ctrl->setExtraData(FileManagerSelectModeOption, FileManagerSelectModeDirsOnly);
    }
    else
    {
        ctrl->setExtraData(APP_CONTROL_DATA_SELECTION_MODE, multiselection ? FileManagerSelectModeMultiple : FileManagerSelectModeSingle);
    }

    if (filter)
    {
        boost::apply_visitor(boost::make_overloaded_function(
                                 [ctrl](const FileSelector::MimeFilter& filter) {
                                     EFLCPP_ASSERT(filter.mimes.size() == 1); // tizen file manager supports only one MIME filter
                                     ctrl->setMime(filter.mimes.front().c_str());
                                 },
                                 [ctrl](const FileSelector::ExtFilter& filter) {
                                     static const std::string separator(";");
                                     const std::string filterStr = boost::algorithm::join(filter.extensions, separator);
                                     ctrl->setExtraData(FileManagerExtensionsFilterOption, filterStr.c_str());
                                 }),
                             *filter);
    }

    ctrl->setExtraData(FileManagerPathOption, root.string().c_str());

    ctrl->sendLaunchRequest();
}

} // namespace FileSelector
} // namespace EflCpp
