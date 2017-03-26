/* This Source Code Form is subject to the terms of the Mozilla Public
 * License, v. 2.0. If a copy of the MPL was not distributed with this
 * file, You can obtain one at http://mozilla.org/MPL/2.0/. */

#include <ncurses.h>
#include <future>
#include <thread>

#include "../lib.hh"
#include "file_contents.hh"
#include "mode.hh"
#include "prompt.hh"
#include "show_message.hh"
#include "vick-shell-command/lib.hh"

namespace vick {
namespace compile {

static std::string last_cmd;

static int compile(std::string last_cmd, contents& cont) {
    // contents cont(&read_only_mode);
    try {
        shell_command::exec_shell_command(last_cmd + " ; printf "
                                          // ~~~~~~~~~~^
                                          // Space required here
                                          // so that ``;;`` won't
                                          // occur by accident
                                                     "'\n%s\n' "
                                                     "\"$?\"",
                                          cont);
    } catch (const std::exception&) {
    }
    int ret = std::stoi(cont.cont.back());
    cont.cont.pop_back();
    if (cont.cont.back().empty())
        cont.cont.pop_back();
    return ret;
}

std::shared_ptr<change>
compile_project(contents& cont, boost::optional<int> force_prompt) {
    if (force_prompt or last_cmd.empty()) {
        attron(COLOR_PAIR(1));
        auto temp = prompt("Compile command: ");
        attroff(COLOR_PAIR(1));
        if (temp)
            last_cmd = *temp;
        else
            return nullptr;
    }

    // std::packaged_task<int(std::string, contents&)> tsk(compile);
    // auto future = tsk.get_future();

    // std::thread thread(std::move(tsk), last_cmd, std::ref(cont));
    // thread.join();
    // //     ^^^^ TODO: FIXME.  Makes a thread then immediately
    // joins.

    // int res = future.get();
    int res = compile(last_cmd, cont);
    if (res != 0)
        show_message("ERROR! " + std::to_string(res));

    return nullptr;
}
}
}
