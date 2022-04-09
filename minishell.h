/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ikgonzal <ikgonzal@student.42urduliz.com>  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/24 13:31:13 by ikgonzal          #+#    #+#             */
/*   Updated: 2022/04/09 09:30:00 by ikgonzal         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include <stdlib.h>
# include <stdio.h>
# include <signal.h>
# include <readline/readline.h>
# include <readline/history.h>
# include "libft/libft.h"

typedef struct s_node
{
	int				pid;
	char			**args;
	char			**args_red;
	char			*route;
	int				reds;
	int				has_red;
	int				outfd;
	int				infd;
	int				status;
	//int			is_empty;
	int				is_built_in;
	struct s_node	*previous;
	struct s_node	*next;
}					t_node;

typedef struct s_sig
{
	int			act_child;
	int			exit_status;
	pid_t		pid;
}				t_sig;

t_sig	g_sig;

typedef struct s_set
{
	char	**env;
	char	**paths;
}				t_set;

typedef struct s_proc
{
	char	**process;
	//char	**paths;
	//char	**env;
	char	*prompt;
	char	*aux;
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
	int		lpipe[2];
	int		rpipe[2];
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
	int		added_spc;
	int		dollar;
	int		lock;
	int		row_len;
	int		col_len;
	int		old_pwd;
	t_node	*head;
	t_node	**lst;
	t_set	*set;
}				t_proc;

//// Set up ////
void	set_up_shell(t_set *set, char **env);
void	ft_get_env(t_set *set, char **env);
void	ft_format_paths(t_set *set);
void	ft_create_terminal(t_proc *proc);
void	ft_cmd_exist(t_proc *proc, t_set *set);
void	ft_execute_command(t_set *set, char *route, char **args);

///// Read input ///////
void	ft_read_input(t_proc *proc);
void	ft_lstiter(t_proc *proc, void (*f)(t_proc *));

///// Linked list ////
t_node	*ft_new_node(char **args);
void	ft_add_node_back(t_proc *proc, t_node **node, t_node *new);
void	ft_gen_lst(t_proc *proc, char **args, int row_len);
void	ft_lstiter(t_proc *proc, void (*f)(t_proc *));
void	print_args(t_proc *proc);

///// Parse input /////
void	ft_parse_input(t_proc *proc);
int		ft_quote_pref_close(char *line_read, int i);
void	ft_quote_pref_open(t_proc *proc);
void	ft_count_pipes(t_proc *proc);
void	ft_count_redirections(t_proc *proc);
int		ft_findchar(char *line, char c);

////// Expand input /////
void	ft_expand_input(t_proc *proc);
void	ft_expand_line_read(t_proc *proc);
int		ft_expand_dollar(t_proc *proc, int *i);
void	ft_expand_exit(t_proc *proc);
void	ft_expand_env(t_proc *proc, int *i);
void	ft_expand_pipe(t_proc *proc, char c);
void	ft_expand_red_in(t_proc *proc, char c, int *i);
void	ft_expand_red_out(t_proc *proc, char c, int *i);
void	ft_expand_spaces(t_proc *proc, char c, int *i);

////// Proceniser ////////
void	ft_process_count(t_proc *proc);
void	ft_mem_proceniser(t_proc *proc);
void	ft_proceniser(t_proc *proc);

///// Tokenizer /////////
void	ft_tokenizer(t_proc *proc);
char	**ft_split_sp(t_proc *proc, char *process, int *sp_len, int *k);

//////// Fds & Processes /////////
void	ft_launch_process(t_proc *proc);
void	ft_set_route(t_proc *proc, char *arg);
void	ft_create_children(t_proc *proc);
void	ft_create_child(int *lpipe, int *rpipe, t_node *node, t_proc *proc);

///////// Pipes ///////////////
void	ft_parental_wait(t_proc *proc);
void	ft_close_pipe(int *pipe);
void	ft_set_read(int *lpipe);
void	ft_set_write(int *rpipe);
void	ft_swap_pipes(t_proc *proc);

/////// Redirections ///////////
void	ft_redirection_parse(t_proc *proc);
int		ft_contain_red(char *arg);
void	ft_redirection_set_up(t_proc *proc);
void	ft_check_red_type(t_proc *proc);
void	ft_set_red_out(t_proc *proc, int i, int j);
void	ft_set_red_out_app(t_proc *proc, int i, int j);
void	ft_set_red_in(t_proc *proc, int i, int j);
void	ft_set_args_red(t_proc *proc);
void	ft_set_red_write(int fd);
void	ft_set_red_read(int fd);
int		ft_red_count(char **args);

//////// Utils ///////////
void	ft_exp_sp_arr(t_proc *proc);
int		ft_strncmp_len(const char *s1, const char *s2, size_t n);
int		ft_count_argc(char **argv);

//////// Builtins /////////
int		ft_env(t_proc *proc, int cmd_count, int child);
int		ft_echo(char **argv, int fd);
int		ft_pwd(void);
int		ft_cd(char **argv, t_set *set, int child);
int		ft_update_oldpwd(t_set *set);
char	*ft_get_env_path(t_set *set, char *var, int var_len);
int		export(t_set *set, char **argv, int child);
char	**add_var(t_set *set, char *var);
void	edit_var(t_set *set, char *var);
void	print_sorted_env(t_set *set);
int		unset(t_set *set, char **argv, int child);
void	ft_exit(char **argv, int child, t_set *set);
void	ft_check_builtins(t_proc *proc, t_node *node, int child, char **args);

////////// Signals //////////
void	listen_signals(void);
void	child_message(int signum);

/////// Errors //////////
int		ft_check_redirections(char *line, char c);
int		ft_check_errors(t_proc *proc);
int		ft_check_empty_line(char *line_read);
int		print_error(char *str, int err, char *cmd, int child);
int		ft_check_null_line(char *line_read);

///////// Test //////////////
void	ft_test(t_proc *proc);
void	ft_print_line(char **line);
void	ft_print_val(t_proc *proc);

//////// Free ////////////////
void	ft_free(t_proc *proc);
void	ft_free_double_char(char **str);
void	ft_free_set(t_set *set);


#endif
