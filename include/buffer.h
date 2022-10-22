//
// Created by Bin Ma on 2022/9/30.
//

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

#define FastIO ios::sync_with_stdio(false); std::cin.tie(nullptr); std::cout.tie(nullptr);
#define PrefetchLine 5
#define indiceNum (4582772)

#define bufferSize 272334
//#define bufferSize 424333
//#define bufferSize 424011
//#define bufferSize 420741
//#define bufferSize 426738
//#define bufferSize 428154

//#define bufferSize (205608) //
using namespace std;

int handleCache(unordered_map<long,long> &cacheBuffer,long &cacheHit, long &cacheMiss,stringstream &cacheS,long groundItem,long timeStep);
void handlePrefetch(unordered_map<long,long> &prefetchBuffer,long &prefetchHit,long &prefetchMiss,stringstream &prefetchS,long groundItem,long timeStep,int triggerPrefetch);
int handleFIFO(unordered_map<long,long> &cacheBuffer,unordered_map<long,long> &prefetchBuffer,long &cacheHit, long &cacheMiss,long groundItem,long timeStep);
int handleLRU(unordered_map<long,long> &cacheBuffer,unordered_map<long,long> &prefetchBuffer,long &cacheHit, long &cacheMiss,long groundItem,long timeStep);
void handleGTandPrefetch(unordered_map<long,long> &prefetchBuffer,long &prefetchHit, long &prefetchMiss,stringstream &prefetchS,long groundItem,long timeStep);




