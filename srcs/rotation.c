#include "../includes/cluster.h"

void	rotation(int num_rotations, t_axial *tmp)
{
	while (num_rotations > 0)
	{
		int s = - tmp->q - tmp->r;
		tmp->q = - tmp->r;
		tmp->r = - s;
		num_rotations--;
	}
}

int	reinsert_hash_table()
{
	int n = 0;
	for (size_t i = 0; i < HASH_SIZE; i++)
	{
		if (rotated_hash_array[i] != NULL)
		{
			t_hash_item *tmp = rotated_hash_array[i];
			while (tmp != NULL)
			{
				if (!insert(tmp->hex->axial, tmp->hex->color))
					return 0;
				if (!delete_other(tmp->hex->axial))
					return 0;
				tmp = tmp->next;
				n++;
			}
		}
	}
	return 1;
}

int	rotate_cluster(int num_rotations)
{
	int n = 0;
	t_axial	axial_tmp;
	for (size_t i = 0; i < HASH_SIZE; i++)
	{
		if (hash_array[i] != NULL)
		{
			t_hash_item *tmp = hash_array[i];
			while (tmp != NULL)
			{
				axial_tmp = tmp->hex->axial;
				rotation(num_rotations, &axial_tmp);
				if (!insert_other(axial_tmp, tmp->hex->color))
					return 0;
				if (!delete(tmp->hex->axial))
					return 0;
				tmp = tmp->next;
				n++;
			}
		}
	}
	if (!reinsert_hash_table())
		return 0;
	return 1;
}

int	check_empty_hex(t_axial *axial)
{
	t_axial	axial_tmp;
	axial_tmp = *axial;
	axial_tmp.r++;
	if (search(axial_tmp))
		return (axial_tmp.r--);
	else
		return (axial_tmp.r);
		// check_empty_hex(&axial_tmp);
	return(0);
}

int	add_gravity()
{
	int check = 0;
	for(int q = -SIZE + 1; q < SIZE; q++)
	{
		int r = fmax(-SIZE + 1, -SIZE + 1 - q);
		int column_len = (2*SIZE -1 - abs(q));
		for (int i = column_len - 2; i >= 0; --i)
		{
			t_axial axial_tmp;
			axial_tmp.q = q;
			axial_tmp.r = r + i;
			t_hex *hex_tmp = search(axial_tmp);
			if (hex_tmp)
			{
				check = 1;
				int r2 = check_empty_hex(&axial_tmp);
				printf("q = %d, r = %d| new  r = %d\n", axial_tmp.q, axial_tmp.r, r2);
				if (r2 != axial_tmp.r)
				{
					printf("JELLo\n");
					if (!delete(axial_tmp))
					{
						printf("DELLo\n");
						return 0;
					}	
					axial_tmp.r = r2;
					if (!insert(axial_tmp, hex_tmp->color))
					{
						printf("IELLo\n");
						return 0;
					}	
				}
			}
		}
		printf("CHECK = %d\n", check);
		if (q == SIZE - 1 && check == 1)
		{
			q = - SIZE;
			check = 0;
		}		
	}
	// if (!reinsert_hash_table())
	// 	return 0;


	// int n = 0;
	// for (int i = 0; i < HASH_SIZE; i++)
	// {
	// 	int check = 0;
	// 	if (hash_array[i] != NULL)
	// 	{
	// 		t_hash_item *tmp = hash_array[i];
	// 		while (tmp != NULL)
	// 		{

	// 			tmp = tmp->next;
	// 			n++;
	// 		}
	// 	}
	// 	if (check == 0 && i == HASH_SIZE - 1)
	// 		break;
	// 	else if (i == HASH_SIZE - 1 && check == 1)
	// 		i = -1;
	// }
	return 1;
}
