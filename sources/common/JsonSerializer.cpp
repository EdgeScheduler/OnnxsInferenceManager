#include "../../include/common/JsonSerializer.h"

/*

you need to install <nlohmann/...> to your system. Example: "/usr/include/c++/$version/".
refer to website: https://github.com/nlohmann/json#serialization--deserialization.

*/

#include <fstream>
#include <iostream>
#include <filesystem>
#include <nlohmann/json.hpp>

namespace JsonSerializer
{
    nlohmann::json LoadJson(std::filesystem::path path)
    {
        nlohmann::json obj = nlohmann::json::value_t::discarded;
        try
        {
            std::ifstream f(path);
            obj = nlohmann::json::parse(f);
        }
        catch (nlohmann::json::exception &error)
        {
            std::cout << "error while read json from " << path << ": " << error.what() << std::endl;
        }
        catch (...)
        {
            std::cout << "error while read json from " << path << ": unknown error." << std::endl;
        }

        return obj;
    }

    bool StoreJson(nlohmann::json json, std::filesystem::path path, bool enable_null_json)
    {
        if (json.is_discarded())
        {
            if (!enable_null_json)
            {
                std::cout << "warning: json to " << path.string() << " is null." << std::endl;
                return false;
            }
            else
            {
                json = nullptr;
            }
        }

        try
        {
            std::filesystem::path fold = path.parent_path();
            if (fold != "")
            {
                std::filesystem::create_directories(fold);
            }

            std::ofstream o(path);
            o << std::setw(4) << json << std::endl;
        }
        catch (const std::exception &error)
        {
            std::cout << "error while write json to " << path << ": " << error.what() << std::endl;
            return false;
        }
        catch (...)
        {
            std::cout << "error while write json to " << path << ": unknown error." << std::endl;
            return false;
        }

        return true;
    }
}