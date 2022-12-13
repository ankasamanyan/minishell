
#ifndef PARSING_H
# define PARSING_H

# define E_ARGC "Additional arguments discarded. Running as \"./minishell\"\n"
# define E_UNCLOSEDQUOTE "unclosed quote"
# define E_SENUT "Minishell: syntax error near unexpected token `"
# define E_BLTNFLAG "Minishell: flags not accepted for builtin `"
# define E_MANYARG "too many arguments"
# define E_NOFILDIR "No such file or directory"
# define E_INVALOPT "invalid option (options not allowed for this builtin \
in Minishell)"

//forward declarations
typedef struct s_list	t_list;
typedef struct s_cmd	t_cmd;
typedef struct s_pair	t_pair;

typedef enum char_type
{
	init_lex = 1,
	word = 2,
	whitespace = 4,
	operator = 8,
	pipe_char = 16,
}	t_chartype;

typedef enum token_type
{
	init_tok = 1,
	newcmd = 2,
	input_redir_oper = 4,
	output_redir_oper = 8,
	input_redir_str = 16,
	output_redir_str = 32,
	pipe_oper = 64,
	cmdstring = 128
}	t_toktype;

typedef struct parsing
{
	char			*input;
	t_data			*data;
	t_chartype		prev_chartype;
	t_toktype		prev_tokentype;
	bool			single_quoted;
	bool			double_quoted;
	t_list			*tokenlist;
	t_list			*cmdlist;
	char			*str_a;
	char			*str_b;
	char			*str_c;
}	t_par;

typedef struct token
{
	char	*lexeme;
	bool	operator;
}	t_tok;

//00_parsing.c
int		parsing(t_data *data, char *input);
void	init_parsingstruct(t_par *p, t_data *data, char *input);

//01_preproc_syntax.c
bool	preproc_syntaxerror(t_par *p);
bool	has_unclosedquote(char *input);
bool	postproc_syntaxerror(t_par *p);
bool	has_invalidoperator(t_list *tokenlist);
bool	has_illegaloperatorsequence(t_par *p);

//02_lexer.c
void	lexer(t_par *p);
int		get_chartype(t_par *p, char c);
void	add_tokennode(t_par *p, char *lexeme);
void	check_quotation(t_par *p, char c);

//03_expand_var.c
void	expand_var(t_par *p);
int		get_dollarposition(t_par *p, char *input);
char	*replace_dollar(t_par *p, char *string);
void	findandexpand(t_par *p);
char	*joinandfree(t_par *p, char *lexeme);

//04_remove_quotes.c
void	remove_quotes(t_par *p);

//05_postproc_syntax.c
bool	postproc_syntaxerror(t_par *p);
bool	has_invalidoperator(t_list *tokenlist);
bool	has_illegaloperatorsequence(t_par *p);

//06_parser1.c
void	parser(t_par *p);
int		get_tokentype(t_par *p, t_tok *token);
t_cmd	*handle_token(t_par *p, t_cmd *cmdnode, t_toktype curr_tokentype,
			char *lexeme);

//06_parser2.c
t_cmd	*add_commandnode(t_par *p);
t_pair	*add_redirnode(t_cmd *cmdnode, char *operator, t_toktype tokentype);

//07_check_builtin.c
void	check_builtin(t_par *p);
bool	is_builtin(t_cmd *cmdnode);

//07_util_general.c
char	*append_char(char *string, char c);
char	**append_string(char **array, char *string);
char	*del_singlechar(char *string, int del_pos);

//07_util_is.c
bool	is_whitespace(char c);
bool	is_operatorchar(char c);
bool	is_metachar(char c);
bool	is_quotationmark(char c);

//08_helper_print.c
void	print_tokenlist(t_list *list);
void	print_cmdlist(t_list *list);
void	print_cmd_arr(t_list *node);
void	print_inputlist(t_list *node);
void	print_outputlist(t_list *node);

//09_exits+broadcast.c
void	errorexit_onlymsg(char *msg);
void	msg_senut(char c);
void	msg_error(char *err_msg0, char *err_msg1, char *err_msg2);
void	msg_err_quote(char *err_msg0, char *err_msg1, char *err_msg2);

//10_shutdown1.c
void	shutdown_parsing(t_data *data);
void	del_tokenlist(t_list *list);
void	del_cmdlist(t_list *list);
void	del_pairlist(t_list *list);
void	free2d_char(char **array);

//10_shutdown2.c
void	del_explist(t_list *list);

#endif