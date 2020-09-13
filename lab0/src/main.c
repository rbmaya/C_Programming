#include <stdio.h>
#include <string.h>

static char int_to_char(int temp) {
    if ((temp >= 0) && (temp <= 9)) {
        return temp + '0';
    } else if ((temp >= 10) && (temp <= 16)) {
        return temp + 'a' - 10;
    } else {
        return 0;
    }
}

static int char_to_int(char temp) {
    if ((temp >= '0') && (temp <= '9')){
        return temp - '0';
    } else if ((temp >= 'a') && (temp <= 'f')) {
        return temp - 'a' + 10;
    } if ((temp >= 'A') && (temp <= 'F')) {
        return temp - 'A' + 10;
    } else {
        return -1;
    }
}


int main() {
    const float eps = 0.000000000001;
    int b1 = 0;
    int b2 = 0;
    int i = 0;
    int position_of_point = 0;
    int length = 0;
    long long temp = 0;
    long long int_num_in_10 = 0;
    double float_num_in_10 = 0;
    char number_in_b1[14] = {0};
    char int_part_num[50] = {0};
    char float_part_num[50] = {0};

    scanf("%d%d", &b1, &b2);

    if ((b1 < 2) || (b1 > 16) || (b2 < 2) || (b2 > 16)) {
        printf("bad input");
        return 0;
    }

    scanf("%s", number_in_b1);

    length = strlen(number_in_b1);
    for (i = 0; i < length; ++i) {
        if ((((number_in_b1[i] >= '0') && (number_in_b1[i] <= '9')) ||
             ((number_in_b1[i] >= 'a') && (number_in_b1[i] <= 'f')) ||
             ((number_in_b1[i] >= 'A') && (number_in_b1[i] <= 'F'))) &&
            (number_in_b1[i] < int_to_char(b1)) ||
            (number_in_b1[i] == '.')) {
            if (number_in_b1[i] == '.') {
                if (position_of_point != 0) {
                    printf("bad input");
                    return 0;
                }
                position_of_point = i;
                if ((i == 0) || (i == length - 1)) {
                    printf("bad input");
                    return 0;
                }
                continue;
            }
            if (position_of_point == 0){
                int_part_num[i] = number_in_b1[i];
            } else {
                float_part_num[i - position_of_point - 1] = number_in_b1[i];
            }
        } else {
            printf("bad input");
            return 0;
        }
    }

    length = strlen(int_part_num);
    temp = 1;
    for (i = length - 1; i >= 0; --i) {
        int_num_in_10 += char_to_int(int_part_num[i]) * temp;
        int_part_num[i] = 0;
        temp *= b1;
    }


    temp = b1;
    if (position_of_point != 0) {
        length = strlen(float_part_num);
        for (i = 0; i < length; ++i) {
            float_num_in_10 += (float)char_to_int(float_part_num[i]) / temp;
            float_part_num[i] = 0;
            temp *= b1;
        }
    }

    i = 0;
    while (int_num_in_10 >= b2) {
        int_part_num[i] = int_to_char(int_num_in_10 % b2);
        int_num_in_10 /= b2;
        ++i;
    }
    int_part_num[i] = int_to_char(int_num_in_10);

    i = 0;
    while ((float_num_in_10 - eps > 0) && (i < 12)) {
        float_num_in_10 = float_num_in_10 * b2;
        float_part_num[i] = int_to_char(float_num_in_10);
        float_num_in_10 -= (int)float_num_in_10;
        ++i;
    }

    for (i = strlen(int_part_num) - 1; i >= 0; --i) {
        printf("%c", int_part_num[i]);
    }

    if (position_of_point != 0){
        printf(".%s", float_part_num);
    }

    return 0;
}
