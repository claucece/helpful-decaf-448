//a pretty useful 'for', already defined in the code
#define FOR_LIMB(i,op) { unsigned int i=0; for (i=0; i<NLIMBS; i++)  { op; }}

// THE STRUCTURES

// Galois field struct
/** Galois field element internal structure */
typedef struct gf_s {
    decaf_word_t limb[DECAF_448_LIMBS];
} __attribute__((aligned(32))) gf_s, gf[1];
/** @endcond */


/** Twisted Edwards (-1,d-1) extended homogeneous coordinates */
typedef struct decaf_448_point_s { /**@cond internal*/gf x,y,z,t;/**@endcond*/ } decaf_448_point_t[1];

/* Projective Niels coordinates */
typedef struct { gf a, b, c; } niels_s, niels_t[1];
typedef struct { niels_t n; gf z; } pniels_s, pniels_t[1];

/* Scalar */
typedef struct decaf_448_scalar_s {
    /** @cond internal */
    decaf_word_t limb[DECAF_448_SCALAR_LIMBS];
    /** @endcond */
} decaf_448_scalar_t[1];


// PRINTS
//Take in account that sometimes, you will want to print a 'const'. In that case,
//add 'const' to signature.

//Print each limb in a galoisField. gF are found everywhere.
static void gfPrint(gf_s * a){
    FOR_LIMB(i, {
        printf("0x%08x, \n", a->limb[i]);
    });
}

//Print each coordinate of the point.
//Can be used for niels or extended.
//This will be printed with strike golang's format.
//To use it, do: pointPrint("the x coor of point p", p->x)
static void pointPrint(char * c, gf_s * a){
    printf("%s \n", c);
    printf("%s", "&bigNumber{");
    FOR_LIMB(i, {
        printf("0x%08x, \n", a->limb[i]);
    });
    printf("%s", "} \n");
}

//Print each coord of a NielsPoint. It can also be used with extended.
static void nielsPrint(niels_t n){
    printf("%s", "nielsA := &bigNumber{");
    FOR_LIMB(i, {
        printf("0x%08x,", n->a->limb[i]);
    });
    printf("}, \n");

    printf("%s", "nielsB := &bigNumber{");
    FOR_LIMB(i, {
        printf("0x%08x,", n->b->limb[i]);
    });
    printf("}, \n");

    printf("%s", "nielsC := &bigNumber{");
    FOR_LIMB(i, {
        printf("0x%08x,", n->c->limb[i]);
    });
    printf("}, \n");
}

//Print each limb of scalars
void scalarprint(char * a, scalar_t s) {
    printf("%s \n", a);
    unsigned int i;
    for (i=0; i<SCALAR_LIMBS;i++) {
        printf("%08x \n", s->limb[i]);
    }
}

//ASSIGNATIONS
//For any struct that holds 'decaf_word_t'
gf x;
decaf_word_t a;
a = 0x08db85c2;
x->limb[0] = a;

//to assing several coordinates
decaf_word_t x, y, z, t;
x = 0x1;
y = 0x2;
z = 0x3;
t = 0x4;

point_t p = {{{{{x}}}, {{{y}}}, {{{z}}}, {{{t}}}}};

//CLEANING

//For gF
void cleanGf(gf_s * a) {
    FOR_LIMB(i, {
        a->limb[i] = 0;
    });
}
