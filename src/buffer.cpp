#include "../include/buffer.h"


int handleCache(unordered_map<long,long> &cacheBuffer,long &cacheHit, long &cacheMiss,stringstream &cacheS,long groundItem,long timeStep){
    string iter;
    int cacheItem;
    cacheS>>iter;
    cacheItem=stoi(iter);
    int triggerPrefetcher=0;
    if(cacheItem){
        if(cacheBuffer.count(groundItem)){
            cacheHit++;
        } else {
            cacheMiss++;
            triggerPrefetcher=1;
            if(cacheBuffer.size()>=bufferSize){
                long minTime=indiceNum;
                long minIndex=0;
                for(auto it:cacheBuffer){
                    if(it.second<minTime){
                        minTime=it.second;
                        minIndex=it.first;
                    }
                }
                cacheBuffer.erase(minIndex);
            }
            cacheBuffer[groundItem]=timeStep;
        }
    } else{
        if(cacheBuffer.count(groundItem)){
            cacheBuffer[groundItem] = timeStep;
            cacheHit++;
        }else{
            cacheMiss++;
            triggerPrefetcher=1;
            if(cacheBuffer.size()>=bufferSize){
                long minTime=indiceNum;
                long minIndex=0;
                for(auto it:cacheBuffer){
                    if(it.second<minTime){
                        minTime=it.second;
                        minIndex=it.first;
                    }
                }
                cacheBuffer.erase(minIndex);
            }
            cacheBuffer[groundItem]=timeStep-1*bufferSize;
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
                  if (prefetchBuffer.find(prefetchItem) != prefetchBuffer.end()) {
           // if(prefetchBuffer.count(prefetchItem)){
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


    if(cacheBuffer.count(groundItem)){  //cache hit
        cacheBuffer[groundItem] = timeStep;
        cacheHit++;
        return 0;
    } else {
	cacheMiss++;
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


void handleGTandPrefetch(unordered_map<long,long> &prefetchBuffer,long &prefetchHit, long &prefetchMiss,stringstream &prefetchS,long groundItem,long timeStep){


    if(prefetchBuffer.count(groundItem)){  //cache hit
        prefetchBuffer[groundItem] = timeStep;
        prefetchHit++;
    } else{
        prefetchMiss++;
        if(prefetchBuffer.size()<=bufferSize) { // if the cache is not full
            prefetchBuffer[groundItem] = timeStep;
        }else{
            long minTime=indiceNum;
            long minIndex=0;
            for(auto it:prefetchBuffer){
                if(it.second<minTime){
                    minTime=it.second;
                    minIndex=it.first;
                }
            }
            prefetchBuffer.erase(minIndex);
            prefetchBuffer[groundItem]=timeStep;
        }
    }
    handlePrefetch(prefetchBuffer,prefetchHit,prefetchMiss,prefetchS,groundItem,timeStep,0);

}
