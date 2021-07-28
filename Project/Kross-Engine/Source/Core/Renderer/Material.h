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

        Sprite* p_Diffuse;
        Sprite* p_Normal;
        Sprite* p_Specular;

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

        // Gets the Diffuse Sprite.
        Sprite* GetDiffuse() { return p_Diffuse; };

        // Gets the Normal Sprite.
        Sprite* GetNormal() { return p_Normal; };

        // Gets the Specular Sprite.
        Sprite* GetSpecular() { return p_Specular; }

        // Sets the Diffuse Sprite.
        void SetDiffuse(Sprite* sprite) { p_Diffuse = sprite; };

        // Sets the Normal Sprite.
        void SetNormal(Sprite* sprite) { p_Normal = sprite; };

        // Sets the Specular Sprite.
        void SetSpecular(Sprite* sprite) { p_Specular = sprite; }
    };
}