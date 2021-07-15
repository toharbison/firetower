#include <list>
#include "firewall.hpp"
#include "quickcheck/quickcheck.hh"

using namespace quickcheck;

class AddrtypeSetSrc : public Property<unsigned short, bool> {
  bool accepts(const unsigned short& x, const bool& y){
    return src < (1 << 12) && src > 0;
  }
  bool holdsFor(const unsigned short& x, const bool& y){
    AddrtypeMatch match;
    match.setSrc(x, y);
    xt_addrtype_match* specs = match.getSpecs();
    return specs->src == x && specs->flags & XT_ADDRTYPE_INVERT_SOURCE;
  }
};

class AddrtypeSetDst : public Property<unsigned short, bool> {
  bool accepts(const unsigned short& x, const bool& y){
    return x < (1 << 12) && x > 0;
  }
  bool holdsFor(const unsigned short& x, const bool& y){
    AddrtypeMatch match;
    match.setDst(x, y);
    xt_addrtype_match* specs = match.getSpecs();
    return specs->dest == x && specs->flags & XT_ADDRTYPE_INVERT_DEST;
  }
};

class AddrtypeLimitIFace : public Property<bool> {
  bool holdsFor(const bool& x){
    AddrtypeMatch match;
    match.limitIFace();
    xt_addrtype_match specs = match.getSpecs();
    return specs->flags & XT_ADDRTYPE_LIMIT_IFACE_IN;
  }
};

class AddrtypeLimitOFace : public Property<bool> {
  bool holdsFor(const bool& x){
    AddrtypeMatch match;
    match.limitOFace();
    xt_addrtype_match specs = match.getSpecs();
    return specs->flags & XT_ADDRTYPE_LIMIT_IFACE_OUT;
  }
}

int main(){
  check<AddrtypeSetSrc>("Addrtype::setSrc");
  check<AddrtypeSetDst>("Addrtype::setDst");
  check<AddrtypeLimitIFace>("Addrtype::limitIFace");
  check<AddrtypeLimitOFace>("Addrtype::limitOFace");