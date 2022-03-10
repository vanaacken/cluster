#include "cluster.h"

t_hash_item* rotated_hash_array[HASH_SIZE];

void	rotation(int num_rotations, t_axial *tmp)
{
	while (num_rotations >= 0)
	{
		int s = - tmp->q - tmp->r;
		tmp->q = - tmp->r;
		tmp->r = - s;
		num_rotations--;
	}
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
				rotation(num_rotations, &axial_tmp);
				insert(axial_tmp, tmp->hex->color, &rotated_hash_array);
				tmp = tmp->next;
				n++;
			}
		}
	}
}

