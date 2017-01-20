/* Example on how to do a test and expose a function

On this example, we will expose the function: 'sc_halve(out,x,y);' from
'src/decaf_fast.c'
*/

//Original function
snv sc_halve (
    scalar_t out,
    const scalar_t a,
    const scalar_t p
) {
    decaf_word_t mask = -(a->limb[0] & 1);
    decaf_dword_t chain = 0;
    unsigned int i;
    for (i=0; i<SCALAR_LIMBS; i++) {
        chain = (chain + a->limb[i]) + (p->limb[i] & mask);
        out->limb[i] = chain;
        chain >>= WBITS;

    }

    for (i=0; i<SCALAR_LIMBS-1; i++) {
        out->limb[i] = out->limb[i]>>1 | out->limb[i+1]<<(WBITS-1);
    }
    out->limb[i] = out->limb[i]>>1 | chain<<(WBITS-1);
}

//function for exposing (on the same file)
void API_NS(new_halve) (const scalar_t s, const scalar_t t) { //don't forget the 'API_NS'

    scalar_t x, y;
    x->limb[13] = 314;
    y->limb[13] = 69;

    scalar_t out;

    sc_halve(out,x,y);
}

//Exposing it in the 'include/decaf.h' file
/**
  New Halve
**/
void decaf_448_new_halve (
    const decaf_448_scalar_t scalar,
    const decaf_448_scalar_t scalar1
) API_VIS NONNULL2 NOINLINE; //this means that it is visible, that its params
//should not be null (the 2 of them), that it should not be inlined

//Exposing it in the 'include/decaf.hxx' file
//As it works with scalars, place it on the 'class: Scalar'
//Params are generated on that file. Search for them.
/** @brief new halve */
inline void new_halve() const NOEXCEPT{
    decaf_448_new_halve(s, s);
}

//Make a test on the 'test/test_decaf.cxx' file
static void test_halve() {
    Test test("Halve");
    Scalar s(0);
    s.new_halve();
}

//add it to the main on the same file
#define TRUE false // a tweak ;)

int main(int argc, char **argv) {
	(void) argc; (void) argv;

	if (TRUE){
		Tests<decaf::Ed448>::test_arithmetic();
		Tests<decaf::Ed448>::test_elligator();
		Tests<decaf::Ed448>::test_ec();
		test_decaf();
		Tests<decaf::Ed448>::test_encode();
		Tests<decaf::Ed448>::test_convert();
		Tests<decaf::Ed448>::test_derivePrivate();
	}

                Tests<decaf::Ed448>::test_halve();


	if (passing) printf("Passed all tests.\n");

	return passing ? 0 : 1;
}

//Run it! (make test)
