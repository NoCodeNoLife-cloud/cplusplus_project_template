#include "src/gen/UuidGenerator.hpp"

#include <boost/uuid/uuid.hpp>
#include <boost/uuid/uuid_generators.hpp>
#include <boost/uuid/uuid_io.hpp>
#include <string>

namespace fox
{
    // ReSharper disable once CppDFAConstantFunctionResult
    auto UuidGenerator::GenerateRandomUuid() noexcept -> std::string
    {
        static auto generator = boost::uuids::random_generator();
        return boost::uuids::to_string(generator());
    }
}
