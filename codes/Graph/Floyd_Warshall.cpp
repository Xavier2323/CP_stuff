int d[100][100];
void FloydWarshall(int N){
    for(int k=0;k<N;++k)
        for(int i=0;i<N;++i)
            for(int j=0;j<N;++j)
                if(d[i][j] > d[i][k] + d[k][j])
                    d[i][j] = d[i][k] + d[k][j];
}