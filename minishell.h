/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ikgonzal <ikgonzal@student.42urduliz.co    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/24 13:31:13 by ikgonzal          #+#    #+#             */
/*   Updated: 2022/03/19 12:49:36 by ikgonzal         ###   ########.fr       */
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
	char			**args;
	//int				is_empty;
	struct s_node	*previous;
	struct s_node	*next;
}					t_node;

typedef struct s_proc
{
	char	**process;
	char	**tokens;
	char	**paths;
	char	*prompt;
	int		process_count;
	int		token_count;
	//////// line /////////
	char	*line_read;
	char	*line_expanded;
	int		line_exp_len;
	////// quotes ///////////
	int		quote_scope;
	int		single_quote;
	int		double_quote;
	////// spaces /////////
	int		*space_arr;
	int		*exp_sp_arr;
	int		exp_sp_arr_len;
	int		space_arr_len;
	int		space_count;
	int		exp_space_count;
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
	int		red_out_count;
	////// red out del ///////
	int		*red_out_del_arr;
	int		red_out_del_arr_len;
	int		red_out_del_count;
	////// other ///////////
	int		dollar;
	int		lock;
	int		row_len;
	int		col_len;
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
void	ft_lstiter(t_proc *proc, void (*f)(t_proc *));


///// Linked list ////
t_node	*ft_new_node(char **args);
void	ft_add_node_back(t_node **node, t_node *new);
void	ft_gen_lst(t_proc *proc, char **args, int row_len);
void	ft_lstiter(t_proc *proc, void (*f)(t_proc *));
void 	print_args (t_proc *proc);

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
void	ft_expand_red_out(t_proc *proc, char c, int *i);
void	ft_expand_spaces(t_proc *proc, char c, int *i);

////// Proceniser ////////
void    ft_process_count(t_proc *proc);
void    ft_mem_proceniser(t_proc *proc);
void    ft_proceniser(t_proc *proc);


///// Tokenizer /////////
void	ft_tokenizer(t_proc *proc);
char	**ft_split_sp(t_proc *proc, char *process, int *sp_len, int *k);

//////// Utils ///////////
void	ft_exp_sp_arr(t_proc *proc);

///////// Test //////////////
void	ft_test(t_proc *proc);
void	ft_print_line(char **line);
void    ft_print_val(t_proc *proc);

//////// Free ////////////////
void	ft_free_nodes(t_proc *proc);

#endif
