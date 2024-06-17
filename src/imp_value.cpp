#include "imp_value.hh"

ImpValue::ImpValue() : type(NOTYPE) {}

ImpType ImpValue::get_basic_type(const string &s) {
    ImpType tt;
    if (s == "int") tt = TINT;
    else if (s == "bool") tt = TBOOL;
    else tt = NOTYPE;
    return tt;
}

void ImpValue::set_default_value(ImpType tt) {
    type = tt;
    if (tt == TINT) {
        int_value = 0;
    } else if (tt == TBOOL) {
        bool_value = true;
    }
}

std::ostream &operator<<(std::ostream &outs, const ImpValue &v) {
    if (v.type == TINT)
        outs << v.int_value;
    else if (v.type == TBOOL) {
        if (v.bool_value)
            outs << "true";
        else
            outs << "false";
    } else {
        outs << "NOTYPE";
    }
    return outs;
}


