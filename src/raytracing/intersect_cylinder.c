#include "minirt.h"

static void	init_i(t_i *i1, t_i *i2)
{
	i1->t = 0;
	i1->object = NULL;
	i2->t = 0;
	i2->object = NULL;
}

/**
 * @brief Returns true if [r]ay intersects curved portion of cylinder. 
 * @param [in] r: t_ray to be tested
 * @param [in] *q: t_quad - pointer to struct for quadratic values 
 */
bool	cylinder_discriminant(t_ray r, t_quad *q)
{
	q->a = (r.dir.x * r.dir.x) + (r.dir.z * r.dir.z);
	if (q->a < 0)
		return (false);
	q->b = 2 * r.origin.x * r.dir.x + 2 * r.origin.z * r.dir.z;
	q->c = (r.origin.x * r.origin.x) + (r.origin.z * r.origin.z) - 1;
	q->d = (q->b * q->b) - 4 * q->a * q->c;
	if (q->d < 0)
		return (false);
	return (true);
}

/**
 * @brief Fill pointed xs with i1,i2 depending on actual cylinder intersections 
 * @details This is to ensure we always pass 2 intersections to xs, regardless
 * 			of which intersections are filled or not 
 */
void	cylinder_fill_intersections(t_xs *xs, t_i i1, t_i i2)
{
	if (i1.object && i2.object)
		intersections(xs, i1, i2);
	else if (i1.object && !i2.object)
		intersections(xs, i1, i1);
	else if (i2.object && !i1.object)
		intersections(xs, i2, i2);
}

/**
 * @brief Swap the order of t values 
 */
void	swap_t_values(float *t)
{
	float	tmp;
	tmp = t[0];
	t[0] = t[1];
	t[1] = tmp;
}

/**
 * @brief Returns intersection information for given cylinder and ray
 * @todo will need breaking up for norm
 */
t_xs	*intersects_cylinder(t_scene_obj *obj, t_ray r, t_xs *xs)
{
	t_i		i1;
	t_i		i2;
	t_quad	q;
	float	t[2];
	float	y[2];

	init_i(&i1, &i2);
	if (!cylinder_discriminant(r, &q))
		return (xs);

	t[0] = (-q.b - sqrt(q.d)) / (2 * q.a);
	t[1] = (-q.b + sqrt(q.d)) / (2 * q.a);
	if (t[0] > t[1])
		swap_t_values(&t);
	y[0] = r.origin.y + t[0] * r.dir.y;
	if (obj->min < y[0] && y[0] < obj->max)
		i1 = intersection(t[0], obj);
	y[1] = r.origin.y + t[1] * r.dir.y;
	if (obj->min < y[1] && y[1] < obj->max)
		i2 = intersection(t[1], obj);

	cylinder_fill_intersections(xs, i1, i2);

	return (xs);
}

