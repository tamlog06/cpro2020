#include "nn.h"
#include "MT.h"
// 下記のサイトからMT.hをダウンロード．一様乱数を生成する際に用いる
// https://omitakahiro.github.io/random/random_variables_generation.html#Prepare_MT

// m×n型の行列xを表示
void print(int m, int n, const float *x)
{
    for (int count = 0; count < m * n; count++)
    {
        if (count % n == 0 && count != 0)
        {
            printf("\n");
        }
        printf("%.4f ", x[count]);
    }
}

// 要素数nのxをシャッフル
void shuffle(int n, int *x)
{
    int vmin = 0;
    int vmax = n - 1;
    double vrange = vmax - vmin + 1;

    for (int i = 0; i < n; i++)
    {
        int temp = x[i];
        int j = vmin + (int)(rand() * vrange / (1.0 + RAND_MAX));
        x[i] = x[j];
        x[j] = temp;
    }
}

// 要素数nの行列xの各要素の値を行列oの各要素に足す
void add(int n, const float *x, float *o)
{
    for (int i = 0; i < n; i++)
    {
        o[i] += x[i];
    }
}

// 要素数nの行列oの各要素にxをかける
void scale(int n, float x, float *o)
{
    for (int i = 0; i < n; i++)
    {
        o[i] *= x;
    }
}

// 要素数nの行列oの各要素の値をxで初期化
void init(int n, float x, float *o)
{
    for (int i = 0; i < n; i++)
    {
        o[i] = x;
    }
}

// [-1:1]の範囲で要素数nの行列oをランダムに初期化
void rand_init(int n, float *o)
{
    int vmin = -1;
    int vmax = 1;
    double vrange = vmax - vmin;

    for (int i = 0; i < n; i++)
    {
        o[i] = vmin + (float)(rand() * vrange / (1.0 + RAND_MAX));
    }
}

// 一様乱数を生成
float Uniform(void)
{
    // MT.hをダウンロードしていない場合はこちらで生成する
    // return rand() / (RAND_MAX + 1.0);
    return genrand_real3();
}

// n行ベクトルをガウス分布で初期化．muは平均，sigmaは分散
void Gaussian_init(int n, float *o, float mu, float sigma)
{
    int i;
    for (i = 0; i < n; i++)
    {
        float z = sqrt(-2.0 * log(Uniform())) * sin(2.0 * M_PI * Uniform());
        o[i] = mu + sigma * z;
    }
}

// m×n行列A,m次元ベクトルbの値をfilenameに保存する
void save(const char *filename, int m, int n, const float *A, const float *b)
{
    FILE *fp;
    fp = fopen(filename, "wb");
    fwrite(A, sizeof(float), m * n, fp);
    fwrite(b, sizeof(float), m, fp);
    fclose(fp);
}

// m×n行列A,m次元ベクトルbをfilenameから読み込む
void load(const char *filename, int m, int n, float *A, float *b)
{
    FILE *fp;
    fp = fopen(filename, "rb");
    fread(A, sizeof(float), m * n, fp);
    fread(b, sizeof(float), m, fp);
    fclose(fp);
}

// FC層．n次元ベクトルx，m×n行列A，m次元ベクトルb，m次元ベクトルy
void fc(int m, int n, const float *x, const float *A, const float *b, float *y)
{
    for (int k = 0; k < m; k++)
    {
        float sum = 0;
        sum += b[k];
        for (int i = 0; i < n; i++)
        {
            sum += (A[k * n + i] * x[i]);
        }
        y[k] = sum;
    }
}

// Relu関数．n次元ベクトルのxとy
void relu(int n, const float *x, float *y)
{
    for (int k = 0; k < n; k++)
    {
        if (x[k] > 0)
        {
            y[k] = x[k];
        }
        else
        {
            y[k] = 0;
        }
    }
}

// softmax層．n次元ベクトルのxとy
void softmax(int n, const float *x, float *y)
{
    float xmax = 0;
    for (int i = 0; i < n; i++)
    {
        if (x[i] > xmax)
        {
            xmax = x[i];
        }
    }
    // 念のため，0除算回避でsumを1e-7にしておく
    float sum = 1e-7;
    for (int i = 0; i < n; i++)
    {
        sum += exp(x[i] - xmax);
    }

    for (int k = 0; k < n; k++)
    {
        y[k] = exp(x[k] - xmax) / sum;
    }
}

// 損失関数の値を返す
float cross_entropy_error(const float *y, int t)
{
    return (-1) * log(y[t] + 1e-7);
}

// softmax逆伝播
void softmaxwithloss_bwd(int m, const float *y, unsigned char t, float *dEdx)
{
    /* t がone-hot表現でないから直す */
    float ans[10] = {0.0};
    for (int i = 0; i < 10; i++)
    {
        if (i == t)
        {
            ans[i] = 1.0;
        }
    }

    for (int k = 0; k < m; k++)
    {
        dEdx[k] = y[k] - ans[k];
    }
}

// relu逆伝播．
void relu_bwd(int m, const float *x, const float *dEdy, float *dEdx)
{
    for (int k = 0; k < m; k++)
    {
        if (x[k] > 0)
        {
            dEdx[k] = dEdy[k];
        }
        else
        {
            dEdx[k] = 0;
        }
    }
}

// fc逆伝播．
void fc_bwd(int m, int n, const float *x, const float *dEdy, const float *A, float *dEdA, float *dEdb, float *dEdx)
{
    /* dEdA */
    for (int k = 0; k < m; k++)
    {
        for (int i = 0; i < n; i++)
        {
            dEdA[k * n + i] = dEdy[k] * x[i];
        }
    }

    /* dEdb */
    for (int k = 0; k < m; k++)
    {
        dEdb[k] = dEdy[k];
    }

    /* dEdx */
    for (int k = 0; k < n; k++)
    {
        float product = 0;
        for (int i = 0; i < m; i++)
        {
            product += A[k + i * n] * dEdy[i];
        }
        dEdx[k] = product;
    }
}

// 誤差逆伝播(６層)を計算する
void backward6(const float *A1, const float *A2, const float *A3, const float *b1, const float *b2, const float *b3, const float *x, unsigned char t, float *y,
               float *dEdA1, float *dEdA2, float *dEdA3, float *dEdb1, float *dEdb2, float *dEdb3)
{
    // fc層，relu層への入力値を保存するための変数の準備
    float *fc1 = malloc(sizeof(float) * 784);
    float *fc2 = malloc(sizeof(float) * 50);
    float *fc3 = malloc(sizeof(float) * 100);
    float *relu1 = malloc(sizeof(float) * 50);
    float *relu2 = malloc(sizeof(float) * 100);

    float *dEdx_784 = malloc(sizeof(float) * 784);
    float *dEdx_50 = malloc(sizeof(float) * 50);
    float *dEdx_100 = malloc(sizeof(float) * 100);
    float *dEdx_10 = malloc(sizeof(float) * 10);

    // 順伝播　初めにfc1に入力値を保存しておく
    for (int i = 0; i < 784; i++)
    {
        fc1[i] = x[i];
    }
    fc(50, 784, x, A1, b1, relu1);
    relu(50, relu1, fc2);
    fc(100, 50, fc2, A2, b2, relu2);
    relu(100, relu2, fc3);
    fc(10, 100, fc3, A3, b3, y);
    softmax(10, y, y);

    // 逆伝播
    softmaxwithloss_bwd(10, y, t, dEdx_10);
    fc_bwd(10, 100, fc3, dEdx_10, A3, dEdA3, dEdb3, dEdx_100);
    relu_bwd(100, relu2, dEdx_100, dEdx_100);
    fc_bwd(100, 50, fc2, dEdx_100, A2, dEdA2, dEdb2, dEdx_50);
    relu_bwd(50, relu1, dEdx_50, dEdx_50);
    fc_bwd(50, 784, fc1, dEdx_50, A1, dEdA1, dEdb1, dEdx_784);

    // メモリの解放
    free(dEdx_784);
    free(dEdx_50);
    free(dEdx_100);
    free(dEdx_10);
    free(fc1);
    free(fc2);
    free(fc3);
    free(relu1);
    free(relu2);
}

// 推論（6層）した結果を返す
int inference6(const float *A1, const float *A2, const float *A3, const float *b1, const float *b2, const float *b3, const float *x, float *y)
{
    float *y1 = malloc(sizeof(float) * 50);
    float *y2 = malloc(sizeof(float) * 100);

    // 6層を通る
    fc(50, 784, x, A1, b1, y1);
    relu(50, y1, y1);
    fc(100, 50, y1, A2, b2, y2);
    relu(100, y2, y2);
    fc(10, 100, y2, A3, b3, y);
    softmax(10, y, y);

    // yの各要素のうち最大のもののインデックス番号をmax[1]に保存
    float max[2] = {y[0], 0};
    for (int i = 0; i < 10; i++)
    {
        if (y[i] > max[0])
        {
            max[0] = y[i];
            max[1] = i;
        }
    }

    // メモリの解放
    free(y1);
    free(y2);
    return max[1];
}

// 推論（6層）確率付き, accを引数にして，これに確率を格納する
int inference6_with_acc(const float *A1, const float *A2, const float *A3, const float *b1, const float *b2, const float *b3, const float *x, float *y, float *acc)
{
    float *y1 = malloc(sizeof(float) * 50);
    float *y2 = malloc(sizeof(float) * 100);

    // 6層を通る
    // print(28, 28, x);
    fc(50, 784, x, A1, b1, y1);
    relu(50, y1, y1);
    fc(100, 50, y1, A2, b2, y2);
    relu(100, y2, y2);
    fc(10, 100, y2, A3, b3, y);
    softmax(10, y, y);
    // print(10, 1, y);

    // yの各要素のうち最大のもののインデックス番号をmax[1]に保存
    float max[2] = {y[0], 0};
    for (int i = 0; i < 10; i++)
    {
        if (y[i] > max[0])
        {
            max[0] = y[i];
            max[1] = i;
        }
    }
    // 正解率を保存
    acc[0] = max[0];

    // メモリの解放
    free(y1);
    free(y2);
    return max[1];
}

// SGDで最適化
void SGD(int n, int size, float *W, float *dLdW, float eta)
{
    // W <- W - eta/size*dLdWで更新
    scale(n, -eta / size, dLdW);
    add(n, dLdW, W);
}

// Momentum の実装
void Momentum(int n, float *v, float *w, float *dEdw, float alpha, float eta)
{
    // v <- alpha*v - eta*dEdw で更新
    scale(n, alpha, v);
    scale(n, -eta, dEdw);
    add(n, dEdw, v);
    // w <- w + v で更新
    add(n, v, w);
}

// 要素数nの同じ型の行列xとyのそれぞれの要素を掛け合わせてyの値を更新
void multiple(int n, float *x, float *y)
{
    for (int i = 0; i < n; i++)
    {
        y[i] *= x[i];
    }
}

// AdaGrand の実装
void AdaGrad(int n, float *h, float *w, float *dEdw, float eta)
{
    // h を h + dEdw * dEdw (行列の要素ごとの掛け算) で更新
    float *temp1 = malloc(sizeof(float) * n);
    float *temp2 = malloc(sizeof(float) * n);
    init(n, 0.0, temp1);
    init(n, 0.0, temp2);
    // dEdwをtemp1に保存して，掛け合わせた値をhに加える
    for (int i = 0; i < n; i++)
    {
        temp1[i] = dEdw[i];
    }
    multiple(n, temp1, temp1);
    add(n, temp1, h);
    // hをtemp2に保存する
    for (int i = 0; i < n; i++)
    {
        temp2[i] = h[i];
    }

    // w を w - eta*(1/sqrt(h))*dEdw で更新
    for (int i = 0; i < n; i++)
    {
        temp2[i] = -eta / (sqrtf(temp2[i] + 1e-7));
    }
    multiple(n, dEdw, temp2);
    add(n, temp2, w);

    // // メモリの解放
    // free(temp1);
    // free(temp2);
}

// NNの学習の実装
// 1~3引数：各パラメータの保存先
int NN_6layers(int argc, char *argv[])
{
    // [-1,1]の乱数で初期化かガウス分布で初期化かを選択
    int initialization;
    printf("\nSelect the parameter initialization method\nIf you want to select rand_init: 1\nIf you want to select Gaussian_init: 2\n");
    scanf("%d", &initialization);
    while (initialization != 1 && initialization != 2)
    {
        printf("Invalid input => Input again.\n");
        printf("\nSelect the parameter initialization method\nIf you want to select rand_init: 1\nIf you want to select Gaussian_init: 2\n");
        scanf("%d", &initialization);
        printf("\n");
    }
    if (initialization == 1)
    {
        printf("rand_init is selected\n");
    }
    else if (initialization == 2)
    {
        printf("Gaussian_init is selected\n");
    }
    else
    {
        printf("Error: Invalid Input\nPlease restart");
        return 0;
    } 

    // 最適化の方法の選択。SGDまたはMomentumまたはAdaGrad。
    // Momentumは上手く動作しない
    int mode;
    printf("\nSelect optimization mode\nIf you want to select SGD: 1\nIf you want to select Momentum: 2\nIf you want to select AdaGrad: 3\nCaution! Momentum doesn't work well\n");
    scanf("%d", &mode);
    while (mode != 1 && mode != 2 && mode != 3)
    {
        printf("Invalid input => Input again.\n");
        printf("\nSelect optimization mode\nIf you want to select SGD: 1\nIf you want to select Momentum: 2\n");
        scanf("%d", &mode);
        printf("\n");
    }
    if (mode == 1)
    {
        printf("SGD is selected\n");
    }
    else if (mode == 2)
    {
        printf("Momentum is selected\n");
    }
    else if (mode == 3)
    {
        printf("AdaGrad is selected\n");
    }
    else
    {
        printf("Error: Invalid Input\nPlease restart\n");
        return 0;
    }

    // 変数の準備
    float *train_x = NULL;
    unsigned char *train_y = NULL;
    int train_count = -1;

    float *test_x = NULL;
    unsigned char *test_y = NULL;
    int test_count = -1;

    int width = -1;
    int height = -1;

    load_mnist(&train_x, &train_y, &train_count, &test_x, &test_y, &test_count, &width, &height);

    float *A1 = malloc(sizeof(float) * 784 * 50);
    float *A2 = malloc(sizeof(float) * 50 * 100);
    float *A3 = malloc(sizeof(float) * 100 * 10);
    float *b1 = malloc(sizeof(float) * 50);
    float *b2 = malloc(sizeof(float) * 100);
    float *b3 = malloc(sizeof(float) * 10);

    float *dEdA1 = malloc(sizeof(float) * 784 * 50);
    float *dEdA2 = malloc(sizeof(float) * 50 * 100);
    float *dEdA3 = malloc(sizeof(float) * 100 * 10);
    float *dEdA1_ave = malloc(sizeof(float) * 784 * 50);
    float *dEdA2_ave = malloc(sizeof(float) * 50 * 100);
    float *dEdA3_ave = malloc(sizeof(float) * 100 * 10);

    float *dEdb1 = malloc(sizeof(float) * 50);
    float *dEdb2 = malloc(sizeof(float) * 100);
    float *dEdb3 = malloc(sizeof(float) * 10);
    float *dEdb1_ave = malloc(sizeof(float) * 50);
    float *dEdb2_ave = malloc(sizeof(float) * 100);
    float *dEdb3_ave = malloc(sizeof(float) * 10);

    // Momentum をするときに必要なパラメータの準備
    float *vA1 = malloc(sizeof(float) * 784 * 50);
    float *vA2 = malloc(sizeof(float) * 50 * 100);
    float *vA3 = malloc(sizeof(float) * 100 * 10);

    float *vb1 = malloc(sizeof(float) * 50);
    float *vb2 = malloc(sizeof(float) * 100);
    float *vb3 = malloc(sizeof(float) * 10);

    // AdaGrad をするときに必要なパラメータ
    float *hA1 = malloc(sizeof(float) * 784 * 50);
    float *hA2 = malloc(sizeof(float) * 50 * 100);
    float *hA3 = malloc(sizeof(float) * 100 * 10);

    float *hb1 = malloc(sizeof(float) * 50);
    float *hb2 = malloc(sizeof(float) * 100);
    float *hb3 = malloc(sizeof(float) * 10);

    // vの値を0で初期化
    init(784 * 50, 0.0, vA1);
    init(50 * 100, 0.0, vA2);
    init(100 * 10, 0.0, vA3);
    init(50, 0.0, vb1);
    init(100, 0.0, vb2);
    init(10, 0.0, vb3);

    // hの値を0で初期化
    init(784 * 50, 0.0, hA1);
    init(50 * 100, 0.0, hA2);
    init(100 * 10, 0.0, hA3);
    init(50, 0.0, hb1);
    init(100, 0.0, hb2);
    init(10, 0.0, hb3);

    float *y = malloc(sizeof(float) * 10);
    int *index = malloc(sizeof(int) * train_count);

    // エポック回数，ミニバッチサイズ，学習回数，学習率，Momentum
    int epoch = 8;
    int n = 100;
    int times = train_count / n;
    float eta = 0.01;
    float alpha = 0.9;

    // パラメータの初期化
    if (initialization == 1)
    {
        // A,bを[-1:1]の乱数で初期化
        rand_init(784 * 50, A1);
        rand_init(50 * 100, A2);
        rand_init(100 * 10, A3);
        rand_init(50, b1);
        rand_init(100, b2);
        rand_init(10, b3);
    }
    else if (initialization == 2)
    {
        // A,bをガウス分布の乱数で初期化
        // 活性化関数がsoftmaxなのでHeの初期値で設定
        Gaussian_init(784 * 50, A1, 0, sqrt(2.0 / 784));
        Gaussian_init(50 * 100, A2, 0, sqrt(2.0 / 50));
        Gaussian_init(100 * 10, A3, 0, sqrt(2.0 / 100));
        Gaussian_init(50, b1, 0, sqrt(2.0 / 50));
        Gaussian_init(100, b2, 0, sqrt(2.0 / 100));
        Gaussian_init(10, b3, 0, sqrt(2.0 / 10));
    }
    else
    {
        printf("Error: Please restart\n");
        return 0;
    }

    // [0:N-1]の値を持つ index を作成
    for (int _ = 0; _ < train_count; _ += 1)
    {
        index[_] = _;
    }

    //エポックの開始
    for (int i = 0; i < epoch; i++)
    {
        printf("-----------------------------------------------------------------------\n");
        printf("Epoch %d/%d\n", i + 1, epoch);

        // index をランダムに並び替え
        shuffle(train_count, index);

        //　ミニバッチ学習
        for (int j = 0; j < times; j++)
        {
            //平均勾配を0で初期化
            init(784 * 50, 0.0, dEdA1_ave);
            init(50 * 100, 0.0, dEdA2_ave);
            init(100 * 10, 0.0, dEdA3_ave);
            init(50, 0.0, dEdb1_ave);
            init(100, 0.0, dEdb2_ave);
            init(10, 0.0, dEdb3_ave);

            // 配列indexから次のn個を取り出して，そのそれぞれについてdEdAとdEdbを計算し
            // dEdA_avとdEdb_aveに加える
            for (int k = 0; k < n; k++)
            {
                backward6(A1, A2, A3, b1, b2, b3, train_x + 784 * index[j * n + k], train_y[index[j * n + k]], y, dEdA1, dEdA2, dEdA3, dEdb1, dEdb2, dEdb3);
                add(784 * 50, dEdA1, dEdA1_ave);
                add(50 * 100, dEdA2, dEdA2_ave);
                add(100 * 10, dEdA3, dEdA3_ave);
                add(50, dEdb1, dEdb1_ave);
                add(100, dEdb2, dEdb2_ave);
                add(10, dEdb3, dEdb3_ave);
            }

            if (mode == 1)
            {
                // 最適化をSGDで実行
                SGD(784 * 50, n, A1, dEdA1_ave, eta);
                SGD(50 * 100, n, A2, dEdA2_ave, eta);
                SGD(100 * 10, n, A3, dEdA3_ave, eta);
                SGD(50, n, b1, dEdb1_ave, eta);
                SGD(100, n, b2, dEdb2_ave, eta);
                SGD(10, n, b3, dEdb3_ave, eta);
            }
            else if (mode == 2)
            {
                // 最適化をMomentumで実行
                Momentum(784 * 50, vA1, A1, dEdA1_ave, alpha, eta);
                Momentum(50 * 100, vA2, A2, dEdA2_ave, alpha, eta);
                Momentum(100 * 10, vA3, A3, dEdA3_ave, alpha, eta);
                Momentum(50, vb1, b1, dEdb1_ave, alpha, eta);
                Momentum(100, vb2, b2, dEdb2_ave, alpha, eta);
                Momentum(10, vb3, b3, dEdb3_ave, alpha, eta);
            }
            else if (mode == 3)
            {
                // 最適化をAdaGradで実行
                AdaGrad(784 * 50, hA1, A1, dEdA1_ave, eta);
                AdaGrad(50 * 100, hA2, A2, dEdA2_ave, eta);
                AdaGrad(50 * 100, hA3, A3, dEdA3_ave, eta);
                AdaGrad(50, hb1, b1, dEdb1_ave, eta);
                AdaGrad(100, hb2, b2, dEdb2_ave, eta);
                AdaGrad(10, hb3, b3, dEdb3_ave, eta);
            }
            else
            {
                printf("Error: Please restart");
                return 0;
            }

            // 進行率の表示
            int progress_i = (j * 100) / times;
            float progress_f = (j * 100.0) / times;
            if (ceil(progress_f) == floor(progress_f) && progress_i % 10 == 0)
            {
                printf("\n%2d%% complete", progress_i);
            }
            else
            {
                printf(".");
            }
        }

        // 訓練データに対する損失関数と正解率を表示
        int sum_train = 0;
        float loss_func_train = 0;
        float accuracy_train = 0.0;
        for (int _ = 0; _ < train_count; _++)
        {
            if (inference6(A1, A2, A3, b1, b2, b3, train_x + _ * 784, y) == train_y[_])
            {
                sum_train++;
            }
            loss_func_train += cross_entropy_error(y, train_y[_]);
        }
        accuracy_train = (sum_train * 100.0) / train_count;
        loss_func_train = loss_func_train / train_count;

        printf("\n\nTrain Accuracy : %f %% \n", accuracy_train);
        printf("Train Loss Func Average: %f\n", loss_func_train);

        // テストデータに対する損失関数と正解率を表示
        int sum_test = 0;
        float loss_func_test = 0.0;
        float accuracy_test = 0.0;
        for (int _ = 0; _ < test_count; _++)
        {
            if (inference6(A1, A2, A3, b1, b2, b3, test_x + _ * 784, y) == test_y[_])
            {
                sum_test++;
            }
            loss_func_test += cross_entropy_error(y, test_y[_]);
        }
        accuracy_test = (sum_test * 100) / test_count;
        loss_func_test = loss_func_test / test_count;

        printf("\nTest Accuracy: %f %%\n", accuracy_test);
        printf("Test Loss Func Average: %f\n", loss_func_test);
    }

    // パラメータの値を保存
    save(argv[1], 50, 784, A1, b1);
    save(argv[2], 100, 50, A2, b2);
    save(argv[3], 10, 100, A3, b3);
    return 0;
}

// 推論の実装
// 1~3引数:各パラメータの読み込み先
// 4引数  :推論する画像
int inference(int argc, char *argv[])
{
    // パラメータの準備
    float *A1 = malloc(sizeof(float) * 784 * 50);
    float *b1 = malloc(sizeof(float) * 50);
    float *A2 = malloc(sizeof(float) * 50 * 100);
    float *b2 = malloc(sizeof(float) * 100);
    float *A3 = malloc(sizeof(float) * 100 * 10);
    float *b3 = malloc(sizeof(float) * 10);

    float *y = malloc(sizeof(float) * 10);

    // 画像の読み込み
    float *x = load_mnist_bmp(argv[4]);

    // パラメータの読み込み
    load(argv[1], 50, 784, A1, b1);
    load(argv[2], 100, 50, A2, b2);
    load(argv[3], 10, 100, A3, b3);

    // 推論
    int inference_num = 0;
    float *accuracy = malloc(sizeof(float) * 1);
    inference_num = inference6_with_acc(A1, A2, A3, b1, b2, b3, x, y, accuracy);

    printf("The number is %d\nAccuracy rate is %f%%", inference_num, accuracy[0] * 100);
    return 0;
}

int main(int argc, char *argv[])
{
    srand(time(NULL));
    init_genrand(time(NULL));

    // 引数が3つの時は学習モード
    if (argc == 4)
    {
        NN_6layers(argc, argv);
    }
    // 引数が4つの時は推論モード
    else if (argc == 5)
    {
        inference(argc, argv);
    }
    // それ以外ならエラーを表示して終了
    else
    {
        printf("Error: Invalid Input\nIf you want to learn: Specify THREE arguments\nIf you want to do inference: Specify FOUR arguments");
        return 0;
    }
}