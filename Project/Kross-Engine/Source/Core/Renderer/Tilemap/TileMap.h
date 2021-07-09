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
        friend class FileSystem;

        void SetMapIndexes(List<List<int>> mapIndexs);
        void SetName(std::string name);


    public:
        std::string GetName()const {return m_Name;};
        List<List<int>> GetMapIndexs()const { return m_MapSpriteIndexs; };
        static TileMap* OnCreate(const std::string& name);
        static void OnDestroy(TileMap* toDestruct);
        int GetCellValue(int x, int y);
        const Vector2 GetDimensions() const;


    private:
        List<List<int>> m_MapSpriteIndexs;
        std::string m_Name;


    };
}