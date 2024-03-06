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

int	main(int argc, char **argv, char **env)
{
	t_data	*data;
	int		result;
	int		i;

	i = 0;
	if (argc != 2)
	{
		ft_putendl_fd("Please put the whole input in one string to start!", 2);
		exit(1);
	}
	data = init_data(env);
	if (data == NULL)
		exit(1);
	result = parser_main(argv[1], data);
	if (result == -1)
	{
		ft_putendl_fd("This is where we would wait for the next prompt", 1);
		exit(0);
	}
	if (result == MALLOC_ERROR)
	{
		//should free the data struct, but I don't think we have a function to free the env variable list yet
		exit(1);
	}
	ft_printf("Parsing successful, the data acquired was:\n\n");
	while (i < data->comm_count)
	{
		ft_printf("Command number %d:\n", i);
		ft_printf("Input redirection:\n");
		print_arr(data->unsanit_comms[i]->input);
		ft_printf("Output redirection:\n");
		print_arr(data->unsanit_comms[i]->output);
		ft_printf("Command and its arguments:\n");
		print_arr(data->unsanit_comms[i]->command);
		i++;
	}
	ft_printf("That was all!\n");
	exit(0);
	}
	
