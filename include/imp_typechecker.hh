#pragma once

#include <unordered_map>

#include "imp.hh"
#include "type_visitor.hh"
#include "environment.hh"

using namespace std;

class ImpTypeChecker : public TypeVisitor {
public:
    ImpTypeChecker();

private:
    Environment<ImpType> env;
    int memory_used = 0;

public:
    void typecheck(Program *);

    void visit(Program *);

    void visit(Body *);

    void visit(VarDecList *);

    void visit(VarDec *);

    void visit(StatementList *);

    void visit(AssignStatement *);

    void visit(PrintStatement *);

    void visit(IfStatement *);

    void visit(WhileStatement *);

    ImpType visit(BinaryExp *e);

    ImpType visit(NumberExp *e);

    ImpType visit(IdExp *e);

    ImpType visit(ParenthExp *e);

    ImpType visit(CondExp *e);

    ImpType visit(BoolConstExp *e);

    int get_memory_used() const { return memory_used; }
};
