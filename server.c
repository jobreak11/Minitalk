/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   server.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gyeepach <gyeepach@student.42bangkok.com>  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/21 17:23:50 by gyeepach          #+#    #+#             */
/*   Updated: 2024/07/22 15:59:57 by gyeepach         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "includes/minitalk.h"


void	handler(int signum, siginfo_t *info, void *context)
{
	
	(void)info;
	(void)context;
	if (signum == SIGUSR2)
		write(1, "1", 1);
	else
		write(1, "0", 1);
	
}

int	main(void)
{
	struct sigaction	action;
	pid_t				server_pid;

	server_pid = getpid();
	ft_printf("Server process_ID = %d\n", server_pid);
	action.sa_sigaction = handler;
	sigemptyset(&action.sa_mask);
	action.sa_flags = SA_SIGINFO;
	sigaction(SIGUSR1, &action, NULL);
	while (1)
		wait(NULL);
	return (0);
}