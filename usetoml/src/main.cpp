#include "../include/toml.h"
#include <cstdlib>
#include <cstring>
#include <cstdio>

int globals[] = {0, 0, 0};


void LoadConfig(const char* filename) {
    FILE* fp = fopen(filename, "r");
    if (!fp) {
        printf("error opening config '%s'\n", filename);
        return;
    }
    toml_table_t* conf = toml_parse_file(fp, NULL, 0);  
    fclose(fp);

    if (!conf) {
        printf("error parsing config file\n");
        return;
    }

    toml_table_t* global_table = toml_table_in(conf, "global");
    if (global_table) {
        printf("Globals:\n");
        for (int i = 0; ; i++) {
            const char* key = toml_key_in(global_table, i);
            if (!key) break;  // No more keys
            printf("i: %d\n", i);

            toml_datum_t value = toml_int_in(global_table, key);
            if (value.ok) {
                printf("%s = %lld\n", key, value.u.i);
            } else {
                value = toml_string_in(global_table, key);
                if (value.ok) {
                    if (i < 3){
                        globals[i] = value.u.d;
                    }
                    free(value.u.s);
                } else {
                    fprintf(stderr, "Failed to parse value for %s\n", key);
                }
            }
        }
    }
    toml_array_t* entry_array = toml_array_in(conf, "entry");
    if (entry_array) {
        printf("Entries:\n");
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
            }
        }
    }
    toml_free(conf);   
}


int main(int argc, char** argv) {
    
    const char* default_filename = "config.toml";
    for (int i = 0; i < sizeof(globals)/sizeof(globals[0]) ; i++){
        printf("globals[%d] = %d\n", i, globals[i]);
    }
        
    if (argc == 3 && strcmp(argv[1], "-c") == 0) {
        printf("using selected config: %s\n", argv[2]);
        LoadConfig(argv[2]);
    } else if (argc == 1) {
        printf("using default config: %s\n", default_filename);
        LoadConfig(default_filename);
    } else {
        printf("Usage: %s -c <path/to/your_config.toml>\n", argv[0]);
        return 1;
    }

    

    return 0;
}