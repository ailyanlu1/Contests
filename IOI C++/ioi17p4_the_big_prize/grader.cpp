#include <bits/stdc++.h>
#include "prize.h"

using namespace std;

const static int MAX_QUERY = 10000;

static int N;
static int* data;
static int** query;
static int query_used = 0;

vector<int> ask(int i){
    assert(0 <= i && i < N);
    query_used++;
    if(query_used > MAX_QUERY){
        printf("Query limit exceeded\n");
        exit(0);
    }
    vector<int> *ret = new vector<int>;
    ret->push_back(query[i][0]);
    ret->push_back(query[i][1]);
    return *ret;
}

int main(){
    assert(scanf("%i", &N) == 1);

    data = (int*) malloc(sizeof(int) * N);
    query = (int**) malloc(sizeof(int*) * N);

    int max_data = 1;
    int answer = -1;
    for(int a = 0; a < N; a++){
        assert(scanf("%i", data + a) == 1);
        assert(data[a] >= 1);
        query[a] = (int*) malloc(sizeof(int) * 2);
        if(data[a] == 1){
            assert(answer == -1); //duplicate answer
            answer = a;
        }
        if(data[a] > max_data){
            max_data = data[a];
        }
    }
    assert(answer != -1); //missing answer
    for(int cost = max_data; cost >= 1; cost--){
        int num_better = 0;
        for(int a = 0; a < N; a++){
            if(data[a] < cost){
                num_better++;
            } else if (data[a] == cost){
                query[a][0] = num_better;
            }
        }
        num_better = 0;
        for(int a = N - 1; a >= 0; a--){
            if(data[a] < cost){
                num_better++;
            } else if (data[a] == cost){
                query[a][1] = num_better;
            }
        }
    }
    int user_answer = find_best(N);
    if(user_answer == answer){
        printf("AC\n");
    } else {
        printf("WA\n");
    }
    printf("Used %i queries\n", query_used);
}
