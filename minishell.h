/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ikgonzal <ikgonzal@student.42urduliz.co    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/24 13:31:13 by ikgonzal          #+#    #+#             */
/*   Updated: 2022/03/10 13:16:33 by ikgonzal         ###   ########.fr       */
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
	int				exp_len;
	int				is_empty;
	int				single_quoted;
	int				double_quoted;
	int				triple_quoted;
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
	int		pipe_count;
	int		*pipe_exp;
	int		squote_count;
	int		dquote_count;
	int		quote_scope;
	int		single_quote;
	int		double_quote;
	t_node	*head;
	t_node	**lst;
}				t_proc;

//// Set up ////
void	set_up_shell(t_proc *proc);
void	ft_format_paths(t_proc *proc);
void	ft_cmd_exist(t_proc *proc, char *token, int processid);
void	ft_execute_command(t_proc *proc, char *route, int processid);

///// Read input ///////
void	ft_read_input(t_proc *proc);

///// Create linked list ////
t_node	*ft_new_node(char *content);
void	ft_add_node_back(t_node **node, t_node *new);
void	ft_gen_lst(t_proc *proc);
void print_list (t_proc *proc);

///// Iterate nodes ///////
void	ft_lstiter(t_proc *proc, void (*f)(t_proc *));

///// Parse input /////
void	ft_parse_input(t_proc *proc);
void    ft_parse_tquotes(t_proc *proc);
void	count_quotations(t_proc *proc);
int    	ft_findchar(t_node *node, char c);
void    ft_parse_pipe(t_proc *proc);
void    ft_parse_red_out(t_proc *proc);
void    ft_parse_red_in(t_proc *proc);
void	ft_determine_scope(t_proc *proc);
int		ft_determine(char *line_read, int i);

void check_leaks();
////// Transform input /////
void	ft_transform_input(t_proc *proc);
void	ft_trm_quotes(t_proc *proc);


void	ft_test(t_proc *proc);
void	ft_print_line(char **line);

//////// Free ////////////////
void	ft_free_nodes(t_proc *proc);


void	ft_print_pipe_exp(t_proc *proc);


#endif
