
#include "../external/webview.h"
#include "../external/json.hpp"
#include "managers/CourseManager.h"
#include <string>
#include <cmrc/cmrc.hpp>

CMRC_DECLARE(html);

using json = nlohmann::json;

/// Used for JSON Serialization
namespace nlohmann {
    /// Course Serializer
    void to_json(json &j, const Course& course) {
        j = json{
                {"id", course.get_id()},
                {"title", course.title},
                {"capacity", course.get_capacity()}
        };
    }

    template <typename T>/// Serialize shared_ptr<T>
    /// @attention nullptr returns as JS null
    struct adl_serializer<std::shared_ptr<T>> {
        static void to_json(json& j, const std::shared_ptr<T>& opt) {
            if (opt.get()) {
                j = *opt;
            } else {
                j = nullptr;
            }
        }
    };
}

#ifdef _WIN32
int CALLBACK WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance,
                     LPSTR lpCmdLine, int nCmdShow)
#else

 /// Create webview and inject functions into UI
int main()
#endif
{
    // create course manager and add a course
    auto cm = CourseManager();
    cm.add_course(string("**Course Injected by C++**",26), 0);

    auto fs = cmrc::html::get_filesystem();
    auto data = fs.open("index.html");
    auto html_page = "data:text/html," + webview::url_encode(string(data.begin(),data.end()));

    // Create webview
    webview::webview w(true, nullptr);
    // Style Window
    w.set_title(std::string ("Example",7));
    w.set_size(350, 420, WEBVIEW_HINT_NONE);
    w.set_size(350, 420, WEBVIEW_HINT_MIN);
    // Bind lambdas to js functions in webview
    w.bind("get_courses", [&cm]([[maybe_unused]]const string& s) -> string {
        json j = cm.list_courses();
        return to_string(j);
    });
    w.bind("add_course", [&cm]([[maybe_unused]]const string& s) -> string {
        auto title = webview::json_parse(s, "", 0);
        auto capacity = std::stoi(webview::json_parse(s, "", 1));
        json j = cm.add_course(title,capacity);
        return to_string(j);
    });
    // Navigate to page served from local host
    w.navigate( html_page);
    w.run();
    return 0;
}