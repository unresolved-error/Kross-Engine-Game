/*
 *  Author: Deklyn Palmer.
 *  Editors:
 *      - Deklyn Palmer.
 */

#pragma once

#include "../../Core.h"

#include "../EditorWindow.h"

#include "../../Manager/ResourceManager.h"

namespace Kross
{
	enum class KROSS_API AssetType
	{
		None,
		Sprite,
		Texture,
		Material,
		Font,
		Animation,
		AudioSource,
		TileMap,
		TileSet,
	};

	class KROSS_API AssetPreview : public EditorWindow
	{
	private:
		float m_Width, m_Height;
		float m_PositionX, m_PositionY;

		bool m_WindowVarSet;
		bool m_IsOpen;

		AssetType m_Type;

		Sprite* p_SelectedSprite;
		Texture* p_SelectedTexture;
		Material* p_SelectedMaterial;
		Font* p_SelectedFont;
		Animation* p_SelectedAnimation;
		AudioSource* p_SelectedAudioSource;
		TileMap* p_SelectedTileMap;
		TileSet* p_SelectedTileSet;

		Sprite* p_DestinationSprite;
		Texture* p_DestinationTexture;
		Material* p_DestinationMaterial;
		Font* p_DestinationFont;
		Animation* p_DestinationAnimation;
		AudioSource* p_DestinationAudioSource;
		TileMap* p_DestinationTileMap;
		TileSet* p_DestinationTileSet;

	protected:
		friend class ObjectEditor;

		// Gets if the Window is Closed.
		bool IsClosed() const { return !m_IsOpen; };

		// Sets the Scene Hierarchy Window Flags.
		void SetFlags() override;

		// Initialises the Window.
		void OnStart() override;

		// Adds the Data to the Window. 
		void Attach() override;

	public:
		AssetPreview() :
			m_Width						(0.0f),
			m_Height					(0.0f),
			m_PositionX					(0.0f),
			m_PositionY					(0.0f),
			m_WindowVarSet				(false), 
			m_IsOpen					(true),
			m_Type						(AssetType::None),
			p_SelectedSprite			(nullptr),
			p_SelectedTexture			(nullptr),
			p_SelectedMaterial			(nullptr),
			p_SelectedFont				(nullptr),
			p_SelectedAnimation			(nullptr),
			p_SelectedAudioSource		(nullptr),
			p_SelectedTileMap			(nullptr),
			p_SelectedTileSet			(nullptr),
			p_DestinationSprite			(nullptr),
			p_DestinationTexture		(nullptr),
			p_DestinationMaterial		(nullptr),
			p_DestinationFont			(nullptr),
			p_DestinationAnimation		(nullptr),
			p_DestinationAudioSource	(nullptr),
			p_DestinationTileMap		(nullptr),
			p_DestinationTileSet		(nullptr)
		{};
		~AssetPreview() {};

		// Sets the Asset Type for the Window to display.
		void SetType(AssetType type) { m_Type = type; };

		// Gets the Asset Type of the Window.
		AssetType GetType() const { return m_Type; };

		// Sets the Dimensions for the Window.
		void SetDimensions(float width = 256.0f, float height = 512.0f) { m_Width = width; m_Height = height; };

		// Sets the Position of the Window.
		void SetPosition(float x, float y) { m_PositionX = x; m_PositionY = y; };

		// Sets the Destination. (SPRITE)
		void SetAssetDestination(Sprite* destination);

		// Gets Sprite Destination.
		Sprite* GetSpriteDestination() const { return p_DestinationSprite; };

		// Gets the Sprite Selected (USE ONLY IF IN SPRITE MODE)
		Sprite* GetSprite() { return p_SelectedSprite; };

		// Gets the Texture Selected (USE ONLY IF IN TEXTURE MODE)
		Texture* GetTexture() const { return p_SelectedTexture; };

		// Gets the Material Selected (USE ONLY IF IN MATERIAL MODE)
		Material* GetMaterial() const { return p_SelectedMaterial; };

		// Gets the Font Selected (USE ONLY IF IN FONT MODE)
		Font* GetFont() const { return p_SelectedFont; };

		// Gets the Animation Selected (USE ONLY IF IN ANIMATION MODE)
		Animation* GetAnimation() const { return p_SelectedAnimation; };

		// Gets the Audio Source Selected (USE ONLY IF IN AUDIOSOURCE MODE)
		AudioSource* GetAudioSource() const { return p_SelectedAudioSource; };

		// Gets the Tile Map Selected (USE ONLY IF IN TILEMAP MODE)
		TileMap* GetTileMap() const { return p_SelectedTileMap; };

		// Gets the Tile Set Selected (USE ONLY IF IN TILESET MODE)
		TileSet* GetTileSet() const { return p_SelectedTileSet; };
	};
}