#include "./builtins/minishell.h"

void    sig_handle(int sig)
{
    if (sig == SIGINT)
        printf("%d\n", sig);
    else if (sig == SIGQUIT)
        printf("Quit: 3\n");
}

int                 main(int argc, char **argv, char **envp)
{
    t_envlist    envlist;
    t_cmd_list   *cmd = (t_cmd_list*)malloc(sizeof(t_cmd_list));

    if (env_varsdup(&envlist,envp))
    {
        printf("---------------------error_0---------------------\n");
        return (1);
    }
    rmfrom_envlist(&envlist, "OLDPWD");
    envlist.envp = envp;
    // signal(SIGINT, sig_handle);
    // signal(SIGQUIT, sig_handle);
    cmd->args = malloc(20 * sizeof(char*));
    cmd->args[0] = strdup("wc");
    cmd->args[1] = strdup("-l");
    cmd->args[2] = strdup("<");
    cmd->args[3] = strdup("file");
    cmd->args[4] = NULL;
    cmd->redir = 2;
    cmd->nbrpipe = 1;
    cmd->iterator = 0;
    cmd->next = NULL;
    // malloc(sizeof(t_cmd_list));
    // cmd->next->args = malloc(20 * sizeof(char*));
    // cmd->next->args[0] = strdup("wc");
    // cmd->next->args[1] = strdup("-l");
    // cmd->next->args[2] = NULL;
    // cmd->next->nbrpipe = 1;
    // cmd->next->iterator = 1;
    // cmd->next->next = NULL;
    // malloc(sizeof(t_cmd_list));
    // cmd->next->next->args = malloc(20 * sizeof(char*));
    // cmd->next->next->args[0] = strdup("wc");
    // cmd->next->next->args[1] = strdup("-c");
    // cmd->next->next->args[2] = strdup(">");
    // cmd->next->next->args[3] = strdup("file2");
    // cmd->next->next->args[4] = NULL;
    // cmd->next->next->nbrpipe = 2;
    // cmd->next->next->iterator = 2;
    // cmd->next->next->next = NULL;

    // cmd->next->next->next = (t_cmd_list*)malloc(sizeof(t_cmd_list));
    // cmd->next->next->next->args = malloc(4 * sizeof(char*));
    // cmd->next->next->next->args[0] = strdup("tr");
    // cmd->next->next->next->args[1] = strdup("-d");
    // cmd->next->next->next->args[2] = strdup("-");
    // cmd->next->next->next->args[3] = NULL;
    // cmd->next->next->next->nbrpipe = 4;
    // cmd->next->next->next->iterator = 3;
    // cmd->next->next->next->next = NULL;
    
    printf("\n\n\n%d\n", execute_cmd(cmd, &envlist));
}