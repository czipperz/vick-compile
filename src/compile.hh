#ifndef HEADER_GUARD_COMPILE_H
#define HEADER_GUARD_COMPILE_H

#include "../../../src/contents.hh"

namespace vick {
namespace compile {

/*!
 * \file compile.hh
 * \brief Defines the `compile_project()` command.
 */
boost::optional<std::shared_ptr<change> >
compile_project(contents& unused, boost::optional<int> force_prompt = boost::none);

}
}

#endif
