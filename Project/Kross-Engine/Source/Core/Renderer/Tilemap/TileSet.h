/*
 *  Author: Chris Deitch.
 *  Editors:
 *      - Chris Deitch.
 */


#pragma once
#include "../../Core.h"
#include "../Image/Sprite.h"
#include "../../Math/Math.h"



namespace Kross
{
    struct KROSS_API TileSet
    {
    protected:

        friend class FileSystem;


        std::string m_Name;
        List<Sprite*> m_Sprites;

        void SetName(std::string name) { m_Name = name; };
        void SetSprites(List<Sprite*> sprites) { m_Sprites = sprites; };


    private:
        ~TileSet();


    public:

        static TileSet* OnCreate(const std::string& name);
        static void OnDestroy(TileSet* tileSet);
        std::string GetName()const { return m_Name; };

        List<Sprite*> GetSprite()const { return m_Sprites; };

    };
}