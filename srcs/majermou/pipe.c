#include "./builtins/minishell.h"

char    *get_path(char **args, char **envp)
{
    struct stat     buf;
    char            **arr;
    char            *tmp;
    char            *path;
    int             i;

    i = 0;
    while (strncmp(envp[i],"PATH=",5))
        i++;
    arr = ft_split(envp[i] + 5,':');
    i = 0;
    while (arr[i])
    {
        path = ft_strjoin(arr[i++],"/");
        tmp = path;
        path = ft_strjoin(path,args[0]);
        free(tmp);
        if (!stat(path,&buf))
        {
            i = 0;
            while (arr[i])
                free(arr[i++]);
            return (path);
        }
        free(path);
    }
    return (NULL);
}

int fork_subprocess(t_cmd_list *command, t_envlist *envlist, int *fds, int *shut_pid)
{
    pid_t       pid;
    char        *path;
    static int  i;

    pid = fork();
    if (pid < 0)
        perror("sh");
    if (!pid)
    {
        path = get_path(command->args, envlist->envp);
        if (command->iterator && command->nbrpipe)
            dup2(fds[command->iterator * 2 - 2],0);
        if (command->next && is_redir(command) < 0)
            dup2(fds[command->iterator * 2 + 1],1);
        handle_redirection(command);
        if (execve(path,command->args,envlist->envp) == -1)
            perror("sh");
        exit(0);
    }
    else
    {
        if (command->iterator && command->nbrpipe)
           close(fds[command->iterator * 2 - 2]);
        if (command->next)
           close(fds[command->iterator * 2 + 1]);
        shut_pid[i++] = pid;
    }
    return (1);
}

int             execute_cmd(t_cmd_list *envlist, t_cmd_list *cmd)
{
    int         *shut_pid;
    int         *fds;
    int         num;
    int         i;
    
    i = 0;
    fds = NULL;
    num = cmd->nbrpipe;
    if (num)
    {
        fds = malloc(2 * num * sizeof(int));
        if (!fds)
            return (1);
        shut_pid = malloc((num + 1) * sizeof(int));
        if (!shut_pid)
            return (1);
    }
    while (cmd)
    {
        if (cmd->next)
            pipe(fds + cmd->iterator * 2);
        if (is_builtin(cmd))
        {
            if (cmd->iterator && cmd->nbrpipe)
                dup2(fds[cmd->iterator * 2 - 2],0);
            if (cmd->next && is_redir(cmd) < 0)
                dup2(fds[cmd->iterator * 2 + 1],1);
            handle_redirection(cmd);
            return (call_builtin(cmd, envlist));
        }
        else
            return (fork_subprocess(cmd, envlist, fds, shut_pid));
        cmd = cmd->next;
    }
    while (i < num + 1)
        waitpid(shut_pid[i++], NULL, 0);
    if (num)
    {
        free(shut_pid);
        free(fds);
    }
    return (0);
}