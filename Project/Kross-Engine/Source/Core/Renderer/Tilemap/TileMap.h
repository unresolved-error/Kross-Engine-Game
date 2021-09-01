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

        //Takes the map indexs and sets them to m_MapSpriteIndexs
        void SetMapIndexes(std::vector<std::vector<int>> mapIndexs);
        void SetName(std::string name);


    public:
        //Overloaded OnCreate Method
        static TileMap* OnCreate(const std::string& name);

        //Destructs.
        static void OnDestroy(TileMap* toDestruct);

        // Gets the Tile Map Name.
        std::string GetName() const { return m_Name; };

        //returns m_MapSpriteIndexs
        std::vector<std::vector<int>> GetMapIndexs()const { return m_MapSpriteIndexs; };
        
        int GetCellValue(int x, int y);

        const Vector2 GetDimensions() const;


    private:
        std::vector<std::vector<int>> m_MapSpriteIndexs;
        std::string m_Name;


    };
}