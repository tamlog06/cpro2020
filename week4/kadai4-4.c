#define M 3
#define N 4

int a[M][N];

void input() {
    for (int i = 0; i < M; i++) {
        for (int j = 0; j < N; j++) {
            a[i][j] = 10 * i + j;
        }
    }
}

void display() {
    for (int i = 0; i < M; i++) {
        for (int j = 0; j < N; j++) {
            printf("%2d ", a[i][j]);
        }
        printf("\n");
    }
}

int main() {
    input();
    display();
    return 0;
}