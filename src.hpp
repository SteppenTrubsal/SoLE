//int x0[] = {1,1,1};
//int tau[] = {1,1,1};

int E1[3][3] = {
    {1,0,0},
    {0,1,0},
    {0,0,1}
};

int** initE(){
    int** E = new int*[3];
    for(int i = 0; i < 3; i++){
        E[i] = new int[3];       
    }
    for(int i = 0; i < 3; i++){
        for(int j = 0; j < 3; j++){
            if(i==j){
                E[i][j] = 1;
            }
            else{
                E[i][j] = 0;
            }
        }
    }
    return E;
}