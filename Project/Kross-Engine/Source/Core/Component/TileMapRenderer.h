/*
 *  Author: Chris Deitch.
 *  Editors:
 *      - Chris Deitch.
 */

#pragma once

#include "../Core.h"

#include "Renderer.h"

#include "../Renderer/Material.h"
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





    protected:


        // Component Start Method.
        void OnStart() override;

        // Component Update Method.
        void OnUpdate() override;


    public:
        TileMap* GetTileMap() { return p_TileMap; };
        TileSet* GetTileSet() { return p_TileSet; };
        void SetTileMap(TileMap* tileMap) { p_TileMap = tileMap; }
        void SetTileSet(TileSet* tileSet) { p_TileSet = tileSet; }


    };

}