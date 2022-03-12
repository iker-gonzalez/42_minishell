/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ikgonzal <ikgonzal@student.42urduliz.com>  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/24 13:31:13 by ikgonzal          #+#    #+#             */
/*   Updated: 2022/03/12 11:24:26 by ikgonzal         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

#include <stdlib.h>
#include <stdio.h>
#include <readline/readline.h>
#include <readline/history.h>
#include "libft/libft.h"
/*
typedef struct s_node
{
	char			*content;
	char			*exp_content;
	int				is_empty;
	struct s_node	*previous;
	struct s_node	*next;
}					t_node;
*/
typedef struct s_proc
{
	char	**tokens;
	char	**paths;
	char	*prompt;
	//////// line /////////
	char	*line_read;
	char	*line_expanded;
	int		line_exp_len;
	//////// pipes ////////
	int		*pipe_arr;
	int		pipe_arr_len;
	/////// red in ////////
	int		*red_in_arr;
	int		red_in_arr_len;
	int		red_in_count;
	/////// red in app /////
	int		*red_in_app_arr;
	int		red_in_app_arr_len;
	int		red_in_app_count;
	////// red out /////////
	int		*red_out_arr;
	int		red_out_arr_len;
	////// red out del ///////
	int		*red_out_del_arr;
	int		red_out_del_arr_len;
	////// quotes ///////////
	int		quote_scope;
	int		single_quote;
	int		double_quote;
	////// other ///////////
	int		dollar;
	int		lock;
	//t_node	*head;
	//t_node	**lst;
}				t_proc;

//// Set up ////
void	set_up_shell(t_proc *proc);
void	ft_format_paths(t_proc *proc);
void	ft_cmd_exist(t_proc *proc, char *token, int processid);
void	ft_execute_command(t_proc *proc, char *route, int processid);

///// Read input ///////
void	ft_read_input(t_proc *proc);

/*
///// Linked list ////
t_node	*ft_new_node(char *content);
void	ft_add_node_back(t_node **node, t_node *new);
void	ft_gen_lst(t_proc *proc);
void	ft_lstiter(t_proc *proc, void (*f)(t_proc *));
void 	print_list (t_proc *proc);
*/

///// Parse input /////
void	ft_parse_input(t_proc *proc);
int		ft_quote_pref_close(char *line_read, int i);
void	ft_quote_pref_open(t_proc *proc);
void    ft_count_pipes(t_proc *proc);
void    ft_count_redirections(t_proc *proc);
int    	ft_findchar(char *line, char c);


////// Expand input /////
void	ft_expand_input(t_proc *proc);
void	ft_expand_line_read(t_proc *proc);
void	ft_expand_dollar(t_proc *proc, int *i);
void	ft_expand_pipe(t_proc *proc, char c);
void	ft_expand_red_in(t_proc *proc, char c, int *i);


///////// Test //////////////
void	ft_test(t_proc *proc);
void	ft_print_line(char **line);
void    ft_print_val(t_proc *proc);

//////// Free ////////////////
void	ft_free_nodes(t_proc *proc);


void	ft_print_pipe_exp(t_proc *proc);


#endif
