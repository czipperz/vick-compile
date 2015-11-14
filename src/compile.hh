#ifndef HEADER_GUARD_COMPILE_H
#define HEADER_GUARD_COMPILE_H

#include "../../../src/contents.hh"

namespace vick {
namespace compile {

boost::optional<std::shared_ptr<change> >
compile_project(contents& unused, boost::optional<int> force_prompt);

}
}

#endif
