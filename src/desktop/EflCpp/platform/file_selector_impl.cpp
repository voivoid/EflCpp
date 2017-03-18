#include "EflCpp/platform/file_selector_impl.h"

#include "EflCpp/assert.h"

#include <boost/filesystem/operations.hpp>
#include <boost/filesystem/path.hpp>
#include <boost/scope_exit.hpp>

#include "EflCpp/elementary_inc.h"

namespace EflCpp
{

namespace FileSelector
{

FileSelector::PathsOpt parseSelectedFilesStr(const char* const str)
{
    if (!str)
    {
        return {};
    }

    // note that file str format is comma separated and only the first file has a full path
    // "/some/path/file1.txt, file2.txt, file3.txt"

    char** files = eina_str_split(str, ", ", 0);
    EFLCPP_ASSERT(files);
    BOOST_SCOPE_EXIT(&files)
    {
        free(files[0]);
        free(files);
    }
    BOOST_SCOPE_EXIT_END;

    std::vector<boost::filesystem::path> results;

    boost::filesystem::path firstFile(files[0]);
    results.push_back(firstFile);
    const auto parentPath = firstFile.parent_path();

    auto** fileIter = files + 1;
    while (*fileIter)
    {
        results.push_back(parentPath / *fileIter);
        ++fileIter;
    }

    for (const auto& path : results)
    {
        EFLCPP_ASSERT(boost::filesystem::exists(path));
    }

    return results;
}

void launchImpl(const bool multiselection, const boost::filesystem::path& root, FileSelector::MultipleFileHandler handler, const FileSelector::Filter& filter, const bool dirsOnly)
{

    auto window = Window::createUnique(nullptr, "FileSelector");
    auto fs = ElmFileSelector::createUnique(*window);

    fs->setMultiselection(multiselection);
    fs->setFolderOnly(dirsOnly);
    fs->setRootPath(root);
    if (filter)
    {
        boost::apply_visitor([&fs](const auto& filter) { fs->setFilter(filter); }, *filter);
    }
    fs->setHintWeightPoint({HintExpand, HintExpand});
    fs->show();

    window->resize({640, 480});
    window->setContent(*fs);
    window->show();

    window->setSmartEventHandler(ElmObj::EventDeleteRequest, [handler](ElmObj& wnd, void*) {
        wnd.delObject();
        handler({});
    });

    fs->setSmartEventHandler(ElmFileSelector::EventDone, [h = std::move(handler)](ElmObj & fs, void* eventInfo) {
        auto& wnd = fs.getWindow();
        wnd.delObject();

        const char* const selectedFiles = reinterpret_cast<const char*>(eventInfo);
        h(parseSelectedFilesStr(selectedFiles));
    });

    EflCpp::releaseWidgetPtr(std::move(fs));
    EflCpp::releaseWidgetPtr(std::move(window));
}

} // namespace FileSelector
} // namespace EflCpp
