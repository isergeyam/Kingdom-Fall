//
// Created by sg on 18.04.18.
//

#pragma once
#include "json.hpp"
class CJsonSerializer {
 public:
  static json Deserialize(std::istream &stream_) ;
};


