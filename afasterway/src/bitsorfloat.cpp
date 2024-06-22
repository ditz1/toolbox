#include "../include/bitsorfloat.hpp"

void Record::AddEntry(Entry e) {
    _data.push_back(e);
}

void Record::AddEntries(std::vector<Entry> entries) {
    _data.insert(_data.end(), entries.begin(), entries.end());
}

void Record::PrintAllEntries() {
    for (const auto& entry : _data) {
        entry.printbytes();
    }
}

void Record::PrintGroupEntries(Group g) {
    for (const auto& entry : _data) {
        if (entry.group == g) {
            entry.printbytes();
        }
    }
}

void Record::PrintAnotherGroupEntries(AnotherGroup ag) {
    for (const auto& entry : _data) {
        if (entry.another_group == ag) {
            entry.printbytes();
        }
    }
}

void print_bytes(const std::vector<Record>& records) {
    for (const auto& record : records) {
        for (const auto& entry : record.datar()) {
            printf("Group: ");
            switch (entry.group) {
                case Group::A: printf("A, "); break;
                case Group::B: printf("B, "); break;
                case Group::C: printf("C, "); break;
                case Group::D: printf("D, "); break;
                case Group::E: printf("E, "); break;
                case Group::F: printf("F, "); break;
                default: printf("Unknown, ");
            }
            
            printf("Another Group: ");
            switch (entry.another_group) {
                case AnotherGroup::U: printf("U, "); break;
                case AnotherGroup::W: printf("W, "); break;
                case AnotherGroup::X: printf("X, "); break;
                case AnotherGroup::Y: printf("Y, "); break;
                case AnotherGroup::Z: printf("Z, "); break;
                default: printf("Unknown, ");
            }
            
            printf("Data: %x | %x | %x | %x\n", 
                   entry.data.bytes.b0, entry.data.bytes.b1, 
                   entry.data.bytes.b2, entry.data.bytes.b3);
        }
        printf("\n");
    }
}

Group GroupFromString(const char* s) {
    if (s == "A") return Group::A;
    if (s == "B") return Group::B;
    if (s == "C") return Group::C;
    if (s == "D") return Group::D;
    if (s == "E") return Group::E;
    if (s == "F") return Group::F;
    return Group::A;
}
AnotherGroup AnotherGroupFromString(const char* s) {
    if (s == "U") return AnotherGroup::U;
    if (s == "W") return AnotherGroup::W;
    if (s == "X") return AnotherGroup::X;
    if (s == "Y") return AnotherGroup::Y;
    if (s == "Z") return AnotherGroup::Z;
    return AnotherGroup::U;
}