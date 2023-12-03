//
// Created by Norbert Olkowski on 03.12.2023.
//
#pragma once

#include <string>
#include <unordered_map>
#include <iostream>
#include <fstream>
#include "../../Utilities/Utilities.hpp"

namespace Resource {

    template<typename Derived, typename T>
    class ResourceManager {
    public:
        explicit ResourceManager(const std::string &l_pathsFile);

        virtual ~ResourceManager();

        T *GetResource(const std::string &l_id);

        std::string GetPath(const std::string &l_id);

        bool RequireResource(const std::string &l_id);

        bool ReleaseResource(const std::string &l_id);

        void PurgeResources();

    private:
        std::unordered_map<std::string, std::pair<T *, unsigned int>> m_resources;
        std::unordered_map<std::string, std::string> m_paths;

        bool *Load(const std::string &l_path);

        std::pair<T *, unsigned int> *Find(const std::string &l_id);

        bool Unload(const std::string &l_id);

        void LoadPaths(const std::string &l_pathFile);
    };
}

#include "Resource.inl"