#pragma once
#include "oDataTypes.h"
#include "oIUpdate.h"
#include "oIRender.h"
#include "oImage.h"
#include "oScreen.h"

namespace Dorothy
{
	class oGroup;

	class DLLEXPORT oObject:public oIRender
	{
	public:
		oObject();
		virtual ~oObject();
		//����ʹ�õ�oImageû�б�����
		void SetImage(oImage* image);
		void SetDetective(bool bDetective);
		void SetGroup(oGroup* group);
		int GetX() const;
		int GetY() const;
		int GetWidth() const;
		int GetHeight() const;
		bool IsDetective() const;
		oImage* GetImage() const;
		oGroup* GetGroup() const;
		oObject* Prev() const;
		oObject* Next() const;
		//������Game World����ϵ���Լ����Ͻǵ�λ��
		virtual void SetPosition(int X, int Y);
		virtual void SetSize(int width, int height);
		virtual const oRect* GetRect() const;
		virtual oColor GetDisplayColor(int X, int Y) const;
		virtual char GetDisplayChar(int X, int Y) const;
		virtual void Render();
	protected:
		void RemoveGroup();
		bool m_bDetective;
		oRect m_kRect;
		oImage* m_pkImage;
		oObject* m_pkPrev;
		oObject* m_pkNext;
		oGroup* m_pkGroup;
	};
}