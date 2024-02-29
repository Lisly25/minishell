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

	if (argc != 2)
		ft_printf("Please put the whole command as one argument\n");
	result = ft_quoted_split(argv[1]);
	print_arr(result);
}
