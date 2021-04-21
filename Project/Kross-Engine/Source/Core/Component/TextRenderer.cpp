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

        /* Call Base Component Function. */
        Component::OnUpdate();
    }

    void TextRenderer::OnRender()
    {
        /* Render the Text. */
        m_Text.OnRender();

        /* Call Base Component Function. */
        Component::OnRender();
    }
}