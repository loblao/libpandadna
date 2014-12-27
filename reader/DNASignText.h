#ifndef DNASIGNTEXT_H
#define DNASIGNTEXT_H

#include "pandabase.h"
#include "DNANode.h"

class EXPCL_PANDASKEL DNASignText : public DNANode
{
	PUBLISHED:
		DNASignText(string name);
		~DNASignText(void);

		void set_letters(const string& letters);
		string get_letters();

	public:
		void make_from_dgi(DatagramIterator& dgi, DNAStorage* store);
		virtual bool is_sign_text();

	private:
		string m_letters;
};

#endif
