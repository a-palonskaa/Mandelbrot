#include "arg_parser.h"
#include <assert.h>

//====================================================================================================
const size_t ITERATIONS_CNT = 1000;
static void PrintHelp();;

//====================================================================================================

cmd_error_t ChangeFlagGrahics(void* flag, const char* arg) {
    assert(flag != nullptr);
    (void) arg;
    flags_t* flags = (flags_t*) flag;

    flags->present = true;
    flags->dontpresent = false;

    return NO_CMD_ERRORS;
}

cmd_error_t ChangeFlagNoGrahics(void* flag, const char* arg) {
    assert(flag != nullptr);
    (void) arg;
    flags_t* flags = (flags_t*) flag;

    flags->present = false;
    flags->dontpresent = true;

    return NO_CMD_ERRORS;
}

cmd_error_t ChangeRunsFlag(void* flag, const char* arg) {
    assert(flag != nullptr);
    (void) arg;
    flags_t* flags = (flags_t*) flag;

    char *endptr = nullptr;
    flags->iteration_cnt = (size_t) strtoul(arg, &endptr, 10);
    if (endptr == nullptr) {
        flags->iteration_cnt = 1000;
        fprintf(stderr, "incorr num");
    }
    return NO_CMD_ERRORS;
}

//====================================================================================================

cmd_error_t Help(void* flag, const char* arg) {
    (void) arg;
    (void) flag;

    PrintHelp();
    return INPUT_ERROR;
}

static void PrintHelp() {
    for (size_t i = 0; i < COMMANDS_ARRAY_LENGTH; i++) {
        printf("%10s %10s %-10s" "\n", COMMANDS[i].name,
                                    COMMANDS[i].long_name,
                                    COMMANDS[i].description);
    }
}

cmd_error_t ValidateInput(const void* flag) {
    assert(flag != nullptr);
    const flags_t* flags = (const flags_t*) flag;

    if (flags->present &&
        flags->dontpresent) {
        printf("MUTUAL DESTRUCTION ERROR\n");
        return INPUT_ERROR;
    }
    return NO_CMD_ERRORS;
}

//====================================================================================================

void InitiallizeFlags(void* flag) {
    assert(flag != nullptr);
    flags_t* flags = (flags_t*) flag;

    flags->iteration_cnt = ITERATIONS_CNT;
    flags->present = true;
    flags->dontpresent = false;
}
//====================================================================================================
