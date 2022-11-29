
#ifndef PARSING_H
# define PARSING_H

# define E_ARGC "Additional arguments discarded. Running as \"./minishell\"\n"
# define E_UNCLOSEDQUOTE "minishell: unclosed quote\n"
# define E_SENUT "minishell: syntax error near unexpected token"

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
	dollar = 16,
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
	t_toktype		prev_token;
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

//0_parsing.c
int		parsing(char *input, char **env, t_data *data);
void	set_struct(t_par *p, t_data *data, char *input, char **env);
void	printtieredlist(t_list *list);
void	print_cmdlist(t_list *list);

//1_syntax.c
bool	preproc_syntaxerror(t_par *p);
bool	has_unclosedquote(char *input);
bool	postproc_syntaxerror(t_par *p);
bool	has_invalidoperator(t_list *tokenlist);
bool	has_consecoperatortokens(t_par *p);

//2_lexer.c
void	lexer(t_par *p);
int		get_chartype(t_par *p, char c);
char	*append_char(char *string, char c);
void	add_tokennode(t_par *p, char *lexeme);
void	check_quotation(t_par *p, char c);

//3_expand_envvar.c
void	expand_envvar(t_par *p);
int		get_dollarposition(t_par *p, char *input);
char	*replace_dollar(t_par *p, char *string);
void	findandexpand(t_par *p);
char	*del_singlechar(char *string, int deletechar);

//4_remove_quotes.c
void	remove_quotes(t_par *p);

//5_make_commands.c
t_list	*make_commands(t_list *tokenlist, t_par *p);
int		get_tokentype(t_par *p, t_tok *token);
char	**append_string(char **array, char *string);
t_cmd	*add_commandnode(t_par *p);
t_list	*freeandreturnnext(t_par *p, t_tok *token);

//6_util_is.c
bool	is_whitespace(char c);
bool	is_operatorchar(char c);
bool	is_metachar(char c);
bool	is_quotationmark(char c);

//7_helper_print.c
void	print_tokenlist(t_list *list);
void	print_cmdlist(t_list *list);
void	print_cmd_arr(t_list *node);
void	print_inputlist(t_list *node);
void	print_outputlist(t_list *node);

//8_exits&broadcast.c
void	errorexit_onlymsg(char *msg);
void	commandexit(void);
bool	broadcast_senut(char c);

//9_shutdown.c
void	shutdown(t_data *data);
void	del_tokenlist(t_list *list);
void	del_cmdlist(t_list *list);
void	del_pairlist(t_list *list);
void	free2d_char(char **array);

#endif