#include "imp_typechecker.hh"

ImpTypeChecker::ImpTypeChecker() = default;

void ImpTypeChecker::typecheck(Program *p) {
    env.clear();
    p->accept(this);
}

void ImpTypeChecker::visit(Program *p) {
    p->body->accept(this);
}

void ImpTypeChecker::visit(Body *b) {
    env.add_level();
    b->var_decs->accept(this);
    b->slist->accept(this);
    env.remove_level();
}

void ImpTypeChecker::visit(VarDecList *decs) {
    list<VarDec *>::iterator it;
    for (it = decs->vdlist.begin(); it != decs->vdlist.end(); ++it) {
        (*it)->accept(this);
    }
}

void ImpTypeChecker::visit(VarDec *vd) {
    ImpType type = ImpValue::get_basic_type(vd->type);
    if (type == NOTYPE) {
        cout << "Invalid type: " << vd->type << endl;
        exit(0);
    }
    list<string>::iterator it;
    for (it = vd->vars.begin(); it != vd->vars.end(); ++it) {
        env.add_var(*it, type);
    }
}


void ImpTypeChecker::visit(StatementList *s) {
    list<Stm *>::iterator it;
    for (it = s->slist.begin(); it != s->slist.end(); ++it) {
        (*it)->accept(this);
    }
}

void ImpTypeChecker::visit(AssignStatement *s) {
    ImpType rhs_type = s->rhs->accept(this);
    if (!env.check(s->id)) {
        cout << "Variable " << s->id << " undefined" << endl;
        exit(0);
    }
    ImpType var_type = env.lookup(s->id);

    if (rhs_type != var_type) {
        cout << "Type mismatch in assignment to variable " << s->id << endl;
        exit(0);
    }

}

void ImpTypeChecker::visit(PrintStatement *s) {
    s->e->accept(this);
}

void ImpTypeChecker::visit(IfStatement *s) {
    ImpType tcond_type = s->cond->accept(this);

    if (tcond_type != TBOOL) {
        cout << "Condition in if statement must be boolean" << endl;
        exit(0);
    }

    s->tbody->accept(this);
    if (s->fbody != nullptr)
        s->fbody->accept(this);
}

void ImpTypeChecker::visit(WhileStatement *s) {
    ImpType tcond_type = s->cond->accept(this);
    if (tcond_type != TBOOL) {
        cout << "Condition in while statement must be boolean" << endl;
        exit(0);
    }
    s->body->accept(this);
}

ImpType ImpTypeChecker::visit(BinaryExp *e) {
    ImpType t1 = e->left->accept(this);
    ImpType t2 = e->right->accept(this);

    if (t1 != t2) {
        cout << "Type mismatch in binary expression with operation "<< e->op << endl;
        exit(0);
    }

    ImpType result = t1;
    switch (e->op) {
        case PLUS:
        case MINUS:
        case MULT:
        case DIV:
        case EXP:
            if (result != TINT) {
                cout << "Integer type expected in operation "<< e->op << endl;
                exit(0);
            }
            break;
        case LT:
        case LTEQ:
        case EQ:
            if (result != TBOOL) {
                cout << "Bool type expected in operation "<< e->op << endl;
                exit(0);
            }
            break;
    }
    return result;
}

ImpType ImpTypeChecker::visit(NumberExp *e) {
    ImpType t = TINT;
    return t;
}

ImpType ImpTypeChecker::visit(IdExp *e) {
    ImpType t = env.lookup(e->id);
    return t;
}

ImpType ImpTypeChecker::visit(ParenthExp *ep) {
    return ep->e->accept(this);
}

ImpType ImpTypeChecker::visit(CondExp *e) {
    ImpType btype = e->cond->accept(this);
    if (btype != TBOOL) {
        cout << "Condition in conditional expression must be boolean" << endl;
        exit(0);
    }

    ImpType ttype = e->etrue->accept(this);
    ImpType ftype = e->efalse->accept(this);

    if (ttype != ftype) {
        cout << "Type mismatch in conditional expression" << endl;
        exit(0);
    }

    return ttype;
}

