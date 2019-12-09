//
// Created by 27689 on 2019/12/8.
//
struct Data;
struct Sensor;
std::default_random_engine generator(time(NULL));
std::uniform_real_distribution<double> distribution(0, 100);
double result = distribution(generator);
const double alpha = 0.1;
extern void gInt(int &v);
struct Data {
    int dimension;
    vector<double> x;
    int expectOutput;
    void Init() {
        x.resize(dimension + 1);
    }
    Data(int dimension) :dimension(dimension){

    }

    Data() {}

    void Input() {
        scanf("%d", &dimension);
        x[0] = -1;
        for (int i = 1; i <= dimension; ++i) {
            //    cin>>x[i];
            scanf("%lf", &x[i]);
        }
    }
};
struct Sensor {
    int dimension;
    vector<double>w;
    void Init(int di) {
        for(int i = 0; i <= di; ++i) {
            w[i] = distribution(generator); //随机化初始权值
        }
    }
    Sensor(int di) {
        w.resize(di + 1);
        Init(di);
    }
    Sensor(){}
    int Calc(const Data &temp) {
        double Sum = 0;
        for(int i = 0;i <= dimension; ++i) {
            Sum += temp.x[i] * w[i];
        }
        return Sum > 0;
    }
};

struct TrainData : Data {
    int realOutput;
    TrainData(int dimension) : Data(dimension){

    }
    TrainData(){}
    void TrainInput() {
      //  scanf("%d", &dimension);
        x[0] = -1;
        for (int i = 1; i <= dimension; ++i) {
            //    cin>>x[i];
            scanf("%lf", &x[i]);
        }
        scanf("%d", realOutput);
    }
};
int Check() {

}
void Train() {
    int n, Dimension;
    gInt(n), gInt(Dimension);
    vector<TrainData> tDataSet;
    tDataSet.resize(n + 1);
    for(int i = 1; i <= n; ++i) {
        tDataSet[i] = TrainData(Dimension);
        tDataSet[i].Init();
        tDataSet[i].TrainInput();
    }
   // dataSet.Input();
    while(Check()) {

    }
}