/*
	Author: Deklyn Palmer.
	Editors:
		- Deklyn Palmer.
*/

#pragma once

/* --- DO NOT INCLUDE THIS FILE ANYWHERE --- */
/* --- PURELY FOR DEMONSTRATION PURPOSES --- */

#define DUMMY_API __declspec(dllexport)

namespace Dummy
{
	class DUMMY_API Dummy
	{
	/* Variables are always private, unless it is a hastle editing or retrieving via function */
	private:
		/* Variable Naming Conventions */

		static int s_Dummy; // Static Variable
		int m_Dummy; // Standard Variable
		const int c_Dummy = 3; // Constant Variable
		bool* p_Dummy; // Pointer Variable

	protected:

	public:
		Dummy();
		~Dummy();

		/* Function Naming Conventions */

		/* --- Getters --- */
		// Gets the m_Dummy Variable.
		int GetDummy() const { return m_Dummy; };
		/* Getters can be defined in the header file if you wish,
		 * not a functional advantage but...
		 * a read and search advantage. 
		 */

		/* --- Setters --- */
		// Sets the m_Dummy Variable.
		void SetDummy(int value = 0); // If the function functionality requires a default value, set one.

		/* --- General Function Calls --- */
		// Called at the start.
		void OnStart();

		// When deleting the dummy.
		void OnDelete();

		// When you wish to reset the dummy.
		void OnReset();

		/* Adding and Removing Functions */
		// Adding a dummy to the current dummy's Child List.
		void AttachDummy(Dummy* dummy);

		// Removes a dummy from the current dummy's Child List.
		void DetachDummy(int index);

	};
}