#include <bits/stdc++.h>
using namespace std;
using namespace std::chrono;
int global_buck_size = 4;

int Str_Ascii(string str){
    int ascii_sum=0;
    for(int i=0;i<str.length();i++){
        ascii_sum = ascii_sum + int(str[i]);
    };
    return ascii_sum;
}

int hash_func(string id){
    return Str_Ascii(id) % int(pow(2, global_buck_size));
}


class TableData{
public:
    int key;
    string Student_ID;
    string Student_Name;
    string Dept;
    string Phn_Num;
    string HostelName;
    string Room_ID;
    string Father_Name;
    int Age;
    string Sex;
    string DOB;
    TableData(string Student_ID, string Student_Name, string Dept, string Phn_Num, string HostelName, string Room_ID, string Father_Name, int Age, string Sex, string DOB){
        this->key = hash_func(Student_ID);
        this->Student_ID = Student_ID;
        this->Student_Name = Student_Name;
        this->Dept = Dept;
        this->Phn_Num = Phn_Num;
        this->HostelName = HostelName;
        this->Room_ID = Room_ID;
        this->Father_Name = Father_Name;
        this->Age = Age;
        this->Sex = Sex;
        this->DOB = DOB;
    }
};

class Bukt{
public:
    vector<TableData*> data;
    int max_size, curr_size;
    Bukt(int max_size){
        max_size = max_size;
        curr_size = 0;
    }
    void Inserting(TableData* dat){
        data.push_back(dat);
        curr_size++;
    }
    void Display(){
        int i=0,n= data.size();
        while(i<n){
            cout<<data[i]->key<<data[i]->Student_ID<<data[i]->Student_Name<<data[i]->Dept<<data[i]->Phn_Num<<data[i]->HostelName<<data[i]->Room_ID<<data[i]->Father_Name<<data[i]->Age<<data[i]->Sex<<data[i]->DOB<<endl;
            i++;
        }
        cout << endl;
    }
};


class Linear_Hashing{
public:
    int buck_size, curr_round, curr_split;
    vector<Bukt*> bucket;

    Linear_Hashing(int bucket_size){
        buck_size = bucket_size;
        curr_round = 0,curr_split=0;
        int i=0,n=bucket_size;
        while(i<n){
            Bukt* buck=new Bukt(buck_size);
            bucket.push_back(buck);
            i++;
        }
    }
    
    void Inserting(TableData* dat){
        int buck_index = hash_function(curr_round, dat->key);
        if (buck_index < curr_split){
            buck_index = hash_function(curr_round + 1, dat->key);
        }
        if (bucket[buck_index]->curr_size == bucket[buck_index]->max_size){
            bucket[buck_index]->Inserting(dat);
            Splitting(curr_split);
            curr_split++;
            if (curr_split == buck_size){
                curr_split = 0;
                curr_round++;
            }
        }
        else{
            bucket[buck_index]->Inserting(dat);
        }
        return;
    }
    void Splitting(int buckIndex){
        Bukt* newBucket=new Bukt(buck_size);
        int i=0,n=bucket[buckIndex]->data.size();
        while(i<n){
            int newBuckIndex = hash_function(curr_round + 1, bucket[buckIndex]->data[i]->key);
            if (newBuckIndex == buckIndex){
                continue;
            }
            else if (newBuckIndex < curr_split){
                newBuckIndex = hash_function(curr_round + 2, bucket[buckIndex]->data[i]->key);
            }
            newBucket->Inserting(bucket[buckIndex]->data[i]);
            bucket[buckIndex]->data.erase(bucket[buckIndex]->data.begin() + i);
            bucket[buckIndex]->curr_size--;
            i--;
            i++;
        }
        bucket.push_back(newBucket);
        return;
    }

    void Display(){
        int i=0,n=bucket.size();
        while(i<n){
            cout<<"Bucket "<<i<<": \n";
            bucket[i]->Display();
            i++;
        }
        return;
    }

    int hash_function(int rounding, int hash_key){
        int final_hash_key = hash_key % ((int)pow(2, rounding) * buck_size);
        return final_hash_key;
    }
};


int main(){
    int bucket_size;
    cout<<"Size of the bucket is: ";
    cin>> bucket_size;
    Linear_Hashing x(bucket_size);
    TableData* data_1=new TableData("B19CS001", "Aman Vaasthav", "CSE", "9561234113", "B1", "101A", "Niranjan Vaasthav", 21, "M", "2001-07-03");
    TableData* data_2=new TableData("B18EE006", "Harsh Meena", "EE", "9162431167", "B1", "101A", "Rajesh Meena", 22, "M", "2000-09-25");
    TableData* data_3=new TableData("B20BB037", "Ankit Shah", "BB", "9441556123", "B1", "102A", "Karan Shah", 21, "M", "2002-01-01");
    TableData* data_4=new TableData("B20CS064", "Ayush Anand", "CSE", "9671443934", "B1", "102A", "Abhishek Anand", 20, "M", "2002-01-06");
    TableData* data_5=new TableData("B20CS032", "Narahari Divya", "CSE", "8500010804", "G1", "101B", "Narahari Mohan", 20, "F", "2000-08-13");
    TableData* data_6=new TableData("B18EE045", "Niharika Manhar", "EE", "7861234567", "G1", "101B", "Rajesh Meena", 22, "F", "2000-09-25");
    TableData* data_7=new TableData("B18CI078", "Mamidipalli Meghana", "CI", "9661284733", "G1", "102B", "Rajesh Meena", 22, "F", "2000-09-25");
    TableData* data_8=new TableData("B19BB016", "Satwik Mutyala", "BB", "9987661253", "B2", "101C", "Rajesh Meena", 21, "M", "2001-07-01");
    TableData* data_9=new TableData("B21CI011", "Shiva Aswani", "CI", "9441556789", "B2", "101C", "Pavan Aswani", 19, "M", "2003-12-18");
    TableData* data_10=new TableData("B21CS044", "Anurag Dia", "CSE", "9876114436", "B2", "102C", "Kushagra Dia", 19, "M", "2003-11-24");

    auto start_time = high_resolution_clock::now();
    x.Inserting(data_1);
    x.Inserting(data_2);
    x.Inserting(data_3);
    x.Inserting(data_4);
    x.Inserting(data_5);
    x.Inserting(data_6);
    x.Inserting(data_7);
    x.Inserting(data_8);
    x.Inserting(data_9);
    x.Inserting(data_10);

    auto stop_time= high_resolution_clock::now();
    auto time_taken = duration_cast<microseconds>(stop_time - start_time);
    cout<<"Time taken for insertion of data is: "<<time_taken.count()<<endl;
    return 0;
}
