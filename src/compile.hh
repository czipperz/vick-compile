/* This Source Code Form is subject to the terms of the Mozilla Public
 * License, v. 2.0. If a copy of the MPL was not distributed with this
 * file, You can obtain one at http://mozilla.org/MPL/2.0/. */

#ifndef HEADER_GUARD_COMPILE_H
#define HEADER_GUARD_COMPILE_H

#include "contents.hh"

namespace vick {
namespace compile {

/*!
 * \file compile.hh
 * \brief Defines the `compile_project()` command.
 */

/*!
 * \brief This command is for interactive use.  It will call a command
 * prompted the first time ran and each time a prefix is given.
 */
boost::optional<std::shared_ptr<change> >
compile_project(contents& unused,
                boost::optional<int> force_prompt = boost::none);
}
}

#endif
