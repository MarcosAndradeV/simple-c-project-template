
#define NOB_IMPLEMENTATION
#define NOB_STRIP_PREFIX
#define NOB_EXPERIMENTAL_DELETE_OLD
#include "nob.h"

#define BIN_PATH "build/sc"

static Cmd cmd = {0};

int main(int argc, char **argv)
{
    NOB_GO_REBUILD_URSELF(argc, argv);

    if(argc >= 1) (void)shift(argv, argc);

    if(!mkdir_if_not_exists("build")) return 1;

    nob_cc(&cmd);
    nob_cc_flags(&cmd);
    nob_cc_inputs(&cmd, "src/main.c");
    cmd_append(&cmd, "-ggdb");
    nob_cc_output(&cmd, BIN_PATH);
    if(!cmd_run(&cmd)) return false;

    if(argc >= 1 && strcmp(shift(argv, argc), "run") == 0) {
        cmd_append(&cmd, BIN_PATH);
        if(argc >= 1 && strcmp(shift(argv, argc), "--") == 0) {
            da_append_many(&cmd, argv, argc);
        }
        if(!cmd_run(&cmd)) return 1;
    }

    return 0;
}
