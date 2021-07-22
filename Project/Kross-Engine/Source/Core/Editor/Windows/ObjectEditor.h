/*
 *  Author: Chris Deitch.
 *  Editors:
 *      - Chris Deitch.
 */

#pragma once
#include "../../Core.h"
#include "../EditorWindow.h"


namespace Kross
{
    class KROSS_API ObjectEditor : public EditorWindow 
    {
    public:

    private:

    protected:
        void Attach();
        
        void SetFlags();

        void OnStart();

    };
}