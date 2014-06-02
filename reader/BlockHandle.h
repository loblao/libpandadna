#ifndef P3_INTERROGATE // we don't need to interrogate this

#pragma once

#include <string>
using namespace std;

class BlockHandle
{
	public:
		BlockHandle();
		~BlockHandle();

		void set_title(const string value);
		void set_article(const string value);
		void set_type(const string value);
		void set_zone(unsigned short value);

		string get_title();
		string get_article();
		string get_type();
		unsigned short get_zone();

	private:
		string m_title;
		string m_article;
		string m_type;
		unsigned short m_zone;

};

#endif // P3_INTERROGATE