/* C Abstract Syntax Implementation generated by the BNF Converter. */

#include <stdio.h>
#include <stdlib.h>
#include "Absyn.h"

/********************   PGround    ********************/

Proc make_PGround(Ground p1)
{
    Proc tmp = (Proc) malloc(sizeof(*tmp));
    if (!tmp)
    {
        fprintf(stderr, "Error: out of memory when allocating PGround!\n");
        exit(1);
    }
    tmp->kind = is_PGround;
    tmp->u.pground_.ground_ = p1;
    return tmp;
}

/********************   PCollect    ********************/

Proc make_PCollect(Collection p1)
{
    Proc tmp = (Proc) malloc(sizeof(*tmp));
    if (!tmp)
    {
        fprintf(stderr, "Error: out of memory when allocating PCollect!\n");
        exit(1);
    }
    tmp->kind = is_PCollect;
    tmp->u.pcollect_.collection_ = p1;
    return tmp;
}

/********************   PVar    ********************/

Proc make_PVar(ProcVar p1)
{
    Proc tmp = (Proc) malloc(sizeof(*tmp));
    if (!tmp)
    {
        fprintf(stderr, "Error: out of memory when allocating PVar!\n");
        exit(1);
    }
    tmp->kind = is_PVar;
    tmp->u.pvar_.procvar_ = p1;
    return tmp;
}

/********************   PVarRef    ********************/

Proc make_PVarRef(VarRefKind p1, Var p2)
{
    Proc tmp = (Proc) malloc(sizeof(*tmp));
    if (!tmp)
    {
        fprintf(stderr, "Error: out of memory when allocating PVarRef!\n");
        exit(1);
    }
    tmp->kind = is_PVarRef;
    tmp->u.pvarref_.varrefkind_ = p1;
    tmp->u.pvarref_.var_ = p2;
    return tmp;
}

/********************   PNil    ********************/

Proc make_PNil()
{
    Proc tmp = (Proc) malloc(sizeof(*tmp));
    if (!tmp)
    {
        fprintf(stderr, "Error: out of memory when allocating PNil!\n");
        exit(1);
    }
    tmp->kind = is_PNil;
    return tmp;
}

/********************   PSimpleType    ********************/

Proc make_PSimpleType(SimpleType p1)
{
    Proc tmp = (Proc) malloc(sizeof(*tmp));
    if (!tmp)
    {
        fprintf(stderr, "Error: out of memory when allocating PSimpleType!\n");
        exit(1);
    }
    tmp->kind = is_PSimpleType;
    tmp->u.psimpletype_.simpletype_ = p1;
    return tmp;
}

/********************   PNegation    ********************/

Proc make_PNegation(Proc p1)
{
    Proc tmp = (Proc) malloc(sizeof(*tmp));
    if (!tmp)
    {
        fprintf(stderr, "Error: out of memory when allocating PNegation!\n");
        exit(1);
    }
    tmp->kind = is_PNegation;
    tmp->u.pnegation_.proc_ = p1;
    return tmp;
}

/********************   PConjunction    ********************/

Proc make_PConjunction(Proc p1, Proc p2)
{
    Proc tmp = (Proc) malloc(sizeof(*tmp));
    if (!tmp)
    {
        fprintf(stderr, "Error: out of memory when allocating PConjunction!\n");
        exit(1);
    }
    tmp->kind = is_PConjunction;
    tmp->u.pconjunction_.proc_1 = p1;
    tmp->u.pconjunction_.proc_2 = p2;
    return tmp;
}

/********************   PDisjunction    ********************/

Proc make_PDisjunction(Proc p1, Proc p2)
{
    Proc tmp = (Proc) malloc(sizeof(*tmp));
    if (!tmp)
    {
        fprintf(stderr, "Error: out of memory when allocating PDisjunction!\n");
        exit(1);
    }
    tmp->kind = is_PDisjunction;
    tmp->u.pdisjunction_.proc_1 = p1;
    tmp->u.pdisjunction_.proc_2 = p2;
    return tmp;
}

/********************   PEval    ********************/

Proc make_PEval(Name p1)
{
    Proc tmp = (Proc) malloc(sizeof(*tmp));
    if (!tmp)
    {
        fprintf(stderr, "Error: out of memory when allocating PEval!\n");
        exit(1);
    }
    tmp->kind = is_PEval;
    tmp->u.peval_.name_ = p1;
    return tmp;
}

/********************   PMethod    ********************/

Proc make_PMethod(Proc p1, Var p2, ListProc p3)
{
    Proc tmp = (Proc) malloc(sizeof(*tmp));
    if (!tmp)
    {
        fprintf(stderr, "Error: out of memory when allocating PMethod!\n");
        exit(1);
    }
    tmp->kind = is_PMethod;
    tmp->u.pmethod_.proc_ = p1;
    tmp->u.pmethod_.var_ = p2;
    tmp->u.pmethod_.listproc_ = p3;
    return tmp;
}

/********************   PExprs    ********************/

Proc make_PExprs(Proc p1)
{
    Proc tmp = (Proc) malloc(sizeof(*tmp));
    if (!tmp)
    {
        fprintf(stderr, "Error: out of memory when allocating PExprs!\n");
        exit(1);
    }
    tmp->kind = is_PExprs;
    tmp->u.pexprs_.proc_ = p1;
    return tmp;
}

/********************   PNot    ********************/

Proc make_PNot(Proc p1)
{
    Proc tmp = (Proc) malloc(sizeof(*tmp));
    if (!tmp)
    {
        fprintf(stderr, "Error: out of memory when allocating PNot!\n");
        exit(1);
    }
    tmp->kind = is_PNot;
    tmp->u.pnot_.proc_ = p1;
    return tmp;
}

/********************   PNeg    ********************/

Proc make_PNeg(Proc p1)
{
    Proc tmp = (Proc) malloc(sizeof(*tmp));
    if (!tmp)
    {
        fprintf(stderr, "Error: out of memory when allocating PNeg!\n");
        exit(1);
    }
    tmp->kind = is_PNeg;
    tmp->u.pneg_.proc_ = p1;
    return tmp;
}

/********************   PMult    ********************/

Proc make_PMult(Proc p1, Proc p2)
{
    Proc tmp = (Proc) malloc(sizeof(*tmp));
    if (!tmp)
    {
        fprintf(stderr, "Error: out of memory when allocating PMult!\n");
        exit(1);
    }
    tmp->kind = is_PMult;
    tmp->u.pmult_.proc_1 = p1;
    tmp->u.pmult_.proc_2 = p2;
    return tmp;
}

/********************   PDiv    ********************/

Proc make_PDiv(Proc p1, Proc p2)
{
    Proc tmp = (Proc) malloc(sizeof(*tmp));
    if (!tmp)
    {
        fprintf(stderr, "Error: out of memory when allocating PDiv!\n");
        exit(1);
    }
    tmp->kind = is_PDiv;
    tmp->u.pdiv_.proc_1 = p1;
    tmp->u.pdiv_.proc_2 = p2;
    return tmp;
}

/********************   PMod    ********************/

Proc make_PMod(Proc p1, Proc p2)
{
    Proc tmp = (Proc) malloc(sizeof(*tmp));
    if (!tmp)
    {
        fprintf(stderr, "Error: out of memory when allocating PMod!\n");
        exit(1);
    }
    tmp->kind = is_PMod;
    tmp->u.pmod_.proc_1 = p1;
    tmp->u.pmod_.proc_2 = p2;
    return tmp;
}

/********************   PPercentPercent    ********************/

Proc make_PPercentPercent(Proc p1, Proc p2)
{
    Proc tmp = (Proc) malloc(sizeof(*tmp));
    if (!tmp)
    {
        fprintf(stderr, "Error: out of memory when allocating PPercentPercent!\n");
        exit(1);
    }
    tmp->kind = is_PPercentPercent;
    tmp->u.ppercentpercent_.proc_1 = p1;
    tmp->u.ppercentpercent_.proc_2 = p2;
    return tmp;
}

/********************   PAdd    ********************/

Proc make_PAdd(Proc p1, Proc p2)
{
    Proc tmp = (Proc) malloc(sizeof(*tmp));
    if (!tmp)
    {
        fprintf(stderr, "Error: out of memory when allocating PAdd!\n");
        exit(1);
    }
    tmp->kind = is_PAdd;
    tmp->u.padd_.proc_1 = p1;
    tmp->u.padd_.proc_2 = p2;
    return tmp;
}

/********************   PMinus    ********************/

Proc make_PMinus(Proc p1, Proc p2)
{
    Proc tmp = (Proc) malloc(sizeof(*tmp));
    if (!tmp)
    {
        fprintf(stderr, "Error: out of memory when allocating PMinus!\n");
        exit(1);
    }
    tmp->kind = is_PMinus;
    tmp->u.pminus_.proc_1 = p1;
    tmp->u.pminus_.proc_2 = p2;
    return tmp;
}

/********************   PPlusPlus    ********************/

Proc make_PPlusPlus(Proc p1, Proc p2)
{
    Proc tmp = (Proc) malloc(sizeof(*tmp));
    if (!tmp)
    {
        fprintf(stderr, "Error: out of memory when allocating PPlusPlus!\n");
        exit(1);
    }
    tmp->kind = is_PPlusPlus;
    tmp->u.pplusplus_.proc_1 = p1;
    tmp->u.pplusplus_.proc_2 = p2;
    return tmp;
}

/********************   PMinusMinus    ********************/

Proc make_PMinusMinus(Proc p1, Proc p2)
{
    Proc tmp = (Proc) malloc(sizeof(*tmp));
    if (!tmp)
    {
        fprintf(stderr, "Error: out of memory when allocating PMinusMinus!\n");
        exit(1);
    }
    tmp->kind = is_PMinusMinus;
    tmp->u.pminusminus_.proc_1 = p1;
    tmp->u.pminusminus_.proc_2 = p2;
    return tmp;
}

/********************   PLt    ********************/

Proc make_PLt(Proc p1, Proc p2)
{
    Proc tmp = (Proc) malloc(sizeof(*tmp));
    if (!tmp)
    {
        fprintf(stderr, "Error: out of memory when allocating PLt!\n");
        exit(1);
    }
    tmp->kind = is_PLt;
    tmp->u.plt_.proc_1 = p1;
    tmp->u.plt_.proc_2 = p2;
    return tmp;
}

/********************   PLte    ********************/

Proc make_PLte(Proc p1, Proc p2)
{
    Proc tmp = (Proc) malloc(sizeof(*tmp));
    if (!tmp)
    {
        fprintf(stderr, "Error: out of memory when allocating PLte!\n");
        exit(1);
    }
    tmp->kind = is_PLte;
    tmp->u.plte_.proc_1 = p1;
    tmp->u.plte_.proc_2 = p2;
    return tmp;
}

/********************   PGt    ********************/

Proc make_PGt(Proc p1, Proc p2)
{
    Proc tmp = (Proc) malloc(sizeof(*tmp));
    if (!tmp)
    {
        fprintf(stderr, "Error: out of memory when allocating PGt!\n");
        exit(1);
    }
    tmp->kind = is_PGt;
    tmp->u.pgt_.proc_1 = p1;
    tmp->u.pgt_.proc_2 = p2;
    return tmp;
}

/********************   PGte    ********************/

Proc make_PGte(Proc p1, Proc p2)
{
    Proc tmp = (Proc) malloc(sizeof(*tmp));
    if (!tmp)
    {
        fprintf(stderr, "Error: out of memory when allocating PGte!\n");
        exit(1);
    }
    tmp->kind = is_PGte;
    tmp->u.pgte_.proc_1 = p1;
    tmp->u.pgte_.proc_2 = p2;
    return tmp;
}

/********************   PMatches    ********************/

Proc make_PMatches(Proc p1, Proc p2)
{
    Proc tmp = (Proc) malloc(sizeof(*tmp));
    if (!tmp)
    {
        fprintf(stderr, "Error: out of memory when allocating PMatches!\n");
        exit(1);
    }
    tmp->kind = is_PMatches;
    tmp->u.pmatches_.proc_1 = p1;
    tmp->u.pmatches_.proc_2 = p2;
    return tmp;
}

/********************   PEq    ********************/

Proc make_PEq(Proc p1, Proc p2)
{
    Proc tmp = (Proc) malloc(sizeof(*tmp));
    if (!tmp)
    {
        fprintf(stderr, "Error: out of memory when allocating PEq!\n");
        exit(1);
    }
    tmp->kind = is_PEq;
    tmp->u.peq_.proc_1 = p1;
    tmp->u.peq_.proc_2 = p2;
    return tmp;
}

/********************   PNeq    ********************/

Proc make_PNeq(Proc p1, Proc p2)
{
    Proc tmp = (Proc) malloc(sizeof(*tmp));
    if (!tmp)
    {
        fprintf(stderr, "Error: out of memory when allocating PNeq!\n");
        exit(1);
    }
    tmp->kind = is_PNeq;
    tmp->u.pneq_.proc_1 = p1;
    tmp->u.pneq_.proc_2 = p2;
    return tmp;
}

/********************   PAnd    ********************/

Proc make_PAnd(Proc p1, Proc p2)
{
    Proc tmp = (Proc) malloc(sizeof(*tmp));
    if (!tmp)
    {
        fprintf(stderr, "Error: out of memory when allocating PAnd!\n");
        exit(1);
    }
    tmp->kind = is_PAnd;
    tmp->u.pand_.proc_1 = p1;
    tmp->u.pand_.proc_2 = p2;
    return tmp;
}

/********************   POr    ********************/

Proc make_POr(Proc p1, Proc p2)
{
    Proc tmp = (Proc) malloc(sizeof(*tmp));
    if (!tmp)
    {
        fprintf(stderr, "Error: out of memory when allocating POr!\n");
        exit(1);
    }
    tmp->kind = is_POr;
    tmp->u.por_.proc_1 = p1;
    tmp->u.por_.proc_2 = p2;
    return tmp;
}

/********************   PSend    ********************/

Proc make_PSend(Name p1, Send p2, ListProc p3)
{
    Proc tmp = (Proc) malloc(sizeof(*tmp));
    if (!tmp)
    {
        fprintf(stderr, "Error: out of memory when allocating PSend!\n");
        exit(1);
    }
    tmp->kind = is_PSend;
    tmp->u.psend_.name_ = p1;
    tmp->u.psend_.send_ = p2;
    tmp->u.psend_.listproc_ = p3;
    return tmp;
}

/********************   PContr    ********************/

Proc make_PContr(Name p1, ListName p2, NameRemainder p3, Proc p4)
{
    Proc tmp = (Proc) malloc(sizeof(*tmp));
    if (!tmp)
    {
        fprintf(stderr, "Error: out of memory when allocating PContr!\n");
        exit(1);
    }
    tmp->kind = is_PContr;
    tmp->u.pcontr_.name_ = p1;
    tmp->u.pcontr_.listname_ = p2;
    tmp->u.pcontr_.nameremainder_ = p3;
    tmp->u.pcontr_.proc_ = p4;
    return tmp;
}

/********************   PInput    ********************/

Proc make_PInput(Receipt p1, Proc p2)
{
    Proc tmp = (Proc) malloc(sizeof(*tmp));
    if (!tmp)
    {
        fprintf(stderr, "Error: out of memory when allocating PInput!\n");
        exit(1);
    }
    tmp->kind = is_PInput;
    tmp->u.pinput_.receipt_ = p1;
    tmp->u.pinput_.proc_ = p2;
    return tmp;
}

/********************   PChoice    ********************/

Proc make_PChoice(ListBranch p1)
{
    Proc tmp = (Proc) malloc(sizeof(*tmp));
    if (!tmp)
    {
        fprintf(stderr, "Error: out of memory when allocating PChoice!\n");
        exit(1);
    }
    tmp->kind = is_PChoice;
    tmp->u.pchoice_.listbranch_ = p1;
    return tmp;
}

/********************   PMatch    ********************/

Proc make_PMatch(Proc p1, ListCase p2)
{
    Proc tmp = (Proc) malloc(sizeof(*tmp));
    if (!tmp)
    {
        fprintf(stderr, "Error: out of memory when allocating PMatch!\n");
        exit(1);
    }
    tmp->kind = is_PMatch;
    tmp->u.pmatch_.proc_ = p1;
    tmp->u.pmatch_.listcase_ = p2;
    return tmp;
}

/********************   PBundle    ********************/

Proc make_PBundle(Bundle p1, Proc p2)
{
    Proc tmp = (Proc) malloc(sizeof(*tmp));
    if (!tmp)
    {
        fprintf(stderr, "Error: out of memory when allocating PBundle!\n");
        exit(1);
    }
    tmp->kind = is_PBundle;
    tmp->u.pbundle_.bundle_ = p1;
    tmp->u.pbundle_.proc_ = p2;
    return tmp;
}

/********************   PIf    ********************/

Proc make_PIf(Proc p1, Proc p2)
{
    Proc tmp = (Proc) malloc(sizeof(*tmp));
    if (!tmp)
    {
        fprintf(stderr, "Error: out of memory when allocating PIf!\n");
        exit(1);
    }
    tmp->kind = is_PIf;
    tmp->u.pif_.proc_1 = p1;
    tmp->u.pif_.proc_2 = p2;
    return tmp;
}

/********************   PIfElse    ********************/

Proc make_PIfElse(Proc p1, Proc p2, Proc p3)
{
    Proc tmp = (Proc) malloc(sizeof(*tmp));
    if (!tmp)
    {
        fprintf(stderr, "Error: out of memory when allocating PIfElse!\n");
        exit(1);
    }
    tmp->kind = is_PIfElse;
    tmp->u.pifelse_.proc_1 = p1;
    tmp->u.pifelse_.proc_2 = p2;
    tmp->u.pifelse_.proc_3 = p3;
    return tmp;
}

/********************   PNew    ********************/

Proc make_PNew(ListNameDecl p1, Proc p2)
{
    Proc tmp = (Proc) malloc(sizeof(*tmp));
    if (!tmp)
    {
        fprintf(stderr, "Error: out of memory when allocating PNew!\n");
        exit(1);
    }
    tmp->kind = is_PNew;
    tmp->u.pnew_.listnamedecl_ = p1;
    tmp->u.pnew_.proc_ = p2;
    return tmp;
}

/********************   PPar    ********************/

Proc make_PPar(Proc p1, Proc p2)
{
    Proc tmp = (Proc) malloc(sizeof(*tmp));
    if (!tmp)
    {
        fprintf(stderr, "Error: out of memory when allocating PPar!\n");
        exit(1);
    }
    tmp->kind = is_PPar;
    tmp->u.ppar_.proc_1 = p1;
    tmp->u.ppar_.proc_2 = p2;
    return tmp;
}

/********************   ListProc    ********************/

ListProc make_ListProc(Proc p1, ListProc p2)
{
    ListProc tmp = (ListProc) malloc(sizeof(*tmp));
    if (!tmp)
    {
        fprintf(stderr, "Error: out of memory when allocating ListProc!\n");
        exit(1);
    }
    tmp->proc_ = p1;
    tmp->listproc_ = p2;
    return tmp;
}

/********************   ProcVarWildcard    ********************/

ProcVar make_ProcVarWildcard()
{
    ProcVar tmp = (ProcVar) malloc(sizeof(*tmp));
    if (!tmp)
    {
        fprintf(stderr, "Error: out of memory when allocating ProcVarWildcard!\n");
        exit(1);
    }
    tmp->kind = is_ProcVarWildcard;
    return tmp;
}

/********************   ProcVarVar    ********************/

ProcVar make_ProcVarVar(Var p1)
{
    ProcVar tmp = (ProcVar) malloc(sizeof(*tmp));
    if (!tmp)
    {
        fprintf(stderr, "Error: out of memory when allocating ProcVarVar!\n");
        exit(1);
    }
    tmp->kind = is_ProcVarVar;
    tmp->u.procvarvar_.var_ = p1;
    return tmp;
}

/********************   NameWildcard    ********************/

Name make_NameWildcard()
{
    Name tmp = (Name) malloc(sizeof(*tmp));
    if (!tmp)
    {
        fprintf(stderr, "Error: out of memory when allocating NameWildcard!\n");
        exit(1);
    }
    tmp->kind = is_NameWildcard;
    return tmp;
}

/********************   NameVar    ********************/

Name make_NameVar(Var p1)
{
    Name tmp = (Name) malloc(sizeof(*tmp));
    if (!tmp)
    {
        fprintf(stderr, "Error: out of memory when allocating NameVar!\n");
        exit(1);
    }
    tmp->kind = is_NameVar;
    tmp->u.namevar_.var_ = p1;
    return tmp;
}

/********************   NameQuote    ********************/

Name make_NameQuote(Proc p1)
{
    Name tmp = (Name) malloc(sizeof(*tmp));
    if (!tmp)
    {
        fprintf(stderr, "Error: out of memory when allocating NameQuote!\n");
        exit(1);
    }
    tmp->kind = is_NameQuote;
    tmp->u.namequote_.proc_ = p1;
    return tmp;
}

/********************   ListName    ********************/

ListName make_ListName(Name p1, ListName p2)
{
    ListName tmp = (ListName) malloc(sizeof(*tmp));
    if (!tmp)
    {
        fprintf(stderr, "Error: out of memory when allocating ListName!\n");
        exit(1);
    }
    tmp->name_ = p1;
    tmp->listname_ = p2;
    return tmp;
}

/********************   BundleWrite    ********************/

Bundle make_BundleWrite()
{
    Bundle tmp = (Bundle) malloc(sizeof(*tmp));
    if (!tmp)
    {
        fprintf(stderr, "Error: out of memory when allocating BundleWrite!\n");
        exit(1);
    }
    tmp->kind = is_BundleWrite;
    return tmp;
}

/********************   BundleRead    ********************/

Bundle make_BundleRead()
{
    Bundle tmp = (Bundle) malloc(sizeof(*tmp));
    if (!tmp)
    {
        fprintf(stderr, "Error: out of memory when allocating BundleRead!\n");
        exit(1);
    }
    tmp->kind = is_BundleRead;
    return tmp;
}

/********************   BundleEquiv    ********************/

Bundle make_BundleEquiv()
{
    Bundle tmp = (Bundle) malloc(sizeof(*tmp));
    if (!tmp)
    {
        fprintf(stderr, "Error: out of memory when allocating BundleEquiv!\n");
        exit(1);
    }
    tmp->kind = is_BundleEquiv;
    return tmp;
}

/********************   BundleReadWrite    ********************/

Bundle make_BundleReadWrite()
{
    Bundle tmp = (Bundle) malloc(sizeof(*tmp));
    if (!tmp)
    {
        fprintf(stderr, "Error: out of memory when allocating BundleReadWrite!\n");
        exit(1);
    }
    tmp->kind = is_BundleReadWrite;
    return tmp;
}

/********************   ReceiptLinear    ********************/

Receipt make_ReceiptLinear(ReceiptLinearImpl p1)
{
    Receipt tmp = (Receipt) malloc(sizeof(*tmp));
    if (!tmp)
    {
        fprintf(stderr, "Error: out of memory when allocating ReceiptLinear!\n");
        exit(1);
    }
    tmp->kind = is_ReceiptLinear;
    tmp->u.receiptlinear_.receiptlinearimpl_ = p1;
    return tmp;
}

/********************   ReceiptRepeated    ********************/

Receipt make_ReceiptRepeated(ReceiptRepeatedImpl p1)
{
    Receipt tmp = (Receipt) malloc(sizeof(*tmp));
    if (!tmp)
    {
        fprintf(stderr, "Error: out of memory when allocating ReceiptRepeated!\n");
        exit(1);
    }
    tmp->kind = is_ReceiptRepeated;
    tmp->u.receiptrepeated_.receiptrepeatedimpl_ = p1;
    return tmp;
}

/********************   ReceiptPeek    ********************/

Receipt make_ReceiptPeek(ReceiptPeekImpl p1)
{
    Receipt tmp = (Receipt) malloc(sizeof(*tmp));
    if (!tmp)
    {
        fprintf(stderr, "Error: out of memory when allocating ReceiptPeek!\n");
        exit(1);
    }
    tmp->kind = is_ReceiptPeek;
    tmp->u.receiptpeek_.receiptpeekimpl_ = p1;
    return tmp;
}

/********************   LinearSimple    ********************/

ReceiptLinearImpl make_LinearSimple(ListLinearBind p1)
{
    ReceiptLinearImpl tmp = (ReceiptLinearImpl) malloc(sizeof(*tmp));
    if (!tmp)
    {
        fprintf(stderr, "Error: out of memory when allocating LinearSimple!\n");
        exit(1);
    }
    tmp->kind = is_LinearSimple;
    tmp->u.linearsimple_.listlinearbind_ = p1;
    return tmp;
}

/********************   LinearBindImpl    ********************/

LinearBind make_LinearBindImpl(ListName p1, NameRemainder p2, Name p3)
{
    LinearBind tmp = (LinearBind) malloc(sizeof(*tmp));
    if (!tmp)
    {
        fprintf(stderr, "Error: out of memory when allocating LinearBindImpl!\n");
        exit(1);
    }
    tmp->kind = is_LinearBindImpl;
    tmp->u.linearbindimpl_.listname_ = p1;
    tmp->u.linearbindimpl_.nameremainder_ = p2;
    tmp->u.linearbindimpl_.name_ = p3;
    return tmp;
}

/********************   ListLinearBind    ********************/

ListLinearBind make_ListLinearBind(LinearBind p1, ListLinearBind p2)
{
    ListLinearBind tmp = (ListLinearBind) malloc(sizeof(*tmp));
    if (!tmp)
    {
        fprintf(stderr, "Error: out of memory when allocating ListLinearBind!\n");
        exit(1);
    }
    tmp->linearbind_ = p1;
    tmp->listlinearbind_ = p2;
    return tmp;
}

/********************   RepeatedSimple    ********************/

ReceiptRepeatedImpl make_RepeatedSimple(ListRepeatedBind p1)
{
    ReceiptRepeatedImpl tmp = (ReceiptRepeatedImpl) malloc(sizeof(*tmp));
    if (!tmp)
    {
        fprintf(stderr, "Error: out of memory when allocating RepeatedSimple!\n");
        exit(1);
    }
    tmp->kind = is_RepeatedSimple;
    tmp->u.repeatedsimple_.listrepeatedbind_ = p1;
    return tmp;
}

/********************   RepeatedBindImpl    ********************/

RepeatedBind make_RepeatedBindImpl(ListName p1, NameRemainder p2, Name p3)
{
    RepeatedBind tmp = (RepeatedBind) malloc(sizeof(*tmp));
    if (!tmp)
    {
        fprintf(stderr, "Error: out of memory when allocating RepeatedBindImpl!\n");
        exit(1);
    }
    tmp->kind = is_RepeatedBindImpl;
    tmp->u.repeatedbindimpl_.listname_ = p1;
    tmp->u.repeatedbindimpl_.nameremainder_ = p2;
    tmp->u.repeatedbindimpl_.name_ = p3;
    return tmp;
}

/********************   ListRepeatedBind    ********************/

ListRepeatedBind make_ListRepeatedBind(RepeatedBind p1, ListRepeatedBind p2)
{
    ListRepeatedBind tmp = (ListRepeatedBind) malloc(sizeof(*tmp));
    if (!tmp)
    {
        fprintf(stderr, "Error: out of memory when allocating ListRepeatedBind!\n");
        exit(1);
    }
    tmp->repeatedbind_ = p1;
    tmp->listrepeatedbind_ = p2;
    return tmp;
}

/********************   PeekSimple    ********************/

ReceiptPeekImpl make_PeekSimple(ListPeekBind p1)
{
    ReceiptPeekImpl tmp = (ReceiptPeekImpl) malloc(sizeof(*tmp));
    if (!tmp)
    {
        fprintf(stderr, "Error: out of memory when allocating PeekSimple!\n");
        exit(1);
    }
    tmp->kind = is_PeekSimple;
    tmp->u.peeksimple_.listpeekbind_ = p1;
    return tmp;
}

/********************   PeekBindImpl    ********************/

PeekBind make_PeekBindImpl(ListName p1, NameRemainder p2, Name p3)
{
    PeekBind tmp = (PeekBind) malloc(sizeof(*tmp));
    if (!tmp)
    {
        fprintf(stderr, "Error: out of memory when allocating PeekBindImpl!\n");
        exit(1);
    }
    tmp->kind = is_PeekBindImpl;
    tmp->u.peekbindimpl_.listname_ = p1;
    tmp->u.peekbindimpl_.nameremainder_ = p2;
    tmp->u.peekbindimpl_.name_ = p3;
    return tmp;
}

/********************   ListPeekBind    ********************/

ListPeekBind make_ListPeekBind(PeekBind p1, ListPeekBind p2)
{
    ListPeekBind tmp = (ListPeekBind) malloc(sizeof(*tmp));
    if (!tmp)
    {
        fprintf(stderr, "Error: out of memory when allocating ListPeekBind!\n");
        exit(1);
    }
    tmp->peekbind_ = p1;
    tmp->listpeekbind_ = p2;
    return tmp;
}

/********************   SendSingle    ********************/

Send make_SendSingle()
{
    Send tmp = (Send) malloc(sizeof(*tmp));
    if (!tmp)
    {
        fprintf(stderr, "Error: out of memory when allocating SendSingle!\n");
        exit(1);
    }
    tmp->kind = is_SendSingle;
    return tmp;
}

/********************   SendMultiple    ********************/

Send make_SendMultiple()
{
    Send tmp = (Send) malloc(sizeof(*tmp));
    if (!tmp)
    {
        fprintf(stderr, "Error: out of memory when allocating SendMultiple!\n");
        exit(1);
    }
    tmp->kind = is_SendMultiple;
    return tmp;
}

/********************   BranchImpl    ********************/

Branch make_BranchImpl(ReceiptLinearImpl p1, Proc p2)
{
    Branch tmp = (Branch) malloc(sizeof(*tmp));
    if (!tmp)
    {
        fprintf(stderr, "Error: out of memory when allocating BranchImpl!\n");
        exit(1);
    }
    tmp->kind = is_BranchImpl;
    tmp->u.branchimpl_.receiptlinearimpl_ = p1;
    tmp->u.branchimpl_.proc_ = p2;
    return tmp;
}

/********************   ListBranch    ********************/

ListBranch make_ListBranch(Branch p1, ListBranch p2)
{
    ListBranch tmp = (ListBranch) malloc(sizeof(*tmp));
    if (!tmp)
    {
        fprintf(stderr, "Error: out of memory when allocating ListBranch!\n");
        exit(1);
    }
    tmp->branch_ = p1;
    tmp->listbranch_ = p2;
    return tmp;
}

/********************   CaseImpl    ********************/

Case make_CaseImpl(Proc p1, Proc p2)
{
    Case tmp = (Case) malloc(sizeof(*tmp));
    if (!tmp)
    {
        fprintf(stderr, "Error: out of memory when allocating CaseImpl!\n");
        exit(1);
    }
    tmp->kind = is_CaseImpl;
    tmp->u.caseimpl_.proc_1 = p1;
    tmp->u.caseimpl_.proc_2 = p2;
    return tmp;
}

/********************   ListCase    ********************/

ListCase make_ListCase(Case p1, ListCase p2)
{
    ListCase tmp = (ListCase) malloc(sizeof(*tmp));
    if (!tmp)
    {
        fprintf(stderr, "Error: out of memory when allocating ListCase!\n");
        exit(1);
    }
    tmp->case_ = p1;
    tmp->listcase_ = p2;
    return tmp;
}

/********************   NameDeclSimpl    ********************/

NameDecl make_NameDeclSimpl(Var p1)
{
    NameDecl tmp = (NameDecl) malloc(sizeof(*tmp));
    if (!tmp)
    {
        fprintf(stderr, "Error: out of memory when allocating NameDeclSimpl!\n");
        exit(1);
    }
    tmp->kind = is_NameDeclSimpl;
    tmp->u.namedeclsimpl_.var_ = p1;
    return tmp;
}

/********************   NameDeclUrn    ********************/

NameDecl make_NameDeclUrn(Var p1, UriLiteral p2)
{
    NameDecl tmp = (NameDecl) malloc(sizeof(*tmp));
    if (!tmp)
    {
        fprintf(stderr, "Error: out of memory when allocating NameDeclUrn!\n");
        exit(1);
    }
    tmp->kind = is_NameDeclUrn;
    tmp->u.namedeclurn_.var_ = p1;
    tmp->u.namedeclurn_.uriliteral_ = p2;
    return tmp;
}

/********************   ListNameDecl    ********************/

ListNameDecl make_ListNameDecl(NameDecl p1, ListNameDecl p2)
{
    ListNameDecl tmp = (ListNameDecl) malloc(sizeof(*tmp));
    if (!tmp)
    {
        fprintf(stderr, "Error: out of memory when allocating ListNameDecl!\n");
        exit(1);
    }
    tmp->namedecl_ = p1;
    tmp->listnamedecl_ = p2;
    return tmp;
}

/********************   BoolTrue    ********************/

BoolLiteral make_BoolTrue()
{
    BoolLiteral tmp = (BoolLiteral) malloc(sizeof(*tmp));
    if (!tmp)
    {
        fprintf(stderr, "Error: out of memory when allocating BoolTrue!\n");
        exit(1);
    }
    tmp->kind = is_BoolTrue;
    return tmp;
}

/********************   BoolFalse    ********************/

BoolLiteral make_BoolFalse()
{
    BoolLiteral tmp = (BoolLiteral) malloc(sizeof(*tmp));
    if (!tmp)
    {
        fprintf(stderr, "Error: out of memory when allocating BoolFalse!\n");
        exit(1);
    }
    tmp->kind = is_BoolFalse;
    return tmp;
}

/********************   GroundBool    ********************/

Ground make_GroundBool(BoolLiteral p1)
{
    Ground tmp = (Ground) malloc(sizeof(*tmp));
    if (!tmp)
    {
        fprintf(stderr, "Error: out of memory when allocating GroundBool!\n");
        exit(1);
    }
    tmp->kind = is_GroundBool;
    tmp->u.groundbool_.boolliteral_ = p1;
    return tmp;
}

/********************   GroundInt    ********************/

Ground make_GroundInt(LongLiteral p1)
{
    Ground tmp = (Ground) malloc(sizeof(*tmp));
    if (!tmp)
    {
        fprintf(stderr, "Error: out of memory when allocating GroundInt!\n");
        exit(1);
    }
    tmp->kind = is_GroundInt;
    tmp->u.groundint_.longliteral_ = p1;
    return tmp;
}

/********************   GroundString    ********************/

Ground make_GroundString(StringLiteral p1)
{
    Ground tmp = (Ground) malloc(sizeof(*tmp));
    if (!tmp)
    {
        fprintf(stderr, "Error: out of memory when allocating GroundString!\n");
        exit(1);
    }
    tmp->kind = is_GroundString;
    tmp->u.groundstring_.stringliteral_ = p1;
    return tmp;
}

/********************   GroundUri    ********************/

Ground make_GroundUri(UriLiteral p1)
{
    Ground tmp = (Ground) malloc(sizeof(*tmp));
    if (!tmp)
    {
        fprintf(stderr, "Error: out of memory when allocating GroundUri!\n");
        exit(1);
    }
    tmp->kind = is_GroundUri;
    tmp->u.grounduri_.uriliteral_ = p1;
    return tmp;
}

/********************   CollectList    ********************/

Collection make_CollectList(ListProc p1, ProcRemainder p2)
{
    Collection tmp = (Collection) malloc(sizeof(*tmp));
    if (!tmp)
    {
        fprintf(stderr, "Error: out of memory when allocating CollectList!\n");
        exit(1);
    }
    tmp->kind = is_CollectList;
    tmp->u.collectlist_.listproc_ = p1;
    tmp->u.collectlist_.procremainder_ = p2;
    return tmp;
}

/********************   CollectTuple    ********************/

Collection make_CollectTuple(Tuple p1)
{
    Collection tmp = (Collection) malloc(sizeof(*tmp));
    if (!tmp)
    {
        fprintf(stderr, "Error: out of memory when allocating CollectTuple!\n");
        exit(1);
    }
    tmp->kind = is_CollectTuple;
    tmp->u.collecttuple_.tuple_ = p1;
    return tmp;
}

/********************   CollectSet    ********************/

Collection make_CollectSet(ListProc p1, ProcRemainder p2)
{
    Collection tmp = (Collection) malloc(sizeof(*tmp));
    if (!tmp)
    {
        fprintf(stderr, "Error: out of memory when allocating CollectSet!\n");
        exit(1);
    }
    tmp->kind = is_CollectSet;
    tmp->u.collectset_.listproc_ = p1;
    tmp->u.collectset_.procremainder_ = p2;
    return tmp;
}

/********************   CollectMap    ********************/

Collection make_CollectMap(ListKeyValuePair p1, ProcRemainder p2)
{
    Collection tmp = (Collection) malloc(sizeof(*tmp));
    if (!tmp)
    {
        fprintf(stderr, "Error: out of memory when allocating CollectMap!\n");
        exit(1);
    }
    tmp->kind = is_CollectMap;
    tmp->u.collectmap_.listkeyvaluepair_ = p1;
    tmp->u.collectmap_.procremainder_ = p2;
    return tmp;
}

/********************   KeyValuePairImpl    ********************/

KeyValuePair make_KeyValuePairImpl(Proc p1, Proc p2)
{
    KeyValuePair tmp = (KeyValuePair) malloc(sizeof(*tmp));
    if (!tmp)
    {
        fprintf(stderr, "Error: out of memory when allocating KeyValuePairImpl!\n");
        exit(1);
    }
    tmp->kind = is_KeyValuePairImpl;
    tmp->u.keyvaluepairimpl_.proc_1 = p1;
    tmp->u.keyvaluepairimpl_.proc_2 = p2;
    return tmp;
}

/********************   ListKeyValuePair    ********************/

ListKeyValuePair make_ListKeyValuePair(KeyValuePair p1, ListKeyValuePair p2)
{
    ListKeyValuePair tmp = (ListKeyValuePair) malloc(sizeof(*tmp));
    if (!tmp)
    {
        fprintf(stderr, "Error: out of memory when allocating ListKeyValuePair!\n");
        exit(1);
    }
    tmp->keyvaluepair_ = p1;
    tmp->listkeyvaluepair_ = p2;
    return tmp;
}

/********************   TupleSingle    ********************/

Tuple make_TupleSingle(Proc p1)
{
    Tuple tmp = (Tuple) malloc(sizeof(*tmp));
    if (!tmp)
    {
        fprintf(stderr, "Error: out of memory when allocating TupleSingle!\n");
        exit(1);
    }
    tmp->kind = is_TupleSingle;
    tmp->u.tuplesingle_.proc_ = p1;
    return tmp;
}

/********************   TupleMultiple    ********************/

Tuple make_TupleMultiple(Proc p1, ListProc p2)
{
    Tuple tmp = (Tuple) malloc(sizeof(*tmp));
    if (!tmp)
    {
        fprintf(stderr, "Error: out of memory when allocating TupleMultiple!\n");
        exit(1);
    }
    tmp->kind = is_TupleMultiple;
    tmp->u.tuplemultiple_.proc_ = p1;
    tmp->u.tuplemultiple_.listproc_ = p2;
    return tmp;
}

/********************   ProcRemainderVar    ********************/

ProcRemainder make_ProcRemainderVar(ProcVar p1)
{
    ProcRemainder tmp = (ProcRemainder) malloc(sizeof(*tmp));
    if (!tmp)
    {
        fprintf(stderr, "Error: out of memory when allocating ProcRemainderVar!\n");
        exit(1);
    }
    tmp->kind = is_ProcRemainderVar;
    tmp->u.procremaindervar_.procvar_ = p1;
    return tmp;
}

/********************   ProcRemainderEmpty    ********************/

ProcRemainder make_ProcRemainderEmpty()
{
    ProcRemainder tmp = (ProcRemainder) malloc(sizeof(*tmp));
    if (!tmp)
    {
        fprintf(stderr, "Error: out of memory when allocating ProcRemainderEmpty!\n");
        exit(1);
    }
    tmp->kind = is_ProcRemainderEmpty;
    return tmp;
}

/********************   NameRemainderVar    ********************/

NameRemainder make_NameRemainderVar(ProcVar p1)
{
    NameRemainder tmp = (NameRemainder) malloc(sizeof(*tmp));
    if (!tmp)
    {
        fprintf(stderr, "Error: out of memory when allocating NameRemainderVar!\n");
        exit(1);
    }
    tmp->kind = is_NameRemainderVar;
    tmp->u.nameremaindervar_.procvar_ = p1;
    return tmp;
}

/********************   NameRemainderEmpty    ********************/

NameRemainder make_NameRemainderEmpty()
{
    NameRemainder tmp = (NameRemainder) malloc(sizeof(*tmp));
    if (!tmp)
    {
        fprintf(stderr, "Error: out of memory when allocating NameRemainderEmpty!\n");
        exit(1);
    }
    tmp->kind = is_NameRemainderEmpty;
    return tmp;
}

/********************   VarRefKindProc    ********************/

VarRefKind make_VarRefKindProc()
{
    VarRefKind tmp = (VarRefKind) malloc(sizeof(*tmp));
    if (!tmp)
    {
        fprintf(stderr, "Error: out of memory when allocating VarRefKindProc!\n");
        exit(1);
    }
    tmp->kind = is_VarRefKindProc;
    return tmp;
}

/********************   VarRefKindName    ********************/

VarRefKind make_VarRefKindName()
{
    VarRefKind tmp = (VarRefKind) malloc(sizeof(*tmp));
    if (!tmp)
    {
        fprintf(stderr, "Error: out of memory when allocating VarRefKindName!\n");
        exit(1);
    }
    tmp->kind = is_VarRefKindName;
    return tmp;
}

/********************   SimpleTypeBool    ********************/

SimpleType make_SimpleTypeBool()
{
    SimpleType tmp = (SimpleType) malloc(sizeof(*tmp));
    if (!tmp)
    {
        fprintf(stderr, "Error: out of memory when allocating SimpleTypeBool!\n");
        exit(1);
    }
    tmp->kind = is_SimpleTypeBool;
    return tmp;
}

/********************   SimpleTypeInt    ********************/

SimpleType make_SimpleTypeInt()
{
    SimpleType tmp = (SimpleType) malloc(sizeof(*tmp));
    if (!tmp)
    {
        fprintf(stderr, "Error: out of memory when allocating SimpleTypeInt!\n");
        exit(1);
    }
    tmp->kind = is_SimpleTypeInt;
    return tmp;
}

/********************   SimpleTypeString    ********************/

SimpleType make_SimpleTypeString()
{
    SimpleType tmp = (SimpleType) malloc(sizeof(*tmp));
    if (!tmp)
    {
        fprintf(stderr, "Error: out of memory when allocating SimpleTypeString!\n");
        exit(1);
    }
    tmp->kind = is_SimpleTypeString;
    return tmp;
}

/********************   SimpleTypeUri    ********************/

SimpleType make_SimpleTypeUri()
{
    SimpleType tmp = (SimpleType) malloc(sizeof(*tmp));
    if (!tmp)
    {
        fprintf(stderr, "Error: out of memory when allocating SimpleTypeUri!\n");
        exit(1);
    }
    tmp->kind = is_SimpleTypeUri;
    return tmp;
}

/********************   SimpleTypeByteArray    ********************/

SimpleType make_SimpleTypeByteArray()
{
    SimpleType tmp = (SimpleType) malloc(sizeof(*tmp));
    if (!tmp)
    {
        fprintf(stderr, "Error: out of memory when allocating SimpleTypeByteArray!\n");
        exit(1);
    }
    tmp->kind = is_SimpleTypeByteArray;
    return tmp;
}
