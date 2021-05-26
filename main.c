#include "push_swap.h"
#include "./libft/libft.h"

#include "stdio.h"

#define INT_MAX 2147483647
#define INT_MIN -2147483648

void		print_dlist(t_dlist *head);

//Parsing
int			ft_push_swap_parsing(int ac, char **av);
int			ft_digit_syntax(char *str);
long		ft_atol(char *str);
int			ft_digit_syntax(char *str);

// Double linked list basics
void		ft_push_back(t_dlist **head, t_dlist *new);
t_dlist		*ft_create_node(int data);
t_dlist		*ft_make_dlist(char **av);

// Stack operations
void		ft_s_push(t_dlist **stack_pulled, t_dlist **stack_pushed);

void		ft_s_swap(t_dlist **top_stack);
void		ft_s_rot(t_dlist **top_stack);
void		ft_s_rev_rot(t_dlist **top_stack);

void		ft_s_double_swap(t_dlist **top_stack_a, t_dlist **top_stack_b);
void		ft_s_double_rot(t_dlist **top_stack_a, t_dlist **top_stack_b);
void		ft_s_double_rev_rot(t_dlist **top_stack_a, t_dlist **top_stack_b):


int		main(int ac, char **av)
{
	int		err_val;
	t_dlist *s_a;
	t_dlist	*s_b;
	
	err_val = ft_push_swap_parsing(ac, av);
	if (err_val != 0)
	{
		//Msg a changer
		printf("err_val = %d\n", err_val);

		ft_putstr("Error _ Parsing\n");
		return (1);
	}

	ft_putstr("Parsing ok\n");

	//Creer la stack A : initiale et non ordonnee 
	s_a = ft_make_dlist(av);
	s_b = NULL;
	if (s_a == NULL)
	{
		ft_putstr("Error _ Malloc ? \n");
		return (1);
	}

	printf("\nStack A:\n");
	print_dlist(s_a);
	printf("\nStack B:\n");
	print_dlist(s_b);
	printf("\n");
	
	return (0);
}

void		print_dlist(t_dlist *head)
{
	t_dlist *tmp;

	if (head == NULL)
	{
		ft_putstr("|NULL|!\n");
		return;
	}
	tmp = head;
	
	while (tmp)
	{
		printf("|%d| --> ", tmp->content);
		tmp = tmp->next;
	}
	printf("|NULL|!\n");
}

t_dlist		*ft_make_dlist(char **av)
{
	int i;
	t_dlist *head;
	t_dlist	*new;
	
	head = NULL;
	i = 1;
	while (av[i])
	{
		new = ft_create_node(ft_atoi(av[i]));
		if (new == NULL)
			return (NULL);
		ft_push_back(&head, new);
		i++;
	}
	return (head);
}

void		ft_push_back(t_dlist **head, t_dlist *new)
{
	t_dlist	*tmp;

	if (*head == NULL)
		*head = new;
	else
	{
		tmp = *head;
		while (tmp->next != NULL)
			tmp = tmp->next;
		tmp->next = new;
		new->previous = tmp;
		new->next = NULL;
	}
}

t_dlist		*ft_create_node(int	data)
{
	t_dlist *new;

	new = malloc(sizeof(t_dlist));
	if (new == NULL)
		return (NULL);
	new->content = data;
	new->next = NULL;
	new->previous = NULL;

//	printf("data = %d\n", new->content);

	return (new);
}


int		ft_push_swap_parsing(int ac, char **av)
{
	int		i;
	int		j;
	long	tmp;

	if (ac < 2)
		return (1);
	i = 1;
	while (av[i])
	{
		//Look for digit syntax
		if (ft_digit_syntax(av[i]))
			return (2);
		tmp = ft_atol(av[i]);

		// Look for INT limit
		if (tmp > INT_MAX || tmp < INT_MIN)
			return (3);
		
		// Look for doublon
		j = 0;
		while (j < i)
		{
			if (tmp == ft_atol(av[j]))
					return (4);
			j++;
		}
		i++;
	}
	return (0);
}

int		ft_digit_syntax(char *str)
{
	int i;

	i = 0;
	while (str[i] == ' ')
		i++;
	if (str[i] == '+' || str[i] == '-')
		i++;
	while (str[i])
	{
		if (!ft_isdigit(str[i]))
			return (1);
		i++;
	}
	return (0);
}


long	ft_atol(char *str)
{
	long	r_val;
	int		sign;
	int		i;

	i = 0;
	sign = 1;
	r_val = 0;
	while (ft_isspace(str[i]))
		i++;
	if (str[i] == '-' || str[i] == '+')
	{
		if (str[i] == '-')
			sign = -1;
		i++;
	}
	while (ft_isdigit(str[i]))
	{
		r_val = 10 * r_val + str[i] - '0';
		i++;
	}
	return (r_val * sign);
}
