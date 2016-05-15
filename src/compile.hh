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
