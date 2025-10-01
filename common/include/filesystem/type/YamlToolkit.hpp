#pragma once

#include <yaml-cpp/yaml.h>
#include <string>
#include <fstream>
#include <filesystem>

namespace fox
{
    /// @brief A utility class for performing CRUD operations on YAML files.
    /// @details This class provides static methods to create, read, update, and delete YAML files,
    /// as well as get and set specific values within YAML files.
    class YamlToolkit
    {
    public:
        /// @brief Create a new YAML file with the specified data.
        /// @param filepath The path to the YAML file to create.
        /// @param data The YAML node data to write to the file.
        /// @return true if the file was created successfully, false otherwise.
        static auto create(const std::string& filepath, const YAML::Node& data) -> bool;

        /// @brief Read YAML data from a file.
        /// @param filepath The path to the YAML file to read.
        /// @return A YAML node containing the file's data, or an empty node if the file doesn't exist or an error occurred.
        [[nodiscard]] static auto read(const std::string& filepath) -> YAML::Node;

        /// @brief Update a YAML file with new data.
        /// @param filepath The path to the YAML file to update.
        /// @param data The new YAML node data to write to the file.
        /// @return true if the file was updated successfully, false otherwise.
        static auto update(const std::string& filepath, const YAML::Node& data) -> bool;

        /// @brief Remove (delete) a YAML file.
        /// @param filepath The path to the YAML file to delete.
        /// @return true if the file was deleted successfully, false otherwise.
        static auto remove(const std::string& filepath) -> bool;

        /// @brief Get a value from a YAML file by key.
        /// @param filepath The path to the YAML file.
        /// @param key The key of the value to retrieve.
        /// @return A YAML node containing the value associated with the key, or an empty node if the key doesn't exist or an error occurred.
        [[nodiscard]] static auto getValue(const std::string& filepath, const std::string& key) -> YAML::Node;

        /// @brief Set a value in a YAML file by key.
        /// @param filepath The path to the YAML file.
        /// @param key The key of the value to set.
        /// @param value The YAML node value to set.
        /// @return true if the value was set successfully, false otherwise.
        static auto setValue(const std::string& filepath, const std::string& key, const YAML::Node& value) -> bool;

        /// @brief Get a nested value from a YAML file using a path.
        /// @param filepath The path to the YAML file.
        /// @param path The path to the value (e.g., "parent.child.grandchild").
        /// @return A YAML node containing the value at the specified path.
        [[nodiscard]] static auto getNestedValue(const std::string& filepath, const std::string& path) -> YAML::Node;

        /// @brief Set a nested value in a YAML file using a path.
        /// @param filepath The path to the YAML file.
        /// @param path The path to the value (e.g., "parent.child.grandchild").
        /// @param value The YAML node value to set.
        /// @return true if the value was set successfully, false otherwise.
        static auto setNestedValue(const std::string& filepath, const std::string& path, const YAML::Node& value) -> bool;

        /// @brief Check if a key exists in the YAML file.
        /// @param filepath The path to the YAML file.
        /// @param key The key to check for.
        /// @return true if the key exists, false otherwise.
        [[nodiscard]] static auto hasKey(const std::string& filepath, const std::string& key) -> bool;

        /// @brief Merge another YAML node into the existing file.
        /// @param filepath The path to the YAML file.
        /// @param data The YAML node to merge.
        /// @return true if the merge was successful, false otherwise.
        static auto merge(const std::string& filepath, const YAML::Node& data) -> bool;

        /// @brief Convert YAML node to string representation.
        /// @param node The YAML node to convert.
        /// @return String representation of the YAML node.
        [[nodiscard]] static auto toString(const YAML::Node& node) -> std::string;

        /// @brief Parse YAML from string.
        /// @param str The string containing YAML data.
        /// @return YAML node parsed from the string.
        [[nodiscard]] static auto fromString(const std::string& str) -> YAML::Node;

        /// @brief Get a node from a YAML node by path, with fallback to root if path doesn't exist
        /// @param root The root YAML node
        /// @param path The path to try (e.g., "grpc")
        /// @return The node at path if it exists, otherwise the root node
        [[nodiscard]] static auto getNodeOrRoot(const YAML::Node& root, const std::string& path) -> YAML::Node;
    };

    inline auto YamlToolkit::create(const std::string& filepath, const YAML::Node& data) -> bool
    {
        try
        {
            // Create directory if it doesn't exist
            if (const std::filesystem::path path(filepath); !path.parent_path().empty())
            {
                std::filesystem::create_directories(path.parent_path());
            }

            // Write data to file
            YAML::Emitter emitter;
            emitter << data;

            if (std::ofstream file(filepath); file.is_open())
            {
                file << emitter.c_str();
                file.close();
                return true;
            }
            return false;
        }
        catch (const std::exception&)
        {
            return false;
        }
    }

    inline auto YamlToolkit::read(const std::string& filepath) -> YAML::Node
    {
        try
        {
            if (std::filesystem::exists(filepath))
            {
                return YAML::LoadFile(filepath);
            }
            return {};
        }
        catch (const std::exception&)
        {
            return {};
        }
    }

    inline auto YamlToolkit::update(const std::string& filepath, const YAML::Node& data) -> bool
    {
        try
        {
            // Update is essentially the same as create - overwrite the file with new data
            return create(filepath, data);
        }
        catch (const std::exception&)
        {
            return false;
        }
    }

    inline auto YamlToolkit::remove(const std::string& filepath) -> bool
    {
        try
        {
            if (std::filesystem::exists(filepath))
            {
                return std::filesystem::remove(filepath);
            }
            return false;
        }
        catch (const std::exception&)
        {
            return false;
        }
    }

    inline auto YamlToolkit::getValue(const std::string& filepath, const std::string& key) -> YAML::Node
    {
        try
        {
            if (const YAML::Node root = read(filepath); root.IsMap())
            {
                return root[key];
            }
            return {};
        }
        catch (const std::exception&)
        {
            return {};
        }
    }

    inline auto YamlToolkit::setValue(const std::string& filepath, const std::string& key, const YAML::Node& value) -> bool
    {
        try
        {
            YAML::Node root = read(filepath);
            if (!root.IsMap())
            {
                root = YAML::Node(YAML::NodeType::Map);
            }

            root[key] = value;
            return create(filepath, root);
        }
        catch (const std::exception&)
        {
            return false;
        }
    }

    inline auto YamlToolkit::getNestedValue(const std::string& filepath, const std::string& path) -> YAML::Node
    {
        try
        {
            const YAML::Node root = read(filepath);
            if (!root.IsMap())
            {
                return {};
            }

            YAML::Node current = root;
            std::string::size_type prev = 0;
            std::string::size_type pos = 0;

            while ((pos = path.find('.', prev)) != std::string::npos)
            {
                if (const std::string key = path.substr(prev, pos - prev); current[key])
                {
                    current = current[key];
                    prev = pos + 1;
                }
                else
                {
                    return {};
                }
            }

            // Handle the last key
            const std::string key = path.substr(prev);
            return current[key];
        }
        catch (const std::exception&)
        {
            return {};
        }
    }

    inline auto YamlToolkit::setNestedValue(const std::string& filepath, const std::string& path, const YAML::Node& value) -> bool
    {
        try
        {
            YAML::Node root = read(filepath);
            if (!root.IsMap())
            {
                root = YAML::Node(YAML::NodeType::Map);
            }

            YAML::Node current = root;
            std::string::size_type prev = 0;
            std::string::size_type pos = 0;

            while ((pos = path.find('.', prev)) != std::string::npos)
            {
                const std::string key = path.substr(prev, pos - prev);
                if (!current[key])
                {
                    current[key] = YAML::Node(YAML::NodeType::Map);
                }
                current = current[key];
                prev = pos + 1;
            }

            // Set the value at the final key
            const std::string key = path.substr(prev);
            current[key] = value;

            return create(filepath, root);
        }
        catch (const std::exception&)
        {
            return false;
        }
    }

    inline auto YamlToolkit::hasKey(const std::string& filepath, const std::string& key) -> bool
    {
        try
        {
            if (const YAML::Node root = read(filepath); root.IsMap())
            {
                return root[key].IsDefined();
            }
            return false;
        }
        catch (const std::exception&)
        {
            return false;
        }
    }

    inline auto YamlToolkit::merge(const std::string& filepath, const YAML::Node& data) -> bool
    {
        try
        {
            YAML::Node root = read(filepath);
            if (!root.IsMap() && !root.IsNull())
            {
                return false; // Can only merge with a map or null node
            }

            if (data.IsMap())
            {
                if (!root.IsMap())
                {
                    root = YAML::Node(YAML::NodeType::Map);
                }

                for (const auto& it : data)
                {
                    root[it.first.as<std::string>()] = it.second;
                }

                return create(filepath, root);
            }

            return false;
        }
        catch (const std::exception&)
        {
            return false;
        }
    }

    inline auto YamlToolkit::toString(const YAML::Node& node) -> std::string
    {
        try
        {
            YAML::Emitter emitter;
            emitter << node;
            return {emitter.c_str()};
        }
        catch (const std::exception&)
        {
            return {};
        }
    }

    inline auto YamlToolkit::fromString(const std::string& str) -> YAML::Node
    {
        try
        {
            return YAML::Load(str);
        }
        catch (const std::exception&)
        {
            return {};
        }
    }

    inline auto YamlToolkit::getNodeOrRoot(const YAML::Node& root, const std::string& path) -> YAML::Node
    {
        try
        {
            if (root[path] && root[path].IsDefined()) {
                return root[path];
            }
            return root;
        }
        catch (const std::exception&)
        {
            return root;
        }
    }
}
