#include <iostream>
#include <fstream>
#include <stack>
using namespace std;

const int max_size = 10;

stack<int> tmp_path, start_city, short_way;
int matrix[max_size][max_size], size = 0, tmp_cost, min_cost, best_min_cost;
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
    if(tmp_path.size() == 1)
        tmp_path.pop();
}

/*void num1_tsp(){
    best_min_cost = 999;
    if(size <= 1){
    	return;
    }
    else{
    	for(int i = 0; i < size; i++){
        	tsp(i);
        	if(min_cost < best_min_cost){
        	    best_min_cost = min_cost;
        	    short_way = start_city;
        	}
        }
    }
}*/

void read_and_write(){
    ifstream fin("matrix4.txt");
    fin>>size;
    for(int i = 0; i < size; i++)
        for(int j = 0; j < size; j++)
            fin>>matrix[i][j];
    cout<<endl;
    cout<<"So thanh pho: "<<size<<endl;
    cout<<endl;
    if(size > 1){
        cout<<"Ma tran do thi quang duong giua cac thanh pho:"<<endl<<endl;
        for(int i = 0; i < size; i++){
            for(int j = 0; j < size; j++)
                cout<<matrix[i][j]<<" ";
            cout<<endl;
        }
	    cout<<endl;
    }
}

void write_path(stack<int> a, int cost){
	if(cost != 999){
	    cout<<"Chu trinh duong di ngan nhat: "<<endl<<endl;
    	while(!a.empty()){
    	    if(a.size() == 1)
    	        cout<<a.top()<<endl;
    	    else 
    	        cout<<a.top()<<" ---> ";
    	    a.pop();
    	}
    	cout<<endl;
    	cout<<"Gia duong di: "<<cost<<endl<<endl;
    	
    }
    else{
    	cout<<"Khong co chu trinh duong di ngan nhat!"<<endl<<endl;
    	//cout<<"Gia duong di: 0"<<endl;
    }
}

int main(){
    read_and_write();
    //num1_tsp();
    if(size <= 1)
        cout<<"Khong co chu trinh duong di ngan nhat!"<<endl<<endl;
    else{
        int start;
        cout<<"Thanh pho ban muon xuat phat: ";
        cin>>start;
        cout<<endl;
        tsp(start-1);
        write_path(start_city, min_cost);
    }
    
    return 0;
}




