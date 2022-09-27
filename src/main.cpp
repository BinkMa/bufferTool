#include <iostream>
#include <map>
#include <fstream>
#include <sstream>
#include <string>
#include <vector>
#include <unordered_map>
#include <ctime>
#include <stdlib.h>
#include <string.h>
using namespace std;

#define FastIO ios::sync_with_stdio(false); std::cin.tie(nullptr); std::cout.tie(nullptr);
#define PrefetchLine 5
//#define indiceNum (46792035)
#define indiceNum (10*1000*1000)
//#define bufferSize 637876 //  for the whole
//#define bufferSize 4423 //  for the first 100000 lines
//#define bufferSize (43305) //  for the first 1000000 lines
#define bufferSize (205608) //  for the first 10000000 lines

int handleCache(unordered_map<long,long> &cacheBuffer,long &cacheHit, long &cacheMiss,stringstream &cacheS,long groundItem,long timeStep){
    string iter;
    int cacheItem;
    cacheS>>iter;
    cacheItem=stoi(iter);
    int triggerPrefetcher=0;
    if(cacheItem){
        if(cacheBuffer.count(groundItem)){
            cacheHit++;
            cacheBuffer[groundItem] = timeStep;
        } else {
            cacheMiss++;
            triggerPrefetcher=1;
            if(cacheBuffer.size()<=bufferSize) {
                cacheBuffer[groundItem] = timeStep;
            }
            else{
                long minTime=indiceNum;
                long minIndex=0;
                for(auto it:cacheBuffer){
                    if(it.second<minTime){
                        minTime=it.second;
                        minIndex=it.first;
                    }
                }
                cacheBuffer.erase(minIndex);
                cacheBuffer[groundItem]=timeStep;
            }
        }
    } else{
        if(cacheBuffer.count(groundItem)){
            cacheHit++;
        }else{
            cacheMiss++;
            triggerPrefetcher=1;
        }
    }
    return triggerPrefetcher;
}

void handlePrefetch(unordered_map<long,long> &prefetchBuffer,long &prefetchHit, long &prefetchMiss,stringstream &prefetchS,long groundItem,long timeStep,int triggerPrefetch){
    string iter;
    long prefetchItem;
    prefetchS>>iter;
    if(triggerPrefetch){
            if(prefetchBuffer.count(groundItem)){
                prefetchHit++;
            }else{
                prefetchMiss++;
            }
        }
    for(int i=0;i<PrefetchLine;i++){
        prefetchS>>iter;
        prefetchItem=stol(iter);
        if(prefetchItem!=0){
            //        if (prefetchBuffer.find(prefetchItem) != prefetchBuffer.end()) {
            if(prefetchBuffer.count(prefetchItem)){
                prefetchBuffer[prefetchItem] = timeStep;
            } else {
                if(prefetchBuffer.size()<=bufferSize) {
                    prefetchBuffer[prefetchItem] = timeStep;
                }
                else{
                    long minTime=indiceNum;
                    long minIndex=0;
                    for(auto it:prefetchBuffer){
                        if(it.second<minTime){
                            minTime=it.second;
                            minIndex=it.first;
                        }
                    }
                    prefetchBuffer.erase(minIndex);
                    prefetchBuffer[prefetchItem]=timeStep;
                }
            }
        }
        prefetchS>>iter;
    }
}


int handleLRU(unordered_map<long,long> &cacheBuffer,unordered_map<long,long> &prefetchBuffer,long &cacheHit, long &cacheMiss,long groundItem,long timeStep){

//    if(prefetchBuffer.count(groundItem)){
//        return 0;
//    }
    if(cacheBuffer.count(groundItem)){  //cache hit
        cacheBuffer[groundItem] = timeStep;
        cacheHit++;
        return 0;
    } else {

        if(cacheBuffer.size()<=bufferSize) { // if the cache is not full
            cacheBuffer[groundItem] = timeStep;
        }
        else{   // if the cache is full
            long minTime=indiceNum;
            long minIndex=0;
            for(auto it:cacheBuffer){
                if(it.second<minTime){
                    minTime=it.second;
                    minIndex=it.first;
                }
            }
            cacheBuffer.erase(minIndex);
            cacheBuffer[groundItem]=timeStep;
        }
        return 1;
    }

}

void run_method2(FILE *fin1, FILE *fin2, FILE *fin3){

    //string indicesLine,cacheLine,prefetchLine;
    char indicesLine[20],cacheLine[10],prefetchLine[64];
    long timeStep=0,cacheHit=0,cacheMiss=0,prefetchHit=0,prefetchMiss=0;

    unordered_map<long,long> cacheBuffer;
    unordered_map<long,long> prefetchBuffer;
    for(int i =0;i<indiceNum;i++){
        fgets(indicesLine,sizeof(indicesLine),fin1);
        fgets(cacheLine,sizeof(cacheLine),fin2);
        fgets(prefetchLine,sizeof(prefetchLine),fin3);
        //cout<<"timeStep: "<<timeStep<<endl;
        stringstream indicesS(indicesLine);
        stringstream cacheS(cacheLine);
        stringstream prefetchS(prefetchLine);
        string iter;
        vector<long> prefetchVec;
        //get ground truth number
        indicesS>>iter;
        char * pEnd;
        long groundItem = stol(iter);
        int triggerPrefetch=handleCache(cacheBuffer,cacheHit,cacheMiss,cacheS,groundItem,timeStep);
        //handle prefetch
        handlePrefetch(prefetchBuffer,prefetchHit,prefetchMiss,prefetchS,groundItem,timeStep,triggerPrefetch);
        timeStep++;
    }
    cout<<"cacheHit: "<<cacheHit<<endl;
    cout<<"cacheMiss: "<<cacheMiss<<endl;
    cout<<"cacheHitRate: "<<(double)cacheHit/(double)(cacheHit+cacheMiss)<<endl;
    cout<<"prefetchHit: "<<prefetchHit<<endl;
    cout<<"prefetchMiss: "<<prefetchMiss<<endl;
    cout<<"prefetchHitRate: "<<(double)prefetchHit/(double)(prefetchHit+prefetchMiss)<<endl;

}

void run_method4(FILE *fin1, FILE *fin2, FILE *fin3){

    char indicesLine[20],cacheLine[10],prefetchLine[64];
    long timeStep=0,cacheHit=0,cacheMiss=0,prefetchHit=0,prefetchMiss=0;
    unordered_map<long,long> cacheBuffer;
    unordered_map<long,long> prefetchBuffer;
    for(int i =0;i<indiceNum;i++){
        fgets(indicesLine,sizeof(indicesLine),fin1);
        fgets(cacheLine,sizeof(cacheLine),fin2);
        fgets(prefetchLine,sizeof(prefetchLine),fin3);
        //cout<<"timeStep: "<<timeStep<<endl;
        stringstream indicesS(indicesLine);
        stringstream cacheS(cacheLine);
        stringstream prefetchS(prefetchLine);
        string iter;
        //get ground truth number
        indicesS>>iter;
        long groundItem = stol(iter);
        int triggerPrefetch=handleLRU(cacheBuffer,prefetchBuffer,cacheHit,cacheMiss,groundItem,timeStep);
        //handle prefetch
//        if(triggerPrefetch){
        handlePrefetch(prefetchBuffer,prefetchHit,prefetchMiss,prefetchS,groundItem,timeStep,triggerPrefetch);
//        }

        timeStep++;
    }
    cout<<"cacheHit: "<<cacheHit<<endl;
//    cout<<"cacheMiss: "<<cacheMiss<<endl;
    cout<<"cacheHitRate: "<<(double)cacheHit/(double)indiceNum<<endl;
    cout<<"prefetchHit: "<<prefetchHit<<endl;
    cout<<"prefetchMiss: "<<prefetchMiss<<endl;
    cout<<"prefetchHitRate: "<<(double)prefetchHit/(double)(prefetchHit+prefetchMiss)<<endl;


}

int main(int argc,char* argv[]){
//    FastIO

    if(argc>2)
    {
        cout<<"Number Of Arguments Passed: %d"<<argc<<endl;
        printf("\n----Following Are The Command Line Arguments Passed----");
        perror(0);
    }
    int method=atoi(argv[1]);

    fstream fin1,fin2,fin3;
    FILE *fp1,*fp2,*fp3;

    char const* indiceFile="../datasets/indices.txt";
    char const* cacheFile="../datasets/fbgemm_t856_bs65536_15_cache_opt_trace.txt";
    char const* prefetchFile="../datasets/fbgemm_t856_bs65536_15_prefetch_trace.txt";

    fp1 = fopen(indiceFile, "r");
    fp2 = fopen(cacheFile, "r");
    fp3 = fopen(prefetchFile, "r");

    //fin1.open(indiceFile,ios::in);
    //fin2.open(cacheFile,ios::in);
    //fin3.open(prefetchFile,ios::in);

    struct timespec start, stop;
    double time;


    if( clock_gettime(CLOCK_REALTIME, &start) == -1) { perror("clock gettime");}

    switch (method) {
        case 2:
            cout<<"method 2"<<endl;
            run_method2(fp1,fp2,fp3);
            break;
        case 4:
            cout<<"method 4"<<endl;
            run_method4(fp1,fp2,fp3);
            break;
        default:
            break;

    }

    if( clock_gettime( CLOCK_REALTIME, &stop) == -1 ) { perror("clock gettime");}
    time = (stop.tv_sec - start.tv_sec)+ (double)(stop.tv_nsec - start.tv_nsec)/1e9;

    std::cout << "time:"<<time <<"s"<< std::endl;
    return 0;


}
