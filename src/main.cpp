#include<vector>
#include<queue>
#include<iostream>
#include"StringManip.h"
#include"UIHelper.h"
#include"Choices.h"
std::vector<std::pair<int, int>> setup(){
    int numOfProcesses;
    std::cout<<"How many processes are there?"<<std::endl;
    std::cin>>numOfProcesses;
    std::vector<std::pair<int, int>> processes;
    for(int i=0;i<numOfProcesses;i++){
        std::pair<int, int> process;
        std::cout<<"What is the arival time of process "<<(i+1)<<"?"<<std::endl;
        std::cin>>process.first;
        std::cout<<"What is the CPU Burst of process "<<(i+1)<<"?"<<std::endl;
        std::cin>>process.second;
        processes.push_back(process);   
    }
    return processes;
}
std::vector<std::pair<int,int>> LoadProcesses(){
    std::vector<std::pair<int, int>> Processes;
    Processes.push_back(std::pair<int, int>(10, 20));
    Processes.push_back(std::pair<int, int>(35, 5));
    Processes.push_back(std::pair<int, int>(45, 10));
    Processes.push_back(std::pair<int, int>(50, 50));
    return Processes;
}
void listProcesses(std::vector<std::pair<int, int>> Processes){
    headerNoCls("List of Processes", 45, '=');
    std::cout<<"Process number | Arrival time | CPU Burst"<<std::endl;
    dividingLine(45, '_');
    for(int i=0;i<Processes.size();i++){
        std::cout<<std::setw(5)<<i+1<<std::setw(10)<<"|"<<std::setw(5)<<Processes[i].first<<std::setw(10)<<"|"<<std::setw(10)<<Processes[i].second<<std::endl;
    } 
}
void listResults(std::vector<std::pair<int, int>> Processes, std::vector<std::pair<int,std::pair<int,int>>> ProcessesFinished){
    headerNoCls("Results", 70, '=');
    std::cout<<std::setw(10)<<"Process number"<<"|"<<std::setw(10)<<"Arrival time"<<std::setw(5)<<"|"<<std::setw(10)<<"CPU Burst"<<std::setw(5)<<"|"<<std::setw(10)<<"Start Time"<<std::setw(5)<<"|"<<std::setw(10)<<"Completion"<<std::endl;
    dividingLine(45, '_');
    for(int i=0;i<Processes.size();i++){
        std::cout<<std::setw(5)<<i+1<<std::setw(10)<<"|"<<std::setw(5)<<Processes[i].first<<std::setw(10)<<"|"<<std::setw(10)<<Processes[i].second;
        for(int j=0;j<ProcessesFinished.size();j++){
            if(ProcessesFinished[j].first==i+1){
                std::cout<<std::setw(10)<<"|"<<std::setw(5)<<ProcessesFinished[j].second.first<<std::setw(5)<<"|"<<std::setw(5)<<ProcessesFinished[j].second.second<<std::endl;
                break;
            }            
        }
    } 
}
std::vector<std::pair<int, std::pair<int, int>>> runtime(std::vector<std::pair<int, int>> Processes){
    std::queue<std::pair<int,std::pair<int,int>>> ProcessQ;
    std::vector<std::pair<int, std::pair<int,int>>> ProcessesLeftToQ;
    for(int i=0;i<Processes.size();i++){
        ProcessesLeftToQ.push_back(std::pair<int, std::pair<int,int>>(i+1, Processes[i]));
    }
    int timestep=0;
    int burstTime=0;
    int waitTime=0;
    std::vector<std::pair<int, std::pair<int, int>>> finishedProcesses;
    std::cout<<"Start of runtime "<<ProcessesLeftToQ.size()<<std::endl;
    while(ProcessesLeftToQ.size()>0||ProcessQ.size()>0){
        for(int i=0;i<ProcessesLeftToQ.size();i++){
            if(timestep==ProcessesLeftToQ[i].second.first)
            {
                ProcessQ.push(ProcessesLeftToQ[i]);
                ProcessesLeftToQ.erase(ProcessesLeftToQ.begin()+i);
                i--;
            }
        }
        if(ProcessQ.size()>0){
            if(burstTime==0&&timestep!=0){
                waitTime=timestep;
            }
            burstTime++;
            if(burstTime==ProcessQ.front().second.second){
                finishedProcesses.push_back(std::pair<int,std::pair<int,int>>(ProcessQ.front().first, std::pair<int,int>(waitTime, timestep+1)));
                burstTime=0;
                waitTime=0;
                ProcessQ.pop();
                if(ProcessQ.size()!=0)
                    waitTime=timestep;
            }
        }
        timestep++;
    }
    return finishedProcesses;
}
main(){
    headerNoCls("CS571 Homework 2", 100, '_');
    headerNoCls("Define processes", 60, '*');
    std::vector<std::pair<int,int>> Processes;
    if(choiceYN("Would you like to create a custom process list?"))
    {
        Processes=setup();
    }
    else{
        Processes=LoadProcesses();
    }
    listProcesses(Processes);
    listResults(Processes, runtime(Processes));
}