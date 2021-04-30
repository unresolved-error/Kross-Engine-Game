/*
 *  Author: Deklyn Palmer.
 *  Editors:
 *      - Deklyn Palmer.
 */

#include "TextRenderer.h"

namespace Kross
{
    void TextRenderer::OnUpdate()
    {
        /* Update the Text. */
        m_Text.OnUpdate();
    }

    void TextRenderer::OnRender()
    {
        /* Render the Text. */
        m_Text.OnRender();
    }
}