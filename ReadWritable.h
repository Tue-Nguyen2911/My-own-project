#ifndef TUENG_READWRITABLE_H
#define TUENG_READWRITABLE_H
#include <iostream>
namespace TueNg
{
	class ReadWritable
	{
		bool m_flag;
	public:
		ReadWritable();
		virtual ~ReadWritable();

		bool isCsv() const;
		void setCsv(bool value);
		virtual std::istream& read(std::istream& is = std::cin) = 0;
		virtual std::ostream& write(std::ostream& os = std::cout) const = 0;
	};

}

#endif // !TUENG_READWRITABLE_H
