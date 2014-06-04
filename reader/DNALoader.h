#include "dnabase.h"
#include <filename.h>
#include <datagram.h>
#include <datagramIterator.h>

#include "DNAStorage.h"

#include "CompCodes.h"
#include "DNAGroup.h"
#include "DNAVisGroup.h"

class EXPCL_PANDASKEL DNALoader
{
	PUBLISHED:
		DNALoader(void);
		~DNALoader(void);
		std::string load_DNA_file(DNAStorage& store, const Filename &name);

	private:
		bool m_had_error;
		void show_error(const std::string& error);
		void handle_storage_data(DatagramIterator& dgi);
		void handle_comp_data(DatagramIterator& dgi);

		string m_x;
		DNAStorage* m_cur_store;
		DNAGroup* m_cur_comp;

		void handle_comp_group(DatagramIterator& dgi);
		void handle_comp_visgroup(DatagramIterator& dgi);
};
