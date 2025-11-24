#include "CustomGlogPrefixFormatter.hpp"

namespace glog
{
    void CustomGlogPrefixFormatter::MyPrefixFormatter(std::ostream& s,
                                                      const google::LogMessage& m,
                                                      void*)
    {
        s << '[' << google::GetLogSeverityName(m.severity()) << "] ["
            << std::setw(4) << 1900 + m.time().year()
            << std::setw(2) << 1 + m.time().month()
            << std::setw(2) << m.time().day()
            << ' '
            << std::setw(2) << m.time().hour() << ':'
            << std::setw(2) << m.time().min() << ':'
            << std::setw(2) << m.time().sec() << "."
            << std::setw(6) << m.time().usec()
            << "] ["
            << std::setfill(' ') << std::setw(5)
            << m.thread_id() << std::setfill('0')
            << "] ["
            << m.basename() << ':' << m.line() << "] ";
    }
} // glog
