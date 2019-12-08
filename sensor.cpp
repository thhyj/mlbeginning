//
// Created by 27689 on 2019/12/8.
//
struct Sensor {
    int dimension;
    vector<double>w;
    Sensor(int dimension) {
        w.resize(dimension + 1);
    }
    Sensor(){}
};
struct Data{
    int dimension;
    vector<double>x;
    int expectingOutput;
    Data(int dimension) {
        x.resize(dimension + 1);
    }
    Data(){}
    void Input() {
        x[0] = -1;
        for(int i = 1; i <= dimension; ++i) {
        //    cin>>x[i];
            scanf("%lf",  &x[i]);
        }
    }
};