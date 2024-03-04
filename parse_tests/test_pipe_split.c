#include "minishell.h"

void	print_arr(char **arr)
{
	int	i;

	i = 0;
	while (arr[i] != NULL)
	{
		ft_printf("%s\n", arr[i]);
		i++;
	}
}

int	main(int argc, char **argv)
{
	char	**result;
	int		cmd_count;

	if (argc != 2)
	{
		ft_printf("Please put the whole command as one argument\n");
		exit(1);
	}
	cmd_count = get_command_count(argv[1]);
	if (cmd_count == -1)
		exit(1);
	result = pipe_split(argv[1]);
	print_arr(result);
}
