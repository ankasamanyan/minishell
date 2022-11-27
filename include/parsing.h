
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
	char			**env;
	t_chartype		prev_chartype;
	t_toktype		prev_token;
	bool			single_quoted;
	bool			double_quoted;
	t_list			*tokenlist;
	t_list			*cmdlist;
}	t_par;

typedef struct token
{
	char	*lexeme;
	bool	operator;
	bool	expansion;
}	t_tok;


//0_parsing.c
int		parsing(char *input, char **env, t_data *data);
void	set_struct(t_par *p, char *input, char **env);
void	printtieredlist(t_list *list);
void	print_cmdlist(t_list *list);

//1_syntax.c
bool	preproc_syntaxerror(t_par *p);
bool	has_unclosedquote(char *input);
bool	postproc_syntaxerror(t_par *p);
bool	has_invalidoperator(t_list *tokenlist);
bool	has_consecoperatortokens(t_par *p);

//2_expand_envvar.c
void	expand_envvar(t_par *p);
int		get_dollarposition(t_par *p, char *input);
void	replace_dollar(t_par *p);

//2_make_tokens.c
char	*make_tokens(char *input, t_par *p);
void	check_quotation(char c, t_par *p);
char	*append_char(char *string, char c);
char	*add_tokennode(t_par *p, char *token);
char	*change_tokennode(t_par *p, char *token, char c);

//3_make_commands.c
t_list	*make_commands(t_list *tokenlist, t_par *p);
char	**append_string(char **array, char *string);
t_cmd	*add_commandnode(t_par *p);
t_list	*freeandreturnnext(t_par *p, t_tok *token);

//6_util_get.c
int		get_chartype(t_par *p, char c);
int		get_tokentype(t_par *p, t_tok *token);

//6_util_is.c
bool	is_whitespace(char c);
bool	is_operatorchar(char c);
bool	is_metachar(char c);
//bool	is_quotationmark(char c);
bool	is_tokenpart(t_par *p, char c);
bool	is_sametoken(t_par *p, t_chartype chartype);

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

#endif