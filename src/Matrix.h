class Matrix {
    public:
    Matrix();
    double matrixArray[4][4] {0};

    void buildScale(double sx, double sy, double sz);
    void buildReflexion(double sx, double sy, double sz);
    void buildRotation(double angle);
    void buildTranslation(double x, double y, double z);
    void buildDiagonal(double x, double y, double z);
};