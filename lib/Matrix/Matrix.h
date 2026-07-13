template<typename T, int R, int C>
struct Matrix {
    T data[R][C];

    // constexpr int rows = R;
    // constexpr int cols = C;

    template<int K>
    Matrix<T, R, K> operator*(const Matrix<T, C, K>& other) const {
        Matrix<T, R, K> result{};

        for (int i = 0; i < R; i++) {
            for (int j = 0; j < K; j++) {
                result.data[i][j] = 0;

                for (int k = 0; k < C; k++) {
                    result.data[i][j] += data[i][k] * other.data[k][j];
                }
            }
        }

        return result;
    }
};