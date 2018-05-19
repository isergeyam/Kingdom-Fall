//
// Created by sg on 18.04.18.
//

#include "CJsonSerializerAdapter.hpp"
json CJsonSerializerAdapter::Deserialize(std::istream &stream_) {
  return json::parse(stream_);
}
