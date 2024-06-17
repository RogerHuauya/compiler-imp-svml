#pragma once

#include <sstream>
#include <iostream>
#include <cstdlib>
#include <cstring>
#include <string>
#include <fstream>

#include "imp.hh"
#include "imp_visitor.hh"
#include "environment.hh"

class ImpCodeGen : public ImpVisitor {
public:
    void codegen(Program *, const string& outfname);

    void visit(Program *);

    void visit(Body *);

    void visit(VarDecList *);

    void visit(VarDec *);

    void visit(StatementList *);

    void visit(AssignStatement *);

    void visit(PrintStatement *);

    void visit(IfStatement *);

    void visit(WhileStatement *);


    int visit(BinaryExp *e);

    int visit(NumberExp *e);

    int visit(IdExp *e);

    int visit(ParenthExp *e);

    int visit(CondExp *e);

    int visit(BoolConstExp *e);

    void set_mem_size(int mem) { mem_size = mem; }

private:
    std::ostringstream code;
    string nolabel;
    int current_label;
    Environment<int> direcciones;
    int siguiente_direccion;
    int mem_size = 10;

    void codegen(const string& label, string instr);

    void codegen(const string& label, string instr, int arg);

    void codegen(const string& label, string instr, string jmplabel);

    string next_label();
};
