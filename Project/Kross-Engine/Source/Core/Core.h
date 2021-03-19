#pragma once

/* --- Global Header --- */

/* --- README --- */
/*
 * This must be used everywhere in order for the Engine API to be put into the DLL for importation on the Game Project side of things
 * Eg. class KROSS_API Classname;
 */

/* Include Files */
/*
 * Eg. Standard Library files like vector and other things.
 * Do Not include API FILES HERE, bad times lie ahead if you do.
 */

#include <vector>
template<typename Type>
// Renaming of std::vector.
using List = std::vector<Type>;

#include <iostream>
#include <string>

/* --- Testing Ground --- */
/*class Test
 *{
 *public:
 *    Test()
 *    {
 *        // List works fine
 *        List<int> list;
 *        list.push_back(1);
 *    }
 *};
 */

/* --- DLL Export and Import Functionality --- */

#ifdef KROSS_PLATFORM_WINDOWS
    #ifdef KROSS_ENGINE
        #define KROSS_API __declspec(dllexport)
    #else
        #define KROSS_API __declspec(dllimport)
    #endif
#else
    #error Kross-Engine only supports Windows!
#endif