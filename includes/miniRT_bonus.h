#ifndef MINIRT_BONUS_H
# define MINIRT_BONUS_H

# include "miniRT.h"

// checkerboard, defalt yes true
#ifndef USE_CHECKERBOARD
# define USE_CHECKERBOARD 1
#endif

// specular strength
#ifndef SPEC_K
# define SPEC_K 0.5
#endif

// shininess
#ifndef SPEC_SHININESS
# define SPEC_SHININESS 16
#endif

t_color	final_color(t_scene *scene, t_hit_record rec);

#endif