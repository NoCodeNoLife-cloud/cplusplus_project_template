#pragma once
#include <iosfwd>
#include <glog/logging.h>

namespace glog
{
    class CustomGlogPrefixFormatter
    {
    public:
        static void MyPrefixFormatter(std::ostream& s,
                                      const google::LogMessage& m,
                                      void* /*data*/);
    };
} // glog
