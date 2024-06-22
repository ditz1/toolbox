#include "../include/bitsorfloat.hpp"
#include "../include/toml.h"
#include <thread>
#include <random>

int total_entries = 200;

std::vector<Record> records;

void populate_records() {
    std::random_device rd;
    std::mt19937 gen(rd());
    std::uniform_real_distribution<float> float_dist(0.0f, 300.0f);
    std::uniform_int_distribution<int> group_dist(0, static_cast<int>(Group::F) - 1);
    std::uniform_int_distribution<int> another_group_dist(0, static_cast<int>(AnotherGroup::Z) - 1);

    for (int i = 0; i < total_entries; ++i) {
        float f = float_dist(gen);
        Group g = static_cast<Group>(group_dist(gen));
        AnotherGroup ag = static_cast<AnotherGroup>(another_group_dist(gen));
        BitsOrFloat bof;
        bof.f = f;
        Entry entry(g, ag, bof);

        if (records.size() <= i) {
            records.emplace_back(std::vector<Entry>{entry});
        } else {
            records[i].AddEntry(entry);
        }
    }
}

void print_all_records() {
    printf("All Records:\n");
    for (size_t i = 0; i < records.size(); ++i) {
        printf("Record %zu:\n", i);
        records[i].PrintAllEntries();
        printf("\n");
    }
}

void load_searches_from_toml(const char* filename) {
    FILE* fp = fopen(filename, "r");
    if (!fp) {
        printf("Error opening file '%s'\n", filename);
        return;
    }
    int records_added = 0; 

    toml_table_t* conf = toml_parse_file(fp, NULL, 0);  
    fclose(fp);

    if (!conf) {
        printf("Error parsing TOML file\n");
        return;
    }

    toml_table_t* global_table = toml_table_in(conf, "global");
    if (global_table) {
        toml_datum_t num_entries_datum = toml_int_in(global_table, "num_entries");
        if (num_entries_datum.ok) {
            int num_entries = num_entries_datum.u.i;
            printf("Global Configuration:\n");
            printf("  num_entries: %d\n", num_entries);
            total_entries = num_entries;
        }
    }

    toml_array_t* entry_array = toml_array_in(conf, "entry");
    if (entry_array) {
        printf("Search Configurations:\n");
        for (int i = 0; ; i++) {
            toml_table_t* entry = toml_table_at(entry_array, i);
            if (!entry) break;

            toml_datum_t group_datum = toml_string_in(entry, "group");
            toml_datum_t another_group_datum = toml_string_in(entry, "another_group");
            toml_datum_t value_datum = toml_double_in(entry, "value");

            if (group_datum.ok && another_group_datum.ok && value_datum.ok) {
                const char* group_str = group_datum.u.s;
                const char* another_group_str = another_group_datum.u.s;
                float value = value_datum.u.d;

                printf("  Entry %d:\n", i);
                printf("    group: %s\n", group_str);
                printf("    another_group: %s\n", another_group_str);
                printf("    value: %.2f\n", value);
                BitsOrFloat val;
                val.f = value;
                Entry entry(GroupFromString(group_str), AnotherGroupFromString(another_group_str), val );
                records.emplace_back(std::vector<Entry>{entry});
                records_added++;
            }
        }
    }
    printf("Records added: %d\n", records_added);
    toml_free(conf);
}

void GetGroups(Group g, AnotherGroup ag) {
    auto start_time = std::chrono::high_resolution_clock::now();

    printf("\n // entries for group %c and another group %c: //\n", 'A' + static_cast<int>(g), 'U' + static_cast<int>(ag));

    int num_records_found = 0;
    for (const auto& record : records) {
        for (const auto& entry : record.datar()) {
            if (entry.group == g && entry.another_group == ag) {
                num_records_found++;
            }
        }
    }

    auto end_time = std::chrono::high_resolution_clock::now();
    auto duration = std::chrono::duration_cast<std::chrono::microseconds>(end_time - start_time);
    float seconds = ((float)duration.count()) / 1000000.0f;
    printf("search time: %lld microseconds, %f seconds\n", duration.count(), seconds);
    printf("total records: %d\n", total_entries);
    printf("records found: %d\n", num_records_found);
}

int main() {
    load_searches_from_toml("config.toml");
    populate_records();

    BitsOrFloat bof;
    bof.f = 100.0f;
    records.emplace_back(std::vector<Entry>{Entry(Group::F, AnotherGroup::Z, bof)});

    //print_all_records();
    //printf("\n Searching for Group A and AnotherGroup X:\n");
    GetGroups(Group::D, AnotherGroup::Z);

    std::this_thread::sleep_for(std::chrono::milliseconds(200));

    //printf("\n Searching for Group B and AnotherGroup U:\n");
    GetGroups(Group::C, AnotherGroup::Y);

    return 0;
}