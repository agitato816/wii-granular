#include "m_pd.h"
#ifdef NT
#pragma warning( disable : 4244 )
#pragma warning( disable : 4305 )
#endif

/* ------------------------ square~ ----------------------------- */


static t_class *square_class;

typedef struct _square
{
    t_object x_obj;
    t_float x_f;
    t_float x_last;
    t_float x_half;
    t_float x_sr;
} t_square;

static t_int *square_perform(t_int *w)
{
	t_square *x = (t_square *)(w[1]);	
    t_float *in = (t_float *)(w[2]);
    t_float *out = (t_float *)(w[3]);
	int n = (int)(w[4]);
	
    float sr = x->x_sr;
	float samp = (float)x->x_last;
	float half = (float)x->x_half;
	float f = 0;
	
    while (n--)
    {
		f = *(in++);
		if(samp < 0){
			if(f == 0.0){
				samp = 0; 
			}
			else{
				samp = sr / f;
			}
			half = samp / 2; 
		}
		*out++ =  samp > half ? -0.5 : 0.5;
		samp--;
    }
		
	x->x_half = half;
	x->x_last = samp;
	
    return (w+5);
}

static void square_dsp(t_square *x, t_signal **sp)
{
	x->x_sr = sp[0]->s_sr;
    dsp_add(square_perform, 4, x, sp[0]->s_vec, sp[1]->s_vec, sp[0]->s_n);
}

static void *square_new(t_floatarg freq)
{
    t_square *x = (t_square *)pd_new(square_class);
    outlet_new(&x->x_obj, gensym("signal"));
    x->x_f = freq;
	x->x_last = -1.0;
	x->x_half = 0.0;
    
    return (x);
}

void square_tilde_setup(void)
{
    square_class = class_new(gensym("square~"), (t_newmethod)square_new, 0,
    	sizeof(t_square), 0, A_DEFFLOAT, 0);
    CLASS_MAINSIGNALIN(square_class, t_square, x_f);
    class_addmethod(square_class, (t_method)square_dsp, gensym("dsp"), 0);
}
