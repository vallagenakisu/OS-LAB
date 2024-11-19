#include<bits/stdc++.h>
using namespace std;

class Process 
{
    public:
    string Name ;
    int BT;
    int priority;
    int art;//arrival_time
    bool completion;
    bool arrived;
    bool isNull() const { return Name == ""; }
    Process()
    {
        completion = false;
        arrived = false;
        BT = 0 ;
        art = 0;
        priority = 0;
        Name ="";
    }
    Process(string name , int BT , int priority , int art , bool completion = false , bool arrived = false)
    {
        this->Name = name;
        this->BT = BT;
        this->priority = priority;
        this->art  = art; 
    }
    int get_bt()
    {
        return BT;
    }
    int get_priority()
    {
        return priority;
    }
    int get_art()
    {
        return art;
    }
    void set_bt(int a )
    {
        BT = a ;
    }
    void set_Name(string a )
    {
        Name = a ;
    }
    void set_priority(int a )
    {
        priority = a ;
    }
    void set_art(int a)
    {
        art = a ;
    }
};
// int priority_based_scheduling::np = 0;
class priority_based_scheduling
{
    public:
    int np; //number of process
    vector<Process> process;
    int cpu_utilization;
    int throughput;
    vector<int> Tournarand_time;
    vector<int> waiting_time;
    vector<int> response_time;
    vector<int> first_response;
    vector<int> completion_done;
    vector<int> finish_time;
    int time_elapsed;
    int completed_process;
    
    priority_based_scheduling()
    {
        time_elapsed = 0;
        cpu_utilization = 0;
        throughput = 0;
        completed_process = 0;
    }
    priority_based_scheduling(int np , vector<Process> process)
    {
        completed_process = 0;
        time_elapsed = 0;
        cpu_utilization = 0;
        throughput = 0;
        this->np = np;
        this->process = process;
        Tournarand_time.resize(np,0);
        waiting_time.resize(np,0);
        response_time.resize(np,0);
        first_response.resize(np,0);
        completion_done.resize(np,0);
        finish_time.resize(np,0);
    }

    void calculate_tournarand()
    {
        for(int i =0 ; i <np ; i++)
        {
            Tournarand_time[i] = finish_time[i] - process[i].art;
        }
    }
    void calculate_waiting_time()
    {
        for(int i =0 ; i <np ; i++)
        {
            waiting_time[i] = Tournarand_time[i] - process[i].BT;
        }
    }
    void calculate_response_time()
    {
        for(int i =0 ; i <np ; i++)
        {
            response_time[i] = first_response[i] - process[i].art;
        }
    }
    Process* get_process(int index)
    {
        return& process[index];
    }
    int get_index(Process P)
    {
        for(int i = 0 ; i<np ; i++)
        {
            if(P.Name == process[i].Name)
            return i;
        }
    }
    int total_process_time()
    {
        int x = 0;
        for(int i =0 ; i <np; i++)
        {
            x +=process[i].BT;
        }
        return x;
    }
    void reset() {
    Tournarand_time.clear();
    waiting_time.clear();
    response_time.clear();
    first_response.clear();
    completion_done.clear();
    finish_time.clear();
    time_elapsed = 0;
    completed_process = 0;
    cpu_utilization = 0;
    throughput = 0;

}
    
};
int main()
{
    int n;
    cin >> n ;
    vector<Process> P(n);
    for(int i = 0 ; i <n ; i++)
    {
        cin >> P[i].Name >> P[i].BT >> P[i].priority >> P[i].art;
    }
    priority_based_scheduling x(n,P);
    // int z = 0;
    // cout << P[z].art<<endl;
    int index = -1;
    vector<Process*> arrived_process;
    while(x.time_elapsed <=100)
    {
  
        for(int i = 0 ; i<x.np ; i++)
        {
            if((x.process[i].art <= x.time_elapsed) && (x.process[i].arrived == false))
            {
                x.process[i].arrived = true;
                arrived_process.push_back( x.get_process(i));
            }
        }
        int minn = 10000 ;
        
        for(auto a : arrived_process)
        {
            if(a->priority <= minn && a->completion == false )   
            {
                minn = a->priority;
                index = x.get_index(*a);
            }
        }
        Process* running = x.get_process(index);
        if(running->completion == 0)
        {
            x.first_response[index] = x.time_elapsed;
            x.completion_done[index]++;
            cout << "Running Process is "<<running->Name <<endl;
            if(x.completion_done[index] >= running->BT)
            {
                running->completion = true;
                x.completed_process++;
                x.finish_time[index] = x.time_elapsed+1;
            }
        }
        else 
        {
            cout << "CPU is Idle"<<endl;
        }
        if(x.completed_process == n)
        break;
        x.time_elapsed++;
    }
    x.time_elapsed++;
    x.calculate_tournarand();
    x.calculate_waiting_time();
    x.calculate_response_time();
    x.cpu_utilization = (x.total_process_time()*1.0/x.time_elapsed )*100 ;
    //cout << x.time_elapsed<<endl;
    cout <<"CPU Utilization" <<x.cpu_utilization<<"%"<<endl;
    int i = 0;
    cout << "Waiting Time"<<endl;
    for(auto a : x.waiting_time)
    {   i++;
        cout << "Process " << i <<" Waiting Time is " << a << endl;
    }
    cout <<"Tournarand Time"<<endl;
    for(auto a : x.Tournarand_time)
    {   i++;
        cout << "Process " << i <<" Tournarand Time is " << a << endl;
    }
    cout <<"Response Time"<<endl;
    for(auto a : x.response_time)
    {   i++;
        cout << "Process " << i <<" Response Time is " << a << endl;
    }


}
