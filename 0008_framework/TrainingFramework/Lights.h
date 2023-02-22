#pragma once
#include "../Utilities/utilities.h"

class Lights
{
public:
	int			m_ID;
	Vector3		m_pos;
	Vector3		m_color;
	Lights();
	~Lights();
};