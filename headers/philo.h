/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gmillon <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/21 14:59:30 by gmillon           #+#    #+#             */
/*   Updated: 2022/10/24 18:09:00 by gmillon          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
# define PHILO_H
# include <pthread.h>
# include <stdio.h>
# include <stdlib.h>
# include <unistd.h>
# include <sys/time.h>

//PRINT MESSAGES
# define TIMESTAMP_MSG "%lld ms "
# define SLEEP_MSG "%d is sleeping\n"
# define FORK_MSG "%d has taken a fork\n"
# define THINK_MSG "%d is thinking\n"
# define DIED_MSG "%d died\n"
# define EAT_MSG "%d is eating\n"

enum {
	NUM_PHILOS,
	TIME_TO_DIE,
	TIME_TO_EAT,
	TIME_TO_SLEEP,
	TIMES_MUST_EAT,
};

typedef struct s_philo
{
	int				id;
	int				left_id;
	int				right_id;
	pthread_t		philo_thread;
	pthread_mutex_t	fork;
	int				times_eaten;
	long long		time_last_ate;
	int				time_to_death;
	int				error;
}				t_philo;

typedef struct s_state
{
	t_philo			*philo_arr;
	int				*vars;
	pthread_mutex_t	*forks;
	int				death;
	long long		start_time;
	pthread_mutex_t	writing;
	int				thread_id;
	int				finished;
}				t_state;

//INITIALIZATION

int				*initialize(int argc, char **argv);
t_state			*create_state(int *vars);
int				create_fork(t_philo *philo);

//PHILO ROUTINES
int				philo_eat(t_state *state, t_philo *philo);
int				philo_routine(t_state *state, t_philo *philo);
void			*philo_main(void *arg);

//PHILO UTILS
long long		time_diff(long long start_time);
long long		current_time(void);
int				check_and_print(t_philo *philo, char *msg, t_state *state);
void			handle_error(int *vars);
void			checker(t_state *state);
//THREAD UTILS

int				join_threads(int *vars, t_state *state);
void			destroy_mutexes(t_state *state);
pthread_mutex_t	*make_fork_arr(int *vars);

//PARSE UTILS
int				ft_atoi(const char *str);
int				ft_string_is_num(char *str);

#endif