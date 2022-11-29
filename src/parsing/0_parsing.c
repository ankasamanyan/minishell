#include "../../include/minishell.h"

/*
Parsing is done using hard coded syntax checks (pre-processing
and post-processing) and a very reduced finite state machine.
This seemed the most pragmatic approach for the small
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
	t_list		*temp;
	t_par		*p;

	p = &data->parsing_struct;
	set_struct(p, data, input, env);
	if (preproc_syntaxerror(p))
		return (EXIT_FAILURE);
	lexer(p);
	expand_envvar(p);
	remove_quotes(p);
	if (postproc_syntaxerror(p))
		return (EXIT_FAILURE);
	printf("Start: make cmds\n");
	temp = p->tokenlist;
	while (temp)
		temp = make_commands(temp, p);
	data->cmd_list = p->cmdlist;
	print_cmdlist(data->cmd_list);
	return (EXIT_SUCCESS);
}

void	set_struct(t_par *p, t_data *data, char *input, char **env)
{
	p->input = input;
	p->data = data;
	p->prev_chartype = init_lex;
	p->prev_token = init_tok;
	p->single_quoted = false;
	p->double_quoted = false;
	p->tokenlist = NULL;
	p->cmdlist = NULL;
	p->str_a = NULL;
	p->str_b = NULL;
	p->str_c = NULL;
	data->first = true;
	data->cmd_count = 0;
	data->env = env;
}
