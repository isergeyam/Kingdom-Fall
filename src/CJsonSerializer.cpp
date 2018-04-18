//
// Created by sg on 18.04.18.
//

#include "CJsonSerializer.hpp"
json CJsonSerializer::Deserialize(std::istream &stream_) {
  return json::parse(stream_);
}
