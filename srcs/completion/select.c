#include "minishell.h"

int		hand_arrow(t_compl *c, char *tmp)
{
	if ((tmp[0] == 27 && tmp[1] == 91 && ((tmp[2] == 65 && !tmp[3])
					|| (tmp[2] == 53 && tmp[3] == 126)))
			|| (tmp[0] == 16 && !tmp[1]))
		c->num_curr = (c->num_curr - 1 < 0) ? c->ac : c->num_curr - 1;
	else if ((tmp[0] == 27 && tmp[1] == 91 && ((tmp[2] == 66 && !tmp[3])
					|| (tmp[2] == 54 && tmp[3] == 126)))
			|| (tmp[0] == 14 && !tmp[1]))
		c->num_curr = (c->num_curr - 1 < 0) ? c->ac : c->num_curr - 1;
	else
		return (0);
	return (2);
}

int		handle_compl(t_compl *c, char *tmp, int **i)
{
	if (tmp[0] == 10 && !tmp[1])
		return (1);
	else if (tmp[0] == 9 && !tmp[1])
		c->num_curr = (c->num_curr + 1 > c->ac) ? 0 : c->num_curr + 1;
	else
		return (hand_arrow(c, tmp));
	return (2);
}

int		do_select(t_compl *c, char **tmp, int **i)
{
	int	j;

	read(0, *tmp, LIMIT_LINE);
	if (is_complsiged(0))
		return (-1);
//	int p = 0;
//	while (p < 6)
//		printf("%i\n", (*tmp)[p++]);
	return (handle_compl(c, *tmp, i));
}