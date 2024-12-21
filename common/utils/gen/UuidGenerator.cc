#include "UuidGenerator.hpp"

#include <boost/uuid/uuid.hpp>
#include <boost/uuid/uuid_generators.hpp>
#include <boost/uuid/uuid_io.hpp>

namespace common
{
    // ReSharper disable once CppDFAConstantFunctionResult
    auto UuidGenerator::GenerateRandomUuid() -> std::string
    {
        static auto generator = boost::uuids::random_generator();
        return boost::uuids::to_string(generator());
    }
}
