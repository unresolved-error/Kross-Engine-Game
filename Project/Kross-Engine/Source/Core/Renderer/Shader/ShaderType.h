/*
 *  Author: Deklyn Palmer.
 *  Editors:
 *      - Deklyn Palmer.
 */

#pragma once

#include "../../Core.h"

namespace Kross
{
    enum class KROSS_API ShaderType
    {
        Standard,
        PostProcess,

        /* Just in case. */
        Count,
    };
}