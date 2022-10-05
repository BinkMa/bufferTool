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
//#define indiceNum (46792035)
//#define indiceNum (2*1000*1000)
//#define indiceNum (13)
#define indiceNum (1000*1000)
//#define bufferSize 637876 //  for the whole
//#define bufferSize 4423 //  for the first 100000 lines
//#define bufferSize (43305) //  for the first 1000000 lines
// #define CbufferSize (86610) //  for the first 1000000 lines
// #define PbufferSize (43305) //  for the first 1000000 lines
#define bufferSize (90947)//this is for test data 1000 000 lines
//#define bufferSize (70985)  //
//#define bufferSize (205608) //
//#define bufferSize 10
using namespace std;

int handleCache(unordered_map<long,long> &cacheBuffer,long &cacheHit, long &cacheMiss,stringstream &cacheS,long groundItem,long timeStep);
void handlePrefetch(unordered_map<long,long> &prefetchBuffer,long &prefetchHit,long &prefetchMiss,stringstream &prefetchS,long groundItem,long timeStep,int triggerPrefetch);
int handleFIFO(unordered_map<long,long> &cacheBuffer,unordered_map<long,long> &prefetchBuffer,long &cacheHit, long &cacheMiss,long groundItem,long timeStep);
int handleLRU(unordered_map<long,long> &cacheBuffer,unordered_map<long,long> &prefetchBuffer,long &cacheHit, long &cacheMiss,long groundItem,long timeStep);
void handleGTandPrefetch(unordered_map<long,long> &prefetchBuffer,long &prefetchHit, long &prefetchMiss,stringstream &prefetchS,long groundItem,long timeStep);




