#include "ICTranslator.h"

ICTranslator *ICTranslator::self = nullptr;

ICTranslator *ICTranslator::getInstance() {
    if (self == nullptr) {
        self = new ICTranslator();
    }
    return self;
}

ICTranslator::ICTranslator() {
    icEntries = new std::vector<ICEntry *>;
}

ICTranslator::~ICTranslator() {
    for (const auto *pItem: *icEntries) delete pItem;
    delete icEntries;
}

void ICTranslator::translate_ConstVarDef(bool isGlobal, SymbolTableEntry *tableEntry) const {
    auto icItemVar = new ICItemVar(tableEntry->getName(), tableEntry,
                                   true, isGlobal, tableEntry->varGet());
    auto *icEntry = new ICEntry(ICEntryType::ConstVarDefine, icItemVar);
    icEntries->push_back(icEntry);
}

void ICTranslator::translate_ConstArray1Def(bool isGlobal, SymbolTableEntry *tableEntry, int d1) const {
    auto icItemArray = new ICItemArray(tableEntry->getName(), tableEntry, isGlobal, true, d1,
                                       tableEntry->array1ConstGetAll());
    auto *icEntry = new ICEntry(ICEntryType::ConstArrayDefine, icItemArray);
    icEntries->push_back(icEntry);
}

void ICTranslator::translate_ConstArray2Def(bool isGlobal, SymbolTableEntry *tableEntry,
                                            int d1, int d2) const {
    int **oldArray = tableEntry->array2ConstGetAll();
    int *newArray = new int[d1 * d2];

    int k = 0;
    for (int i = 0; i < d1; ++i) {
        for (int j = 0; j < d2; ++j) {
            newArray[k++] = oldArray[i][j];
        }
    }

    auto icItemArray = new ICItemArray(tableEntry->getName(), tableEntry, isGlobal,
                                       true, d1 * d2, newArray);
    auto *icEntry = new ICEntry(ICEntryType::ConstArrayDefine, icItemArray);
    icEntries->push_back(icEntry);
}



