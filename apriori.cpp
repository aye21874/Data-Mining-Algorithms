#include<bits/stdc++.h>
#include<stdio.h>
using namespace std;

void pruning(vector<vector<string>>&candidate,int k,map<string,int>& c){
    for(int i=0;i<candidate.size();i++){
        for( int j=0;j<candidate[i].size();j++){
            string can = "";
            for(int k = 0;k<candidate[i].size();k++){
                if(j==k){
                    continue;
                }            
                can += candidate[i][k] + ",";
            }
            can.pop_back();
            cout<<can<<"\n";
            auto it = c.find(can);
                if (it == c.end()){
                    candidate.erase(candidate.begin()+i);
                    i--;
                    break;
                }
               
        }
    }
    cout<<"after pruning"<<candidate.size()<<"\n";
}
void gen_cand(vector<vector<string>>&frequent, vector<vector<string>>&candidate, int k,map<string,int>&c){
     int flag = 0;
     int index = 0;
     candidate.clear();
    //cout<<frequent.size()<<"\n";
     for(int i=0;i<frequent.size()-1;i++){
        
         for(int j=i+1;j<frequent.size();j++){
            vector<string> temp;
             for(int l = 0;l<k-1; l++){
                 if(frequent[i][l] != frequent[j][l]){
                    flag = 1;
                    break;
                 }
             }
             if(flag == 1){
                 break;
             }
            
            for(int l=0;l<frequent[i].size();l++){
                temp.push_back(frequent[i][l]);
                cout<<frequent[i][l]<<"yo\n";
            }
                temp.push_back(frequent[j][k-1]);
                cout<<frequent[j][k-1]<<"why\n";
                //index++;
                candidate.push_back(temp);
         }
        if(flag == 1){
            flag = 0;
        }
         
     }
     /*
    for(int i=0;i<candidate.size();i++){
        cout<<candidate[i][0]<<" "<<candidate[i][1]<<"\n";
    }
    */
   cout<<candidate.size()<<"\n";
   if(k>=2){
       pruning(candidate,k,c);
   }
}

void count_min(vector<vector<string>>&candidate,set<string>&l,vector<vector<string>>&frequent,map<string,int>& c,int m,vector<set<string>>&tr){
    int count[candidate.size()] = {0};
    int flag = 0;
    frequent.clear();
    vector<string> can_str;
    for(int i =0 ;i<tr.size();i++){
        for(int j=0;j<candidate.size();j++){
            for(int k=0;k<candidate[j].size();k++){
                
                auto it = tr[i].find(candidate[j][k]);
                if (it != tr[i].end())
                {
                    // Do something with it, no more lookup needed.
                    continue;
                }
                else
                {
                    // Key was not present.
                    flag = 1;
                    break;
                }
                    
            


            }

            if(flag==1){
                flag = 0;
            }
            else{
                count[j]++;
            }
        }

    }
    
    string can="";
    for(int i = 0;i<candidate.size(); i++){
        for(int j = 0;j<candidate[i].size(); j++){
            if(j != 0){
                can+=",";
            }
            can+=candidate[i][j];
            
        }
        can_str.push_back(can);
        can = "";
    
    }
    
    for(int i = 0;i<candidate.size(); i++){
        if(count[i] >= m){
            c[can_str[i]] = count[i];
            frequent.push_back(candidate[i]);
            l.insert(can_str[i]);
        }
    }
    
}
int main(){
    int n,m;
    int k = 1;
    string str,word;
    cout<<"enter the number of transactions:";
    cin>>n;
    vector<set<string>> tr(n);
    for(int i=0;i<n;i++){
        cout<<"enter the items of "<<i+1<<" transactions:";
        cin>>str;
        stringstream str_1(str);
        while(getline(str_1,word,',')){
            tr[i].insert(word);
        }
    }
    //cout<<tr[3].items[0];
    cout<<"enter the min support:";
    cin>>m;
    map<string,int> c;
    set<string> l;
    vector<vector<string>> frequent;
    vector<vector<string>> candidate;
    //read database
    for(int i =0 ;i<tr.size();i++){
        for(auto it = tr[i].begin(); it != tr[i].end(); ++it){
            c[*it]++;
        }
    }
    //generate frequent set
    int z = 0;
    for(auto it = c.begin();it!=c.end();it++){
        vector<string> temp;
        if(it->second >= m){
            l.insert(it->first);
            temp.push_back(it->first);
            frequent.push_back(temp);
        }
        
    }
    /*
    for(int i=0;i<frequent.size();i++){
        cout<<frequent[i][0]<<"\n";
    }
    */
    //generate candiate set
    while(!frequent.empty()){
    gen_cand(frequent,candidate,k,c);
    count_min(candidate,l,frequent,c,m,tr);
    k++;
    }
    //print results
    for (auto it=l.begin(); it != l.end(); ++it) 
        cout << '{' << *it <<'}'; 

    
    return 0;
}