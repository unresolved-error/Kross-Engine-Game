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
    struct KROSS_API Tile
    {
        Sprite* p_Sprite;
        Vector2 m_Offset;
        

        Tile() :
            p_Sprite(nullptr),
            m_Offset(Vector2(0.0f,0.0f))
        {};

        Tile(Sprite* tileSprite, Vector2 tileOffset) :
            p_Sprite(tileSprite),
            m_Offset(tileOffset)
        {};

    };
}