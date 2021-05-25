#include "push_swap.h"
#include "./libft/libft.h"

#include "stdio.h"

#define INT_MAX 2147483647
#define INT_MIN -2147483648

void		print_dlist(t_dlist *head);
int		ft_push_swap_parsing(int ac, char **av);
int		ft_digit_syntax(char *str);
long	ft_atol(char *str);
int		ft_digit_syntax(char *str);
t_dlist	*ft_make_dlist(char **av);

int		main(int ac, char **av)
{
	int		err_val;
	t_dlist *s_a;
	//(void)t_dlist *s_b;
	
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
	//s_b = NULL;
	if (s_a == NULL)
	{
		ft_putstr("Error _ Malloc ? \n");
		return (1);
	}
	print_dlist(s_a);
	
	return (0);
}

void		print_dlist(t_dlist *head)
{
	t_dlist *tmp;

	if (head == NULL)
	{
		ft_putstr("Empty list ... \n");
		return;
	}
	tmp = head;
	while (tmp)
	{
		//printf("|%d| --> ", tmp->data);
		tmp = tmp->next;
	}
	printf("NULL\n");
}
t_dlist		*ft_create_node(void *content)
{
	t_dlist *new;

	new = malloc(sizeof(t_dlist));
	if (new == NULL)
		return (NULL);
	new->data = content;
	new->next = NULL;
	new->previous = NULL;
	return (new);
}


int		ft_push_back(void *content, t_dlist **head)
{
	t_dlist	*tmp;
	t_dlist *new;

	if (head == NULL)
		return (1);
	if (*head == NULL)
	{
		*head = ft_create_node(content);
		if (*head == NULL)
			return (1);
	}
	else
	{
		tmp = *head;
		while (tmp->next != NULL)
			tmp = tmp->next;
		new = ft_create_node(content);
		if (new == NULL)
			return (1);
		tmp->next = new;
		new->previous = tmp;
		new->next = NULL;
	}
	return (0);
}

t_dlist		*ft_make_dlist(char **av)
{
	int i;
	t_dlist *head;

	head = NULL;
	i = 0;
	while (av[i])
	{
		if (ft_push_back(av[i], &head))
			return (NULL);
		i++;
	}
	return (head);
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
