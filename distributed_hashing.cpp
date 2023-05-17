#include<bits/stdc++.h>
#include <vector>
using namespace std;
using namespace std::chrono;

int bucket_size, global_depth;

class Tabledata{
    public:
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
        Tabledata(string Student_ID, string Student_Name, string Dept, string Phn_Num, string HostelName, string Room_ID, string Father_Name, int Age, string Sex, string DOB){
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

class Distributed_Hash{
    public:

    void Dec_To_Bin(int n){
        int binvalues[32];
        int i=0, k=0;
        while(k<bucket_size){
            binvalues[i] = n%2;
            n/=2;
            i++;
            k++;
        }  
        int j=i-1;
        while(j >= 0){
            cout << binvalues[j];
            j--;
        }
        cout<< endl;
    }

    int StrToAscii(string str){
        int ascii_sum=0;
        for(int i=0;i<str.length();i++){
            ascii_sum += int(str[i]);
        };  
        return ascii_sum%10; 
    }
    
    unordered_map<int, vector<Tabledata*>> hash;

    void Retrieve_Data(string Student_ID){
        int key=StrToAscii(Student_ID);
        vector<Tabledata*> temp=hash[key];
        for(auto it:temp){
            if(it->Student_ID == Student_ID){
                cout<<it->Student_ID<<" "<<it->Student_Name<<" "<<it->Dept<<" "<<it->Phn_Num<<it->HostelName<<" "<<it->Room_ID<<" "<<it->Father_Name<<" "<<it->Age<<" "<<it->Sex<<" "<<it->DOB<<endl<<endl;
            }
        }
    }

    void Insertion(string Student_ID, string Student_Name, string Dept, string Phn_Num, string HostelName, string Room_ID, string Father_Name, int Age, string Sex, string DOB){
        int hash_key = StrToAscii(Student_ID);
        if(Searching(hash_key, Student_ID)== false){
            Tabledata* first = new Tabledata(Student_ID, Student_Name, Dept, Phn_Num, HostelName, Room_ID, Father_Name, Age, Sex, DOB);
            if(hash[hash_key].size()<bucket_size){
                hash[hash_key].push_back(first);
            }
        }
        else{
            cout<<"The data which you're trying to insert is already present!"<<endl;
        }
    }

    bool Searching(int key, string Student_ID){
        vector<Tabledata*> temp;
        temp=hash[key];
        for(auto it:temp){
            if(it->Student_ID==Student_ID){
                return true;
            }
        }
        return false;
    }

    
};

int main(){
    cout<<"Value of the global depth is: ";
    cin>>global_depth;
    cout<<"Size of the bucket is: ";
    cin>>bucket_size;
    Distributed_Hash x;

    x.Insertion("B19CS001", "Aman Vaasthav", "CSE", "9561234113", "B1", "101A", "Niranjan Vaasthav", 21, "M", "2001-07-03");
    x.Insertion("B18EE006", "Harsh Meena", "EE", "9162431167", "B1", "101A", "Rajesh Meena", 22, "M", "2000-09-25");
    x.Insertion("B20BB037", "Ankit Shah", "BB", "9441556123", "B1", "102A", "Karan Shah", 21, "M", "2002-01-01");
    x.Insertion("B20CS064", "Ayush Anand", "CSE", "9671443934", "B1", "102A", "Abhishek Anand", 20, "M", "2002-01-06");
    x.Insertion("B20CS032", "Narahari Divya", "CSE", "8500010804", "G1", "101B", "Narahari Mohan", 20, "F", "2000-08-13");
    x.Insertion("B18EE045", "Niharika Manhar", "EE", "7861234567", "G1", "101B", "Rajesh Meena", 22, "F", "2000-09-25");
    x.Insertion("B18CI078", "Mamidipalli Meghana", "CI", "9661284733", "G1", "102B", "Rajesh Meena", 22, "F", "2000-09-25");
    x.Insertion("B19BB016", "Satwik Mutyala", "BB", "9987661253", "B2", "101C", "Rajesh Meena", 21, "M", "2001-07-01");
    x.Insertion("B21CI011", "Shiva Aswani", "CI", "9441556789", "B2", "101C", "Pavan Aswani", 19, "M", "2003-12-18");
    x.Insertion("B21CS044", "Anurag Dia", "CSE", "9876114436", "B2", "102C", "Kushagra Dia", 19, "M", "2003-11-24");


    auto start = high_resolution_clock::now();
    x.Retrieve_Data("B19CS001");
    x.Retrieve_Data("B18EE006");
    x.Retrieve_Data("B20BB037");
    x.Retrieve_Data("B20CS064");
    x.Retrieve_Data("B20CS032");
    x.Retrieve_Data("B18EE045");
    x.Retrieve_Data("B18CI078");
    x.Retrieve_Data("B19BB016");
    x.Retrieve_Data("B21CI011");
    x.Retrieve_Data("B21CS044");
    auto end = high_resolution_clock::now();
    auto time_taken= duration_cast<microseconds>(end - start);
    cout<<"Time taken for the Retrival of data is: "<< time_taken.count()<<endl;
}