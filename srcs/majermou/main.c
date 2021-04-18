#include "./builtins/minishell.h"

int                 main(int argc, char **argv, char **envp)
{
    t_cmd_list      *cmd = (t_cmd_list*)malloc(sizeof(t_cmd_list));

    cmd->args = malloc(20 * sizeof(char*));
    cmd->args[0] = strdup("cat");
    cmd->args[1] = strdup("<");
    cmd->args[2] = strdup("file");
    cmd->args[3] = NULL;
    cmd->nbrpipe = 2;
    cmd->iterator = 0;
    cmd->next = malloc(sizeof(t_cmd_list));
    cmd->next->args = malloc(20 * sizeof(char*));
    cmd->next->args[0] = strdup("ls");
    cmd->next->args[1] = strdup("-la");
    cmd->next->args[2] = strdup(">>");
    cmd->next->args[3] = strdup("file2");
    cmd->next->args[4] = NULL;
    cmd->next->nbrpipe = 2;
    cmd->next->iterator = 1;
    cmd->next->next = malloc(sizeof(t_cmd_list));
    cmd->next->next->args = malloc(20 * sizeof(char*));
    cmd->next->next->args[0] = strdup("wc");
    cmd->next->next->args[1] = strdup("-c");
    cmd->next->next->args[2] = strdup(">");
    cmd->next->next->args[3] = strdup("file3");
    cmd->next->next->args[4] = NULL;
    cmd->next->next->nbrpipe = 2;
    cmd->next->next->iterator = 2;
    cmd->next->next->next = NULL;

    // cmd->next->next->next = (t_cmd_list*)malloc(sizeof(t_cmd_list));
    // cmd->next->next->next->args = malloc(4 * sizeof(char*));
    // cmd->next->next->next->args[0] = strdup("tr");
    // cmd->next->next->next->args[1] = strdup("-d");
    // cmd->next->next->next->args[2] = strdup("-");
    // cmd->next->next->next->args[3] = NULL;
    // cmd->next->next->next->nbrpipe = 4;
    // cmd->next->next->next->iterator = 3;
    // cmd->next->next->next->next = NULL;
    
    execute_cmd(cmd,envp);
    return (0);
}