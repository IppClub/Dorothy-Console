#pragma once
#include <Windows.h>
#include "oDataTypes.h"

namespace Dorothy
{
	class DLLEXPORT oImage
	{
	public:
		oImage();
		~oImage();
		void Create(int width, int height);
		//���������Լ����Ͻ�Ϊ(0,0)������
		void SetChar(int x, int y, char ch);
		void SetColor(int x, int y, oColor color);
		char GetChar(int x, int y) const;
		oColor GetColor(int x, int y) const;
		int GetWidth() const;
		int GetHeight() const;
		void Release();
		CHAR_INFO** GetData();
	protected:
		int m_iWidth;
		int m_iHeight;
		CHAR_INFO** m_ppData;
	};
}