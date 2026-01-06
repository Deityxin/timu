int max_(const vector<vector<int>> sta,vector<int> fin){
    for(int i = 0; i < 3;i++){
        for(int j = 0; j < 4; j++){
            fin.push_back(sta[i][j]);
        }
    }
    sort(fin.begin(),fin.end());
    int c = fin[fin.size() - 1];
    return c;
}