/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ikgonzal <ikgonzal@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/24 13:31:13 by ikgonzal          #+#    #+#             */
/*   Updated: 2022/04/15 21:52:46 by ikgonzal         ###   ########.fr       */
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
	char			*heredoc_line;
	int				reds;
	int				has_red;
	int				outfd;
	int				infd;
	int				status;
	int				is_built_in;
	struct s_node	*previous;
	struct s_node	*next;
}					t_node;

int	g_exit_status;

typedef struct s_set
{
	char	**env;
	char	**paths;
}				t_set;

typedef struct s_proc
{
	char	**process;
	char	*prompt;
	char	*aux;
	int		**red_spc;
	int		process_count;
	int		token_count;
	char	*line_read;
	char	*line_expanded;
	int		line_exp_len;
	int		single_quote;
	int		double_quote;
	int		*space_arr;
	int		*exp_sp_arr;
	int		exp_sp_arr_len;
	int		space_arr_len;
	int		space_count;
	int		exp_space_count;
	int		*pipe_arr;
	int		pipe_arr_len;
	int		lpipe[2];
	int		rpipe[2];
	int		*red_in_arr;
	int		red_in_arr_len;
	int		red_in_count;
	int		*red_in_app_arr;
	int		red_in_app_arr_len;
	int		red_in_app_count;
	int		*red_out_arr;
	int		red_out_arr_len;
	int		red_out_count;
	int		*red_out_del_arr;
	int		red_out_del_arr_len;
	int		red_out_del_count;
	int		added_spc;
	int		**added_spc_arr;
	int		**added_spc_arr_length;
	int		added_spc_arr_len;
	int		infile;
	int		dollar;
	int		lock;
	int		row_len;
	int		col_len;
	int		old_pwd;
	int		ex;
	int		count_y;
	int		lock_col;
	int		row_tok;
	int		no_cmd;
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
int		ft_char_match(char c, char match);
char	*ft_get_abs_path(char *arg);
void	ft_set_abs_path(t_proc *proc, char *arg);
void	ft_is_route(char *route, t_proc *proc, char *path, char *arg);
void	ft_set_route(t_proc *proc, char *arg);

///// Read input ///////
void	ft_read_input(t_proc *proc);
void	ft_lstiter(t_proc *proc, void (*f)(t_proc *));

///// Linked list ////
t_node	*ft_new_node(char **args);
void	ft_add_node_back(t_proc *proc, t_node **node, t_node *new);
void	ft_gen_lst(t_proc *proc, char **args, int row_len);
void	print_args(t_proc *proc);

///// Parse input /////
void	ft_parse_input(t_proc *proc);
int		ft_quote_pref_close(char *line_read, int i);
void	ft_quote_pref_open(t_proc *proc);
void	ft_count_pipes(t_proc *proc);
void	ft_count_redirections(t_proc *proc);
int		ft_findchar(char *line, char c);
void	ft_red_spc(t_proc *proc);
void	ft_count_added_spaces(t_proc *proc, int i);

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
char	**ft_split_sp(t_proc *proc, int i, int *sp_len, int *k);

//////// Fds & Processes /////////
void	ft_launch_process(t_proc *proc);
void	ft_set_route(t_proc *proc, char *arg);
void	ft_create_children(t_proc *proc);
void	ft_create_child(int *lpipe, int *rpipe, t_node *node, t_proc *proc);

///////// Pipes ///////////////
void	ft_case_only_child(t_proc *proc);
void	ft_case_first_of_many(t_proc *proc);
void	ft_case_middle_guy(t_proc *proc);
void	ft_case_last_of_many(t_proc *proc);
void	ft_parental_wait(t_proc *proc);
void	ft_close_pipe(int *pipe);
void	ft_set_read(int *lpipe);
void	ft_set_write(int *rpipe);
void	ft_swap_pipes(t_proc *proc);

/////// Redirections ///////////
void	ft_redirection_parse(t_proc *proc);
void	ft_redirection_set_up(t_proc *proc);
void	ft_check_red_type(t_proc *proc);
void	ft_set_red_out(t_proc *proc, int i);
void	ft_set_red_out_app(t_proc *proc, int i);
void	ft_set_red_in(t_proc *proc, int i);
void	ft_set_red_in_del(t_proc *proc, int i);
void	ft_set_args_red(t_proc *proc);
void	ft_set_red_write(int fd);
void	ft_set_red_read(int fd);
int		ft_red_count(char **args);
void	ft_fill_single(t_proc *proc, int i, int j, int *k);
void	ft_fill_double(t_proc *proc, int i, int j, int *k);
void	ft_check_if_red(t_proc *proc);
void	ft_copy_on_aux(t_proc *proc, int i, int j, int k);
void	ft_check_red_condition_aux(t_proc *proc, int i, int *j, int *k);
void	ft_no_space_after(t_proc *proc, int i, int j, int *k);
void	ft_no_space_before(t_proc *proc, int i, int j, int *k);
void	ft_no_space_bfr_aftr(t_proc *proc, int i, int j, int *k);
void	ft_no_space_after_single(t_proc *proc, int i, int j, int *k);
void	ft_no_space_bfr_aftr_single(t_proc *proc, int i, int j, int *k);

//////// Utils ///////////
void	ft_exp_sp_arr(t_proc *proc);
int		ft_strncmp_len(const char *s1, const char *s2, size_t n);
int		ft_count_argc(char **argv);

//////// Builtins /////////
int		ft_env(t_proc *proc, int cmd_count, int child, int fd);
int		ft_echo(t_proc *proc, char **argv, int fd, int child);
int		ft_pwd(t_proc *proc, int child, int fd);
int		ft_cd(char **argv, t_set *set, int child);
int		ft_update_oldpwd(t_set *set);
char	*ft_get_env_path(t_set *set, char *var, int var_len);
int		export(t_proc *proc, char **argv, int child, int fd);
char	**add_var(t_set *set, char *var);
char	**edit_var(t_set *set, char *var);
void	print_sorted_env(t_proc *proc, t_set *set, int fd);
int		unset(t_set *set, char **argv, int child);
void	ft_exit(char **argv, int child, t_set *set, t_proc *proc);
void	ft_check_builtins(t_proc *proc, t_node *node, int child, char **args);
int		ft_varlen(char *str);

////////// Signals //////////
void	listen_signals_daddy(void);
void	listen_signals_child(void);

/////// Errors //////////
int		ft_check_redirections(char *line, char c);
int		ft_check_errors(t_proc *proc);
int		ft_check_empty_line(char *line_read);
int		print_error(char *str, int err, char *cmd, int child);
int		ft_check_null_line(char *line_read);
int		ft_check_pipe(char *line_read);

///////// Test //////////////
void	ft_test(t_proc *proc);
void	ft_print_line(char **line);
void	ft_print_val(t_proc *proc);

//////// Free ////////////////
void	ft_free(t_proc *proc);
void	ft_free_double_char(char **str);
void	ft_free_set(t_set *set);
void	ft_free_process(t_proc *proc);
void	ft_free_args(t_proc *proc);
void	ft_free_args_red(t_proc *proc);
void	ft_free_node_routes(t_proc *proc);
void	ft_free_double_int(t_proc *proc, int **str);
void	ft_freelist(t_node *lst);

#endif
