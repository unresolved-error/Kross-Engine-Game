/*
 *  Author: Chris Deitch.
 *  Editors:
 *      - Chris Deitch.
 *      - Deklyn Palmer.
 */

#pragma once

#include "../Core.h"

#include "Renderer.h"

#include "../Renderer/Tilemap/Tile.h"
#include "../Renderer/Tilemap/TileSet.h"
#include "../Renderer/Tilemap/TileMap.h"

#include "../Math/Math.h"

#include "Camera.h"

namespace Kross
{
    //class KROSS_API Renderer;

    class KROSS_API TileMapRenderer : public Renderer
    {
    private:
        TileMap* p_TileMap;
        TileSet* p_TileSet;
        std::vector<Tile*> m_Tiles;

        //Do not call manually. takes the xy of a tile Map, and then finds appropriate value. Uses that value to select correct sprite.
        Sprite* MatchMapCell(int x, int y);

        //As per title.
        void CreateTiles();




    protected:
        //friend class RigidBody2D;
        /* Friend classing Batch. */
        template<typename Type> friend class Batch;
        /* ^ I Hate this even more. Deklyn, what is this bs?*/

        // Component Start Method.
        void OnStart() override;



    public:
        TileMapRenderer() :
            p_TileMap   (nullptr),
            p_TileSet   (nullptr)
        {};
        ~TileMapRenderer();

        //Returns tileMap Pointer
        TileMap* GetTileMap() { return p_TileMap; };

        //Gets the tileset pointer
        TileSet* GetTileSet() { return p_TileSet; };
        std::vector<Tile*> GetTileList() { return m_Tiles; };

        //takes the tile map pointer and sets it to this renderer
        void SetTileMap(TileMap* tileMap);

        //takes tileSet pointer and sets it to this renderer.
        void SetTileSet(TileSet* tileSet);
   

    };

}