#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#define OK 0
#define ERR_INPUT -1
#define ERR_TOO_LARGE -2
#define ERR_DIV_ZERO -3
#define ERR_WRONG_E -4


struct number
{
   int mant1[30];//Мантисса вещественного числа
   int minind;//Индикатор того, отрицательное ли число
   int mineind;//Индикатор того, отрицательная ли степень E
   int ie;//порядок числа
};

struct result
{
    int mant[60];//Мантисса вещественного числа
    int minind;//Индикатор того, отрицательное ли число
    int mineind;//Индикатор того, отрицательная ли степень E
    int rese;//порядок числа
};

//Вывод массива
int masout(int altmas[], int altmaslen, int e1, int e2, int addtoe, int newe, int minind1, int minind2)
{
    int flag = 0, sch = 0, resmas[62];
    int rese = 0;
    for (int i = 0; i < 35; i++)
    {
        if (altmas[i] != 0 || flag == 1)
        {
            flag = 1;
            resmas[sch] = altmas[i];
            sch++;
        }
    }
    //printf("\ne1 is %d e2 is %d\n", e1, e2);
    //округление чисел при 31 числе >=5
    if (resmas[30] >= 5)
    {
        resmas[29] += 1;
        for (int j = 29; j > 0; j--)
        {
            if (resmas[j] == 10)
            {
                resmas[j] = 0;
                resmas[j -1] += 1;
            }
        }
    }
    else
    {
        if (sch == 31)
            sch--;
    }
    sch = 30;
    //цикл для ограничения ввода незначащих нулей
    for (int i = 29; i > 0; i--)
    {
        //printf("resmas %d", resmas[i]);
        if (resmas[i] == 0)
            sch = i;
        else
            break;
    }
    //printf("newe %d %d addtoe virazhenie %d\n", newe, addtoe, e1 - e2 - newe - addtoe);
    //Нахождение степени E
    if (e1 - e2 - newe - addtoe > 1 || e1 - e2 - newe - addtoe < -1)
    {
        if (sch == 1 && resmas[0] == 1)
            rese = e1 - e2 + 1;
        else
            rese = e1 - e2;
    }
    else
    {
        if (e1 <= 0 || e2 <= 0)
            if (e2 <= 0)
                rese = e1 - e2;
            else
                rese = e1 - e2 + 1;
        else
            rese = newe + addtoe;
    }
    //Проверка на то, что степень E меньше 5 разрядов
    if (rese > 99999 || rese < -99999)
    {
        printf("Res E is too big or too small");
        return ERR_WRONG_E;
    }
    //Вывод результата
    printf("\n-----------------------------------------------\n");
    puts("\nThe result of division is: ");
    if ((minind1 == 1 && minind2 == 1) || (minind1 == 0 && minind2 == 0))
        printf("+");
    else
        printf("-");
    printf("0.");
    for (int i = 0; i < sch; i++)
    {
        printf("%d", resmas[i]);
    }
    printf("E");
    printf("%d", rese);
    puts("\n   |   |    |    |    |    |    |");
    puts("   123451234512345123451234512345");
    return OK;
}

//Нахождение делителя для конкретной части числа
int newnum(char mant1[], char mant2[], int mantlen2, int mantlen1, int curpos1, int altmas[], int *altmaslen, int *lm, int *prevpos, int *addtoe, int resmantlen1)
{
    int divok = 1;
    int counter = 0;
    int flag = 0, flag1 = 0, flag2 = 0;
    char reserv;
    //int prevlm = 0;
    while (divok == 1)
    {
        //puts("MMMM");
        //prevlm = *lm;
        *lm = 0;
        flag2 = 0;
        if (mantlen1 == 0)
        {
            divok = -1;
            break;
        }
        //printf("\nmantlen1 %d\n", mantlen1);
        /*
        puts("\nALTMAS:");
        for (int i = 0; i < *altmaslen; i++)
        {
            printf("%d", altmas[i]);
        }
        puts("\nMas is:");
        for (int i = 0; i < mantlen1; i++)
        {
            printf("%d", mant1[i] - '0');
        }
        */
        //printf("\ncurpos %d i prevpos %d i mantlen2 %d\n", curpos1, *prevpos, mantlen2);
        // eto ne trogat''
        for (int j = 0; j < curpos1; j++)
        {
            if (mant1[j] != '0' || flag2 == 1)
            {
                (*lm)++;
                flag2 = 1;
            }
        }
        //printf("\nLm %d prevlm %d\n", *lm, prevlm);
        //printf("\nresmantlen %d\n", resmantlen1);
        /*
        if (*lm - prevlm > 1 && resmantlen1 >= curpos1)
        {
            if (curpos1 - *lm != 0)
            {            
                for (int r = 1; r < *lm - prevlm; r++)
                {
                    printf("\n\nOAOAOmm\n");
                    altmas[*altmaslen] = 0;
                    (*altmaslen)++;
                    (*addtoe)++;
                }
            }
        }
        */
        if (*lm == mantlen2)
        {
            for (int k = curpos1 - mantlen2, d = 0; d < mantlen2; d++, k++)
            {
                //printf("\nmant1[k] %c mant2[d] %c uf e\n", mant1[k],mant2[d]);
                if (mant1[k] > mant2[d])
                    break;
                if(mant1[k] < mant2[d])
                {
                    flag1 = 1;
                    break;
                }

            }
        }
        else if (*lm < mantlen2)
        {

            if (curpos1 == mantlen1)
                divok = -1;
            break;
        }
        //printf("\nFLAG1 %d\n", flag1);
        if (flag1 == 1)
        {
            break;
        }
        else
        {
            for (int i = curpos1 - 1, j = mantlen2 - 1; j >= 0; i--, j--)
            {
                //printf("\n mant1[i] %d mant2[j] %d\n", mant1[i] - '0', mant2[j] - '0');
                if (mant1[i] - '0' < mant2[j] - '0')
                {
                    reserv = mant1[i] + 1;
                    for(int k = i - 1; k >= 0; k--)
                    {
                        if (mant1[k] - '0' != 0)
                        {
                            //printf("\n mant1[k] %d\n", mant1[k] - '0');
                            mant1[k] -= 1;
                            for(int l = k + 1; l <= i; l++)
                            {
                                mant1[l] = '9';
                                //printf("\nmant1l %c\n", mant1[l - 1] - 1);
                            }
                            flag = 1;
                            break;
                        }
                    }
                    //printf("\nmant1iii %c\n", mant1[i] - mant2[j]);
                    mant1[i] -= mant2[j] - reserv;
                    if (flag == 0)
                    {
                        divok = -1;
                        break;
                    }
                }
                else
                {
                    if (mant1[i] == 0)
                    {
                        divok = -1;
                        break;
                    }
                    else
                    {
                        mant1[i] -= mant2[j] - '0';
                        //printf("\nmant1[i] %c mant2[j] %c\n", mant1[i], mant2[j]);
                    }
                }
            }
            flag = 0;
            if (divok != -1)
                counter += 1;
        }
    }
    *prevpos = curpos1;
    altmas[*altmaslen] = counter;
    (*altmaslen)++;
    //printf("\n\n%d counter now\n\n", counter);
    /*
    puts("\nALTMAS:");
    for (int i = 0; i < *altmaslen; i++)
    {
        printf("%d ", altmas[i]);
    }
    */
    return divok;
}

//Выделение новых отрезков от делителя для последущего нахождения делителя
int division(char mant1[], char mant2[], int ie1, int ie2, int mantlen2, int mantlen1, int resmantlen1, int minind1, int minind2)
{
    int curpos1 = 0;
    int flag = 0;
    int altmas[62] = {0};
    int altmaslen = 0;
    int prevpos = 0;
    int lm = 0;
    int count = 0;
    int newe;
    int flag1 = 0, flag2 = 0;
    int addtoe = 0;
    if (resmantlen1 == 0)
    {
        printf("The result of division is: 0");
        return OK;
    }
    while (1)
    {
        flag = 0;
        count = 0;
        flag2 = 0;
        for (int u = curpos1; u < resmantlen1; u++)
        {
            if (mant1[u] == '0')
            {
                count++;
            }
            else
            {
                flag2 = 1;
                break;
            }
        }
        if (flag2 == 0)
        {
            if (curpos1 == mantlen1)
                break;
            for (int u = 0; u < count; u++)
            {
                addtoe++;
            }         
        }
        for (int j = 0, k = curpos1; j < mantlen2; j++, k++)
        {
            //printf("\nmant1[k] %c i mant2[j] %c\n", mant1[k],mant2[j]);
            if (mant1[k] > mant2[j] && flag == 0)
            {
                curpos1 += mantlen2;
                flag = 1;
                break;
            }
            else if(mant1[k] == mant2[j])
            {
                if (j == mantlen2 - 1 && k + 1 != mantlen1)
                {
                    curpos1 += mantlen2;
                }
                if(k + 1 == mantlen1)
                    curpos1 = mantlen1;
                continue;
            }
            else
            {
                //printf("needed LM %d", lm);
                curpos1 += mantlen2 + 1;
                if (lm + 1 < mantlen2 && prevpos != 0 && curpos1 <= resmantlen1)
                {
                    //puts("ASHASH");
                    //printf("\nashash lm %d mantlen2 %d curpos1 %d prevlm %d\n", lm + 1, mantlen2, curpos1, prevpos);
                    //altmas[altmaslen] = 0;
                    //altmaslen++;
                    //addtoe++;
                }
                if(curpos1 > mantlen1)
                    flag1 = 1;
                break;
            }
        }
        if (flag1 == 1)
            break;
        //printf("\ncurpos1 %d i lm %d i prevpos %d\n", curpos1, lm,prevpos);
        if ((lm + 1 < mantlen2 || curpos1 - prevpos > 1) && prevpos != 0)
        {
            for(int i = 0; i <= mantlen2 - lm - 1; i++)
            {
                altmas[altmaslen] = 0;
                altmaslen++;
                if (curpos1 <= resmantlen1)
                    addtoe++;
            }
        }
        if (newnum(mant1, mant2, mantlen2, mantlen1, curpos1, altmas, &altmaslen, &lm, &prevpos, &addtoe, resmantlen1) == -1)
        {
            break;
        }
        else
        {
            if (curpos1 <= resmantlen1)
                newe++;
        }
        curpos1 -= lm;
        //printf("\nlast curpos %d\n", curpos1);
        /*
        for (int i = 0; i < altmaslen; i++)
        {
            printf("altmas %d ", altmas[i]);
        }
        */
    }
    /*
    puts("\nRESALTMAS:");
    for (int i = 0; i < altmaslen; i++)
    {
        printf("%d ", altmas[i]);
    }
    puts("\nRESMas is:");
    for (int i = 0; i < mantlen1; i++)
    {
        printf("%d ", mant1[i] - '0');
    }
    */
    //printf("%d addtoe", addtoe);
    masout(altmas, altmaslen, ie1, ie2, addtoe, newe, minind1, minind2);
    return OK;
}

//Ввод двух вещественных чисел
int masinp()
{
    char num1[38] = {0}, num2[38] = {0};
    char bd1[31] = {0}, ad1[31] = {0}, e1[6] = {0};
    int flag = 0;
    int minind1 = 0, minind2 = 0, plind1 = 0, plind2 = 0;
    int mineind1 = 0, mineind2 = 0;
    int count1 = 0, count2 = 0, count3 = 0;
    int dotskip = 0;
    int mantlen1, mantlen2,resmantlen1;
    puts("Format of input first and second number is:");
    puts("(+-)m.nE(+-)K, where (m + n) <= 30 and K <= 5");
    puts("E is optional");
    printf("-----------------------------------------------\n");
    puts("Enter first num ");
    puts("123451234512345123451234512345|| Last two lines is for the +/- and/or dot were placed");
    puts("|   |    |    |    |    |    |||");
    scanf("%s", num1);
    if (strlen(num1) > 37)
    {
        printf("Incorrect input");
        return ERR_INPUT;
    }
    if (num1[0] == '-')
        minind1 = 1;
    if (num1[0] == '+')
        plind1 = 1;
    for (int i = 0 + minind1 + plind1; i < strlen(num1); i++)
    {
        if (num1[i] != '.' && num1[i] != 'E' && flag == 0)
        {
            if (num1[i] == '0' && i == 0 && num1[i+1] != '.' && strlen(num1) != 1 && num1[i + 1] != 'E')
            {
                printf("Incorrect input");
                return ERR_INPUT;
            }
            else
            {
                if ('0' <= num1[i] && num1[i] <= '9')
                {
                    bd1[count1] = (int) num1[i];
                    count1++;
                }
                else
                {
                    printf("Incorrect input");
                    return ERR_INPUT;
                }
            }
        }
        else
        {
            flag = 1;
            if (num1[i] != 'E' && num1[i] != '.')
            {
                if ('0' <= num1[i] && num1[i] <= '9')
                {
                    ad1[count2] = (int) num1[i];
                    count2++;
                }
                else
                {
                    printf("Incorrect input");
                    return ERR_INPUT;
                }
            }
            else
            {
                dotskip += 1;
                if (num1[i] == '.' && dotskip > 1)
                {
                    printf("incorrect input");
                    return ERR_INPUT;
                }
                if (num1[i] == 'E')
                {
                    if (num1[i + 1] == '-')
                        mineind1 = 1;
                    for (int j = i + 1 + mineind1;j < strlen(num1);j++)
                    {
                        if ('0' <= num1[j] && num1[j] <= '9')
                        {
                            e1[count3] = (int) num1[j];
                            count3++;
                        }
                        else
                        {
                            printf("Incorrect input");
                            return ERR_INPUT;
                        }
                    }
                    break;
                }
            }
        }
    }
    //printf("strlen bd1ad1 %I64u %I64u\n\n", strlen(bd1), strlen(ad1));
    if (strlen(bd1) + strlen(ad1) == 0)
    {
        printf("Incorrect input");
        return ERR_INPUT;
    }
    if (strlen(bd1) + strlen(ad1) > 30 || strlen(e1) > 5)
    {
        printf("too big num");
        return ERR_TOO_LARGE;
    }
    int ie1 = atoi(e1);
    int movee1 = 0;
    char mant1[88] = {0};
    if (mineind1 == 1)
        ie1 *= -1;
    if (strlen(bd1) == 1 && bd1[0] == '0')
    {
        for (int i = 0; ad1[i] == '0' ; i++)
            movee1 += 1;
        for (int j = movee1, k = 0; j < strlen(ad1); j++, k++)
            mant1[k] = ad1[j];
        ie1 -= movee1;
    }
    else
    {
        strcat(mant1, bd1);
        strcat(mant1, ad1);
        ie1 += strlen(bd1);
    }
    fflush(stdin);
    puts("Enter second num ");
    puts("123451234512345123451234512345|| Last two lines is for the +/- and/or dot were placed");
    puts("|   |    |    |    |    |    |||");
    scanf("%s", num2);
    if (strlen(num2) > 37)
    {
        printf("Incorrect input");
        return ERR_INPUT;
    }
    char bd2[31] = {0}, ad2[31] = {0}, e2[6] = {0};
    flag = 0;
    count1 = 0, count2 = 0,count3 = 0;
    dotskip = 0;
    if (num2[0] == '-')
        minind2 = 1;
    if (num2[0] == '+')
        plind2 = 1;
    for (int i = 0 + minind2 + plind2; i < strlen(num2); i++)
    {
        if (num2[i] != '.' && num2[i] != 'E' && flag == 0)
        {
            if (num2[i] == '0' && i == 0 && num2[i+1] != '.' && strlen(num2) != 1  && num2[i + 1] != 'E')
            {
                printf("Incorrect input");
                return ERR_INPUT;
            }
            else
            {
                if ('0' <= num2[i] && num2[i] <= '9')
                {
                    bd2[count1] = (int) num2[i];
                    count1++;
                }
                else
                {
                    printf("Incorrect input");
                    return ERR_INPUT;
                }
            }
        }
        else
        {
            flag = 1;
            if (num2[i] != 'E' && num2[i] != '.')
            {
                if ('0' <= num2[i] && num2[i] <= '9')
                {
                    ad2[count2] = (int) num2[i];
                    count2++;
                }
                else
                {
                    printf("Incorrect input");
                    return ERR_INPUT;
                }
            }
            else
            {
                dotskip += 1;
                if (num2[i] == '.' && dotskip > 1)
                {
                    printf("Incorrect input");
                    return ERR_INPUT;
                }
                if (num2[i] == 'E')
                {
                    if (num2[i + 1] == '-')
                        mineind2 = 1;
                    for (int j = i + 1 + mineind2; j < strlen(num2); j++)
                    {
                        if ('0' <= num2[j] && num2[j] <= '9')
                        {
                            e2[count3] = (int) num2[j];
                            count3++;
                        }
                        else
                        {
                            printf("Incorrect input");
                            return ERR_INPUT;
                        }
                    }
                    break;
                }
            }
        }
    }
    //to delete
    //printf("\n\n\n ee indeces%d %d\n\n",mineind1, mineind2);
    if (strlen(bd2) + strlen(ad2) == 0)
    {
        printf("Incorrect input");
        return ERR_INPUT;
    }
    if (strlen(bd2) + strlen(ad2) > 30 || strlen(e2) > 5)
    {
        printf("too big num");
        return ERR_TOO_LARGE;
    }
    int ie2 = atoi(e2);
    int movee2 = 0;
    char mant2[31] = {0};
    if (mineind2 == 1)
        ie2 *= -1;
    if (strlen(bd2) == 1 && bd2[0] == '0')
    {
        for (int i = 0; ad2[i] == '0' ; i++)
            movee2 += 1;
        for (int j = movee2, k = 0; j < strlen(ad2); j++, k++)
        {
            //printf("%d atoi\n",ad2[j]);
            mant2[k] = ad2[j];
        }
        ie2 -= movee2;
    }
    else
    {
        strcat(mant2, bd2);
        strcat(mant2, ad2);
        ie2 += strlen(bd2);
    }
    mantlen2 = strlen(mant2);
    mantlen1 = strlen(mant1);
    if (mantlen2 == 0)
    {
        printf("division by zero");
        return ERR_DIV_ZERO;
    }
    //printf("mantlen1 mantlen2     %d %d\n", mantlen1, mantlen2);
    resmantlen1 = mantlen1;
    for (int j = mantlen1; j < mantlen1 + 31; j++)
    {
        mant1[j] = '0';
    }
    mantlen1 += 31;
    division(mant1, mant2, ie1, ie2, mantlen2, mantlen1, resmantlen1, minind1, minind2);
    /*
    printf("\n\n\n\n\n\n\n");
    printf("\n\n mant1 %s\npok step %d\n",mant2,ie2);
    printf("\n\n\n%d", ie2);
    printf("%d\n%d\n%d", atoi(bd1), atoi(ad1), atoi(e1));
    printf("%d\n%d\n%d", atoi(bd2), atoi(ad2), atoi(e2));
    printf("\n%d %d\n",minind1,minind2);
    */
    return OK;
}

int main()
{
    printf("This program divides real number on real number\n");
    printf("-----------------------------------------------\n");
    masinp();
    return OK;
}
