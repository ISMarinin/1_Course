int sign(int a) {
    if (a > 0) {
        return 1;
    }
    else if (a < 0) {
        return -1;
    }
    else {
        return 0;
    }
}

int abs(int a) {
    if (a >= 0) {
        return a;
    }
    else {
        return -a;
    }
}

int min(int a, int b) {
    if (a <= b) {
        return a;
    }
    else {
        return b;
    }
}