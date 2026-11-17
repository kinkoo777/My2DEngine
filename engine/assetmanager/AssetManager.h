#pragma once 

#include "glad/glad.h"
#include <unordered_map>
#include <memory>
#include <string>
#include <stdexcept>

class AssetManger
{
    public:
        template <typename T>
        static std::shared_ptr<T>Load(const std::string& name, const std::string& filepath)
        {
            auto& storage = GetStorage<T>();

            if (storage.find(name) != storage.end())
            {
                return storage[name];
            }

            // Create new instance and load from file 

            auto asset = std::make_shared<T>();
            if (!asset->LoadFromFile(filepath)) 
            {
                throw std::runtime_error("There was an error while loading asset: "+ filepath);
            }

            storage[name] = asset;
            return asset;
        }

        template <typename T>
        static std::shared_ptr<T>Get(const std::string& name) 
        {
            auto& storage = GetStorage<T>();
            auto it = storage.find(name);

            if (it == storage.end())
            {
                throw std::runtime_error("Asset was not found: " + name);
            }
            return it->second;
        }

        template <typename T>

        static void UnloadUnused()
        {
            auto& storage = GetStorage<T>();

            for (auto it = storage.begin(); it != storage.end();)
            {
                if (it->second.use_count() == 1)
                {
                    it = storage.erase(it);
                }
                else 
                {
                    ++it;
                }
            }
        }



    private:
        template <typename T>
        static std::unordered_map<std::string, std::shared_ptr<T>>& GetStorage() {
            static std::unordered_map<std::string, std::shared_ptr<T>> storage;
            return storage;
        }

};