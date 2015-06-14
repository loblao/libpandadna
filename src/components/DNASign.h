#ifndef _H_DNA_SIGN_
#define _H_DNA_SIGN_

#include "DNAProp.h"

class EXPCL_DNA DNASign : public DNAProp
{
    PUBLISHED:
        DNASign(const std::string& name);
        ~DNASign();
        
        COMP_CODE(COMPCODE_SIGN);
        COMP_NAME(sign);

    public:
        virtual void make_from_dgi(DatagramIterator& dgi, DNAStorage* store);
        virtual void traverse(NodePath& np, DNAStorage* store);
    
    TYPE_HANDLE(DNASign, DNAProp);
};

#endif
