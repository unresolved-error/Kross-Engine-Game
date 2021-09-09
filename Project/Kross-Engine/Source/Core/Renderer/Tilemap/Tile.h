/*
 *  Author: Chris Deitch.
 *  Editors:
 *      - Chris Deitch.
 *      - Deklyn Palmer.
 */


#pragma once
#include "../../Core.h"
#include "../Image/Sprite.h"
#include "../../Math/Math.h"



namespace Kross
{
    struct KROSS_API Tile
    {
    private:
        Sprite* m_Sprite;
        Vector2 m_Offset;
        
    public:
        Tile() :
            m_Sprite    (nullptr),
            m_Offset    (Vector2(0.0f,0.0f))
        {};

        //overloaded tile creator. not currently used.
        Tile(Sprite* tileSprite, Vector2 tileOffset) :
            m_Sprite    (tileSprite),
            m_Offset    (tileOffset)
        {};

        // Gets the Sprite of the Tile.
        Sprite* GetSprite() const { return m_Sprite; };

        // Sets the Sprite of the Tile.
        void SetSprite(Sprite* sprite) { m_Sprite = sprite; };

        // Gets the Tile Offset.
        const Vector2 GetOffset() const { return m_Offset; };

        // Sets the Tile Offset.
        void SetOffset(Vector2 offset) { m_Offset = offset; };
    };
}