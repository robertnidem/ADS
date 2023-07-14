/*
 * IGRF.h
 *
 *  Created on: 20 jun 2022
 *      Author: rober
 */

#ifndef IGRF_H_
#define IGRF_H_

struct magField{
    float Bx;
    float By;
    float Bz;
};
typedef struct magField magField;
#define g1_0 -0.0000294048f
#define g1_1 -0.0000014509f
#define g2_0 -0.0000024996f
#define g2_1  0.000001677f
#define g2_2  0.000001672f
#define g3_0  0.0000013632f
#define g3_1 -0.0000023812f
#define g3_2  0.000001236f
#define g3_3  0.0000005257f
#define g4_0  0.000000903f
#define g4_1  0.0000008095f
#define g4_2  0.0000000863f
#define g4_3 -0.0000003094f
#define g4_4  0.000000048f
#define g5_0 -0.0000002343f
#define g5_1  0.0000003632f
#define g5_2  0.0000001878f
#define g5_3 -0.0000001407f
#define g5_4 -0.0000001512f
#define g5_5  0.0000000135f
#define g6_0  0.000000066f
#define g6_1  0.0000000655f
#define g6_2  0.0000000729f
#define g6_3 -0.0000001215f
#define g6_4 -0.0000000362f
#define g6_5  0.0000000135f
#define g6_6 -0.0000000647f
#define g7_0  0.0000000806f
#define g7_1 -0.0000000767f
#define g7_2 -0.0000000082f
#define g7_3  0.0000000565f
#define g7_4  0.0000000158f
#define g7_5  0.0000000064f
#define g7_6 -0.0000000072f
#define g7_7  0.0000000098f
#define g8_0  0.0000000237f
#define g8_1  0.0000000097f
#define g8_2 -0.0000000176f
#define g8_3 -0.0000000005f
#define g8_4 -0.0000000211f
#define g8_5  0.0000000153f
#define g8_6  0.0000000137f
#define g8_7 -0.0000000165f
#define g8_8 -0.0000000003f
#define g9_0  0.000000005f
#define g9_1  0.0000000084f
#define g9_2  0.0000000029f
#define g9_3 -0.0000000015f
#define g9_4 -0.0000000011f
#define g9_5 -0.0000000132f
#define g9_6  0.0000000011f
#define g9_7  0.0000000088f
#define g9_8 -0.0000000093f
#define g9_9 -0.0000000119f
#define g10_0  -0.0000000019f
#define g10_1  -0.0000000062f
#define g10_2  -0.0000000001f
#define g10_3   0.0000000017f
#define g10_4  -0.0000000009f
#define g10_5   0.0000000007f
#define g10_6  -0.0000000009f
#define g10_7   0.0000000019f
#define g10_8   0.0000000014f
#define g10_9  -0.0000000024f
#define g10_10 -0.0000000038f
#define g11_0   0.000000003f
#define g11_1  -0.0000000014f
#define g11_2  -0.0000000025f
#define g11_3   0.0000000023f
#define g11_4  -0.0000000009f
#define g11_5   0.0000000003f
#define g11_6  -0.0000000007f
#define g11_7  -0.0000000001f
#define g11_8   0.0000000014f
#define g11_9  -0.0000000006f
#define g11_10  0.0000000002f
#define g11_11  0.0000000031f
#define g12_0  -0.000000002f
#define g12_1  -0.0000000001f
#define g12_2   0.0000000005f
#define g12_3   0.0000000013f
#define g12_4  -0.0000000012f
#define g12_5   0.0000000007f
#define g12_6   0.0000000003f
#define g12_7   0.0000000005f
#define g12_8  -0.0000000003f
#define g12_9  -0.0000000005f
#define g12_10  0.0000000001f
#define g12_11 -0.0000000011f
#define g12_12 -0.0000000003f
#define g13_0   0.0000000001f
#define g13_1  -0.0000000009f
#define g13_2   0.0000000005f
#define g13_3   0.0000000007f
#define g13_4  -0.0000000003f
#define g13_5   0.0000000008f
#define g13_6   0.0f
#define g13_7   0.0000000008f
#define g13_8   0.0f
#define g13_9   0.0000000004f
#define g13_10  0.0000000001f
#define g13_11  0.0000000005f
#define g13_12 -0.0000000005f
#define g13_13 -0.0000000004f

#define h1_0  0
#define h1_1  0.0000046525f
#define h2_0  0
#define h2_1 -0.0000029916f
#define h2_2 -0.0000007346f
#define h3_0  0
#define h3_1 -0.0000000821f
#define h3_2  0.0000002419f
#define h3_3 -0.0000005434f
#define h4_0  0
#define h4_1  0.0000002819f
#define h4_2 -0.0000001584f
#define h4_3  0.0000001997f
#define h4_4 -0.0000003497f
#define h5_0  0
#define h5_1  0.0000000477f
#define h5_2  0.0000002083f
#define h5_3 -0.0000001212f
#define h5_4  0.0000000323f
#define h5_5  0.0000000989f
#define h6_0  0
#define h6_1 -0.0000000191f
#define h6_2  0.0000000251f
#define h6_3  0.0000000528f
#define h6_4 -0.0000000645f
#define h6_5  0.0000000089f
#define h6_6  0.0000000681f
#define h7_0  0
#define h7_1 -0.0000000515f
#define h7_2 -0.0000000169f
#define h7_3  0.0000000022f
#define h7_4  0.0000000235f
#define h7_5 -0.0000000022f
#define h7_6 -0.0000000272f
#define h7_7 -0.0000000018f
#define h8_0  0
#define h8_1  0.0000000084f
#define h8_2 -0.0000000153f
#define h8_3  0.0000000128f
#define h8_4 -0.0000000117f
#define h8_5  0.0000000149f
#define h8_6  0.0000000036f
#define h8_7 -0.0000000069f
#define h8_8  0.0000000028f
#define h9_0  0
#define h9_1 -0.0000000234f
#define h9_2  0.000000011f
#define h9_3  0.0000000098f
#define h9_4 -0.0000000051f
#define h9_5 -0.0000000063f
#define h9_6  0.0000000078f
#define h9_7  0.0000000004f
#define h9_8 -0.0000000014f
#define h9_9  0.0000000096f
#define h10_0   0
#define h10_1   0.0000000034f
#define h10_2  -0.0000000002f
#define h10_3   0.0000000036f
#define h10_4   0.0000000048f
#define h10_5  -0.0000000086f
#define h10_6  -0.0000000001f
#define h10_7  -0.0000000043f
#define h10_8  -0.0000000034f
#define h10_9  -0.0000000001f
#define h10_10 -0.0000000088f
#define h11_0   0
#define h11_1   0
#define h11_2   0.0000000025f
#define h11_3  -0.0000000006f
#define h11_4  -0.0000000004f
#define h11_5   0.0000000006f
#define h11_6  -0.0000000002f
#define h11_7  -0.0000000017f
#define h11_8  -0.0000000016f
#define h11_9  -0.000000003f
#define h11_10 -0.000000002f
#define h11_11 -0.0000000026f
#define h12_0   0
#define h12_1  -0.0000000012f
#define h12_2   0.0000000005f
#define h12_3   0.0000000014f
#define h12_4  -0.0000000018f
#define h12_5   0.0000000001f
#define h12_6   0.0000000008f
#define h12_7  -0.0000000002f
#define h12_8   0.0000000006f
#define h12_9   0.0000000002f
#define h12_10 -0.0000000009f
#define h12_11  0
#define h12_12  0.0000000005f
#define h13_0   0
#define h13_1  -0.0000000009f
#define h13_2   0.0000000006f
#define h13_3   0.0000000014f
#define h13_4  -0.0000000004f
#define h13_5  -0.0000000013f
#define h13_6  -0.0000000001f
#define h13_7   0.0000000003f
#define h13_8  -0.0000000001f
#define h13_9   0.0000000005f
#define h13_10  0.0000000005f
#define h13_11 -0.0000000004f
#define h13_12 -0.0000000004f
#define h13_13 -0.0000000006f


float kronDel(float j,float k);

VECTOR earthmagfield13(float r_N[3][1], float t, float alpha_G_0, int n);

#endif /* IGRF_H_ */
