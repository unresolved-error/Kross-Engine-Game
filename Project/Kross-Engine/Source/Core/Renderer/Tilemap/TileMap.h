/*
 *  Author: Chris Deitch.
 *  Editors:
 *      - Chris Deitch.
 */

#pragma once
#include "../../Core.h"
#include "Tile.h"



namespace Kross
{
    class KROSS_API TileMap
    {
    protected:
        void SetOrigin(Vector2 origin);
        void SetDimension(Vector2 dimension);
        void SetMapIndexes(List<List<int>> mapIndexs);
       
    public:

        Vector2 GetOrigin();
        


        static void OnCreate();
        static void OnDestroy(TileMap* toDestruct);

    private:
        List<List<int>> m_MapSpriteIndexs;
        List<List<Tile*>> m_Tiles;
        std::string m_Name;
        List<Sprite*> m_Sprites;
        Vector2 m_Origin;
        Vector2 m_Dimension;


    };
}