#include <stdio.h>

int main(int argc, char **argv) {
    if (argc != 3) {
        printf("A programnak kell 1 bemenet es 1 kimenet!");
        return -1;
    }

    typedef enum LyAllapot {
        alap,
        l_volt,
        ll_volt,
        pont_volt,
        L_volt,
        Ll_volt
    } LyAllapot;

    LyAllapot all;
    int szaml, c;

    FILE *bemenet;
    FILE *kimenet;
    bemenet = fopen(argv[1], "r");
    if (bemenet == NULL) {
        printf("Nem sikerult megnyitni a bemenetet!");
        return -1;
    }
    kimenet = fopen(argv[2], "w");
    if (kimenet == NULL) {
        printf("Nem sikerult megnyitni a kimenetet!");
        return -1;
    }

    szaml = 0;
    all = alap;
    while ((c = fgetc(bemenet)) != EOF) {
        switch (all) {
            case alap:
                if (c == '.') {
                    putchar('.');
                    fputc('.', kimenet);
                    all = pont_volt;
                } else {
                    if (c == 'l') {
                        all = l_volt;
                    } else {
                        putchar(c);
                        fputc(c, kimenet);
                    }
                }
                break;

            case l_volt:
                switch (c) {
                    case 'l':
                        all = ll_volt;
                        break;
                    case 'y':
                        szaml += 1;
                        putchar('j');
                        fputc('j', kimenet);
                        all = alap;
                        break;
                    case '.':
                        putchar('l');
                        putchar('.');
                        fputc('l', kimenet);
                        fputc('.', kimenet);
                        all = pont_volt;
                        break;
                    default:
                        putchar('l');
                        putchar(c);
                        fputc('l', kimenet);
                        fputc(c, kimenet);
                        all = alap;
                        break;
                }
                break;

            case ll_volt:
                switch (c) {
                    case 'l':
                        putchar('l');
                        fputc('l', kimenet);
                        break;
                    case 'y':
                        szaml += 2;
                        putchar('j');
                        putchar('j');
                        fputc('j', kimenet);
                        fputc('j', kimenet);
                        all = alap;
                        break;
                    case '.':
                        putchar('l');
                        putchar('l');
                        putchar('.');
                        fputc('l', kimenet);
                        fputc('l', kimenet);
                        fputc('.', kimenet);
                        all = pont_volt;
                        break;
                    default:
                        putchar('l');
                        putchar('l');
                        putchar(c);
                        fputc('l', kimenet);
                        fputc('l', kimenet);
                        fputc(c, kimenet);
                        all = alap;
                        break;
                }
                break;
            case pont_volt:
                if(c == '.'){
                    putchar('.');
                    fputc('.', kimenet);
                    break;
                }
                if (c == 'L') {
                    all = L_volt;
                } else {
                    putchar(c);
                    fputc(c, kimenet);
                    all = alap;
                }
                break;

            case L_volt:
                switch (c) {
                    case 'l':
                        all = Ll_volt;
                        break;
                    case 'y':
                        szaml += 1;
                        putchar('J');
                        fputc('J', kimenet);
                        all = alap;
                        break;
                    case '.':
                        putchar('L');
                        putchar('.');
                        fputc('L', kimenet);
                        fputc('.', kimenet);
                        all = pont_volt;
                        break;
                    default:
                        putchar('L');
                        putchar(c);
                        fputc('L', kimenet);
                        fputc(c, kimenet);
                        all = alap;
                        break;
                }
                break;

            case Ll_volt:
                switch (c) {
                    case 'l':
                        putchar('L');
                        fputc('L', kimenet);
                        all = ll_volt;
                        break;
                    case 'y':
                        szaml += 2;
                        putchar('J');
                        putchar('j');
                        fputc('J', kimenet);
                        fputc('j', kimenet);
                        all = alap;
                        break;
                    case '.':
                        putchar('L');
                        putchar('l');
                        putchar('.');
                        fputc('L', kimenet);
                        fputc('l', kimenet);
                        fputc('.', kimenet);
                        all = pont_volt;
                        break;
                    default:
                        putchar('L');
                        putchar('l');
                        putchar(c);
                        fputc('L', kimenet);
                        fputc('l', kimenet);
                        fputc(c, kimenet);
                        all = alap;
                        break;
                }
                break;
        }
    }

    printf("\n%d darab volt.\n", szaml);

    fclose(bemenet);
    fclose(kimenet);

    return 0;
}