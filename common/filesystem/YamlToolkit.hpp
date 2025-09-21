#pragma once

#include <yaml-cpp/yaml.h>
#include <string>
#include <fstream>
#include <filesystem>
#include <iostream>

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
        static auto read(const std::string& filepath) -> YAML::Node;

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
        static auto getValue(const std::string& filepath, const std::string& key) -> YAML::Node;

        /// @brief Set a value in a YAML file by key.
        /// @param filepath The path to the YAML file.
        /// @param key The key of the value to set.
        /// @param value The YAML node value to set.
        /// @return true if the value was set successfully, false otherwise.
        static auto setValue(const std::string& filepath, const std::string& key, const YAML::Node& value) -> bool;
    };

    inline auto YamlToolkit::create(const std::string& filepath, const YAML::Node& data) -> bool
    {
        try
        {
            // Create directory if it doesn't exist
            std::filesystem::path path(filepath);
            if (!path.parent_path().empty())
            {
                std::filesystem::create_directories(path.parent_path());
            }

            // Write data to file
            YAML::Emitter emitter;
            emitter << data;

            std::ofstream file(filepath);
            if (file.is_open())
            {
                file << emitter.c_str();
                file.close();
                return true;
            }
            return false;
        }
        catch (...)
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
            return YAML::Node();
        }
        catch (...)
        {
            return YAML::Node();
        }
    }

    inline auto YamlToolkit::update(const std::string& filepath, const YAML::Node& data) -> bool
    {
        try
        {
            // Update is essentially the same as create - overwrite the file with new data
            return create(filepath, data);
        }
        catch (...)
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
        catch (...)
        {
            return false;
        }
    }

    inline auto YamlToolkit::getValue(const std::string& filepath, const std::string& key) -> YAML::Node
    {
        try
        {
            YAML::Node root = read(filepath);
            if (root.IsMap())
            {
                return root[key];
            }
            return YAML::Node();
        }
        catch (...)
        {
            return YAML::Node();
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
        catch (...)
        {
            return false;
        }
    }
} // namespace fox
