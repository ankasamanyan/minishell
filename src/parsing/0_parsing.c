#include "../../include/minishell.h"

/*
Parsing is done using hard syntax checks (pre-processing
and post-processing) and a simple machine state model.
This seemed the most pragmatic approach for the very reduced
number of operators in the subject.
Less pragmatic, more oriented along the way bash handles it:
- lexing, creating tokens
- var expansion
- quote removal
- parsing
Had it in a more compact model with hybrid steps and rewrote to be
more similar to the order in which bash deals with it.
Old model was like
- var expansion
- lexing, quote removal
- parsing
*/
int	parsing(char *input, char **env, t_data *data)
{
	t_par		p;
	t_list		*temp;

	set_struct(&p, input, env);
	if (preproc_syntaxerror(&p))
		return (EXIT_FAILURE);
	//lexer makes tokens: separates words / operators, removes whitespace but not quotation
	//variable expansion
	//quote removal
	//parsing into commands
	printf("Start: make tokens\n");
	while (p.input)
		p.input = make_tokens(p.input, &p);
	if (postproc_syntaxerror(&p))
		return (EXIT_FAILURE);
	print_tokenlist(p.tokenlist);
	//printf("Start: expand_envvar\n");
	//expand_envvar(&p);
	printf("Start: make cmds\n");
	temp = p.tokenlist;
	while (temp)
		temp = make_commands(temp, &p);
	data->cmd_list = p.cmdlist;
	print_cmdlist(data->cmd_list);
	return (EXIT_SUCCESS);
}

void	set_struct(t_par *p, char *input, char **env)
{
	p->input = input;
	p->env = env;
	p->prev_chartype = init_lex;
	p->prev_token = init_tok;
	p->tokenlist = NULL;
	p->cmdlist = NULL;
	p->single_quoted = false;
	p->double_quoted = false;
}