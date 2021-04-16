#include <sys/types.h>
#include <sys/stat.h>
#include <stdio.h>
#include <unistd.h>
#include <errno.h>
#include <fcntl.h>
#include <stdlib.h>
#include <string.h>

typedef struct          s_cmd_list
{
    char	            **args;
	int		            nbrpipe;
    int                 iterator;
	struct s_cmd_list   *next;
}                       t_cmd_list;

char                    **ft_split(char const *s, char c);
char                    *ft_strjoin(char const *s1, char const *s2);
int                     ft_strncmp(const char *s1, const char *s2, size_t n);



char                    *get_path(char **args, char **envp)
{
    struct stat         buf;
    char                **arr;
    char                *tmp;
    char                *path;
    int                 i;

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



int                 handle_redirection(t_cmd_list *command)
{
    int             i;
    int             input;
    int             output;

    i = 0;
    //printf("been_here\n");
    while (command->args[i] && ft_strncmp(command->args[i],"<",2) && ft_strncmp(command->args[i],">",2) && ft_strncmp(command->args[i],">>",2))
    {
        i++;
    }
    while (command->args[i])
    {
        if (!ft_strncmp(command->args[i],"<",2))
        {
            if ((input = open(command->args[i + 1], O_RDONLY)) == -1)
            {
                printf("%s\n", strerror(errno));
                return (0);           
            }
            dup2(input,0);
        }
        if (!ft_strncmp(command->args[i],">",2))
        {
            output = open(command->args[i + 1], O_WRONLY | O_TRUNC | O_CREAT, S_IRUSR | S_IRGRP | S_IWGRP | S_IWUSR);
            dup2(output,1);
        }
        if (!ft_strncmp(command->args[i],">>",2))
        {
            output = open(command->args[i + 1], O_WRONLY | O_APPEND | O_CREAT, S_IRUSR | S_IRGRP | S_IWGRP | S_IWUSR);
            dup2(output,1);
        }
        command->args[i] = NULL;
        command->args[i + 1] = NULL;
        i += 2;
    }
    return (0);
}


int             fork_subprocess(t_cmd_list *command, int *fds, char **envp)
{
    pid_t       pid;
    static int j = 0;
    pid_t       wpid;
    pid_t       *w_pid = malloc(sizeof(pid_t) * command->nbrpipe);
    char        *path;
    int         status;

    pid = fork();
    w_pid[j++] = pid;
    if (pid < 0)
        perror("sh");
    if (!pid)
    {
        path = get_path(command->args, envp);
        if (command->iterator && command->nbrpipe)
            dup2(fds[command->iterator * 2 - 2],0);
        if (command->next)
            dup2(fds[command->iterator * 2 + 1],1);
        handle_redirection(command);
        if (execve(path,command->args,envp) == -1)
            perror("sh");
        exit(0);
    }
    else
    {
        if (command->iterator && command->nbrpipe)
           close(fds[command->iterator * 2 - 2]);
        if (command->next)
           close(fds[command->iterator * 2 + 1]);
        if (command->nbrpipe == 0)
            waitpid(pid, &status, WUNTRACED);
        else {
            for (int i = 0; i < command->nbrpipe + 1; i++)
                waitpid(w_pid[i], &status, 0);
        }
    }
    return (1);
}

int         is_builtin(t_cmd_list *command)
{
    if (!ft_strncmp(command->args[0],"echo",5))
        return (1);
    if (!ft_strncmp(command->args[0],"cd",3))
        return (1);
    if (!ft_strncmp(command->args[0],"pwd",4))
        return (1);
    if (!ft_strncmp(command->args[0],"export",7))
        return (1);
    if (!ft_strncmp(command->args[0],"unset",6))
        return (1);
    if (!ft_strncmp(command->args[0],"env",4))
        return (1);
    if (!ft_strncmp(command->args[0],"exit",5))
        return (1);
    return (0);
}

int         implement_cmd(t_cmd_list *command, int *fds, char **envp)
{

    if (is_builtin(command))
    {
        if (command->iterator && command->nbrpipe)
            dup2(fds[command->iterator * 2 - 2],0);
        if (command->next)
            dup2(fds[command->iterator * 2 + 1],1);
        handle_redirection(command);
        //call_builtin;
    }
    else
        fork_subprocess(command,fds,envp);
    return (0);
}


int             execute_cmd(t_cmd_list *command, char **envp)
{
    int         *fds;

    fds = NULL;
    if (command->nbrpipe)
        if (!(fds = (int*)malloc(2 * command->nbrpipe * sizeof(int))))
            return (0);
    while (command)
    {
        if (command->next)
            pipe(fds + command->iterator * 2);
        implement_cmd(command,fds,envp);
        command = command->next;
    }
    if (fds)
      free(fds);
    return (1);
}

int                 main(int argc, char **argv, char **envp)
{
    t_cmd_list      *cmd = (t_cmd_list*)malloc(sizeof(t_cmd_list));

    cmd->args = malloc(3 * sizeof(char*));
    cmd->args[0] = strdup("sleep");
    cmd->args[1] = strdup("2");
    cmd->args[2] = NULL;
    cmd->nbrpipe = 1;
    cmd->iterator = 0;
    cmd->next = (t_cmd_list*)malloc(sizeof(t_cmd_list));
    cmd->next->args = malloc(5 * sizeof(char*));
    cmd->next->args[0] = strdup("ls");
    cmd->next->args[1] = strdup("-la");
    cmd->next->args[2] = NULL;
    cmd->next->nbrpipe = 1;
    cmd->next->iterator = 1;
    cmd->next->next = NULL;
    // (t_cmd_list*)malloc(sizeof(t_cmd_list));
    // cmd->next->next->args = malloc(3 * sizeof(char*));
    // cmd->next->next->args[0] = strdup("awk");
    // cmd->next->next->args[1] = strdup("{print $1}");
    // cmd->next->next->args[2] = NULL;
    // cmd->next->next->nbrpipe = 4;
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
    
    execute_cmd(cmd,envp);
    return (0);
}