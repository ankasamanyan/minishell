#include "../../include/minishell.h"

/*
Syntax checks are perfomed in two steps (pre-processing
and post-processing) to make it easier to detect illegal
sequences.
Lexing and parsing use small finite state machines.
Due to the small number of possible operators in the subject,
the identification and handling of operators is pretty much
hard coded. This is a pragmatic approach for the subject, but
not useful for the creation of a more complex shell.
*/
int	parsing(char *input, t_data *data)
{
	t_par		*p;

	p = &data->parsing_struct;
	init_parsingstruct(p, data, input);
	if (preproc_syntaxerror(p))
		return (EXIT_FAILURE);
	lexer(p);
	expand_var(p);
	remove_quotes(p);
	if (postproc_syntaxerror(p))
		return (EXIT_FAILURE);
	parse_commands(p);
	if (is_builtinwithflag(p))
		return (EXIT_FAILURE);
	print_cmdlist(data->cmd_list);
	return (EXIT_SUCCESS);
}

void	init_parsingstruct(t_par *p, t_data *data, char *input)
{
	p->input = input;
	p->data = data;
	p->prev_chartype = init_lex;
	p->prev_tokentype = init_tok;
	p->single_quoted = false;
	p->double_quoted = false;
	p->tokenlist = NULL;
	p->cmdlist = NULL;
	p->str_a = NULL;
	p->str_b = NULL;
	p->str_c = NULL;
}
