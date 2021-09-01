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
            m_Diffuse       (nullptr),
            m_Normal        (nullptr),
            m_Specular      (nullptr)
        {};
        ~Material();

        Sprite* m_Diffuse;
        Sprite* m_Normal;
        Sprite* m_Specular;

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
        Sprite* GetDiffuse() { return m_Diffuse; };

        // Gets the Normal Sprite.
        Sprite* GetNormal() { return m_Normal; };

        // Gets the Specular Sprite.
        Sprite* GetSpecular() { return m_Specular; }

        // Sets the Diffuse Sprite.
        void SetDiffuse(Sprite* sprite) { m_Diffuse = sprite; };

        // Sets the Normal Sprite.
        void SetNormal(Sprite* sprite) { m_Normal = sprite; };

        // Sets the Specular Sprite.
        void SetSpecular(Sprite* sprite) { m_Specular = sprite; }
    };
}