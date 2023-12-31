/*
 * IGRF.c
 *
 *  Created on: 13 sep 2022

 Code adapted to C language from:
 "Luigi De Maria (2023). Earth Magnetic Field with IGRF 13th Gen. (https://www.mathworks.com/matlabcentral/fileexchange/88406-earth-magnetic-field-with-igrf-13th-gen), MATLAB Central File Exchange. Retrieved July 14, 2023."
 */

#include<stdio.h>
#include<stdint.h>
#include<stdlib.h>
#include<math.h>
#include"structs.h"
#include"matrix.h"
#include"vector.h"
#include"IGRF.h"


const float g_irf[14][13]={{g1_0, g2_0, g3_0, g4_0, g5_0, g6_0, g7_0, g8_0, g9_0, g10_0, g11_0, g12_0, g13_0},
                       {g1_1, g2_1, g3_1, g4_1, g5_1, g6_1, g7_1, g8_1, g9_1, g10_1, g11_1, g12_1, g13_1},
                       {0   , g2_2, g3_2, g4_2, g5_2, g6_2, g7_2, g8_2, g9_2, g10_2, g11_2, g12_2, g13_2},
                       {0   , 0   , g3_3, g4_3, g5_3, g6_3, g7_3, g8_3, g9_3, g10_3, g11_3, g12_3, g13_3},
                       {0   , 0   , 0   , g4_4, g5_4, g6_4, g7_4, g8_4, g9_4, g10_4, g11_4, g12_4, g13_4},
                       {0   , 0   , 0   , 0   , g5_5, g6_5, g7_5, g8_5, g9_5, g10_5, g11_5, g12_5, g13_5},
                       {0   , 0   , 0   , 0   , 0   , g6_6, g7_6, g8_6, g9_6, g10_6, g11_6, g12_6, g13_6},
                       {0   , 0   , 0   , 0   , 0   , 0   , g7_7, g8_7, g9_7, g10_7, g11_7, g12_7, g13_7},
                       {0   , 0   , 0   , 0   , 0   , 0   , 0   , g8_8, g9_8, g10_8, g11_8, g12_8, g13_8},
                       {0   , 0   , 0   , 0   , 0   , 0   , 0   , 0   , g9_9, g10_9, g11_9, g12_9, g13_9},
                       {0   , 0   , 0   , 0   , 0   , 0   , 0   , 0   , 0   , g10_10, g11_10, g12_10, g13_10},
                       {0   , 0   , 0   , 0   , 0   , 0   , 0   , 0   , 0   , 0     , g11_11, g12_11, g13_11},
                       {0   , 0   , 0   , 0   , 0   , 0   , 0   , 0   , 0   , 0     , 0     , g12_12, g13_12},
                       {0   , 0   , 0   , 0   , 0   , 0   , 0   , 0   , 0   , 0     , 0     , 0     , g13_13}};



const float h_irf[14][13]={{h1_0, h2_0, h3_0, h4_0, h5_0, h6_0, h7_0, h8_0, h9_0, h10_0, h11_0, h12_0, h13_0},
                 {h1_1, h2_1, h3_1, h4_1, h5_1, h6_1, h7_1, h8_1, h9_1, h10_1, h11_1, h12_1, h13_1},
                 {0   , h2_2, h3_2, h4_2, h5_2, h6_2, h7_2, h8_2, h9_2, h10_2, h11_2, h12_2, h13_2},
                 {0   , 0   , h3_3, h4_3, h5_3, h6_3, h7_3, h8_3, h9_3, h10_3, h11_3, h12_3, h13_3},
                 {0   , 0   , 0   , h4_4, h5_4, h6_4, h7_4, h8_4, h9_4, h10_4, h11_4, h12_4, h13_4},
                 {0   , 0   , 0   , 0   , h5_5, h6_5, h7_5, h8_5, h9_5, h10_5, h11_5, h12_5, h13_5},
                 {0   , 0   , 0   , 0   , 0   , h6_6, h7_6, h8_6, h9_6, h10_6, h11_6, h12_6, h13_6},
                 {0   , 0   , 0   , 0   , 0   , 0   , h7_7, h8_7, h9_7, h10_7, h11_7, h12_7, h13_7},
                 {0   , 0   , 0   , 0   , 0   , 0   , 0   , h8_8, h9_8, h10_8, h11_8, h12_8, h13_8},
                 {0   , 0   , 0   , 0   , 0   , 0   , 0   , 0   , h9_9, h10_9, h11_9, h12_9, h13_9},
                 {0   , 0   , 0   , 0   , 0   , 0   , 0   , 0   , 0   , h10_10, h11_10, h12_10, h13_10},
                 {0   , 0   , 0   , 0   , 0   , 0   , 0   , 0   , 0   , 0     , h11_11, h12_11, h13_11},
                 {0   , 0   , 0   , 0   , 0   , 0   , 0   , 0   , 0   , 0     , 0     , h12_12, h13_12},
                 {0   , 0   , 0   , 0   , 0   , 0   , 0   , 0   , 0   , 0     , 0     , 0     , h13_13}};




VECTOR earthmagfield13(float r_N[3][1], float t, float alpha_G_0, int n)
{
    /*
     * INPUTS
     * r_N          [3x1]   S/C Pos (Inertial Frame)  [km]
     * t            [1x1]   Day Time                  [sec]
     * g            [14x13] Gauss Coff. g_nm Matrix   [T]
     * h            [14x13] Gauss Coff. h_nm Matrix   [T]
     * alpha_G_0    [1,1]   Greenwich Init. Longitude [rad]
     * n            [1x1]   Order Desired             [-]
     * --------------------------------------------------
     * OUTPUTS
     * B_N          [3x1]   Mag. Field Components     [T]
     *
     */


    VECTOR B_N=Vinit(3);
    //MATRIZ S_nm = MinitZ(n+1,n);
    float S_nm[14][13]={{0,0,0,0,0,0,0,0,0,0,0,0,0},{0,0,0,0,0,0,0,0,0,0,0,0,0},{0,0,0,0,0,0,0,0,0,0,0,0,0},{0,0,0,0,0,0,0,0,0,0,0,0,0},{0,0,0,0,0,0,0,0,0,0,0,0,0},{0,0,0,0,0,0,0,0,0,0,0,0,0},{0,0,0,0,0,0,0,0,0,0,0,0,0},{0,0,0,0,0,0,0,0,0,0,0,0,0},{0,0,0,0,0,0,0,0,0,0,0,0,0},{0,0,0,0,0,0,0,0,0,0,0,0,0},{0,0,0,0,0,0,0,0,0,0,0,0,0},{0,0,0,0,0,0,0,0,0,0,0,0,0},{0,0,0,0,0,0,0,0,0,0,0,0,0},{0,0,0,0,0,0,0,0,0,0,0,0,0}};
    float S_00 =1;
    //MATRIZ P_nm = MinitZ(n+1,n);
    float P_nm[14][13]={{0,0,0,0,0,0,0,0,0,0,0,0,0},{0,0,0,0,0,0,0,0,0,0,0,0,0},{0,0,0,0,0,0,0,0,0,0,0,0,0},{0,0,0,0,0,0,0,0,0,0,0,0,0},{0,0,0,0,0,0,0,0,0,0,0,0,0},{0,0,0,0,0,0,0,0,0,0,0,0,0},{0,0,0,0,0,0,0,0,0,0,0,0,0},{0,0,0,0,0,0,0,0,0,0,0,0,0},{0,0,0,0,0,0,0,0,0,0,0,0,0},{0,0,0,0,0,0,0,0,0,0,0,0,0},{0,0,0,0,0,0,0,0,0,0,0,0,0},{0,0,0,0,0,0,0,0,0,0,0,0,0},{0,0,0,0,0,0,0,0,0,0,0,0,0},{0,0,0,0,0,0,0,0,0,0,0,0,0}};
    float P_00=1;
    //MATRIZ d_P_nm = MinitZ(n+1,n);
    float d_P_nm[14][13]={{0,0,0,0,0,0,0,0,0,0,0,0,0},{0,0,0,0,0,0,0,0,0,0,0,0,0},{0,0,0,0,0,0,0,0,0,0,0,0,0},{0,0,0,0,0,0,0,0,0,0,0,0,0},{0,0,0,0,0,0,0,0,0,0,0,0,0},{0,0,0,0,0,0,0,0,0,0,0,0,0},{0,0,0,0,0,0,0,0,0,0,0,0,0},{0,0,0,0,0,0,0,0,0,0,0,0,0},{0,0,0,0,0,0,0,0,0,0,0,0,0},{0,0,0,0,0,0,0,0,0,0,0,0,0},{0,0,0,0,0,0,0,0,0,0,0,0,0},{0,0,0,0,0,0,0,0,0,0,0,0,0},{0,0,0,0,0,0,0,0,0,0,0,0,0},{0,0,0,0,0,0,0,0,0,0,0,0,0}};
    float d_P_00 =0;
    //MATRIZ k_nm = MinitZ(n+1,n);
    //MATRIZ g_nm = MinitZ(n+1,n);
    //MATRIZ h_nm = MinitZ(n+1,n);
    float k_nm[14][13]={{0,0,0,0,0,0,0,0,0,0,0,0,0},{0,0,0,0,0,0,0,0,0,0,0,0,0},{0,0,0,0,0,0,0,0,0,0,0,0,0},{0,0,0,0,0,0,0,0,0,0,0,0,0},{0,0,0,0,0,0,0,0,0,0,0,0,0},{0,0,0,0,0,0,0,0,0,0,0,0,0},{0,0,0,0,0,0,0,0,0,0,0,0,0},{0,0,0,0,0,0,0,0,0,0,0,0,0},{0,0,0,0,0,0,0,0,0,0,0,0,0},{0,0,0,0,0,0,0,0,0,0,0,0,0},{0,0,0,0,0,0,0,0,0,0,0,0,0},{0,0,0,0,0,0,0,0,0,0,0,0,0},{0,0,0,0,0,0,0,0,0,0,0,0,0},{0,0,0,0,0,0,0,0,0,0,0,0,0}};
    float g_nm[14][13]={{0,0,0,0,0,0,0,0,0,0,0,0,0},{0,0,0,0,0,0,0,0,0,0,0,0,0},{0,0,0,0,0,0,0,0,0,0,0,0,0},{0,0,0,0,0,0,0,0,0,0,0,0,0},{0,0,0,0,0,0,0,0,0,0,0,0,0},{0,0,0,0,0,0,0,0,0,0,0,0,0},{0,0,0,0,0,0,0,0,0,0,0,0,0},{0,0,0,0,0,0,0,0,0,0,0,0,0},{0,0,0,0,0,0,0,0,0,0,0,0,0},{0,0,0,0,0,0,0,0,0,0,0,0,0},{0,0,0,0,0,0,0,0,0,0,0,0,0},{0,0,0,0,0,0,0,0,0,0,0,0,0},{0,0,0,0,0,0,0,0,0,0,0,0,0},{0,0,0,0,0,0,0,0,0,0,0,0,0}};
    float h_nm[14][13]={{0,0,0,0,0,0,0,0,0,0,0,0,0},{0,0,0,0,0,0,0,0,0,0,0,0,0},{0,0,0,0,0,0,0,0,0,0,0,0,0},{0,0,0,0,0,0,0,0,0,0,0,0,0},{0,0,0,0,0,0,0,0,0,0,0,0,0},{0,0,0,0,0,0,0,0,0,0,0,0,0},{0,0,0,0,0,0,0,0,0,0,0,0,0},{0,0,0,0,0,0,0,0,0,0,0,0,0},{0,0,0,0,0,0,0,0,0,0,0,0,0},{0,0,0,0,0,0,0,0,0,0,0,0,0},{0,0,0,0,0,0,0,0,0,0,0,0,0},{0,0,0,0,0,0,0,0,0,0,0,0,0},{0,0,0,0,0,0,0,0,0,0,0,0,0},{0,0,0,0,0,0,0,0,0,0,0,0,0}};
    float z=r_N[2][0];
    float x=r_N[0][0];
    float y=r_N[1][0];
    float ab=sqrt(z*z+x*x+y*y);
    float Re=6371;
    float om_E = 0.00007292124;
    float delta = asin(z/ab);
    float theta = (PI/2)-delta;
    float alpha_G=alpha_G_0 + t*om_E;
    float alpha;
    if (y/ab > 0)
    {
        alpha = acos((x/ab)/cos(delta));
    }
    else
    {
        alpha = 2*PI - acos((x/ab)/cos(delta));
    }
    float phi=alpha-alpha_G;
    // Gauss Normalization
    //Función para monitorear la matriz
    float A[14][13];

    int i,j;
    float ac;
    for (j=0;j<n;j++)
    {
        if (j==0)
        {
            S_nm[0][j]=1*((2*(j+1)-1)/(j+1));
        }
        else //if(j>=1)
        {
            ac=(2*(float)j+1)/((float)j+1);
            S_nm[0][j]=S_nm[0][j-1]*ac;
        }
    }

    //Remaining Componentes
    for(j=0;j<n;j++)
    {
        for (i=1;i<(j+2);i++)
        {
            S_nm[i][j]=S_nm[i-1][j]*sqrt(((kronDel(1,i)+1)*((j+1)-(i)+1))/((j+1)+(i)));
        }
    }

    for(i=0;i<n+1;i++)
    {
        for(j=0;j<n;j++)
        {
            A[i][j]=S_nm[i][j];
        }
    }


    //Coefficients k^n,m
    for(j=0;j<n;j++)
    {
        for(i=0;i<(j+2);i++)
        {
            if (j==0)
            {
                k_nm[i][j]=0;
            }
            else if(j>0)
            {
                k_nm[i][j]=((float)((j)*(j)-(i)*(i)))/((2*((float)j+1)-1)*(2*((float)j+1)-3));
            }

        }
    }
    //Coefficients P^n,m
    P_nm[0][0]=cos(theta)*P_00;
    P_nm[1][0]=sin(theta)*P_00;
    for (j=1;j<n;j++)
    {
        for(i=0;i<(j+2);i++)
        {
            if(i==(j+1))
            {
                P_nm[i][j] = sin(theta)*P_nm[j][j-1];
            }
            else
            {
                if (j<2)
                {
                    P_nm[i][j]=cos(theta)*P_nm[i][j-1];

                }
                else
                {
                    P_nm[i][j]=cos(theta)*P_nm[i][j-1]-k_nm[i][j]*P_nm[i][j-2];

                }
            }
        }
    }
    //Derivative of d_P^n,m
    d_P_nm[0][0]=cos(theta)*d_P_00-sin(theta)*P_00;
    d_P_nm[1][0]=sin(theta)*d_P_00+cos(theta)*P_00;

    for(j=1;j<n;j++)
    {
        for(i=0;i<(j+2);i++)
        {
            if (i==j+1)
            {
                d_P_nm[i][j] = sin(theta)*d_P_nm[j][j-1]+cos(theta)*P_nm[j][j-1];
            }
            else
            {
                if (j<2)
                {
                    d_P_nm[i][j]=cos(theta)*d_P_nm[i][j-1]-sin(theta)*P_nm[i][j-1];
                }
                else
                {
                    d_P_nm[i][j]=cos(theta)*d_P_nm[i][j-1]-sin(theta)*P_nm[i][j-1]-k_nm[i][j]*d_P_nm[i][j-2];
                }
            }
        }
    }
    //Gaussian Coefficients Normalization
    for(j=0;j<n;j++)
    {
        for(i=0;i<(j+2);i++)
        {
            g_nm[i][j]=S_nm[i][j]*g_irf[i][j];
            h_nm[i][j]=S_nm[i][j]*h_irf[i][j];
        }
    }


    for(i=0;i<n+1;i++)
    {
        for(j=0;j<n;j++)
        {
            A[i][j]=g_nm[i][j];
        }
    }

    for(i=0;i<n+1;i++)
    {
        for(j=0;j<n;j++)
        {
            A[i][j]=h_nm[i][j];
        }
    }
    //Magnetic Field Components - Spherical Coordinates

    float dx=0;
    float pr=0;
    float sx=0;
    //Radial component

    for (j=0;j<n;j++)
    {
        sx=(pow((Re/ab),(j+3))*(j+2));
        for (i=0;i<j+2;i++)
        {
            dx=dx+(g_nm[i][j]*cos((i)*phi)+h_nm[i][j]*sin((i)*phi))*P_nm[i][j];
            //dx=dx+((i+1)*(-g_nm[i][j]*sin((i)*phi)+h_nm[i][j]*cos((i)*phi))*P_nm[i][j]);
        }
        pr=pr+sx*dx;
        dx=0;
    }

    float B_r=pr;
    //Coelevation Component
    dx=0;
    pr=0;
    for (j=0;j<n;j++)
    {
        sx=pow((Re/ab),(j+3));
        for (i=0;i<j+2;i++)
        {
            dx=dx+(g_nm[i][j]*cos((i)*phi)+h_nm[i][j]*sin((i)*phi))*d_P_nm[i][j];
        }
        pr=pr+sx*dx;
        dx=0;
    }
    float B_th=-pr;
    dx=0;
    pr=0;
    //Azimuth component
    for(j=0;j<n;j++)
    {
        sx=pow((Re/ab),(j+3));
        for (i=0;i<j+2;i++)
        {
            dx=dx+((i+1)*(-g_nm[i][j]*sin((i)*phi)+h_nm[i][j]*cos((i)*phi))*P_nm[i][j]);
        }
        pr=pr+sx*dx;
        dx=0;
    }
    float B_phi=-1/sin(theta)*pr;
    //Magnetic Field Components-- IRF
    B_N.p[0]=((B_r*cos(delta)+B_th*sin(delta))*cos(alpha)-B_phi*sin(alpha))*10000;
    B_N.p[1]=((B_r*cos(delta)+B_th*sin(delta))*sin(alpha)+B_phi*cos(alpha))*10000;
    B_N.p[2]=((B_r*sin(delta)-B_th*cos(delta)))*10000;
    B_N.willFree=1;


/*    free(S_nm.p);
    free(P_nm.p);
    free(d_P_nm.p);
    free(k_nm.p);
    free(g_nm.p);
    free(h_nm.p);*/

    return B_N;


}
float kronDel(float j,float k)
{
    float d;
    if (j==k)
    {
        d=1;
    }
    else
    {
        d=0;
    }
    return d;
}



