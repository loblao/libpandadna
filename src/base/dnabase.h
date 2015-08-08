#ifndef _H_DNA_BASE_
#define _H_DNA_BASE_

#include "config_dna.h"

#include <pandabase.h>

#define COMPCODE_GROUP 1
#define COMPCODE_VISGROUP 2
#define COMPCODE_NODE 3
#define COMPCODE_PROP 4
#define COMPCODE_SIGN 5
#define COMPCODE_SIGN_BASELINE 6
#define COMPCODE_SIGN_GRAPHIC 8
#define COMPCODE_FLAT_BUILDING 9
#define COMPCODE_WALL 10
#define COMPCODE_WINDOWS 11
#define COMPCODE_CORNICE 12
#define COMPCODE_LANDMARK_BUILDING 13
#define COMPCODE_ANIM_PROP 14
#define COMPCODE_INTERACTIVE_PROP 15
#define COMPCODE_ANIM_BUILDING 16
#define COMPCODE_DOOR 17
#define COMPCODE_FLAT_DOOR 18
#define COMPCODE_STREET 19
#define COMPCODE_RETURN 255

typedef unsigned short zone_id_t;
typedef int block_number_t;
typedef unsigned short point_index_t;

#include <datagramIterator.h>
#include <luse.h>

inline LVecBase4f dgi_extract_color(DatagramIterator& dgi)
{
    double r = dgi.get_uint8() / 255.;
    double g = dgi.get_uint8() / 255.;
    double b = dgi.get_uint8() / 255.;
    double a = dgi.get_uint8() / 255.;
    return LVecBase4f(r, g, b, a);
}

#define DGI_EXTRACT_COLOR dgi_extract_color(dgi)

// PROPERTY MACRO (TYPE, NAME)
// This is a helper for classes
// Declares protected m_NAME variable of type TYPE
// and generates PUBLISHED INLINE setter/getter
// N.B. Anything below a PROPERTY declaration will
// default to protected
#define PROPERTY(TYPE, NAME) PUBLISHED: \
                                INLINE void set_##NAME (TYPE value) { m_##NAME = value; }; \
                                INLINE TYPE get_##NAME () { return m_##NAME ; }; \
                            protected: \
                                TYPE m_##NAME ;
                                
// PROPERTY_STRING is like above, but it uses const std::string& for setter
#define PROPERTY_STRING(NAME) PUBLISHED: \
                                INLINE void set_##NAME (const std::string& value) { m_##NAME = value; }; \
                                INLINE std::string get_##NAME () { return m_##NAME ; }; \
                            protected: \
                                std::string m_##NAME ;
                                
// TYPE_HANDLE MACRO
// This is a helper for classes
// Reduces litter in class declaration
#define TYPE_HANDLE(NAME, PARENT) public: \
                                    static TypeHandle get_class_type() { return _type_handle; }; \
                                    virtual TypeHandle force_init_type() { init_type(); return get_class_type(); }; \
                                    virtual TypeHandle get_type() const { return get_class_type(); }; \
                                    static void init_type() { PARENT :: init_type(); register_type(_type_handle, #NAME, PARENT :: get_class_type()); }; \
                                  private: static TypeHandle _type_handle;
                                  
// WRITE_DNA
// This is a helper for classes
// Reduces litter in class declaration
#define WRITE_DNA INLINE virtual void write_dna(std::ostream& out, bool recursive=true, int indent=0)

// WRITE_PDNA
// This is a helper for classes
// Reduces litter in class declaration
#define WRITE_PDNA INLINE virtual void write_pdna(Datagram& dg, bool recursive=true)

// Helper functions
inline void pack_color(Datagram& dg, const LVecBase3f& color)
{
    dg.add_uint8(floor(color.get_x() * 255));
    dg.add_uint8(floor(color.get_y() * 255));
    dg.add_uint8(floor(color.get_z() * 255));
}

inline void pack_color(Datagram& dg, const LVecBase4f& color)
{
    dg.add_uint8(floor(color.get_x() * 255));
    dg.add_uint8(floor(color.get_y() * 255));
    dg.add_uint8(floor(color.get_z() * 255));
    dg.add_uint8(floor(color.get_w() * 255));
}

#define PACK_COLOR pack_color(dg, m_color)

#define COMP_CODE(X) INLINE virtual unsigned char get_comp_code() {return X;}
#define COMP_NAME(X) INLINE virtual const char* get_comp_name() {return #X;}
#define INDENTED_OUT out << std::string(indent, ' ')

#endif
