#include <iostream>
#include "ReadWritable.h"

namespace TueNg
{
	ReadWritable::ReadWritable()
	{
		m_flag = false;
	}
	ReadWritable::~ReadWritable()
	{

	}
	bool ReadWritable::isCsv() const
	{
		return m_flag;
	}
	void ReadWritable::setCsv(bool value)
	{
		m_flag = value;
	}

	//Save for later 
	//std::ostream& operator<<(std::ostream& os, const ReadWritable& obj)
	//{
	//	obj.write(os);
	//	return os;
	//}
	//std::istream& operator>>(std::istream& is, ReadWritable& obj)
	//{
	//	obj.read(is);
	//	return is;
	//}
}