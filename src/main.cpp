#include <iostream>
#include <map>
#include <fstream>
#include <sstream>
#include <string>
#include <vector>
#include <unordered_map>
#include <ctime>
#include <stdlib.h>
#include <queue>
#include <string.h>
#include <algorithm>
#include "buffer.h"
using namespace std;


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
    cout<<"cacheHitRate: "<< (double)cacheHit/(double)(cacheHit+cacheMiss)<<endl;
    cout<<"prefetchHit: "<<prefetchHit<<endl;
    cout<<"prefetchMiss: "<<prefetchMiss<<endl;
    cout<<"prefetchHitRate: "<<(double)prefetchHit/(double)(prefetchHit+prefetchMiss)<<endl;

}


void run_method3(FILE *fin1, FILE *fin2, FILE *fin3){
    //string indicesLine,cacheLine,prefetchLine;
    char indicesLine[20],cacheLine[10],prefetchLine[64];
    long timeStep=0,cacheHit=0,cacheMiss=0,prefetchHit=0,prefetchMiss=0;
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
        // int triggerPrefetch=handleCache(cacheBuffer,cacheHit,cacheMiss,cacheS,groundItem,timeStep);
        // handle prefetch
        handleGTandPrefetch(prefetchBuffer,prefetchHit,prefetchMiss,prefetchS,groundItem,timeStep);
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
        int triggerPrefetch=handleFIFO(cacheBuffer,prefetchBuffer,cacheHit,cacheMiss,groundItem,timeStep);
        //handle prefetch
        if(triggerPrefetch){
            handlePrefetch(prefetchBuffer,prefetchHit,prefetchMiss,prefetchS,groundItem,timeStep,triggerPrefetch);
        }

        timeStep++;
    }
    cout<<"cacheHit: "<<cacheHit<<endl;

//    cout<<"cacheMiss: "<<cacheMiss<<endl;
    cout<<"cacheHitRate: "<<(double)cacheHit/(double)indiceNum<<endl;
    cout<<"prefetchHit: "<<prefetchHit<<endl;
    cout<<"prefetchMiss: "<<prefetchMiss<<endl;
    cout<<"prefetchHitRate: "<<(double)prefetchHit/(double)(prefetchHit+prefetchMiss)<<endl;


}

void run_method5(FILE *fin1, FILE *fin2, FILE *fin3){

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
        // int triggerPrefetch=handleLRU(cacheBuffer,prefetchBuffer,cacheHit,cacheMiss,groundItem,timeStep);

        int triggerPrefetch=handleCache(cacheBuffer,cacheHit,cacheMiss,cacheS,groundItem,timeStep);
        //handle prefetch
        if(triggerPrefetch){
            handlePrefetch(prefetchBuffer,prefetchHit,prefetchMiss,prefetchS,groundItem,timeStep,triggerPrefetch);
        }

        timeStep++;
    }
    cout<<"cacheHit: "<<cacheHit<<endl;
}


int main(int argc,char* argv[]){
//    FastIO

    if(argc>2)
    {
        cout<<"Number Of Arguments Passed: %d"<<argc<<endl;
        //printf("\n----Following Are The Command Line Arguments Passed----");
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
        case 3:
            cout<<"method 3"<<endl;
            run_method3(fp1,fp2,fp3);
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
