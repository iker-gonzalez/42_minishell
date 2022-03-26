/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ikgonzal <ikgonzal@student.42urduliz.com>  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/24 13:31:13 by ikgonzal          #+#    #+#             */
/*   Updated: 2022/03/27 00:24:55 by jsolinis         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

#include <stdlib.h>
#include <stdio.h>
#include <signal.h>
#include <readline/readline.h>
#include <readline/history.h>
#include "libft/libft.h"

typedef struct s_node
{
	int				pid;
	char			**args;
	char			*route;
	int				status;
	//int			is_empty;
	struct s_node	*previous;
	struct s_node	*next;
}					t_node;

typedef struct s_sig
{
	int			act_child;
	int			sigint;
	int			sigquit;
	int			status;
	pid_t		pid;
}				t_sig;

extern t_sig sig;

typedef struct s_proc
{
	char	**process;
	char	**paths;
	char	**env;
	char	*home;
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
	int		p[2][2];
	int		launched_processes;
	int		pipe1;
	int		pipe2;
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

///// Init ///////
void	ft_get_env(t_proc *proc, char **env);

//// Set up ////
void	set_up_shell(t_proc *proc, char **env);
void	ft_format_paths(t_proc *proc);
void	ft_cmd_exist(t_proc *proc);
void	ft_execute_command(t_proc *proc, char *route, char **args);

///// Read input ///////
void	ft_read_input(t_proc *proc);
void	ft_lstiter(t_proc *proc, void (*f)(t_proc *));

///// Linked list ////
t_node	*ft_new_node(char **args);
void	ft_add_node_back(t_proc *proc, t_node **node, t_node *new);
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

//////// Fds & Processes /////////
void	ft_launch_process(t_proc *proc);
void	ft_set_route(t_proc *proc);
void	ft_parental_wait(t_proc *proc);
void	ft_initialize_pipes(t_proc *proc);
void	ft_create_children(t_proc *proc);
void	ft_create_only_child(t_node *node, char **env);
void	ft_create_first_child(t_proc *proc, t_node *node, char **env);
void	ft_create_last_child(t_proc *proc, t_node *node, char **env);
void	ft_create_child(t_proc *proc, t_node *node, char **env);

//////// Utils ///////////
void	ft_exp_sp_arr(t_proc *proc);

//////// Builtins /////////
int		ft_env(t_proc *proc);
int		echo(int argc, char **argv, int fd);
int		ft_pwd(void);
int		ft_cd(char **argv, t_proc *proc);
char	*ft_get_env_path(t_proc *proc, char *var, int var_len);
//void	export(t_proc *proc, char **argv);
char	**add_edit_var(t_proc *proc, char *var);
void	unset(t_proc *proc, char **argv);
void	ft_check_builtins(t_proc *proc);

////////// Signals //////////
void	listen_signals(void);
void	handler(int signum);
void	child_message(int signum);



///////// Execute ////////////
void	ft_execute(t_proc *proc);

/////// Errors //////////
void    ft_check_errors(t_proc *proc);
int		ft_check_empty_line(char *line_read);

///////// Test //////////////
void	ft_test(t_proc *proc);
void	ft_print_line(char **line);
void    ft_print_val(t_proc *proc);

///////// Signals ////////////
void	listen_signals(void);

//////// Free ////////////////
void	ft_free(t_proc *proc);
void	ft_free_double_char(char **str);

#endif
