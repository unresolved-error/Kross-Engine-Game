/*
 *  Author: Deklyn Palmer.
 *  Editors:
 *      - Deklyn Palmer.
 */

#pragma once

#include "../Core.h"

#include "Image/Sprite.h"

namespace Kross
{
    struct KROSS_API Material
    {
    private:
        Material() :
            m_Name          (""),
            p_Sprite        (nullptr),
            p_NormalMap     (nullptr),
            p_SpecularMap   (nullptr)
        {};
        ~Material();

        std::string m_Name;

    protected:
        // Sets the Material Name.
        void SetName(const std::string& name) { m_Name = name; };

    public:
        // Creates a fresh Material.
        static Material* OnCreate(const std::string& name);

        // Destroys the Specified Material.
        static void OnDestroy(Material* material);

        // Gets the Name of the Material.
        const std::string GetName() const { return m_Name; }

        Sprite* p_Sprite;
        Sprite* p_NormalMap;
        Sprite* p_SpecularMap;
    };
}