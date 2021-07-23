/*
 *  Author: Deklyn Palmer.
 *  Editors:
 *      - Deklyn Palmer.
 *      - Chris Deitch
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
            p_Diffuse       (nullptr),
            p_Normal        (nullptr),
            p_Specular      (nullptr)
        {};
        ~Material();

        std::string m_Name;

    protected:
        friend class ObjectEditor;

        // Sets the Material Name.
        void SetName(const std::string& name) { m_Name = name; };

    public:
        // Creates a fresh Material.
        static Material* OnCreate(const std::string& name);

        // Destroys the Specified Material.
        static void OnDestroy(Material* material);

        // Gets the Name of the Material.
        const std::string GetName() const { return m_Name; }

        Sprite* p_Diffuse;
        Sprite* p_Normal;
        Sprite* p_Specular;
    };
}