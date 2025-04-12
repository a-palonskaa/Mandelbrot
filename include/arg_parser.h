#ifndef PROC_ARG_PARSER_H
#define PROC_ARG_PARSER_H

#include "parse_arguments.h"

typedef struct {
    size_t iteration_cnt;
    int present;
    int dontpresent;
} flags_t;

void InitiallizeFlags(void* flag);

cmd_error_t ChangeFlagGrahics(void* flags, const char* arg);
cmd_error_t ChangeFlagNoGrahics(void* flag, const char* arg);
cmd_error_t ChangeRunsFlag(void* flags, const char* arg);

cmd_error_t Help(void* flags, const char* arg);

cmd_error_t ValidateInput(const void* flag);

//====================================================================================================

const option_t COMMANDS[] = {
    // short_name  long_name         changeflag function         description                     has_arg
        {"-g",  "--graphics",    &ChangeFlagGrahics,    "Show graphics"        , false},
        {"-ng", "--no-graphics", &ChangeFlagNoGrahics, "No graphics"          , false},
        {"-r",  "--runs=",        &ChangeRunsFlag,       "Enter amount of runs" , true},
        {"-h",  "--help",        &Help,                 "Help"                 , false}
};

const size_t COMMANDS_ARRAY_LENGTH = sizeof(COMMANDS) / sizeof(COMMANDS[0]);

#endif /* PROC_ARG_PARSER_H */
