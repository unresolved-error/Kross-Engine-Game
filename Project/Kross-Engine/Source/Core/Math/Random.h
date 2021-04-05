/*
 *  Author: Deklyn Palmer.
 *  Editors:
 *      - Deklyn Palmer.
 */

#pragma once

#include "../Core.h"

namespace Kross
{
    class KROSS_API Random
    {
    private:
        static int m_Seed;

    protected:
        
    public:
        Random() {};
        ~Random() {};

        // Base Template Random Range Function. (DO NOT USE)
        template<typename Type>
        static Type GetRandomRange(Type min, Type max)
        {
            static_assert(false, "Incorrect Type for Random!");
        };

        // Base Template Random Function. (DO NOT USE)
        template<typename Type>
        static Type GetRandom(int seed = 5489)
        {
            static_assert(false, "Incorrect Type for Random!");
        };

        // Generates a Random Number between the Min and Max. (INCLUSIVE)
        template<>
        static float GetRandomRange<float>(float min, float max)
        {
            /* Random Engine. */
            std::default_random_engine randomEngine;

            /* Randomise the seed everytime. */
            int seed = rand() % rand();
            srand(seed);
            randomEngine.seed(seed);

            /* Get a number within the min and max. */
            std::uniform_real_distribution<float> random(min, max);
            return random(randomEngine);
        };

        // Generates a Random Number between the Min and Max. (INCLUSIVE)
        template<>
        static int GetRandomRange<int>(int min, int max)
        {
            /* Random Engine. */
            std::default_random_engine randomEngine;

            /* Randomise the seed everytime. */
            int seed = rand() % rand();
            srand(seed);
            randomEngine.seed(seed);

            /* Get a number within the min and max. */
            std::uniform_int_distribution<int> random(min, max);
            return random(randomEngine);
        };

        // Generates a Random Number. (0.0 and 2147483647.0)
        template<>
        static float GetRandom(int seed)
        {
            /* Random Engine. */
            std::minstd_rand randomEngine;

            /* Set the Seed to one if the seed has been used before, that way we get the same number as last time. */
            if (m_Seed == seed)
                randomEngine.seed(1);

            /* Set the seed if it was differnet and generate a number from that seed. */
            else
            {
                m_Seed = seed;
                randomEngine.seed((unsigned int)seed);
            }

            /* Get a random number from the seed. */
            std::uniform_real_distribution<float> random(0.0f, (float)INT32_MAX);
            return random(randomEngine);
        };

        // Generates a Random Number. (0 and 2147483647)
        template<>
        static int GetRandom(int seed)
        {
            /* Random Engine. */
            std::minstd_rand randomEngine;

            /* Set the Seed to one if the seed has been used before, that way we get the same number as last time. */
            if (m_Seed == seed)
                randomEngine.seed(1);

            /* Set the seed if it was differnet and generate a number from that seed. */
            else
            {
                m_Seed = seed;
                randomEngine.seed((unsigned int)seed);
            }

            /* Get a random number from the seed. */
            std::uniform_int_distribution<int> random(0, INT32_MAX);
            return random(randomEngine);
        };
    };
}