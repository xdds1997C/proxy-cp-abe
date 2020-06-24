/*
	Include glib.h, pbc.h, and bswabe.h before including this file.
 */

struct bswabe_pub_s
{
	char* pairing_desc;
	pairing_t p;
	element_t g;           /* G_1 */
	element_t h;           /* G_1 */
	element_t gp;          /* G_2 */
	element_t g_hat_alpha; /* G_T */
};

typedef struct
{
	int deg;
	/* coefficients from [0] x^0 to [deg] x^deg */
	element_t* coef; /* G_T (of length deg + 1) */
}
bswabe_polynomial_t;

struct bswabe_point_s
{
	int count;
	element_t* x; //Zp
	element_t* p_x; //Zp
};

struct bswabe_msk_s
{
	element_t beta;    /* Z_r */
	element_t g_alpha; /* G_2 */
	bswabe_polynomial_t* rpt;

};

typedef struct
{
	/* these actually get serialized */
	char* attr;
	element_t d;  /* G_2 */
	element_t dp; /* G_2 */
	element_t dpp; /* G_2 */ 

	/* only used during dec (only by dec_merge) */
	int used;
	element_t z;  /* G_1 */
	element_t zp; /* G_1 */
}
bswabe_prv_comp_t;

struct bswabe_prv_s
{
	element_t d;   /* G_2 */
	GArray* comps; /* bswabe_prv_comp_t's */
};

/*delegated private key*/
typedef struct
{
	/* these actually get serialized */
	char* attr;
	element_t d;  /* G_2 */
	element_t dp; /* G_2 */
	element_t dpp; /* G_2 */ 
	element_t d3p; /* G_2 */ 

	/* only used during dec (only by dec_merge) */
	int used;
	element_t z;  /* G_1 */
	element_t zp; /* G_1 */
}
bswabe_del_prv_comp_t;

struct bswabe_del_prv_s
{
	element_t d;   /* G_2 */
	GArray* comps; /* bswabe_del_prv_comp_t's */
};

typedef struct
{
	/* serialized */
	int k;            /* one if leaf, otherwise threshold */
	char* attr;       /* attribute string if leaf, otherwise null */
	element_t c;      /* G_1, only for leaves */
	element_t cp;     /* G_1, only for leaves */
	element_t cpp;     /* G_1, only for leaves, done by proxy*/ 
	GPtrArray* children; /* pointers to bswabe_policy_t's, len == 0 for leaves */

	/* only used during encryption */
	bswabe_polynomial_t* q;

	/* only used during decryption */
	int satisfiable;
	int min_leaves;
	int attri;
	GArray* satl;
}
bswabe_policy_t;

struct bswabe_cph_s
{
	element_t cs; /* G_T */
	element_t c;  /* G_1 */
	bswabe_policy_t* p;
};

