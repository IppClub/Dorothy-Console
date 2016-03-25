#pragma once
#include <Windows.h>
#include "oDataTypes.h"

namespace Dorothy
{
	class DLLEXPORT oAccurateTimer
	{
	public:
		oAccurateTimer();
		void Start();
		void Stop();
		bool IsRunning();
		void ZeroCount();
		//���ʱ���(s)
		float GetCount();
	protected:
		bool m_bRun;
		/*Ӳ����ʱ������*/
		LARGE_INTEGER m_iFrequency;
		LARGE_INTEGER m_iCurrentQuery;
		LARGE_INTEGER m_iLastQuery;
		LARGE_INTEGER m_iCount;
	};
}