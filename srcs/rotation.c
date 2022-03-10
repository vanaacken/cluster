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
