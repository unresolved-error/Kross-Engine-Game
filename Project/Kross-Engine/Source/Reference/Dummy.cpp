/*
 *  Author: Deklyn Palmer.
 *  Editors:
 *      - Deklyn Palmer.
 */

#include "Dummy.h"

/* --- NO FUNCTIONALITY INTENDED WITH THIS FILE --- */
/* ------  PURELY FOR DEMONSTRATION PURPOSES ------ */

namespace Dummy
{
	int		Dummy::s_Dummy =	0;

	Dummy::Dummy()
		: m_Dummy(0), p_Dummy(nullptr)
	{}

	Dummy::~Dummy()
	{}

	void Dummy::SetDummy(int value)
	{
		m_Dummy = value;
	}

	void Dummy::OnStart()
	{
		/* Do stuff... */
	}

	void Dummy::OnDelete()
	{
		/* Do stuff... */
	}

	void Dummy::OnReset()
	{
		/* Do stuff... */
	}

	void Dummy::AttachDummy(Dummy* dummy)
	{
		/* Do stuff... */
	}

	void Dummy::DetachDummy(int index)
	{
		/* Do stuff... */
	}
}