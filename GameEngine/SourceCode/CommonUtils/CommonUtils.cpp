//
// Created by 谭地杰 on 2021/10/28.
//

#include "CommonUtils.h"

//----------------------------------   static element   ----------------------------------
std::unordered_map<int,CommonUtils::Thread*> CommonUtils::thread_map;
int CommonUtils::base_thread_id = 0;

//----------------------------------   static element   ----------------------------------