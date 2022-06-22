struct datframe {
    unsigned long long millis;
    float framerate;
    double xx;
    double yx;
    double zx;
};

char *astrcat(char *a, char *b);

char *dattoa(struct datframe *dat);

char *datlltoa(struct ll_list *ll);