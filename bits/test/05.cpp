#include <iostream>
#include <vector>
using namespace std;
vector<int> time_data;// 用来存储每天的工作时间
vector<int> max_data;// 用来存储大于8小时的工作时间
vector<int> sequence_data;// 用来存储对应的天数
int maximum (){
    int max = max_data [0];
    int i = sequence_data [0];
    for ( int j = 1 ; j < max_data.size () ; j ++){
        if ( max_data [j] > max){
            max = max_data [j];
            i = sequence_data [j];
        }else{
                continue;
        }
    }
    return i + 1;
}   
int compare (const vector<int> &time_data){
    for(int i = 0 ; i < 7; i++){
        if (time_data [i] > 8){
            max_data.push_back (time_data [i]);
            sequence_data.push_back (i);
        }
    }
    if (max_data.size () == 0){
        return 0;
    }
    else {
        return maximum ();
    }
}
int output (const vector<vector<int>>& matrix){
    for (int i = 0 ; i < 7 ; i ++){
        
            time_data.push_back (matrix [i][0] + matrix [i][1]);
        }
    return compare (time_data);
}
int main (){
    vector <vector <int>> matrix (7, vector <int> (2)); 
    for (int i = 0 ; i < 7 ; i ++){
        for ( int j = 0; j < 2 ; j++){
            cin >> matrix [i][j];
        }
    }
    cout << output(matrix) << endl;
    return 0;
}