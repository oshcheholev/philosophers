#include "philo.h"

int main(int argc, char **argv)
{
	int arg = 1;
	t_data data;
//	t_philo philo;

	if (argc != 5 && argc != 6)
	{
		printf("Error: Wrong number of arguments\n");
		return (1);
	}
	while (arg < argc)
	{
		if (ft_is_num(argv[arg]))
		{
			printf("Error: Wrong arguments\n");
			return (1);
		}
		if (ft_atoi(argv[arg]) == 0)
		{
			printf("Error: Wrong arguments\n");
			return 1;
		}
		if (ft_atoi(argv[arg]) < 0)
		{
			printf("Error: Negative arguments\n");
			return 1;
		}
//		printf("argv[%d] = %d\n", arg, ft_atoi(argv[arg]));
		arg++;
	}
	if (init_data(&data, argc, argv))
		return 1;
//	printf("data.time = %lld\n", data.start);
	if (routine(&data))
	{
//		cleanup(&data);
		return 1;
	}
	// if (init_philo(&data))
	// 	return 1;
	// if (start_philo(&data))
	// 	return 1;
//	cleanup(&data);
	// free(data.forks);
	// free(data.philos);
	return 0;
}

