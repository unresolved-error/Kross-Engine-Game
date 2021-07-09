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
        List<Tile*> m_Tiles;

        Sprite* MatchMapCell(int x, int y);

        void CreateTiles();




    protected:
        /* Friend classing Batch. */
        template<typename Type> friend class Batch;
        /* ^ I Hate this even more. Deklyn, what is this bs?*/

        // Component Start Method.
        void OnStart() override;



    public:
        TileMap* GetTileMap() { return p_TileMap; };
        TileSet* GetTileSet() { return p_TileSet; };
        void SetTileMap(TileMap* tileMap);
        void SetTileSet(TileSet* tileSet);
   

    };

}