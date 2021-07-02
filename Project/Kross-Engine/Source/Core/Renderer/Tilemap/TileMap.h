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
        void AttachSprites(List<Sprite*> sprites);
        void SetName(std::string name);
        void SetTiles(List<List<Tile*>> tiles);


    public:

        Vector2 GetOrigin()const { return m_Origin; };
        Vector2 GetDimensions()const { return m_Dimension; };
        std::string GetName()const {return m_Name;};
        List<List<int>> GetMapIndexs()const { return m_MapSpriteIndexs; };
        List<Sprite*> GetSprites()const { return m_Sprites; };
        List<List<Tile*>> GetTiles()const { return m_Tiles; };
        static TileMap* OnCreate(const std::string& name);
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