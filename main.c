#include <stdio.h>

#define TYPE_NULL    0
#define TYPE_INTEGER 1
#define TYPE_LONG    2
#define TYPE_REAL    3
#define TYPE_CSET    4
#define TYPE_FILE    5
#define TYPE_PROC    6
#define TYPE_LIST    7
#define TYPE_TABLE   8
#define TYPE_RECORD  9
#define TYPE_TELEM   10
#define TYPE_LELEM   11
#define TYPE_TVSUBS  12
#define TYPE_TVKYWD  13
#define TYPE_TVTBL   14
#define TYPE_SET     15
#define TYPE_SELEM   16
#define TYPE_REFRESH 17
#define TYPE_COEXPR  18

// TODO: What should the values of this flags be?
// Book just says "depends on the word size of the computer"
// On 64-bit computer, word size is 8
#define FLAG_NOT_QUALIFIER 0 // n - differentiates qualifies (descriptors that point to strings) from other descriptor types
#define FLAG_PTR           1 // p - specifies that the v-word contains a pointer to a block
#define FLAG_VAR           2 // v -
#define FLAG_TVAR          3 // t -

#define D_NULL    (TYPE_NULL | FLAG_NOT_QUALIFIER)
#define D_INTEGER (TYPE_INTEGER | FLAG_NOT_QUALIFIER)
#define D_LONG    (TYPE_LONG | FLAG_PTR | FLAG_NOT_QUALIFIER)
#define D_TVSUBS  (TYPE_TVSUBS | D_TVAR)
#define D_TVKYWD  (TYPE_TVKYWD | D_TVAR)

#define D_VAR     (FLAG_VAR | FLAG_NOT_QUALIFIER | FLAG_PTR)
#define D_TVAR    (D_VAR | FLAG_TVAR)

typedef long word;
typedef unsigned long uword;

struct Descriptor {
    word dword;
    union {
        word integerValue;
        char *stringValue;
        union Block *blockPointer;
        struct Descriptor *descriptorPointer; // Pointer to another Descriptor in the case of a variable
    } vword;
};

struct RecordBlock { // record Block
    word title;
    word blockSize;
    struct Descriptor recordConstructor;
    struct Descriptor fields[1];
};

struct KeywordTrappedVariableBlock { // keyword trapped variable Block
    word title;

    int (*putval)();

    struct Descriptor keywordValue;
    struct Descriptor keywordName;
};

union Block {
    //struct IntBlock intBlock;
    //struct RealBlock realBlock;
    //struct CSetBlock cSetBlock;
    //struct FileBlock fileBlock;
    //struct ProcBlock procBlock;
    //struct ListBlock listBlock;
    //struct LElemBlock lElemBlock;
    //struct TableBlock tableBlock;
    //struct TElemBlock tElemBlock;
    //struct SetBlock setBlock;
    //struct SElemBlock sElemBlock;
    struct RecordBlock recordBlock;
    struct KeywordTrappedVariableBlock keywordTrappedVariableBlock;
    //struct TVSubsBlock tvSubsBlock;
    //struct TVTBLBlock tvtblBlock;
    //struct CoExprBlock coExprBlock;
    //struct RefreshBlock refreshBlock;
};

int main() {
    printf("%lu", sizeof(int));
    return 0;
}
