/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins_cd.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: madelvin <madelvin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/11 14:24:54 by madelvin          #+#    #+#             */
/*   Updated: 2025/02/18 21:31:41 by madelvin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "builtins.h"
#include "command_exec.h"
#include "utils.h"
#include <unistd.h>
#include <stdio.h>

static char	*make_env_assignment(const char *env_name, const char *env_value)
{
    char	*tmp;
    char	*res;

    if (!env_name || !env_value)
        return (NULL);
    tmp = ft_strjoin(env_name, "=");
	if (tmp == NULL)
		return (NULL);
    res = ft_strjoin(tmp, env_value);
    free(tmp);
    return (res);
}

static void	update_oldpwd(t_child_info *child_info, t_alloc *all)
{
    t_env	*env;
    char	*current_pwd;
    char	*assign_str;

	env = child_info->envp_pars;
    current_pwd = NULL;
    assign_str = NULL;
    while (env)
    {
        if (ft_strcmp(env->name, "PWD") == 0)
        {
            current_pwd = env->value;
            break;
        }
        env = env->next;
    }
    if (current_pwd)
    {
        assign_str = make_env_assignment("OLDPWD", current_pwd);
        if (assign_str)
        {
            export_var(assign_str, all);
            free(assign_str);
        }
    }
}

static void	update_pwd(t_alloc *all)
{
    char	*new_pwd;
    char	*assign_str;

	assign_str = NULL;
    new_pwd  = getcwd(NULL, 0);
    if (!new_pwd)
		exit_error(all, NULL, 1);
    assign_str = make_env_assignment("PWD", new_pwd);
    free(new_pwd);
    if (assign_str)
    {
        export_var(assign_str, all);
        free(assign_str);
    }
	else
		exit_error(all, NULL, 1);
}

static int	go_to_old(t_child_info *child_info, t_alloc *all)
{
    char	*oldpwd_value;
    char	*current_pwd;
	char	*assign_pwd;
	char	*assign_oldpwd;
    char	*tmp;

    oldpwd_value = get_env_value(child_info->envp_pars, "OLDPWD");
    current_pwd  = get_env_value(child_info->envp_pars, "PWD");
	exec_pwd();
    if (!oldpwd_value)
    {
        putstr_fd("minishell: cd: OLDPWD not set\n", 2);
        return (1);
    }
    if (chdir(oldpwd_value) < 0)
    {
        perror("minishell: cd -");
        return (1);
    }
    if (current_pwd)
    {
        assign_oldpwd = make_env_assignment("OLDPWD", current_pwd);
        if (assign_oldpwd)
        {
            export_var(assign_oldpwd, all);
            free(assign_oldpwd);
        }
    }
    tmp = getcwd(NULL, 0);
    if (tmp == NULL)
		exit_error(all, NULL, 1);
    else
    {
        assign_pwd = make_env_assignment("PWD", tmp);
        free(tmp);
        if (assign_pwd)
        {
            export_var(assign_pwd, all);
            free(assign_pwd);
        }
    }
    return (0);
}

int go_to_home(t_child_info *child_info)
{
    t_env *env;

	env = child_info->envp_pars;
    while (env)
    {
        if (ft_strcmp(env->name, "HOME") == 0)
        {
            if (chdir(env->value) < 0)
            {
                perror("minishell: cd: ");
                return (1);
            }
            return (0);
        }
        env = env->next;
    }
    putstr_fd("minishell: cd: HOME not set\n", 2);
    return (1);
}

int exec_cd(t_child_info *child_info, t_alloc *all)
{
    if (child_info->pipe_after == 0 && child_info->first == 1)
    {
        if (child_info->args[2])
        {
            putstr_fd("minishell: cd: too many arguments\n", 2);
            return (1);
        }
        if (!child_info->args[1])
        {
            update_oldpwd(child_info, all);
            if (go_to_home(child_info) == 0)
                update_pwd(all);
            return (0);
        }
        if (ft_strcmp(child_info->args[1], "-") == 0)
            return (go_to_old(child_info, all));
        update_oldpwd(child_info, all);
        if (chdir(child_info->args[1]) < 0)
        {
            putstr_fd("minishell: cd: ", 2);
            perror(child_info->args[1]);
            return (1);
        }
        update_pwd(all);
    }
    return (0);
}
