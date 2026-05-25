#include <stdio.h>

int main()
{
    int wood=0;
    int brick =0;
    int wool = 0;
    int grain =0;
    int ore=0;
    char line[64];

    while(scanf("%s",line)==1) {
        if(line[0]=='r' &&line[1]=='o' && line[2] == 'a' && line[3] == 'd' && line[4]=='\0') {
            wood++;
            brick++;
        } else if(line[0] == 's' && line[1] =='e' && line[2] == 't' && line[3] =='t' && line[4] =='l' &&line[5] == 'e' &&
             line[6]=='m' && line[7] == 'e' && line[8] == 'n' && line[9] == 't' && line[10]=='\0') {
            wood++;
            brick++;
            wool++;
            grain++;
        } else if(line[0]=='c' &&line[1]=='i' && line[2] == 't' && line[3] == 'y' && line[4]=='\0') {
            grain+=2;
            ore+=3;
        } else if(line[0] == 'd' && line[1] =='e' && line[2] == 'v' && line[3] =='e' && line[4] =='l' && line[5] == 'o' &&
             line[6] == 'p' && line[7]=='m' && line[8] == 'e' && line[9] == 'n' && line[10] == 't' && line[11]=='\0') {
            grain++;
            ore++;
            wool++;
        }
    }
    printf("%02d %02d %02d %02d %02d\n", wood, brick, wool, grain, ore);
}