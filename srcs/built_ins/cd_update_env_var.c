/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd_updtae_env_var.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: purmerinos <purmerinos@protonmail.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/08 15:59:12 by purmerinos        #+#    #+#             */
/*   Updated: 2024/02/08 15:59:13 by purmerinos       ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "built_ins.h"

char	*get_pwd_in_buffer(void)
{
	char	*pwd;

	pwd = ft_calloc(PWD_BUFFER + 1, sizeof(char));
	if (pwd)
		get_pwd(pwd, PWD_BUFFER);
	return (pwd);
}

void	free_if_needed(void **str)
{
	if (*str)
		free(*str);
}

char	*build_var(const char *s1, const char *s2)
{
	char	*joined_str;
	char	*tmp;

	joined_str = NULL;
	tmp = ft_strjoin(s1, "=");
	if (tmp != NULL)
	{
		joined_str = ft_strjoin(tmp, s2);
		free(tmp);
	}
	return (joined_str);
}

void	swap_var(t_core *core, char *var_content, const char *var_name)
{
	char		**pwd_address;
	char		*full_var;

	pwd_address = get_valid_addr(core, (char *)var_name);
	free_if_needed((void **)pwd_address);
	full_var = build_var(var_name, var_content);
	if (!full_var)
	{
		ft_clean_exit(core, MALLOC);
	}
	*pwd_address = ft_strdup(full_var);
	free(full_var);
	if (*pwd_address == NULL)
	{
		ft_clean_exit(core, MALLOC);
	}
	free(var_content);
}

void	update_env_var(t_core	*core, char *old_pwd)
{
	char	*new_pwd;

	swap_var(core, old_pwd, "OLDPWD");
	new_pwd = assign_pwd(core);
	swap_var(core, new_pwd, "PWD");
}
