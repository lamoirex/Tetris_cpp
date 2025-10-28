#ifndef _OFFSET_
#define _OFFSET_
int tetrisBlocksInitialPosition[7 /*kinds of a piece*/][4 /*rotation*/][2 /*offset*/] = {
    // Square
    {
        {-2,-3},
        {-2,-3},
        {-2,-3},
        {-2,-3}
    },
    // "|" block(vertical/horizontal block)
    {
        {-2,-2},
        {-2,-3},
        {-2,-2},
        {-2,-3}
    },
    // "L" block
    {
        {-2,-3},
        {-2,-3},
        {-2,-3},
        {-2,-2},
    },
    // "L mirrored" block
    {
        {-2,-3},
        {-2,-2},
        {-2,-3},
        {-2,-3},
    },
    // "N" block
    {
        {-2,-3},
        {-2,-2},
        {-2,-3},
        {-2,-3},
    },
    // "N mirrored" block
    {
        {-2,-3},
        {-2,-3},
        {-2,-3},
        {-2,-2},
    },
    // "T" block
    {
        {-2,-3},
        {-2,-3},
        {-2,-3},
        {-2,-2},
    },
};
#endif