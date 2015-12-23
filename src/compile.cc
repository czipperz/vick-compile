#include <thread>
#include <future>
#include <ncurses.h>

#include "../../../src/show_message.hh"
#include "../../../src/split.hh"
#include "../../vick-shell-command/src/shell_command.hh"
#include "../../../src/file_contents.hh"
#include "../../../src/prompt.hh"
#include "../../../src/mode.hh"
#include "compile.hh"

namespace vick {
namespace compile {

static std::string last_cmd;

static int compile__(std::string last_cmd, contents& cont)
{
    // contents cont(&read_only_mode);
    try {
        shell_command::exec_shell_command(last_cmd + " ; printf '\n%s\n' \"$?\"", cont);
        // Space required here: ~~~~~~~~~~~~~~~~~~~~~~^ so that ``;;`` won't occur by accident
    } catch (const std::exception&) {}
    int ret = std::stoi(cont.cont.back());
    cont.cont.pop_back();
    if (cont.cont.back().size() == 0) cont.cont.pop_back();
    return ret;
}

boost::optional<std::shared_ptr<change> >
compile_project(contents& cont, boost::optional<int> force_prompt)
{
    if (force_prompt or last_cmd.empty()) {
        attron(COLOR_PAIR(1));
        auto temp = prompt("Compile command: ");
        if (temp) last_cmd = *temp;
        attroff(COLOR_PAIR(1));
        if (not temp) return boost::none;
    }

    std::packaged_task<int(std::string, contents&)> tsk(compile__);
    auto future = tsk.get_future();

    std::thread thread(std::move(tsk), last_cmd, std::ref(cont));
    thread.join();

    int res = future.get();
    if (res != 0) show_message("ERROR! " + std::to_string(res));

    return boost::none;
}

}
}
