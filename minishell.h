/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ikgonzal <ikgonzal@student.42urduliz.co    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/24 13:31:13 by ikgonzal          #+#    #+#             */
/*   Updated: 2022/02/24 14:03:59 by ikgonzal         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

#include <stdlib.h>
#include <stdio.h>
#include <readline/readline.h>
#include <readline/history.h>
#include "libft/libft.h"

typedef struct s_node
{
	char			*content;
	char			*exp_content;
	int				is_empty;
	int				single_quoted;
	int				double_quoted;
	int				pipe;
	int				dollar;
	int				dollar_exit;
	int				red_in;
	int				red_in_append;
	int				red_out;
	int				red_out_del;
	struct s_node	*previous;
	struct s_node	*next;
}					t_node;

typedef struct s_proc
{
	char	**tokens;
	char	**paths;
	char	*prompt;
	char	*line_read;
	char	**line_expanded;
	int		node_count;
	//int	cmd_found;
	int		squote_count;
	int		dquote_count;
	t_node	*head;
	t_node	**lst;
}				t_proc;

void	set_up_shell(t_proc *proc);
void	ft_format_paths(t_proc *proc);
void	ft_cmd_exist(t_proc *proc, char *token, int processid);
void	ft_execute_command(t_proc *proc, char *route, int processid);
void	ft_tokenizer(char *process, t_proc *proc, int processid);
void	ft_read_input(t_proc *proc);
void	ft_add_node_back(t_node **node, t_node *new);
t_node	*ft_new_node(char *content);
void	print_list (t_node **lst);
void	ft_parse_input(t_proc *proc);
void	ft_gen_lst(t_proc *proc);
void	count_quotations(t_proc *proc);
int    	ft_findchar(t_node *node, char c);
void    ft_parse_pipe(t_proc *proc);
void    ft_parse_red_out(t_proc *proc);
void    ft_parse_red_in(t_proc *proc);
void	ft_lstiter(t_proc *proc, void (*f)(t_node *));
void	ft_rmv_squotes(t_node *node);
void	ft_transform_input(t_proc *proc);
void	ft_test(t_proc *proc);
void	ft_print_line(char **line);
void	ft_rmv_dollar(t_node *node);
int		ft_count_char(t_node *node, char c);

#endif
