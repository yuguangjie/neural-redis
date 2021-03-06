/* This test was taken from:
 *
 * https://mattmazur.com/2015/03/17/a-step-by-step-backpropagation-example/
 *
 * It is interesting since allows to cross-validate the implementation
 * with manually obtained values. */

#include <stdio.h>

#include "../nn.h"

int main(void) {
    struct Ann *nn = AnnCreateNet3(2, 2, 2);
    float inputs[2] = {.05,.10};
    float desired[2] = {.01,.99};

    nn->learn_rate = 0.5;

    /* Input layer. */
    WEIGHT(nn,2,0,0) = .15;
    WEIGHT(nn,2,0,1) = .25;

    WEIGHT(nn,2,1,0) = .20;
    WEIGHT(nn,2,1,1) = .30;

    WEIGHT(nn,2,2,0) = .35;
    WEIGHT(nn,2,2,1) = .35;

    INPUT_NODE(nn,0) = inputs[0];
    INPUT_NODE(nn,1) = inputs[1];

    /* Hidden layer. */
    WEIGHT(nn,1,0,0) = .40;
    WEIGHT(nn,1,0,1) = .50;

    WEIGHT(nn,1,1,0) = .45;
    WEIGHT(nn,1,1,1) = .55;

    WEIGHT(nn,1,2,0) = .60;
    WEIGHT(nn,1,2,1) = .60;

    int j;
    for (j = 0; j < 10000; j++) {
        AnnSimulateError(nn, inputs, desired);
        AnnSetDeltas(nn, 0);
        AnnCalculateGradients(nn, desired);
        AnnUpdateDeltasGD(nn);
        AnnAdjustWeights(nn,1);

        if (j == 0) {
            AnnPrint(nn);
            printf("\n*** TEST VECTOR ***\n"
                   "Weights at layer 2 should be: "
                   "0.1497, 0.2497, 0.1995, 0.2995\n");
        }
    }
    printf("\nAfter training:\n\n");
    AnnPrint(nn);
    return 0;
}
