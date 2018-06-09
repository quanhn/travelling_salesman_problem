#include <iostream>
#include <fstream>
#include <stack>
using namespace std;

const int max_size = 10;

stack<int> tmp_path, start_city, short_way;
int matrix[max_size][max_size], size, tmp_cost, min_cost, best_min_cost;
int checked[max_size] = {0};

int front_stack(stack<int> a){
    stack<int> tmp;
    while(!a.empty()){
        int value = a.top();
        tmp.push(value);
        a.pop();
    }
    int front = tmp.top();
    while(!tmp.empty()){
        int value = tmp.top();
        a.push(value);
        tmp.pop();
    }
    return front;
}

void tsp(int city){
	if(size == 1){
		
	}
    if(tmp_path.size() == size){
    	
        if(matrix[city][front_stack(tmp_path)-1] != 0){
            tmp_cost += matrix[city][front_stack(tmp_path)-1];
            if(tmp_cost < min_cost){
                min_cost = tmp_cost;
                tmp_path.push(front_stack(tmp_path));
                while(!start_city.empty())
                    start_city.pop();
                start_city = tmp_path;
                tmp_path.pop();
            }
            tmp_cost -= matrix[city][front_stack(tmp_path)-1];
        }
    }
    else{
        if(tmp_path.empty()){
            checked[city] = 1;
            tmp_path.push(city+1);
            tmp_cost = 0;
			min_cost = 999;
        }
        for(int i = 0; i < size; i++){
            if(matrix[city][i] != 0 && checked[i] == 0){
                checked[i] = 1;
                tmp_path.push(i+1);
                tmp_cost += matrix[city][i];
                tsp(i);
                checked[i] = 0;
                tmp_path.pop();
                tmp_cost -= matrix[city][i];
            }
        }
        
    }
}

void num1_tsp(){
    best_min_cost = 999;
    if(size == 1){
    	return;
    }
    else{
    	for(int i = 0; i < size; i++){
    		tmp_cost = 0;
        	while(!tmp_path.empty())
        		tmp_path.pop();
        	tsp(i);
        	if(min_cost < best_min_cost){
        	    best_min_cost = min_cost;
        	    short_way = start_city;
        	}
        }
    }
}

void read_and_write(){
    ifstream fin("matrix.txt");
    fin>>size;
    for(int i = 0; i < size; i++)
        for(int j = 0; j < size; j++)
            fin>>matrix[i][j];
    cout<<"Ma tran do thi:"<<endl;
    for(int i = 0; i < size; i++){
        for(int j = 0; j < size; j++)
            cout<<matrix[i][j]<<" ";
        cout<<endl;
    }
}

void write_path(stack<int> a, int cost){
	cout<<"Duong di ngan nhat: "<<endl;
	if(cost != 999){
    	while(!a.empty()){
    	    if(a.size() == 1)
    	        cout<<a.top()<<endl;
    	    else 
    	        cout<<a.top()<<" ---> ";
    	    a.pop();
    	}
    	cout<<"Gia duong di: "<<cost<<endl;
    	
    }
    else{
    	cout<<"Khong co duong di ngan nhat!"<<endl;
    	cout<<"Gia duong di: 0"<<endl;
    }
}

int main(){
    read_and_write();
    num1_tsp();
    write_path(short_way, best_min_cost);
    
    /*tsp(0);
    while(!start_city.empty()){
        cout<<start_city.top()<<" ";
        start_city.pop();
    }
    cout<<min_cost<<endl;*/
    return 0;
}




