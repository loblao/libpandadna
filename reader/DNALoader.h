#include "dnabase.h"
#include <filename.h>
#include <datagram.h>
#include <datagramIterator.h>

#include "DNAStorage.h"

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

		string m_x;
		DNAStorage* m_cur_store;
};
