/*
 * estimadores.c
 *
 *  Created on: 13 sep 2022
 *      Author: rober
 */

#include<stdio.h>
#include<stdlib.h>
#include<stdint.h>
#include<math.h>
#include"structs.h"
#include"matrix.h"
#include"vector.h"
#include"rotacion.h"
#include"estimadores.h"
extern int memoria;

MATRIZ TRIAD(VECTOR rs, VECTOR rm, VECTOR s,VECTOR m)
{
    float  o3_mod, r3_mod;
    int i;
    VECTOR o1=Vinit(3);
    o1.willFree=1;
    o1.p[0]=m.p[0];
    o1.p[1]=m.p[1];
    o1.p[2]=m.p[2];
    VECTOR o2;
    o2=Vcrz(m,s);
    o2=Vnorm(o2);
    o2.willFree=1;
    VECTOR o3;
    o3=Vcrz(m,s);
    o3.willFree=1;
    o3_mod=Vmod(o3);
    o3.willFree=0;
    o3=Vcrz(m,o3);
    o3.willFree=1;
    for (i=0;i<o3.dim;i++)
    {
        o3.p[i]=o3.p[i]/o3_mod;
    }

    VECTOR r1=Vinit(3);
    r1.willFree=1;
    r1.p[0]=rm.p[0];
    r1.p[1]=rm.p[1];
    r1.p[2]=rm.p[2];
    VECTOR r2;
    r2=Vcrz(rm,rs);
    r2=Vnorm(r2);
    r2.willFree=1;
    VECTOR r3;
    r3=Vcrz(rm,rs);
    r3.willFree=1;
    r3_mod=Vmod(r3);
    r3.willFree=0;
    r3=Vcrz(rm,r3);
    r3.willFree=1;
    for (i=0;i<r3.dim;i++)
    {
        r3.p[i]=r3.p[i]/r3_mod;
    }

    MATRIZ Mo=Minit(3,3);
    Mo.willFree=1;
    MATRIZ Mr=Minit(3,3);
    Mr.willFree=1;
    MATRIZ A;

    Mo.p[0][0]=o1.p[0];
    Mo.p[1][0]=o1.p[1];
    Mo.p[2][0]=o1.p[2];
    Mo.p[0][1]=o2.p[0];
    Mo.p[1][1]=o2.p[1];
    Mo.p[2][1]=o2.p[2];
    Mo.p[0][2]=o3.p[0];
    Mo.p[1][2]=o3.p[1];
    Mo.p[2][2]=o3.p[2];

    Mr.p[0][0]=r1.p[0];
    Mr.p[1][0]=r1.p[1];
    Mr.p[2][0]=r1.p[2];
    Mr.p[0][1]=r2.p[0];
    Mr.p[1][1]=r2.p[1];
    Mr.p[2][1]=r2.p[2];
    Mr.p[0][2]=r3.p[0];
    Mr.p[1][2]=r3.p[1];
    Mr.p[2][2]=r3.p[2];


    Mr.willFree=0;
    Mr=Mtrans(Mr);
    A=Mmul(Mo,Mr);
    A.willFree=1;

    //free(o1.p);
    memoria-=1;
    //free(o2.p);
    memoria-=1;
    //free(o3.p);
    memoria-=1;
    //free(r1.p);
    memoria-=1;
    //free(r2.p);
    memoria-=1;
    //free(r3.p);
    memoria-=1;
    //free(Mo.p);
    memoria-=1;
    //free(Mr.p);
    memoria-=1;

    return A;


}
float func(float fun[],int dim, float l0)
{
    float c=0;
    int i;
    for(i=0;i<dim;i++)
    {
        c=c+fun[i]*pow(l0,(dim-i-1));
    }
    return c;
}

float dfunc(float fun[],int dim,float l0)
{
    float fund[4];
    int i;
    for(i=0;i<dim;i++)
    {
        fund[i]=(dim-1-i)*fun[i];
    }

    return func(fund,dim-1,l0);


}

float NwtRhp(float fun[], int pres, int dim, float l0)
{
    float *p=(float*)malloc(pres*sizeof(float));
    *p=l0;
    int i=0;
    for (i=0;i<pres-1;i++)
    {
        *(p+1+i)=*(p+i)-func(fun,dim,*(p+i))/dfunc(fun,dim,*(p+i));
        l0=*(p+i+1);
    }
    l0=*(p+pres-1);
    free(p);
    return l0;

}

QUAT QUEST(VECTOR rmag, VECTOR rsol, VECTOR mag, VECTOR sol)
{

    float ra[4][4];
    int i ,j;
    float des[2]={1,1};//des mag, des sol
    float des2[2];
    des2[0]=((des[0]*des[0]*des[1]*des[1])/(des[0]*des[0]+des[1]*des[1]))/des[0];
    des2[1]=((des[0]*des[0]*des[1]*des[1])/(des[0]*des[0]+des[1]*des[1]))/des[1];
    MATRIZ B=Msum(Mmules(des2[0],Mmul(Mtrans(vec2m(mag)),vec2m(rmag))),Mmules(des2[1],Mmul(Mtrans(vec2m(sol)),vec2m(rsol))));
    B.willFree=1;
    MATRIZ S=Msum(B,Mtrans(B));
    S.willFree=1;
    MATRIZ Z=Minit(3,1);
    Z.p[0][0]=B.p[1][2]-B.p[2][1];
    Z.p[1][0]=B.p[2][0]-B.p[0][2];
    Z.p[2][0]=B.p[0][1]-B.p[1][0];
    Z.willFree=1;

    float sigma=Mtraza(B);
    MATRIZ I=Meye(3);
    I.willFree=1;
    MATRIZ K_A=Mres(S,Mmules(sigma,I));
    K_A.willFree=1;
    float *pk,k[4][4]={{K_A.p[0][0],K_A.p[0][1],K_A.p[0][2],Z.p[0][0]},{K_A.p[1][0],K_A.p[1][1],K_A.p[1][2],Z.p[1][0]},{K_A.p[2][0],K_A.p[2][1],K_A.p[2][2],Z.p[2][0]},{Z.p[0][0],Z.p[1][0],Z.p[2][0],sigma}};
    MATRIZ K=Minit(4,4);
    pk=k;
    K=Masign(K,pk);
    K.willFree=1;

    float a, b, c, d;

    a=sigma*sigma-Mtraza(Madj(S));

    b=sigma * sigma + Mtraza(Mmul(Mtrans(Z),Z));
    c=Mdet(S)+Mtraza(Mmul(Mtrans(Z),Mmul(S,Z)));
    d=Mtraza(Mmul(Mtrans(Z),Mmul(Mmul(S,S),Z)));

    float poly[5]={1, 0, -(a+b), -c, (a*b+c*sigma-d)};

    float lmax=NwtRhp(poly,8,5,des[0]+des[1]);
    MATRIZ q=Mmul(Minv(Mres(Mmules((lmax+sigma),I),S)),Z);
    q.willFree=1;
    VECTOR vq=Vinit(4);
    float *vqpp, vqp[4]={q.p[0][0],q.p[1][0],q.p[2][0],1};
    vqpp=vqp;
    vq=Vasign(vq,vqpp);
    //vq.dim=4;
    vq.willFree=1;

    QUAT qb=m2q(Mtrans(Mmules(1/(sqrt(1+Mtraza(Mmul(Mtrans(q),q)))),Mtrans(vec2m(vq)))));


    //free(B.p);
    memoria-=1;

    //free(S.p);
    memoria-=1;
    //free(Z.p);
    memoria-=1;
    //free(I.p);
    memoria-=1;
    //free(K_A.p);
    memoria-=1;
    //free(K.p);
    memoria-=1;
    //free(q.p);
    memoria-=1;
    //free(vq.p);
    memoria-=1;


    return qb;



}

VECTOR estSol(time_stat time)
{
    int a=2000+time.year;
    int m=time.month;
    int d=time.date;
    int h=time.hour+5;//Tiempo en UTC -6, horario de verano -5
    int min=time.minutes;
    int s=time.seconds;
    float dj=367*a-ent((7*(a+ent((m+9)/12))/4))+ent(275*m/9)+d+1721013.5+h/24+min/1440+s/86400;
    float Tutc=(dj-2451545)/36525;
    float LmSol=280.460684+36000.77005361*Tutc;
    float MSol=357.5277233+35999.05034*Tutc;
    float Leclip=LmSol+1.91466471*sind(MSol)+0.918994643*sind(2*MSol);
    float oblic=23.439291-0.013004*Tutc;
    //float *pc,c[3]={cosd(Leclip), cosd(oblic)*sind(Leclip), sind(oblic)*cosd(Leclip)};
    // pc=c;
    VECTOR sol=Vinit(3);
    sol.willFree=1;
    sol.p[0]=cosd(Leclip);
    sol.p[1]=cosd(oblic)*sind(Leclip);
    sol.p[2]=sind(oblic)*cosd(Leclip);
    return sol;

}


parOrb propOrb(parOrb para, float t, float t0)
{
    int i;
    parOrb paraN;
    float E=2*atand(tand(para.anomVerd/2)/sqrt((1+para.excent)/(1-para.excent)));
    float M1=E-para.excent*sind(E);

    float mu=398600;//constante de gravitacion[km^3/s^2]
    float R=6370;//radio de la tierra [km]
    float p=para.semiMayor*(1-(para.excent*para.excent));//[km]
    float n=sqrt(mu/(pow(para.semiMayor,3)));//[rad/s]

    float J2=0.00108263;

    paraN.semiMayor=para.semiMayor;
    paraN.excent=para.excent;
    paraN.incl=para.incl;
    paraN.ascDer=para.ascDer-((3/2)*(((R*R*sqrt(mu))/(pow((1-paraN.excent),2)*sqrt(pow(paraN.semiMayor,7))))*J2*cosd(paraN.incl))*(t-t0))*180/PI;
    paraN.periArg=para.periArg+(3/2)*((R*R*sqrt(mu))/(pow((1-paraN.excent),2)*sqrt(pow(paraN.semiMayor,7))))*J2*((5/2)*(((1/2)-(1/2)*cosd(2*paraN.incl)))-2)*(t-t0)*180/PI;
    float M1n=M1+(n+(3/4)*n*((R*R)/(p*p))*J2*sqrt(1-paraN.excent*paraN.excent)*(2-3*((1-cosd(2*paraN.incl))/2)))*(t-t0)*180/PI;

    float ET=E;
    for(i=0;i<5;i++)
    {
        ET=ET-(ET-paraN.excent*sind(ET)-M1n)/(1-paraN.excent*cosd(ET));//Obtiene la anomalía excentrica por medio de Newton Rhapson
    }

    paraN.anomVerd=2*atand(sqrt((1+paraN.excent)/(1-paraN.excent))*tand(ET/2));
    float pT=paraN.semiMayor*(1-paraN.excent*paraN.excent);

    float *ap0, p0[3]={p*cosd(para.anomVerd)/(1+para.excent*cosd(para.anomVerd)), p*sind(para.anomVerd)/(1+para.excent*cosd(para.anomVerd)),0};
    //float *ap, ps[3]={pT*cosd(paraN.anomVerd)/(1+paraN.excent*cosd(paraN.anomVerd)), pT*sind(paraN.anomVerd)/(1+paraN.excent*cosd(paraN.anomVerd)),0};

    ap0=p0;
    //ap=ps;

    VECTOR pos0=Vinit(3);
    Vasign(pos0,ap0);
    //VECTOR pos={ap,3,1};
    VECTOR pos=Vinit(3);
    pos.willFree=1;
    pos.p[0]=pT*cosd(paraN.anomVerd)/(1+paraN.excent*cosd(paraN.anomVerd));
    pos.p[1]=pT*sind(paraN.anomVerd)/(1+paraN.excent*cosd(paraN.anomVerd));
    pos.p[2]=0;


    MATRIZ rot0=Mmul(Mmul(ROT_Z(para.ascDer),ROT_X(para.incl)),ROT_Z(para.periArg));
    rot0.willFree=1;
    //MATRIZ rot=Mmul(Mmul(ROT_Z(paraN.ascDer),ROT_X(paraN.incl)),ROT_Z(paraN.periArg));
    MATRIZ rot=Mmul(Mmul(ROT_Z(paraN.periArg),ROT_X(paraN.incl)),ROT_Z(paraN.ascDer));
    rot.willFree=1;

    MATRIZ posS=Mmul(rot,Mtrans(vec2m(pos)));
    posS.willFree=1;

    paraN.pos[0][0]=posS.p[0][0];
    paraN.pos[1][0]=posS.p[1][0];
    paraN.pos[2][0]=posS.p[2][0];

    //obtener lat long alt.

    if(posS.p[2][0]>=0)
        paraN.lat=90-acosd(fabs(posS.p[2][0])/fabs(Vmod(m2vec(Mtrans(posS)))));
    else
        paraN.lat=-90+acosd(fabs(posS.p[2][0]))/fabs(Vmod(m2vec(Mtrans(posS))));

    if(posS.p[0][0]>=0)
        paraN.lng=atand(fabs(posS.p[1][0])/fabs(posS.p[0][0]));
    else
        paraN.lng=180-atand(fabs(posS.p[1][0])/fabs(posS.p[0][0]));

    if (posS.p[1][0]<0)
        paraN.lng=-paraN.lng;

    paraN.alt=Vmod(m2vec(Mtrans(posS)));

    //free(pos0.p);
    //free(pos.p);
    memoria-=1;
    //free(rot0.p);
    memoria-=1;
    //free(rot.p);
    memoria-=1;
    //free(posS.p);
    memoria-=1;

    return paraN;
}



